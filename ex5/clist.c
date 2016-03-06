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
        COP_MOVE(DDFSTRT, DDFSTRT_LORES-8),
        /* DMA fetch stop, per scan line */
        COP_MOVE(DDFSTOP, DDFSTOP_LORES),

        /*
         * Modulo is two counts less than the difference between the address of
         * the next word you want to fetch and the address of the last word
         * that was fetched.
         */
        COP_MOVE(BPL1MOD, SQWORDS*4-2),
        COP_MOVE(BPL2MOD, 0x0000),
        /* Horizontal scroll control */
        //COP_MOVE(BPLCON1, (0 & BPLCON1F_PF2H ) | (0 & BPLCON1F_PF1H)),

#define COP_BPL 8
        /* Set bitplane pointers */
        COP_MOVE(0xe0, 0x0000),
        COP_MOVE(0xe2, 0x0000),

        /* Do not enable raster DMA until bitplane pointers are set. */
        COP_MOVE(BPLCON0, BPLCON0F_BPU0 | BPLCON0F_COLOR),

        COP_MOVE(COLOR00, 0x0349),
        COP_MOVE(COLOR01, 0x0d9d),

        COP_WAIT(LINE_FIRST-1, LINE_START, 0xfffe),
        COP_MOVE(COLOR00, 0x056c),

        COP_WAIT(LINE_FIRST, LINE_START, 0xfffe),
        COP_MOVE(COLOR00, 0x0113),

#define VP0 17
#define VP1 19
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

