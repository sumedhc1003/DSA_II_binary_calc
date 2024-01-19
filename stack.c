#include "stack.h"
#include "linked_list.h"

//initiation function for both the stacks
void init_operator_stack(operator_stack* s, int d){
    s->size = d;
    s->top = -1;
    s->arr = (char*)malloc(sizeof(char) * d);
    return;
}

void init_operand_stack(operand_stack* s, int d){
    s->size = d;
    s->top = -1;
    s->arr = (node**)malloc(sizeof(node*) * d);
    return;
}

//empty condition check
int is_empty_operator(operator_stack* s){
    if(s->top == -1){
        return 1;
    }
    return 0;
}

int is_empty_operand(operand_stack* s){
    if(s->top == -1){
        return 1;
    }
    return 0;
}

//full condition check
int is_full_operator(operator_stack* s){
    if((s->size - 1) == s->top){
        return 1;
    }
    return 0;
}

int is_full_operand(operand_stack* s){
    if((s->size - 1) == s->top){
        return 1;
    }
    return 0;
}


//push function definitions

void push_operand(operand_stack* s, node *LL){
    if(is_full_operand(s) != 1){ //only when stack is not full
        s->top++;
        s->arr[s->top] = LL;
    }
    return;
}

void push_operator(operator_stack* s, char c){
    if(is_full_operator(s) != 1){
        s->top++;
        s->arr[s->top] = c;
    }
    return;
}

char peek_operator(operator_stack* s){
    if(is_empty_operator(s) == 1){
        return '\0';
    }
    return s->arr[s->top];
}

//pop functions
char pop_operator(operator_stack* s){
    if(is_empty_operator(s) == 1){
        return '\0';
    }

    return s->arr[s->top--]; //return the top char and then decrement the top
}

node* pop_operand(operand_stack* s){
    if(is_empty_operand(s) ==1){
        return NULL;
    }

    return s->arr[s->top--]; //return the top node pointer and then decrement
}