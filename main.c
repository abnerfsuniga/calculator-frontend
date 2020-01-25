#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include "ast.h"
#include "calculator.h"
#include "ll.h"
#include "calculator.tab.h"
#include "semantic.h"

int main(int argc, char **argv) { 
 	int opt, DEBUG = 0;
	char *filename = NULL, *tree_filename = NULL;
	while( (opt = getopt(argc, argv, "hi:a:d")) > 0 ) {
        switch (opt) {
            case 'h':
                printf("Comandos:\n-h\tAjuda\n-i\tArquivo de entrada\n-a\tArquivo de saída AST\n-d\tDebug mode\n");
                break ;
            case 'i':
                filename = optarg;
                break;
            case 'a':
                tree_filename = optarg;
                break;
			case 'd':
                DEBUG = 1;
                break;
            default:
                fprintf(stderr, "Opcao invalida ou faltando argumento: `%c'\n", opt) ;
                return -1 ;
        }
    }


	FILE *code_file = fopen(filename, "r");
	if (!code_file) {
		printf("Não foi possível abrir arquivo contendo código\n");
		exit(1);
	}
	yyin = code_file;
	yyparse();

	if (tree_filename) {
		FILE *tree_file = fopen(tree_filename, "w");
		if (!tree_file){
			printf("ERRO ao abrir o arquivo %s\n", tree_filename);
			exit(1);
		}
		llnode p;
		p = tree_list;
		while(p != NULL){
			printtree(p->tree, 0, tree_file);
			p = p->next;
		}
		fclose(tree_file);
	}

	llnode p;
	p = tree_list;

	// Reset line error tracking 
	yylloc.first_line = 1; 
	while(p != NULL){

		// Reset column error tracking
		yylloc.first_column = 1;

		struct evalexp *ee = eval_tree(p->tree);
		yylloc.first_line++;

		if (DEBUG && ee) {
			printf("Value: %.2f Type: %s\n", ee->value, get_type_str(ee->type));
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
