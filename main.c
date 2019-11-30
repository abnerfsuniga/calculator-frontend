#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "ast.h"
#include "calculator.h"
#include "ll.h"
#include "calculator.tab.h"
#include "semantic.h"

int main(int argc, char **argv) { 
	FILE *myfile = fopen("test_cases/3.txt", "r");
	if (!myfile) {
		return -1;
	}
	yyin = myfile;
	yyparse();

	llnode p;
	p = tree_list;
	while(p != NULL){
		struct evalexp *ee = eval_tree(p->tree);
		if (ee) {
			printf("Value: %f Type: %d\n", ee->value, ee->type);
		}
		p = p->next;
	}
	return 0;
}

void yyerror(char *s, ...) {
	va_list ap;
	va_start(ap, s);

	fprintf(stderr, "\n");
	fprintf(stderr, "ERRO na linha %d: coluna: %d.\n%s\n", yylloc.first_line, yylloc.first_column, s);
	exit(0);
}
