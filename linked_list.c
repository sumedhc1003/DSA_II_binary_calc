#include <stdio.h>
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
    nn->data = d;
    nn->next = NULL;

    nn->next = *head;
    *head = nn;
}

void traverse(node **head){
    printf("\nList: [");
    node *p = *head;
    while(p){
        printf("%d ", p->data);
        p = p->next;
    }
    printf("]\n");
    return;
}

void reverse_list(node** head)  //reverses list 
{
    node* prev = NULL;
    node* current = *head;
    node* next = NULL;
    while (current != NULL) 
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    *head = prev;
}