#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int item;
    struct node * next;
    struct node * prev;
} Node;

//add a new node to end of list or create if not exists
Node * create_node(Node * head, int data){
    Node * new;
    new = malloc (sizeof(Node));
    if ( new == NULL){
        printf("Memory not allocated.\n");
        return head;
    }
    new -> item = data;
    new -> next =NULL;
    new -> prev = NULL;

    if ( head == NULL){
        head = new;
        return head;
    }

    Node * temp = head;
    while (temp -> next != NULL){
        temp = temp ->next;
    }
    temp -> next = new;
    new -> prev = temp;
    new -> next = NULL;

    return head;
}

void traverse_list(Node * head){
    if (head == NULL){
        printf("List is empty.\n");
        return;
    }

    Node * temp = head;
    printf("The linked list is: \n");
    printf("NULL <=> ");
    while (temp != NULL){
        printf("%d <=> ", temp->item);
        temp = temp->next;
    }
    printf("NULL\n");
}


Node * insert_beginning(Node * head, int data){
    if (head ==NULL){
        head = create_node(head, data);
        return head;
    }

    Node * new;
    new = malloc ( sizeof(Node));
    if ( new == NULL){
        printf("Memory not allocated.\n");
        return head;
    }
    new -> item = data;
    new -> next = NULL;
    new -> prev = NULL;

    new -> next = head;
    new -> prev = NULL;
    head -> prev = new;
    head = new;
    return head;
}

Node * insert_at_position(Node * head, int data, int pos){
    if (pos == 1 || head ==NULL){
        head = insert_beginning(head, data);
        return head;
    }
    Node * new;
    new = malloc(sizeof(Node));
    if ( new == NULL){
        printf("Memory not allocated.\n");
        return head;
    }
    new -> item = data;
    Node * temp = head;
    for ( int i = 1; i < pos -1 && temp != NULL; i++)
    {
        temp = temp -> next;
    }
    if (temp == NULL){
        printf("Invalid Position.\n");
        free(new);
        return head;
    }

    new -> next = temp -> next;
    new -> prev = temp;
    temp -> next = new;
    if (new-> next != NULL){
        new -> next -> prev = new;
    }
    return head;
}

Node * delete_from_beginning(Node * head){
    if (head == NULL){
        printf("Cannot delete form an empty list.\n");
        return head;
    }
    Node * temp = head;
    if (head -> next == NULL){
        free(head);
        printf("List is now empty.\n");
        return NULL;
    }
    temp -> next -> prev = NULL;
    temp = head -> next;
    free(head);
    return temp;

}

Node * delete_from_end(Node * head){
    if ( head ==NULL){
        printf("Cannot delete form an empty list.\n");
        return head;
    }
    if ( head -> next == NULL){
        return delete_from_beginning(head);
    }
    Node * temp = head;
    while ( temp -> next != NULL){
        temp = temp -> next;
    }
    temp -> prev -> next = NULL;
    free(temp);
    return head;
}

Node * delete_at_position(Node * head, int pos){
    if ( head == NULL){
        printf("Cannot delete form an empty list.\n");
        return head;
    }
    if ( pos == 1 || head -> next == NULL){
        return delete_from_beginning(head);
    }
    Node * curr, * prev;
    curr = head;
    prev = head;
    for ( int i = 1; i< pos && curr != NULL; i++){
        prev = curr;
        curr = curr -> next;
    }
    if (curr ==NULL){
        printf("Invalid Position.\n");
        return head;
    }
    prev -> next = curr -> next;
    if (curr -> next != NULL){
        curr -> next -> prev = prev;
    }
    free(curr);
    return head;
}


int main(){
    Node * head = NULL;

    head = create_node(head, 5);
    traverse_list(head);

    head = create_node(head, 10);
    traverse_list(head);

    head = insert_beginning(head, 1);
    traverse_list(head);

    head = insert_beginning(head, 35);
    traverse_list(head);

    head = insert_beginning(head, 89);
    traverse_list(head);

    head = insert_at_position(head, 25, 1);
    traverse_list(head);
    
    head = delete_from_beginning(head);
    traverse_list(head);

    head = delete_from_end(head);
    traverse_list(head);

    head = delete_at_position(head, 3);
    traverse_list(head);
}