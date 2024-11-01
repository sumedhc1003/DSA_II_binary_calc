#include <stdio.h>
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

        //getting the LL in correct order so that we can start comparing from start.
        reverse_list(operand1);
        reverse_list(operand2);
        ptr1 = *operand1;
        ptr2 = *operand2;

        //iterate until the first point of difference
        while(ptr1 && ptr2 && (ptr1->data == ptr2->data)){
            ptr1 =ptr1->next;
            ptr2 =ptr2->next;
        }

        //handing the case when both operands are identical!
        if((ptr1 == NULL) && (ptr2 == NULL)){
            return *operand1;
        }

        //returning the greater
        if(ptr1->data > ptr2->data){
            //getting back the order to normal from last manipulation
            reverse_list(operand1);
            reverse_list(operand2);

            return *operand1;
        }
        else{
            //getting back the order to normal from last manipulation
            reverse_list(operand1);
            reverse_list(operand2);

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

node* create_zero_list(int size){
	node* head = NULL;
    
	for(int i = 0; i < size; i++){
        insert_at_beginning(&head, 0);
    }
        
	return head;
}


node* multiplication(node** operand1, node** operand2){

    node* result = create_zero_list(count_nodes(operand1) + count_nodes(operand2) + 1);
    
    //declaring the pointers for iteration ahead
    node *ptr1 = NULL, *ptr2 =*operand2;
    node* result_ptr1 = result, *result_ptr2 = NULL;

    //traversing each digit of operand to be multiplied with each of operant1
    while(ptr2){

        result_ptr2 = result_ptr1; //resetting the result pointer to be used to traverse result LL again.
        ptr1 = *operand1;  //resetting the point to the start operand1 after each iteration
        int carry = 0; //resetting carry

        while(ptr1){

            int mul_result = (result_ptr2->data) + (ptr1->data * ptr2->data) + carry;
            carry = mul_result / 10; //finding the carry 
            result_ptr2->data = mul_result % 10; //updating the value in the LL

            //incremeting the required pointers
            result_ptr2 = result_ptr2->next;
            ptr1 =ptr1->next;
        }

        // if carry is remaining from last multiplication
        if (carry != 0) {
                result_ptr2->data += carry;
        }

        result_ptr1 = result_ptr1->next; //move one place left for addition of the next digit of operand2 with operand1
        ptr2 = ptr2->next;
    }

    // removing zeros at the start
    reverse_list(&result);
    node* temp = NULL;
    while (result && result->data == 0){
        temp = result;
        result = result->next;
        free(temp);
    }

    if(result == NULL){
        insert_at_beginning(&result, 0);
        return result;
    }

    reverse_list(&result);
    return result;
}

//division

//for making a copy of the LL
node* copy_LL(node* head){

    node* result = NULL;
    node* ptr = head;

    //travering a making copy of each node present
    while(ptr != NULL)
    {
        insert_at_beginning(&result,ptr->data);
        ptr = ptr->next;
    }
    return result;
}


node* division(node** operand1, node** operand2){

    //handling divide by zero error by checking if operand 2 is zero.
    if (is_zero(operand2)) {
        return NULL;
    }

    //initializing the result LL
    node* result = NULL;
    insert_at_beginning(&result, 0);

    //initializing a LL to be used to increment result later on
    node *increment_result_by_one = NULL;
    insert_at_beginning(&increment_result_by_one, 1);

    node* greater = determine_greater_operand(operand1, operand2);


    if(greater == *operand2){
        return result;
    }
    else{
        //making a copy of operand2 to be added repeatedly
        node* operand2_copy = copy_LL(*operand2);
        reverse_list(&operand2_copy);

        //iterating and going on adding operand2 to itself until its greater than operand1
        while(determine_greater_operand(operand1, operand2) == *operand1){
            result = addition(&result, &increment_result_by_one);
            *operand2 = addition(operand2,&operand2_copy);
        }

        return result;
    }
   return NULL;
}