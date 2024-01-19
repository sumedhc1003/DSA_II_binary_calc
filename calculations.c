#include <stdlib.h>
#include "calculations.h"
#include "linked_list.h"

node* addition(node** operand1, node** operand2){
    //setting pointer to iterate both the LL
    node* op1_ptr = *operand1;
    node* op2_ptr = *operand2;

    //declaring a result LL
    node* result = NULL;
    int carry = 0, sum = 0;

    //traversing both lists until we reach someones end
    while(op1_ptr && op2_ptr){
        sum = carry + op1_ptr->data + op2_ptr->data;
        carry = sum / 10; //updating carry
        insert_at_beginning(&result, sum % 10); //adding the result to the result LL

        op1_ptr = op1_ptr->next;
        op2_ptr = op2_ptr->next;
    }

    //iterating the remaining nodes of LL
    while(op1_ptr){
        sum = carry + op1_ptr->data;
        carry = sum / 10; //updating carry
        insert_at_beginning(&result, sum % 10);
        op1_ptr = op1_ptr->next;
    }

    while(op2_ptr){
        sum = carry + op2_ptr->data;
        carry = sum / 10; //updating carry
        insert_at_beginning(&result, sum % 10);
        op2_ptr = op2_ptr->next;
    }

    //case when carry is not yet zero
    if(carry != 0){
        insert_at_beginning(&result, carry);
    }

    reverse_list(&result); // because we got our addition in correct order but we store in reverse for ease of calculations further!
    return result;
}