/*
 * Implemented according to Photon/Scoopex video "Amiga Hardware Programming 8
 * - Displaying bitmap graphics"
 */

#include <stddef.h>
#include <custom.h>
#include <custombits.h>
#include <gfx.h>
#include <copper.h>

#define WIDTH 320L
#define HEIGHT 256L
#define SCREENBYTES (WIDTH*HEIGHT/8)

/* NOTE: Word aligned */
uint16_t screen[SCREENBYTES/2];

struct copper_instruction clist[] =
{
        COP_SLOW_FETCH_MODE,
        /* Do not enable raster DMA until bitplane pointers are set. */
        COP_MOVE(BPLCON0, BPLCON0F_COLOR),

        /* Define screen of 320x256 pixels lores. */
        /* Shrinking screen does not stop DMA fetches. */
        /* Display window start, start at ($2c,$81). Top left corner. */
        COP_MOVE(DIWSTRT, DIWSTRT_LORES),
        /* Display window stop, ends at ($12c,$1c1). Bottom right corner. */
        COP_MOVE(DIWSTOP, DIWSTOP_LORES),

        /* Display window vertically decides when DMA shall start and stop. */
        /* DMA fetch start, per scan line */
        COP_MOVE(DDFSTRT, DDFSTRT_LORES),
        /* DMA fetch stop, per scan line */
        COP_MOVE(DDFSTOP, DDFSTOP_LORES),

        /* Modulo can be used to shrink/expand vertically */
        COP_MOVE(BPL1MOD, 0x0000),
        COP_MOVE(BPL2MOD, 0x0000),

#define COP_BPL 8
        /* Set bitplane pointers */
        COP_MOVE(0xe0, 0x0000),
        COP_MOVE(0xe2, 0x0000),
        //COP_MOVE(0xe0, ((const uint32_t) &screen[0]) ),
        //COP_MOVE(0xe2, ((const uint32_t) &screen[0]) ),

        /* Do not enable raster DMA until bitplane pointers are set. */
        COP_MOVE(BPLCON0, BPLCON0F_BPU0 | BPLCON0F_COLOR),

        COP_MOVE(COLOR00, 0x0349),

        COP_WAIT(LINE_FIRST-1, LINE_START, 0xfffe),
        COP_MOVE(COLOR00, 0x056c),

        COP_WAIT(LINE_FIRST, LINE_START, 0xfffe),
        COP_MOVE(COLOR00, 0x0113),

#define VP0 16
#define VP1 18
        /* Dynamic part begins. Wait VP is written by CPU each frame. */
        COP_WAIT(0x00, LINE_START, 0xfffe),
        COP_MOVE(COLOR00, 0x0fff),
        COP_WAIT(0x00, LINE_START, 0xfffe),
        COP_MOVE(COLOR00, 0x0113),
        /* Dynamic part ends */

        /* Wait for end of VP $ff */
        COP_WAIT(0xff, LINE_END, 0xfffe),
        /* First line below display */
        COP_WAIT(LINE_LAST+1, LINE_START, 0xfffe),
        COP_MOVE(COLOR00, 0x056c),
        COP_WAIT(LINE_LAST+2, LINE_START, 0xfffe),
        COP_MOVE(COLOR00, 0x0349),

        /* End of copper list */
        COP_END
};

int main(void)
{
        uint8_t v = 0xac;
        int8_t vadd = 1;
        volatile uint8_t *vp0 = (uint8_t *) &clist[VP0].w0;
        volatile uint8_t *vp1 = (uint8_t *) &clist[VP1].w0;

        /* Write a pattern to screen buffer. */
        for (size_t i = 0; i < sizeof screen / sizeof screen[0]; i++) {
                screen[i] = i;
        }
        custom->dmacon = DMAF_MASTER | DMAF_ALL;
        /* Install the copper list */
        copper_install(1, clist);
        copper_start();
        custom->dmacon = DMAF_SETCLR | DMAF_MASTER | DMAF_RASTER;

        /* Install bitplane pointers */
        clist[COP_BPL + 0].w1 = (uint32_t) screen >> 16;
        clist[COP_BPL + 1].w1 = (uint32_t) screen & 0xffff;

        while (1) {
                /* Wait for maximum vertical beam position. */
                vsync(VPOS_MAX);

                /* Frame loop start */

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

