#ifndef BUSH_BUILDER_H
#define BUSH_BUILDER_H

#include "types.h"

/*	
branch:
	id  -- 	an operator id;
	lvl -- 	an operator level (how many parenthesis it is in);
	rnk -- 	an operator rank (priority); (removed)
	uf  -- 	unary flag that used to indicate operand's signes; (removed)
	xf  -- 	execution flag used to indicate that the operator has 
			already been processed by the execute function;
	------------------------
	l- & r- indicate that this attribute describes a left/right operand; */

enum { TP_NUM, TP_EXPR, TP_FN, TP_VAR };

typedef struct {
	i64_t i64;
	f64_t f64;
} val_t;

typedef struct {
	u8_t _id:6, l_id:6, r_id:6,
		 _tp:2, l_tp:2, r_tp:2,
		 _lvl:5, _xf:1, _ef:1, _rf:1;
} branch_t;

extern u8_t analyse(u8_t *);

#endif

