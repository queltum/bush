#include "inc\bush.h"

static u8_t opd[64];
static branch_t op[64];

static char _gettp(char c) {
	switch (c) {
		case '+': return 0;
		case '-': return 1;
		case '*': return 2;
		case '/': return 3;
		default: return -1;
	}
}

/* doesn't work */
static branch_t *l_getroot(u8_t shft) {
	u8_t i, j;

	i = shft;
	for (j = i - 1; op[j].lvl >= op[shft].lvl && j + 1; --j)
		if (op[i].lvl == op[j].lvl)
			if (op[i].rnk < op[j].rnk)
				i ^= j ^= i ^= j;
		else if (op[i].lvl > op[j].lvl)
			i ^= j ^= i ^= j;
	return &op[i];
}

/* doesn't work */
static branch_t *r_getroot(u8_t shft) {
	u8_t i, j;

	i = shft;
	for (j = i + 1; op[j].lvl >= op[shft].lvl; ++j) {
		if (op[i].ef || j == 64)
			break;
		if (op[i].lvl == op[j].lvl)
			if (op[i].rnk < op[j].rnk)
				i ^= j ^= i ^= j;
		else if (op[i].lvl > op[j].lvl)
			i ^= j ^= i ^= j;
	}
	return &op[i];
}

void dump(void) {
	u8_t i;

	for (i = 0; i < 10; ++i) {
		printf("[id:%d, tp:??, lvl:%d, rnk:%d, tp:%d, ef:%d,", 
			op[i].id, op[i].lvl, op[i].rnk, op[i].tp,
			op[i].ef);
		printf(" {l_id:%d, l_tp:%d}, {r_id:%d, r_tp:%d}]\n", 
			op[i].r_id, op[i].r_tp);
	}
	for (i = 0; i < 10; ++i)
		printf("[id:%d, shft:%d]\n", i, opd[i]);
}

static void hay(char *s) {
	u8_t opdc, opc, sc, lc;

	opdc = opc = sc = lc = 0;
	for (;;) {
		if (_isdigit(s[sc])) {
			opd[opdc++] = sc;
			while (_isdnfp(s[++sc]))
				;
		}

		switch (s[sc]) {
			case '(':
				++lc;
				++sc;
				break;
			case ')':
				--lc;
				++sc;
				break;
			case '+': case '-':
				if (!opd || s[sc - 1] == '(')
					if (_isdigit(s[sc + 1])) {
						++sc;
						break;
					}
			case '*': case '/':
				op[opc].id = opc;
				op[opc].tp = _gettp(s[sc]);
				op[opc].lvl = lc;
				op[opc].rnk = _getrnk(s[sc]);
				++opc;
				++sc;
				break;
			case '\0':
				op[opc - 1].ef = 1;
				return;
		}
	}
}

/* doesn't work */
static void bind(void) {
	u8_t i, j;
}

branch_t *bush(char *s) {
	hay(s);
	printf("%d;\n", r_getroot(0)->id);
	return op;
}

