#include <stdio.h>
#include <stdarg.h>

#include "inc\bush.h"

#define b_log(msg) puts("log: " fmt)
#define b_wrn(fmt, ...) printf("wrn: " fmt "\n", ##__VA_ARGS__)
#define b_err(fmt, ...) printf("err: " fmt "\n", ##__VA_ARGS__)

/* 1KB */
static u8_t buf[256];
static u8_t opd[128];
static branch_t op[128];
static f64_t mem[16];

static void b_sort(void) {
	u8_t i, j, lim;
	branch_t tmp;

	lim = 0;
	for (i = 0; !op[i].ef; ++i)
		++lim;

	for (i = 0; i < lim; ++i) {
		for (j = i + 1; j <= lim; ++j)
			if (op[i].lvl == op[j].lvl && op[i].rnk < op[j].rnk) {
				tmp = op[i];
				op[i] = op[j];
				op[j] = tmp;	
				op[j].ef = op[i].ef = 0;
			}
			else if (op[i].lvl < op[j].lvl) {
				tmp = op[i];
				op[i] = op[j];
				op[j] = tmp;	
				op[j].ef = op[i].ef = 0;
			}
	}
	op[lim].ef = 1;
}

static branch_t *b_getroot(u8_t shft) {
	u8_t i, j;

	i = shft;
	for (j = i + 1; op[j].lvl >= op[shft].lvl; ++j) {
		if (op[i].ef || j == 128)
			break;
		if (op[i].lvl == op[j].lvl)
			if (op[i].rnk < op[j].rnk)
				i ^= j ^= i ^= j;
		else if (op[i].lvl > op[j].lvl)
			i ^= j ^= i ^= j;
	}
	return &op[i];
}

void readin(void) {
	u8_t c, i;

	fwrite("bush> ", 1, 6, stdout);
	
	i = 0;
	while (i < 255)
		switch (c = getchar()) {
			case '\n':
				buf[i] = '\0';
				return;
			case ' ': case '\t':
				break;
			default:
				buf[i++] = c;
				break;
		}
}

u8_t analyse(void) {
	u8_t lc, sc;

	struct { 
		u8_t opd:1, op:1, nfp:1, 
		un:1, lp:1, rp:1, rsvd:2; 
	} fg;

	*(char *)&fg = lc = sc = 0;

	for (;;) {
		if (b_isdigit(buf[sc])) {
			if (fg.opd) {
				b_err("expected an operator at %d;", ++sc);
				return 3;
			}
			while (b_isdigit(buf[++sc]))
				;
			if (b_isnfp(buf[sc])) {
				if (fg.nfp) {
					b_err("invalid number format at %d;", ++sc);
					return 6;
				}
				fg.nfp = 1;
				++sc;
				continue;
			}

			*(char *)&fg = 0;
			fg.opd = 1;
		}

		switch (buf[sc]) {
			case '(':
				++lc;
				++sc;
				fg.lp = 1;
				break;
			case ')':
				if (!lc) {
					b_err("expected \'(\' at %d;", ++sc);
					return 1;
				}
				if (fg.op) {
					b_err("expected an operand at %d;", ++sc);
					return 4;
				}
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
				if (fg.op) {
					b_err("expected an operand at %d;", ++sc);
					return 4;
				}
				++sc;
				*(char *)&fg = 0;
				fg.op = 1;
				break;
			case '\0':
				if (fg.op) {
					b_err("expected an operand at %d;", ++sc);
					return 4;
				}
				if (fg.nfp) {
					b_err("invalid number format at %d;", ++sc);
					return 6;
				}
				if (lc) {
					b_err("expected \')\' at %d;", ++sc);
					return 2;
				}
				return 0;
			default:
				b_err("undefined token \'%c\';", buf[sc]);
				return 5;
		}
	}
}

u8_t hay(void) {
	u8_t opdc, opc, sc, lc;

	opdc = opc = sc = lc = 0;
	for (;;) {
		switch (buf[sc]) {
			case '(':
				++lc;
				++sc;
				break;
			case ')':
				--lc;
				++sc;
				break;
			case '+': case '-':
				if (!sc || buf[sc - 1] == '(') {
					++sc;
					break;
				}
			case '*': case '/':
				op[opc].id = opc;
				op[opc].lvl = lc;
				op[opc].tp = b_gettp(buf[sc]);
				op[opc++].rnk = b_getrnk(buf[sc++]);
				break;
			case '0': case '1': case '2': case '3': case '4':
			case '5': case '6': case '7': case '8': case '9':
				while (b_isdnfp(buf[++sc]))
					;
				opd[opdc++] = sc - 1;
				break;
			case '\0':
				if (!opc) {
					b_wrn("the expression doesn't make sense by itself;");
					return 1;
				}
				op[opc - 1].ef = 1;
				return 0;
		}
	}
}

void bind(void) {
	u8_t i, j;

	i = 0, j = 1;
	op[i].l_id = i; /* if (!i) */

	for (;; ++i, ++j) {
		if (op[i].ef) {
			op[i].r_id = j;
			return;
		} 
		if (op[i].lvl == op[j].lvl) {
			if (op[i].rnk > op[j].rnk) {
				op[i].r_id = j;
				op[j].l_id = i;
				op[j].l_tp = TP_OPD;
			} else if (op[i].rnk <= op[j].rnk) {
				op[j].l_id = op[i].r_id = j;
				op[i].r_tp = TP_ROOT;
			}
		} else if (op[i].lvl < op[j].lvl) {
			op[i].r_id = b_getroot(j)->id;
			op[i].r_tp = TP_ROOT;
			op[j].l_id = j;
		} else if (op[i].lvl > op[j].lvl) {
			op[i].r_id = j;
			op[i].r_tp = TP_OPD;
		}
	}
}

void dump(void) {
	u8_t i;

	for (i = 0; i < 4; ++i) {
		printf("[id:%d, lvl:%d, rnk:%d, tp:%d, ef:%d,", 
			op[i].id, op[i].lvl, op[i].rnk, op[i].tp,
			op[i].ef);
		printf(" {l_id:%d, l_tp:%d}, {r_id:%d, r_tp:%d}]\n", 
			op[i].l_id, op[i].l_tp, op[i].r_id, op[i].r_tp);
	}
	for (i = 0; i < 5; ++i)
		printf("[id:%d, shft:%d]\n", i, opd[i]);
}
