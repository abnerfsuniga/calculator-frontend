#include <stdio.h>
#include <stdlib.h>
#include "ll.h"

llnode create_node() {
    llnode temp; 
    temp = (llnode)malloc(sizeof(struct ll));
    temp->next = NULL;
    return temp;
}

llnode add_node(llnode head, int data) {
    llnode temp, p;
    temp = create_node();
    temp->data = data;
    if (head == NULL) {
        head = temp;
    } else {
        p = head;
        // ** Implementação ruim
        while(p->next != NULL) {
            p = p->next;
        }
        p->next = temp;
    }
    return head;
}