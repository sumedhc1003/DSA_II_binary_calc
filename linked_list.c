#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

//def for initialization
void init(node **head){
    *head = NULL;
}

//appending at the end of LL
node* append_at_end(node **head, int d){
    
    // creating and initializing the new node
    node *nn = (node*)malloc(sizeof(node));
    nn->data = d;
    nn->next = NULL;


    // If the linked list is empty, make the new node as the head
    if (*head == NULL) {
        *head = nn;
        return nn;
    }

    // Traverse the list to find the temp node
    node* temp = *head;  // To traverse the list
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = nn;

    return nn;
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

//counting the number of nodes
int count_nodes(node **head){

    node* ptr = *head;
    int size = 0;
    while (ptr) {
        ptr = ptr->next;
        size++;
    }
    return size;
}

int is_zero(node **head){
    node* ptr = *head;
    while(ptr){
        if(ptr->data != 0){
            return 0;
        }

        ptr = ptr->next;
    }
    return 1;
}

//function for freeing nodes
void free_list(node* head) {
    while (head != NULL) {
        node* temp = head;
        head = head->next;
        free(temp);
    }
}