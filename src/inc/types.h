#ifndef BUSH_TYPES_H
#define BUSH_TYPES_H

typedef unsigned char u8_t;
typedef unsigned short u16_t;
typedef double f64_t;

typedef enum {
	TP_OPD,
	TP_ROOT
} tp_t;

typedef struct {
	u8_t id:7, tp:1;
} opd_t;

/* branch:
	id  -- 	an operator id;
	lvl -- 	an operator level (how many parenthesis it is in);
	*rnk -- an operator rank (priority);
	*tp -- it has only 4 states: add, sub, mul, div.
	xf  -- 	execution flag used to indicate that the operator has 
			already been processed by the execute function;
	------------------------ 
	(*) the meaning of tp depends on rnk. if rnk=1 then tp can be either
	'*' or '/', else - '+' or '-'; 
*/
typedef struct {
	u16_t id:7, tp:1, rf:1, ef:1, rnk:1, lvl:5;
	opd_t l, r;
} branch_t;

#endif

