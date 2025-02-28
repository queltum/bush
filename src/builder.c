#include <stdio.h>
#include <stdarg.h>

#include "inc\builder.h"

#define _log(msg) puts("log: " fmt)
#define _wrn(fmt, ...) printf("wrn: " fmt "\n", ##__VA_ARGS__)
#define _err(fmt, ...) printf("err: " fmt "\n", ##__VA_ARGS__)

static inline u8_t _isdigit(u8_t c) {
	return (c >= '0' && c <= '9');
}

/* nfp is number-float-point */
static inline u8_t _isnfp(u8_t c) {
	return (c == ',' || c == '.');
}

u8_t analyse(u8_t *s) {
	u8_t lc, sc;

	struct { 
		u8_t opd:1, op:1, nfp:1, 
			 un:1, lp:1, rp:1, rsvd:2; 
	} fg;

	*(u8_t *)&fg = lc = sc = 0;

	for (;;) {
		if (_isdigit(s[sc])) {
			if (fg.opd)
				goto _ERREOP;
			while (_isdigit(s[++sc]))
				;
			if (_isnfp(s[sc])) {
				if (fg.nfp)
					goto _ERRINF;
				fg.nfp = 1;
				++sc;
				continue;
			}

			*(u8_t *)&fg = 0;
			fg.opd = 1;
		}

		switch (s[sc]) {
			case '(':
				++lc;
				++sc;
				fg.lp = 1;
				break;
			case ')':
				if (!lc)
					goto _ERRERP;
				if (!fg.opd)
					goto _ERREOPD;
				--lc;
				++sc;
				*(u8_t *)&fg = 0;
				break;
			case '+': case '-':
				if (!*(u8_t *)&fg || fg.lp) {
					fg.op = fg.un = 1;
					++sc;
					break;
				}
			case '*': case '/': case '%':
				if (fg.op)
					goto _ERREOPD;
				++sc;
				*(u8_t *)&fg = 0;
				fg.op = 1;
				break;
			case '\0':
				if (fg.op)
					goto _ERREOPD;
				if (fg.nfp)
					goto _ERRINF;
				if (lc)
					goto _ERRELP;
				return 0;
			default:
				goto _ERRUT;
		}
	}

_ERRINF:
	_err("invalid number format at %d;", ++sc);
	return 6;
_ERRUT:
	_err("undefined token \'%c\';", s[sc]);
	return 5;
_ERREOPD:
	_err("expected an operand at %d;", ++sc);
	return 4;
_ERREOP:
	_err("expected an operator at %d;", ++sc);
	return 3;
_ERRELP:
	_err("expected \')\' at %d;", ++sc);
	return 2;
_ERRERP:
	_err("expected \'(\' at %d;", ++sc);
	return 1;
}

