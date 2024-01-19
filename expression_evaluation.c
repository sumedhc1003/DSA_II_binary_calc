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
            return 5;
            break;

        case '-':
            return 5;
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

node* calculations(node* operand1, node* operand2, char operator){
    node* result;
    switch(operator){
        case('+'):
            result = addition(&operand1, &operand2);
            break;
        case('-'):
            //result = subtract_Two_Lists(&val1,&val2);
            break;
        case('*'):
            //result = multiply_Two_Lists(&val1,&val2);
            break;
        case('/'):
            //result = divide_Two_lists(&val1,&val2);
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
                    node* operand1 = pop_operand(&s2);
                    node* operand2 = pop_operand(&s2);
                    node* result = calculations(operand1, operand2, operator);
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
        node* operand1 = pop_operand(&s2);
        node* operand2 = pop_operand(&s2);
        node* result = calculations(operand1, operand2, operator);
        push_operand(&s2, result);
    }

   //the only LL in the node stack would be the final result 
   return pop_operand(&s2);
}