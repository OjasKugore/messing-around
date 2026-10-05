#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int item;
    struct node * next;
} Node;

//add a new node to the end of the list or create the list
Node * create_node(Node * head, int data){
    Node * new;
    new = malloc(sizeof(Node));
    if (new == NULL){
        printf("Memory not allocated.\n");
        return head;
    }
    new -> item = data;
    new -> next = NULL;

    if (head == NULL){
        new -> next = new;
        return new;
    }
    Node * temp = head;
    while(temp -> next != head){
        temp = temp -> next;
    }
    temp -> next = new;
    new -> next = head;
    return head;
}

void traverse_list(Node * head){
    Node * temp = head;
    if (temp == NULL){
        printf("The linked list is empty.\n");
        return;
    }
    printf("The circular linked list is: \n");
    while (temp -> next != head){
        printf(" %d -> ", temp -> item);
        temp = temp -> next;
    }
    printf(" %d -> %d\n", temp -> item, head -> item);
}

Node * insert_beginning(Node * head, int data){
    Node * new, *temp;
    new = malloc(sizeof(Node));
    if ( new ==NULL){
        printf("Memory not allocated.\n");
        return head;
    }
    new -> item = data;
    new -> next = NULL;
    if (head == NULL){
        new -> next = new;
        return new;
    }
    temp = head;
    while (temp -> next != head){
        temp = temp -> next;
    }
    temp -> next = new;
    new -> next = head;
    head = new;
    return new;
}

Node * insert_at_position(Node * head, int pos, int data){
    if (pos == 1 || head ==NULL){
        return insert_beginning(head,data);
    }
    Node * new, *temp;
    new = malloc(sizeof(Node));
    if ( new == NULL){
        printf("Memory not allocated");
        return head;
    }
    new -> item = data;
    new -> next = NULL;

    temp = head;
    for ( int i =1; i < pos-1 && temp -> next != head; i++){
        temp = temp -> next;
    }
    new -> next = temp -> next;
    temp -> next = new;

    return head;
    
}

Node * delete_from_beginning(Node * head){
    Node * temp = head;
    if ( temp == NULL){
        printf("Cannot delete from an empty list.\n");
        return head;
    }
    if ( temp -> next == head){
        free(head);
        return NULL;
    }
    while ( temp -> next != head){
        temp = temp -> next;
    }
    temp -> next = head -> next;
    free(head);
    return temp -> next;
}

//try to redo this
Node * delete_at_position(Node * head, int pos){
    if ( head == NULL){
        printf("Cannot delete from an empty linked list.\n");
        return head;
    }
    if (pos == 1){
        return delete_from_beginning(head);
    }
    Node * temp = head;
    Node * prev = head;
    int i;
    for (i = 1; i< pos && temp -> next != head; i++){
        prev = temp;
        temp  = temp -> next;
    }
    if (i < pos){
        printf("Invalid position.\n");
        return head;
    }
    prev -> next = temp -> next;
    free(temp);
    return head;
}

//retry
void search ( Node * head, int data){
    Node * temp = head;
    if ( head == NULL){
        printf("The linked list is empty.\n");
        return;
    }
    int counter = 1;
    int flag = 0;
    if (temp -> item == data){
        printf("Item found at position %d.\n", counter);
        flag = 1;
        return;
    }
    temp = temp -> next;
    counter = 2;
    while (temp != head && flag == 0){
        if (temp -> item == data){
            printf("Item found at position %d.\n", counter);
            flag = 1;
            break;
        }
        counter +=1;
        temp = temp -> next;
    }
    if (flag == 0){
        printf("Item not in the list.\n");
    }
}


//retry important
Node * reverse(Node * head){
    if (head == NULL){
        printf("Cannot reverse an empty list.\n");
        return head;
    }
    if (head->next == head){
        return head;
    }

    Node *prev = NULL;
    Node *curr = head;
    Node *next = NULL;

    do {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    } while (curr != head);

    head->next = prev;
    return head;
}

int main(){
    Node *head = NULL;
    head = create_node(head, 5);
    traverse_list(head);

    head = create_node(head, 10);
    traverse_list(head);

    head = create_node(head, 15);
    traverse_list(head);

    head = insert_beginning(head, 1);
    traverse_list(head);

    head = insert_at_position(head, 4, 20);
    traverse_list(head);

    head = delete_from_beginning(head);
    traverse_list(head);

    head = delete_at_position(head, 2);
    traverse_list(head);

    search(head, 15);

    head = reverse(head);
    traverse_list(head);
}