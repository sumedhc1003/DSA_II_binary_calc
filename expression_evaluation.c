#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"
#include "expression_evaluation.h"
#include "stack.h"
#include "calculations.h"
#define LIMIT 10 //assuming of the max number of operand and operators

//function for assigning precedence to the operators
int precedence(char c){
    switch(c) {
        case '*':
            return 10;
            break;

        case '/':
            return 10;
            break;

        case '+':
            return 3;
            break;

        case '-':
            return 6;
            break;

        default:
            break;
    }
    return -1;
}

//return 1 if c is an operand
int is_operand(char c){
    if(c >= '0' && c <= '9'){
        return 1;
    }
    else{
        return 0;
    }
}

int is_operator(char c)   
{
	if(c == '^' || c == '*' || c == '/' || c == '+' || c =='-'){
        return 1;
    }
	else{
        return 0;
    }
	
}

//function for checking consecutive opertors
int has_consecutive_operators(char input[]) {
    int i = 0;
    while (input[i] != '\0') {
        if (is_operator(input[i])) {
            i++;
            while (is_operator(input[i]) || input[i] == ' ') {
                if (is_operator(input[i])) {
                    printf("Error: Consecutive operators found\n");
                    return 1; // Return an error
                }
                i++;
            }
        } else {
            i++;
        }
    }
    return 0; // No consecutive operators found
}

node* calculations(node* operand1, node* operand2, char operator){

    node* result;
    switch(operator){
        case('+'):
            reverse_list(&operand1);
            reverse_list(&operand2);

            if(operand1->data < 0){
                operand1->data = -(operand1->data);
                if(operand2->data < 0){ //incase both are negative
                    operand2->data = -(operand2->data);
                    reverse_list(&operand1);
                    reverse_list(&operand2);

                    result = addition(&operand1, &operand2);

                    //adding negative to the result
                    reverse_list(&result);
                    result->data = -(result->data);
                    reverse_list(&result);
                }
                else{ // first negative and second positve
                    reverse_list(&operand1);
                    reverse_list(&operand2);
                    result = subtraction(&operand2, &operand1);
                }
            }
            else{ 
                if(operand2->data < 0){ //first positive and second negative
                    operand2->data = -(operand2->data);
                    reverse_list(&operand1);
                    reverse_list(&operand2);
                    result = subtraction(&operand1, &operand2);
                }
                else{ //incase both postive
                    reverse_list(&operand1);
                    reverse_list(&operand2);
                    result = addition(&operand1, &operand2);
                }
            }
            break;
        case('-'):
            result = subtraction(&operand1, &operand2);
            break;
        case('*'):
            result = multiplication(&operand1, &operand2);
            break;
        case('/'):
            result = division(&operand1, &operand2);
            if(result == NULL){
                // Handle divide by zero error
                printf("Error: Division by zero\n");
                return NULL;
            }
            break;
        default:
            break;
    }

    return result;
}


//function for reading the input char by char and creating LL
//also for pushing operator and operands into stack
//carrying out calculation along the way
node* evaluate_expression(char input[]) {

    // Check for consecutive operators
    if (has_consecutive_operators(input)) {
        // Handle error and return NULL or an appropriate error code
        return NULL;
    }

    /***intializing a linked list for each number in the input string***/

    //count the number of operators
    int count = 0, k = 0;
    while(input[k] != '\0'){
        if(is_operator(input[k])){
            count++;
        }
        k++;
    }

    //mallocing an array of linkedlists(one for each operand)
    node **LL_pointer = (node **)malloc(sizeof(node*) * (count + 1));
    //initializing all the LL
    for(int i = 0; i < count + 1; i++){
        init(&LL_pointer[i]);
    }

    /***declaring and initializing stacks for operand and operator***/
    operator_stack s1;
    init_operator_stack(&s1, LIMIT);
    operand_stack s2;
    init_operand_stack(&s2, LIMIT);


    node* operand1 = NULL,*operand2 = NULL, *result = NULL;
    int j = 0; //for travering the array of LL
    int i = 0; //for the input string
    while(input[i] != '\0'){

        //in case of an operand
        if(is_operand(input[i])){

            //we loop inside again to get the whole operand
            do{
                //inserting elements in LL in REVERSE order for easier calculations ahead
                insert_at_beginning(&LL_pointer[j], input[i] - '0'); //converted char to int in the second paramenter
                i++; //moving the input pointer
            }while(is_operand(input[i]));
            push_operand(&s2, LL_pointer[j]);
            j++; //incremented LL array pointer to start filling the next LL
        }
        else if(is_operator(input[i])){ // incase of operators
            //in case of empty stack just push it
            if(is_empty_operator(&s1) == 1){
                push_operator(&s1, input[i]);
                i++;
            }
            else{
                while(is_empty_operator(&s1) != 1 && precedence(input[i]) <= precedence(peek_operator(&s1))){
                    char operator = pop_operator(&s1);
                    operand2 = pop_operand(&s2); //the lastest operand will be at the top
                    operand1 = pop_operand(&s2);
                    result = calculations(operand1, operand2, operator);
                    push_operand(&s2, result);
                }
                push_operator(&s1, input[i]);
                i++;
            }
        }
        else{
            i++; //the case of whitespaces
        }
    }

    //emptying the stack
    while(is_empty_operator(&s1) != 1){
        char operator = pop_operator(&s1);
        operand2 = pop_operand(&s2); //the lastest operand will be at the top
        operand1 = pop_operand(&s2);
        result = calculations(operand1, operand2, operator);
        push_operand(&s2, result);
    }

    // Free the memory allocated for linked lists
    for (int i = 0; i < count + 1; i++) {
        free_list(LL_pointer[i]);  // Assuming you have a function to free the linked list
    }
    free(LL_pointer);

   //the only LL in the node stack would be the final result 
   return pop_operand(&s2);
}