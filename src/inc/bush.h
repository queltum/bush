#ifndef BUSH_H
#define BUSH_H

#include "types.h"

extern branch_t *bush(char *);

#ifdef BUSH_DEBUG
extern void dump(void);
#endif
#endif

