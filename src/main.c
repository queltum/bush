#include <stdio.h>
#include <stdarg.h>

#include "inc\builder.h"

#define BUFSZ 0x100

static u8_t buf[BUFSZ];

static u8_t *readin(u8_t);

int main(void) {
	analyse(readin(BUFSZ - 1));
	return 0;
}

static u8_t *readin(u8_t len) {
	u8_t c, i;

	fwrite("bush> ", 1, 6, stdout);
	for (i = 0; len--; )
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

