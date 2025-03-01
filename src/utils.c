#include "inc\io.h"
#include "inc\utils.h"

inline char _isdigit(char c) {
	return (c >= '0' && c <= '9');
}

inline char _isnfp(char c) {
	return (c == ',' || c == '.');
}

inline char _isdnfp(char c) {
	return (_isdigit(c) || _isnfp(c));
}

inline char _getrnk(char c) {
	return (c != '+' && c != '-');
}

char analyse(char *s) {
	unsigned char lc, sc;

	struct { 
		unsigned char opd:1, op:1, 
		nfp:1, un:1, lp:1, rp:1, rsvd:2; 
	} fg;

	*(char *)&fg = lc = sc = 0;

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

			*(char *)&fg = 0;
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
				if (fg.op)
					goto _ERREOPD;
				--lc;
				++sc;
				*(char *)&fg = 0;
				break;
			case '+': case '-':
				if (!*(char *)&fg || fg.lp) {
					fg.op = fg.un = 1;
					++sc;
					break;
				}
			case '*': case '/':
				if (fg.op)
					goto _ERREOPD;
				++sc;
				*(char *)&fg = 0;
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

