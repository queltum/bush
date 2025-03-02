#ifndef BUSH_UTILS_H
#define BUSH_UTILS_H

extern inline char b_isdigit(char);
extern inline char b_isnfp(char); /* nfp is number-float-point */
extern inline char b_isdnfp(char); /* digit or nfp */
extern inline char b_getrnk(char);
extern inline char b_gettp(char);
extern inline void b_swap32(void *, void *);

#endif

