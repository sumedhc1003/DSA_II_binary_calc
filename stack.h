#ifndef STACK_H
#define STACK_H
#include "linked_list.h"

#include <stdlib.h>

typedef struct operator_stack{
    int size;
    int top;
    char *arr;
}operator_stack;

typedef struct operand_stack{
    int size;
    int top;
    node **arr;
}operand_stack;



void init_operator_stack(operator_stack* s, int d);
void init_operand_stack(operand_stack* s, int d);

int is_empty_operator(operator_stack* s);
int is_empty_operand(operand_stack* s);

int is_full_operator(operator_stack* s);
int is_full_operand(operand_stack* s);


void push_operator(operator_stack* s, char c);
void push_operand(operand_stack* s, node *LL);

char peek_operator(operator_stack* s);

char pop_operator(operator_stack* s);
node* pop_operand(operand_stack* s);

#endif