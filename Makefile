calculator: calculator.l calculator.y calculator.h ll.h ll.c main.c
	bison -d calculator.y
	flex calculator.l
	cc -o $@ calculator.tab.c lex.yy.c ll.c main.c -lfl -lm