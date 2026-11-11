#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int data;
    struct Node *next;
}node;

typedef struct{
    node * front;
    node * rear;
} lq;

void init(lq * q){q -> front = NULL; q -> rear = NULL;}
int isEmpty( lq * q){return q -> front == NULL;}

int enqueue(lq * q, int x){
    node * new = (node *)malloc(sizeof(node));
    if (new == NULL) return 0;

    new -> data = x;
    new -> next = NULL;

    if (q -> front == NULL && q -> rear == NULL){q -> front = new; q -> rear = new;}
    else{
        q -> rear -> next = new;
        q -> rear = new;
    }
    return 1;
}

int dequeue(lq *q, int *x){
    if (isEmpty(q)) return 0;
    node * temp = q -> front;
    q -> front = q -> front -> next;
    *x = temp -> data;
    free(temp);

    if(q -> front == NULL) q -> rear = NULL;
    return 1;
}