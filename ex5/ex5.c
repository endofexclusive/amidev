/*
 * Scroll checker board. Scramble view position with right mouse button. A PI
 * control loop tries to stabilize the view again.
 */

#include <stddef.h>
#include <custom.h>
#include <custombits.h>
#include <gfx.h>
#include <copper.h>

/*
 * Display window is 320x256
 * Screen is (2*16 + 320) x (256 + 2*16)
 * World size is (2<<16) x (2<<16)
 * Center of Display window is coordinate (160,128)
 */
/* Number of words in one square. */
#define SQWORDS 4
#define WIDTH (2*SQWORDS*16 + 320 + 0L)
#define HEIGHT (256 + 2*SQWORDS*16 + 0L)
#define SCREENBYTES (WIDTH*HEIGHT/8)

#include "clist.c"
/* NOTE: Word aligned */
uint16_t screen[SCREENBYTES/2];
extern struct copper_instruction clist[];

/* Center over hpos. */
#if 0
static inline void translate(uint16_t x, uint16_t y)
#endif
void translate(uint16_t x, uint16_t y)
{
        /*
         * The resolution is really 2*SQWORDS*16 x 2*SQWORDS*16 pixels, so mask
         * away unused (upper) coordinate bits.
         */
        x &= (2 * SQWORDS - 1) << 4 | 0xf;
        y &= (2 * SQWORDS - 1) << 4 | 0xf;

        /*
         * Delay display of data, 0 to 15 LORES pixels. For each pixel of
         * delay, the on-screen data shifts one pixel to the right each display
         * field. Only the horizontal bit index is used for delaying, so mask
         * away all higher bits.
         */
        uint16_t delay = x & 0xf;

        custom->bplcon1 = delay;

        /*
         * Calculate screen data word offset to use for first word fetch of the
         * screen. Then install the bitplane pointer.
         *
         * For the horizontal position, the horizontal bit index is not used,
         * so it is removed by shifted right. The horizontal tiles happen to be
         * in the "wrong order" in memory so the position is "negated".
         *
         * The vertical translation is then added. It adds y lines.
         */
        uint16_t word_offset;
        uint32_t offset_addr;

        word_offset = (2 * SQWORDS - 1) - (x >> 4);
        word_offset += y*WIDTH/16;

        offset_addr = (uint32_t) &screen[word_offset];

        clist[COP_BPL + 0].w1 = offset_addr >> 16;
        clist[COP_BPL + 1].w1 = offset_addr & 0xffff;
}

/*
 * pv: Process Variable (current)
 * sp: Set Point (desired)
 * return: control value
 */
static inline int16_t regulate(uint16_t pv, uint16_t sp, int32_t *ack)
{
        const int32_t Kp = 0*0x100 + 0x17;
        const int32_t Ki = 0*0x100 + 0x07;
        int32_t e;
        int32_t ret;
        int32_t a;

        e = sp - pv;
        a = (*ack) + Ki*e;
        ret = ((Kp * e) + a) >> 8;
        *ack = a;

        return (int16_t) ret;
}

static inline int isrmbdown(void)
{
        volatile uint16_t *const b = (void *) 0xdff016;

        return (!(*b & (1 << 10)));
}

int main(void)
{
        volatile uint8_t *vp0 = (uint8_t *) &clist[VP0].w0;
        volatile uint8_t *vp1 = (uint8_t *) &clist[VP1].w0;

        /* Write a pattern to screen buffer. */
        for (uint16_t y = 0; y < HEIGHT; y++) {
                int yon = !!(y & SQWORDS<<4);

                for (uint16_t x = 0; x <= WIDTH/16; x++) {
                        uint16_t val;
                        int xon = !!(x & SQWORDS);

                        if (yon ^ xon) {
                                val = 0xffff;
                        } else {
                                val = 0x0000;
                        }
                        screen[y*(WIDTH/16)+x] = val;
                }
        }

        /*
         * Wait for end of frame before manipulating DMACON.
         */
        waitvpos(VPOS_MAX);
        custom->dmacon = DMAF_MASTER | DMAF_ALL;
        /* Install the copper list */
        copper_install(1, clist);
        copper_start();
        custom->dmacon = DMAF_SETCLR | DMAF_MASTER | DMAF_RASTER;

        /* Process Variable: current coordinate = The Display Window. */
        uint16_t px = 0x2000;
        uint16_t py = 0x2000;
        /* Set Point: desired position */
        uint16_t sx = 0x2030;
        uint16_t sy = 0x2345;
        /* Control variable (velocity) */
        int8_t cx = 0x0;
        int8_t cy = 0x0;
        /* Ackumulated error. */
        int32_t xack = 0;
        int32_t yack = 0;

        uint8_t v = 0xac;
        int8_t vadd = 1;

        while (1) {
                /* Scramble view on right mouse button. */
                if (isrmbdown()) {
                        sx += custom->vhposr & 0x3f;
                        sy -= custom->vhposr & 0x7f;
                }
                sx += 1;
                sy += 2;
                /* Wait for late vertical beam position. */
                vsync(VPOS_MAX-10);

                /* Frame loop start */

                cx = regulate(px, sx, &xack);
                cy = regulate(py, sy, &yack);

                px += cx;
                py += cy;

                translate(px - (320/2), py - (256/2));

                v += vadd;
                /* Bottom check */
                if (0xf0 <= v) {
                        /* Change direction */
                        vadd = -vadd;
                }
                /* Top check */
                if (v <= 0x40) {
                        /* Change direction */
                        vadd = -vadd;
                }

                /*
                 * Install new bar horizontal position in copper list. It is
                 * important that those writes happen before the copper
                 * encounters the corresponding wait instructions.
                 */
                *vp0 = v;
                *vp1 = v + 1;

                /* Frame loop end */
        }

        return 0;
}

