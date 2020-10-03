all: execute
execute:
	@lex lex1.l
	@yacc parser.y
	@yacc -d parser.y
	@gcc y.tab.c -o conversion
	
	