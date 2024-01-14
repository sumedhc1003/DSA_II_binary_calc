#include<stdlib.h>
#include "linked_list.c"
#include "expression_evaluation.h"

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


//function for reading the input char by char and creating LL
//also for pushing operator and operands into stack
//carrying out calculation along the way
node* evaluate_expression(char input[]) {

    /*


    //intializing a linked list for each number in the input string

    //count the number of operators
    int count = 0;
    while(input[i] != '\0'){
        if(is_operator(input[i])){
            count++
        }
        i++;
    }

    //mallocing an array of linkedlists(one for each operand)
    node **LL_pointer = (node **)malloc(sizeof(node*) * (count + 1));
    //initializing all the LL
    for(int i = 0; i < count + 1; i++){
        init(&LL_pointer[i]);
    }

    int j = 0; //for travering the array of LL
    int i = 0; //for the input string
    while(input[i] != '\0'){

        //in case of an operand
        if(is_operand(input[i])){
            //inserting elements in LL in REVERSE order for easier calculations ahead
            insert_at_beginning(&LL_pointer[j], input[i] - '0'); //converted char to int in the second paramenter
        }

    }

    */
   return NULL;
}