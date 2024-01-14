#include <stdlib.h>
#include "linked_list.h"

//def for initialization
void init(node **head){
    *head = NULL;
}

void insert_at_beginning(node **head, int d){
    //creating the node
    node *nn = (node*)malloc(sizeof(node));
    if(nn == NULL){
        return;
    }

    nn->next = (*head)->next;
    *head = nn;
}

void traverse(node **head){
    return;
}