bush is a lightweight syntax calculator;

Here is the stages of handling any maths expressions:
	readin  -- reads an expression from stdout and records it in the buffer;
	analyse -- used to check an expression for syntax errors. 
			   The next functions don't do that;
	hay		-- the bush "tokeniser". You get it if check the source code;
	bind	-- the bush "parser". It binds branches and operands to each other;

	It does not have any evaluators yet.

Limits:
	An expression must have less than:
		128 operands;
		128 operators;
		 32 nested expression's levels;
		 16 nested expression (temporary);

Bush is OS-independent; It can be compiled anywhere a C compiler is avaliable;