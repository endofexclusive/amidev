/*
 * Implemented according to Photon/Scoopex video "Amiga Hardware Programming 6
 * - Understanding the Raster"
 */

#include <custom.h>
#include <custombits.h>
#include <gfx.h>
#include <copper.h>
#include "sin256x63.h"

struct copper_instruction clist[] =
{
        COP_SLOW_FETCH_MODE,
        COP_COLOR_BURST,

        COP_MOVE(COLOR00, 0x0349),

        COP_WAIT(LINE_FIRST-1, LINE_START, 0xfffe),
        COP_MOVE(COLOR00, 0x056c),

        COP_WAIT(LINE_FIRST, LINE_START, 0xfffe),
        COP_MOVE(COLOR00, 0x0113),

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
        const int8_t *sin = (const int8_t *) &sin256x63[0];
        const uint8_t VORIGIN = (LINE_LAST + LINE_FIRST) / 2;
        uint8_t r = 0;
        uint8_t va = VORIGIN;
        uint8_t vb = VORIGIN;
        int8_t radd = 1;
        volatile uint8_t *vp0 = (uint8_t *) &clist[7].w0;
        volatile uint8_t *vp1 = (uint8_t *) &clist[9].w0;

        custom->dmacon = DMAF_MASTER | DMAF_ALL;
        /* Install the copper list */
        copper_install(1, clist);
        copper_start();

        while (1) {
                /* Wait for maximum vertical beam position. */
                vsync(VPOS_MAX);

                /* Frame loop start */

                va = VORIGIN + sin[(uint8_t) r];
                vb = VORIGIN + sin[(uint8_t) (r+0x20)];
                r += radd;

                /*
                 * Install new bar horizontal position in copper list. It is
                 * important that those writes happen before the copper
                 * encounters the corresponding wait instructions.
                 */
                if (va <= vb) {
                        *vp0 = va;
                        *vp1 = vb;
                } else {
                        *vp0 = vb;
                        *vp1 = va;
                }

                /* Frame loop end */
        }

        return 0;
}

