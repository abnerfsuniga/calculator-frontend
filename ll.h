#include <stdio.h>

struct ll {
    int data;
    struct ll *next;
};

typedef struct ll * llnode;

llnode create_node();
llnode add_node();