#ifndef JOY_H_
#define JOY_H_

#include <custom.h>

static inline int isrmbdown(void)
{
        return (!(custom->potgor & POTGOF_DATLY));
}

#endif

