#include <stdlib.h>
#include "calculations.h"
#include "linked_list.h"

// addition definition
node* addition(node** operand1, node** operand2){
    //setting pointer to iterate both the LL
    node* greater_ptr = *operand1;
    node* smaller_ptr = *operand2;

    //declaring a result LL
    node* result = NULL;
    int carry = 0, sum = 0;

    //traversing both lists until we reach someones end
    while(greater_ptr && smaller_ptr){
        sum = carry + greater_ptr->data + smaller_ptr->data;
        carry = sum / 10; //updating carry
        insert_at_beginning(&result, sum % 10); //adding the result to the result LL

        greater_ptr = greater_ptr->next;
        smaller_ptr = smaller_ptr->next;
    }

    //iterating the remaining nodes of whichever LL that remains
    while(greater_ptr){
        sum = carry + greater_ptr->data;
        carry = sum / 10; //updating carry
        insert_at_beginning(&result, sum % 10);
        greater_ptr = greater_ptr->next;
    }

    while(smaller_ptr){
        sum = carry + smaller_ptr->data;
        carry = sum / 10; //updating carry
        insert_at_beginning(&result, sum % 10);
        smaller_ptr = smaller_ptr->next;
    }

    //case when carry is not yet zero
    if(carry != 0){
        insert_at_beginning(&result, carry);
    }

    reverse_list(&result); // because we got our addition in correct order but we store in reverse for ease of calculations further!
    return result;
}

//subtraction definition
//functio to determine which of the two operands is greater
node* determine_greater_operand(node** operand1, node** operand2){
    //counting the length of each operand
    int count1 = 1, count2 = 1; // we have handled the case of empty LL ahead
    node* ptr1 = *operand1;
    node *ptr2 = *operand2;

    //in case of empty LL
    if(ptr1 == NULL || ptr2 == NULL){
        return NULL;
    } 

    //for operand1
    while(ptr1->next){
        count1++;
        ptr1 = ptr1->next;
    }

    //for operand2
    while(ptr2->next){
        count2++;
        ptr2 = ptr2->next;
    }

    //in case of different count
    if(count1 > count2){
        return *operand1;
    }
    else if(count1 < count2){
        return *operand2;
    }
    else{         //handling the case of equal length strings
        if(ptr1->data > ptr2->data){ //as the pointers were left of the last node of LL which happen to be the first digit of the operands
            return *operand1;
        }
        else{
            return *operand2;
        }
    }
}

//function for actual subtraction
node* subtraction(node** operand1, node** operand2){

    //checking the LL for which one is greater
    int flag_for_negative;
    node* greater_LL = determine_greater_operand(operand1, operand2);

    //determining the smaller LL
    node *smaller_LL = NULL;
    if(greater_LL == *operand1){
        smaller_LL = *operand2;
        flag_for_negative = 0; 
    }
    else{
        smaller_LL = *operand1;
        flag_for_negative = 1; //setting the flag as difference would be neagtive
    }

    //declaring the result LL
    node* result = NULL;

    //declaring pointer for ecah of LL
    node* greater_ptr = greater_LL;
    node* smaller_ptr = smaller_LL;

    int difference, borrow = 0;

    //traversing both the LL until the end of one of them
    while(smaller_ptr){
        difference = (greater_ptr->data - borrow) - smaller_ptr->data;

        //in case difference is < 0
        if(difference < 0){
            difference = 10 + difference;
            borrow = 1;
        }
        else{
            borrow = 0;
        }

        //inserting the differnce to LL in the correct order
        insert_at_beginning(&result, difference);

        //incrementing the pointer once the subtraction is done
        greater_ptr = greater_ptr->next;
        smaller_ptr = smaller_ptr->next;
    }

    //for the remain nodes
    while(greater_ptr){

        difference = (greater_ptr->data - borrow);

        //in case of difference < 0
        if(difference < 0){
            difference = 10 + difference;
            borrow = 1;
        }
        else{
            borrow = 0;
        }

        insert_at_beginning(&result, difference);

        //incrementing the pointer
        greater_ptr = greater_ptr->next;
    }

    //making the first of difference negative if negatiev flag is set
    if(flag_for_negative){
        result->data = -(result->data);
    }

    //reversing the result LL as that's how we operate on it
    reverse_list(&result);
    return result;
}


//multiplication
node* multiplication(node** operand1, node** operand2){
    return NULL;
}

//division
node* division(node** operand1, node** operand2){
    return NULL;
}