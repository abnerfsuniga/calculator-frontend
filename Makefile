calculator: calculator.l calculator.y ast.h ast.c ll.h ll.c semantic.h semantic.c main.c
	bison -d calculator.y
	flex calculator.l
	cc -o $@ -g calculator.tab.c lex.yy.c ast.c ll.c semantic.c main.c -lfl -lm