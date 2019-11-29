#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "calculator.h"
#include "ll.h"

struct ast *newast(int nodetype, struct ast *l, struct ast *r) {
  struct ast *a = malloc(sizeof(struct ast));
  if(!a) {
    yyerror("out of space");
    exit(0);
  }
  a->nodetype = nodetype;
  a->l = l;
  a->r = r;
  return a;
}

struct ast *newinteger(double d) {
  struct numvar *a = malloc(sizeof(struct numvar));
  if(!a) {
    yyerror("out of space");
    exit(0);
  }
  a->nodetype = T_INTEGER;
  a->number = d;
  return (struct ast *)a;
}

struct ast *newfloat(double d) {
  struct numvar *a = malloc(sizeof(struct numvar));
  if(!a) {
    yyerror("out of space");
    exit(0);
  }
  a->nodetype = T_FLOAT;
  a->number = d;
  return (struct ast *)a;
}


struct ast *newvar(char *name) {
	struct var *a = malloc(sizeof(struct var));
	if(!a) {
    yyerror("out of space");
    exit(0);
  }
	a->nodetype = T_VAR;
	a->name = name;
	return (struct ast *)a;
}

void printtree(struct ast *a, int level) {
	printf("%*s", 16*level, "");
	level++;

	if(!a) {
    printf("NULL\n");
    return;
  }

	switch(a->nodetype) {
    case T_ROOT:
			printtree(a->l, --level);
			return;
    case T_STATEMENT:
			printtree(a->l, --level);
      printtree(a->r, level);
      return;
		case T_INTEGER:
      printf("%d\n", (int)((struct numvar *)a)->number);
			return;
    case T_FLOAT:
			printf("%.2f\n", ((struct numvar *)a)->number);
			return;
		case T_VAR:
			printf("%s\n", get_node_name(T_VAR));
			return;

		case T_ADD:
    	printf("%s\n", get_node_name(T_ADD));
			printtree(a->l, level);
			printtree(a->r, level);
			return;
		case T_SUB:
    	printf("%s\n", get_node_name(T_SUB));
			printtree(a->l, level);
			printtree(a->r, level);
			return;
		case T_MUL: 
      printf("%s\n", get_node_name(T_MUL));
			printtree(a->l, level);
			printtree(a->r, level);
			return;
		case T_DIV:
      printf("%s\n", get_node_name(T_DIV));
			printtree(a->l, level);
			printtree(a->r, level);
			return;
		case T_EXP:
      printf("%s\n", get_node_name(T_EXP));
			printtree(a->l, level);
			printtree(a->r, level);
			return;

		case T_MINUS:
    	printf("%s\n", get_node_name(T_MINUS));
			printtree(a->l, level);
			return;

    case T_ASSIGNMENT:
      printf("::%s\n", get_node_name(T_ASSIGNMENT));
			printtree(a->l, level);
			return;
    case T_PRINT:
      printf("::%s\n", get_node_name(T_PRINT));
			printtree(a->l, level);
			return;
    case T_EXPRESSION:
		  printf("::%s\n", get_node_name(T_EXPRESSION));
			printtree(a->l, level);
			return;

	  default: 
			printf("BAD NODE %c\n", a->nodetype);
    	return;
	}
}

const char * get_node_name(int nodetype) {
  switch (nodetype) {
    case T_ROOT:
      return "T_ROOT";
    case T_STATEMENT:
      return "T_STATEMENT";
    case T_ASSIGNMENT:
      return "T_ASSIGNMENT";
    case T_EXPRESSION:
      return "T_EXPRESSION";
    case T_PRINT:
      return "T_PRINT";
    case T_ADD:
      return "+";
    case T_SUB:
      return "-";
    case T_MUL:
      return "*";
    case T_DIV:
      return "/";
    case T_EXP:
      return "^";
    case T_MINUS:
      return "M";
    case T_INTEGER:
      return "INT";
    case T_FLOAT:
      return "FLOAT";
    case T_VAR:
      return "VAR";
  }
}

// double eval_expression(struct ast *a) {

// }

// int semantic(struct ast *a) {

//   if(!a) {
//     printf("NULL\n");
//     return;
//   }

//   switch (a->nodetype) {
//     case T_ROOT:
//       return semantic(a->l);
//     case T_STATEMENT:
//       return semantic(a->l) && semantic(a->r);
//       break;
//     case T_ASSIGNMENT:
//     case T_PRINT:
//     case T_EXPRESSION:
//       return eval_expression(a->l);
//     default:
//       printf("BAD NODE %c\n", a->nodetype);
//       return;
//   }
// }

int main(int argc, char **argv) { 
	FILE *myfile = fopen("input.txt", "r");
	if (!myfile) {
		return -1;
	}
  llnode n = create_node();
	yyin = myfile;
	yyparse();
  printtree(AST, 0);
}


void yyerror(char *s, ...) {
  va_list ap;
  va_start(ap, s);

  fprintf(stderr, "%d: error: ", yylineno);
  vfprintf(stderr, s, ap);
  fprintf(stderr, "\n");
}
