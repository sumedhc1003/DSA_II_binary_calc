#ifndef EXPRESSION_EVALUATION_H
#define EXPRESSION_EVALUATION_H

#include "linked_list.h"


int precedence(char c);
int is_operand(char c);
int is_operator(char c);
node* calculations(node* operand1, node* operand2, char operator);
node* evaluate_expression(char input[]);

#endif