#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include "calculator.h"
#include "ast.h"
#include "semantic.h"

const char * get_type_str(int vartype) {
  switch (vartype) {
    case TYPEINTEGER:
      return "TYPEINTEGER";
    case TYPEFLOAT:
      return "TYPEFLOAT";
  }
}

static unsigned symhash(char *sym)
{
	unsigned int hash = 0;
	unsigned c;

	while(c = *sym++) hash = hash*9 ^ c;

	return hash;
}

struct symbol * getcreate_symbol(char *sym) {
	struct symbol *sp = &symtab[symhash(sym)%NHASH];
	int scount = NHASH;		

	while(--scount >= 0) {
    	if(sp->name && !strcmp(sp->name, sym)) { return sp; }

		if(!sp->name) {	
			sp->name = strdup(sym);
			sp->type = -1;
			sp->value = 0;
			return sp;
		}

    	if(++sp >= symtab+NHASH) sp = symtab; 
	}
	yyerror("symbol table overflow\n");
	abort(); 
}

struct symbol * get_symbol(char *sym) {
	struct symbol *sp = &symtab[symhash(sym)%NHASH];
	int scount = NHASH;	
	while(--scount >= 0) {
    	if(sp->name && !strcmp(sp->name, sym)) { return sp; }

		if(!sp->name) {	
			return NULL;
		}
    	if(++sp >= symtab+NHASH) sp = symtab; 
	}
}

struct evalexp * eval_tree(struct ast *a) {
    struct symbol *symbol;
	struct symbol *new_symbol;
	struct evalexp *r;
	struct evalexp *l;

	if(!a) {
		yyerror("Internal error, NULL evalexp");
		return NULL;
	}

	struct evalexp * ee = malloc(sizeof(struct evalexp));

	switch (a->nodetype) {
		case T_INTEGER:
			ee->type = TYPEINTEGER;
			ee->value = (int)((struct numvar *)a)->number;
			break;
		case T_FLOAT:
			ee->type = TYPEFLOAT;
			ee->value = (double)((struct numvar *)a)->number;
			break;
		case T_VAR:
			symbol = get_symbol(((struct var *)a)->name);
			if (symbol) {
				ee->value = symbol->value;
				ee->type = symbol->type;
			} else {
				yyerror("ERRO semantico, variavel não declarada");
				exit(1);
			}
			break;
		case T_ASSIGNMENT:
			new_symbol = getcreate_symbol(((struct var *)a->l)->name);
			r = eval_tree(a->r);

			// Se a variável não é nova e recebe um tipo diferente gera um erro semantico
			if ((new_symbol->type != -1) && (new_symbol->type != r->type)) {
				char str[150];
				snprintf(
					str, 
					sizeof str, 
					"ERRO semantico, variavel %s tem tipo %s e não pode receber um tipo %s", 
					new_symbol->name, 
					get_type_str(new_symbol->type), 
					get_type_str(r->type)
				);
				yyerror(str);
				exit(1);
			}

			new_symbol->value = r->value;
			new_symbol->type = r->type;
			ee->value = r->value;
			ee->type = r->type;
			break;

		case T_EXPRESSION:
		case T_PRINT:
			l = eval_tree(a->l);
			ee = l;
			break;
	}
	return ee;
}