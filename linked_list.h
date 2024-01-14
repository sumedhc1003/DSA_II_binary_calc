
typedef struct node{
    int data;
    struct node *next;
}node;

void init(node **head);
void insert_at_beginning(node **head, int d);
void traverse(node **head);