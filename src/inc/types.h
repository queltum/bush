#ifndef BUSH_TYPES_H
#define BUSH_TYPES_H

typedef unsigned char u8_t;
typedef unsigned short u16_t;
typedef double f64_t;

typedef enum {
	TP_OPD,
	TP_ROOT
} tp_t;

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
	u8_t id:7, l_id:7, r_id:7,
		 tp:1, l_tp:1, r_tp:1,
		 xf:1, ef:1, rnk:1, lvl:5;
} branch_t;

#endif

