#ifndef CALCULATIONS_H
#define CALCULATIONS_H
#include "linked_list.h"
node* addition(node** operand1, node** operand2);
node* determine_greater_operand(node** operand1, node** operand2); 
node* subtraction(node** operand1, node** operand2);
node* create_zero_list(int size);
node* multiplication(node** operand1, node** operand2);
node* copy_LL(node* head);
node* division(node** operand1, node** operand2);

#endif 
