/*
The driver file of the calculator
*/


#include <stdio.h>
#include "expression_evaluation.h"
#include "linked_list.h"
#define SIZE 200


int main() {
    char input[SIZE];
    node *result;

    // creating an environment wherein the user remains in calcutor
    // until the user press 'q'
    printf("////////////////////////////////////////////////////////////////////////////////////\n");
    printf("---------------------------- Binary Calculator -------------------------------------\n");
    printf("////////////////////////////////////////////////////////////////////////////////////\n");
    

    while(1){
        printf("\nType in the expression to be evaluted and hit enter to get the result on next line\n");
        printf("press 'q' to exit the environment\n");
        fgets(input, SIZE, stdin);

        //quit in case of 'q'
        if(input[0] == 'q'){
            return 0;
        }

        // evaluating the input and return a pointer to the result linked list
        result = evaluate_expression(input);

        //exception handling
        if(result == NULL){
            return 1;
        }

        //printing the result
        reverse_list(&result);
        traverse(&result);
    }

    
    return 0;
}