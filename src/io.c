#include <stdio.h>

#include "inc\io.h"

#define BUFSZ 0x100

static char buf[BUFSZ];

char *readin(void) {
	unsigned char c, i;

	fwrite("bush> ", 1, 6, stdout);
	
	i = 0;
	while (i < BUFSZ - 1)
		switch (c = getchar()) {
			case '\n':
				buf[i] = '\0';
				return buf;
			case ' ': case '\t':
				break;
			default:
				buf[i++] = c;
				break;
		}
}

