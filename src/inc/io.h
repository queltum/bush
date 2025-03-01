#ifndef BUSH_IO_H
#define BUSH_IO_H

#include <stdio.h>
#include <stdarg.h>

#define _log(msg) puts("log: " fmt)
#define _wrn(fmt, ...) printf("wrn: " fmt "\n", ##__VA_ARGS__)
#define _err(fmt, ...) printf("err: " fmt "\n", ##__VA_ARGS__)

extern char *readin(void);

#endif

