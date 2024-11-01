#ifndef LINKED_LIST_H
#define LINKED_LIST_H
typedef struct node{
    int data;
    struct node *next;
}node;

void init(node **head);
void insert_at_beginning(node **head, int d);
node* append_at_end(node **head, int d);
void traverse(node **head);
void reverse_list(node **head);
int count_nodes(node **head);
int is_zero(node **head);
void free_list(node* head);

#endif