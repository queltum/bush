#include "inc\utils.h"

inline char b_isdigit(char c) {
	return (c >= '0' && c <= '9');
}

inline char b_isnfp(char c) {
	return (c == ',' || c == '.');
}

inline char b_isdnfp(char c) {
	return (b_isdigit(c) || b_isnfp(c));
}

inline char b_getrnk(char c) {
	return (c != '+' && c != '-');
}

inline void b_swap32(void *a, void *b) {
	*(int *)a ^= *(int *)b ^= *(int *)a ^= *(int *)b;
}

inline char b_gettp(char c) {
	switch (c) {
		case '+': case '*': return 0;
		case '-': case '/': return 1;
	}
}

