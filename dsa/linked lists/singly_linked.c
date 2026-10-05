#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int item;
    struct node *next;
} Node;

//add new node at the end of the list or create one
Node * create_node(Node *head, int data){
    //alocate memory for the node
    Node * new;
    new = malloc(sizeof(Node));
    if (new == NULL){
        printf("Memory not allocated.\n");
        return head;
    }
    new -> item = data;
    new -> next = NULL;

    if (head == NULL){
        head = new;
    }
    else{
        Node *temp = head;
        while (temp -> next != NULL){
            temp = temp -> next;
        }
        temp -> next = new;
    }
    return head;
}

void traverse_list(Node *head){
    Node *temp = head;
    printf("The current linked list is: \n");
    while (temp != NULL){
        printf(" %d -> ", temp -> item);
        temp = temp -> next;
    }
    printf("NULL\n");
}

Node * insert_beginning(Node * head, int data){
    Node *new = NULL;
    new = malloc(sizeof(Node));
    if (new == NULL){
        printf("Memory not allocated.\n");
        return head;
    }
    new -> item = data;
    new -> next = head;
    head = new;
    return head;
}

Node * insert_at_position(Node *head, int data, int pos){
    if (pos <= 1 || head == NULL) {
        return insert_beginning(head, data);
    }

    Node *new = malloc(sizeof(Node));
    if (new == NULL){
        printf("Memory not allocated.\n");
        return head;
    }
    new->item = data;

    Node *temp = head;
    for (int i = 1; i < pos -1  && temp->next != NULL; i++){
        temp = temp->next;
    }

    new->next = temp->next;
    temp->next = new;

    return head;
}

Node * insert_at_end(Node *head, int data){
    Node * new = NULL;
    new = malloc(sizeof(Node));
    if (new == NULL){
        printf("Memory not allocated!\n");
        return head;
    }
    new ->item = data;
    new -> next = NULL;
    if(head == NULL){
        return new;
    }
    Node * temp = head;
    while ( temp -> next != NULL){
        temp = temp -> next;
    }
    temp -> next = new;
    new -> next = NULL;
    return head;
}

Node * delete_from_beginning(Node * head){
    Node * temp;
    if (head == NULL){
        printf("Cannot delete form an empty list.\n");
        return head;
    }
    temp = head -> next;
    free(head);
    head = NULL;
    return temp;
}

Node * delete_from_end(Node * head){
    Node * temp = head;
    Node * ptemp = head;
    if (temp == NULL){
        printf("Cannot delete from an empty list.\n");
        return head;
    }
    if (temp -> next == NULL){
        free(head);
        return NULL;
    }
    while (temp -> next != NULL){
        ptemp = temp;
        temp = temp -> next;
    }
    ptemp -> next = NULL;
    free(temp);
    temp = NULL;
    return head;
}

Node * delete_at_position(Node * head, int pos){
    Node * temp, * ptemp;
    if (head == NULL){
        printf("Cannot delete from an empty list.\n");
        return head;
    }
    temp = head;
    ptemp = head;

    if (pos == 1){
        printf("Invalid Position.\n");
        return head;
    }

    for ( int i =1; i < pos && temp != NULL; i++){
        ptemp = temp;
        temp = temp -> next;
    }

    if (temp == NULL){
        printf("Invalid Position. ( out of bounds)\n");
        return head;
    }

    ptemp -> next = temp ->next;
    free(temp);
    return head;

}


int main(){
    Node *head = NULL;
    head = create_node(head, 10);
    traverse_list(head);
    
    head = insert_beginning(head, 5);
    traverse_list(head);

    head = insert_at_position(head, 7, 2);
    traverse_list(head);

    head = insert_at_end(head, 20);
    traverse_list(head);

    head = delete_from_beginning(head);
    traverse_list(head);

    head = delete_from_end(head);
    traverse_list(head);

    head = delete_at_position(head, 2);
    traverse_list(head);
}