#include <stdio.h>
#include <stdlib.h>

enum vartype {
	TYPEINTEGER,
	TYPEFLOAT
};

struct symbol {
	char *name;
	int type;
	double value;
};

#define NHASH 9997
struct symbol symtab[NHASH];

struct evalexp {
	double value;
	int type;
};

struct evalexp * eval_tree(struct ast *a);

const char * get_type_str(int vartype);

