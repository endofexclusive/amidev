#ifndef GFX_H_
#define GFX_H_

#include <stdint.h>
#include <custom.h>

static inline void setcolor(int n, uint16_t color)
{
        volatile uint16_t *colregs;

        colregs = (void *) &custom->color00;
        colregs[n] = color;
}

/* Get vertical screen position, 16-bit value. */
static inline uint16_t getvpos(void)
{
        return ((custom->vposr & 1) << 8) | (custom->vhposr >> 8);
}

/* Get vertical screen position, 8-bit value. */
static inline uint8_t getvpos8(void)
{
        volatile uint8_t *vlo = (void *) &custom->vhposr;
        return *vlo;
}

/* Wait for vertical screen position, 16-bit value. */
static inline void waitvpos(uint16_t vpos)
{
        while (
                ((custom->vposr & 1) != (vpos >> 8)) ||
                (getvpos8() != (vpos & 0xff))
        );
}

/* Wait for vertical screen position, 8-bit value. */
static inline void waitvpos8(uint8_t vpos)
{
        while (getvpos8() != vpos);
}

/* Synchronize CPU with vertical position vpos. */
static inline void vsync(uint16_t vpos)
{
        waitvpos(vpos);
        while (getvpos8() == (0xff & vpos));
}

/* Wait for vertical screen position, 16-bit value. Alternative to waitvpos. */
static inline void waitraster(uint16_t rasterline)
{
        volatile uint32_t *const p = (void *) &custom->vposr;
        uint32_t mask;
        uint32_t match;

        mask = 0x0001ff00;
        match = mask & (rasterline << 8);
        while ((*p & mask) != match);
}

#endif

