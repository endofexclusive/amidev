#ifndef COPPER_H_
#define COPPER_H_

/*
 * Functions and macros for operating on the Amiga graphics coprocessor
 * (Copper). This file describes PAL displays.
 *
 * For more information on the Copper, see "Amiga hardware reference manual".
 */

/* A copper instruction consists of two words. */
struct copper_instruction {
        uint16_t w0;
        uint16_t w1;
};

/*
 * First screen pixel is at (VP,HP)=($2c,$07). Last line for PAL is at
 * (VP,HP)=($12b,$df).
 */
#define LINE_FIRST      0x02c
#define LINE_LAST       0x12b
#define LINE_START      0x07
#define LINE_END        0xdf

#define DIWSTRT_LORES   0x2c81
#define DIWSTOP_LORES   0x2cc1

#define DDFSTRT_LORES   0x0038
#define DDFSTOP_LORES   0x00d0

/*
 * Minimum and maximum vertical beam positions. There are 312 possible vertical
 * positions on PAL.
 */
#define VPOS_MIN        0x0
#define VPOS_MAX        0x137

/*
 * Copper move instruction
 *
 * One move instruction takes 8 cycles. Destination is limited to register
 * addresses $080 ($040) and up.
 */
#define COP_MOVE(reg, val) {(reg), (val)}

/*
 * Copper wait instruction
 *
 * Wait for vertical position and horizontal position with mask.
 * column is lowres, LSB must be set.
 */
#define COP_WAIT(vp, hp, mask) {((vp)<<8) | (hp) | 0x01, (mask) & ~0x0001}

/* Wait for an impossible screen position. */
#define COP_END COP_WAIT(0xff, 0xff, 0xfffe)

/* Slow fetch mode for AGA compatibility */
#define COP_SLOW_FETCH_MODE COP_MOVE(0x01fc, 0x0000)
#define COP_COLOR_BURST COP_MOVE(BPLCON0, BPLCON0F_COLOR)

static inline void copper_install(int n, struct copper_instruction *clist)
{
        if (1 == n) {
                custom->cop1lch = clist;
        } else if (2 == n) {
                custom->cop2lch = clist;
        }
}

static inline void copper_start(void)
{
        custom->dmacon = DMAF_SETCLR | DMAF_MASTER | DMAF_COPPER;
}

#endif

