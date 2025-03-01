#ifndef BUSH_TYPES_H
#define BUSH_TYPES_H

typedef unsigned char u8_t;
typedef unsigned short u16_t;
typedef long long int i64_t;
typedef double f64_t;

typedef enum { TP_NUM, TP_EXPR, TP_FN, TP_VAR } tp_t;

/* branch:
	id  -- 	an operator id;
	lvl -- 	an operator level (how many parenthesis it is in);
	rnk -- 	an operator rank (priority); (removed)
	uf  -- 	unary flag that used to indicate operand's signes; (removed)
	xf  -- 	execution flag used to indicate that the operator has 
			already been processed by the execute function;
	------------------------
	l- & r- indicate that this attribute describes a left/right operand; */
typedef struct {
	u8_t id:6, l_id:6, r_id:6,
		 tp:2, l_tp:2, r_tp:2,
		 xf:1, uf:1, ef:1,
		 lvl:4, rnk:1;
} branch_t;

#endif

