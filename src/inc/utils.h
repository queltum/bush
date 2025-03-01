#ifndef BUSH_UTILS_H
#define BUSH_UTILS_H

extern inline char _isdigit(char c);
extern inline char _isnfp(char c); /* nfp is number-float-point */
extern inline char _isdnfp(char c); /* digit or nfp */
extern inline char _getrnk(char c);

extern char analyse(char *);
#endif

