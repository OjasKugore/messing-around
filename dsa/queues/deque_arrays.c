#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct{
    int items[MAX];
    int front;
    int rear;
    int counter;
}deque;

void init(deque* q){q -> counter = 0; q -> front = 0; q -> rear = -1;}
int isEmpty(deque *q){return q -> counter == 0;}
int isFull(deque * q){return q -> counter == MAX;}

int insert_rear(deque *q, int x){
    if (isFull(q)){return 0;}

    if(isEmpty(q)){
        q -> front = q -> rear = 0;
    }
    else{                                                   //IMPORTANT
        q -> rear = ((q -> rear + 1) %MAX);
    }
    q -> items[q -> rear] = x;
    q ->counter +=1;
    return 1;
}

int insert_front(deque * q, int x){
    if (isFull(q)){return 0;}

    if (isEmpty(q)){                                        //IMPORTANT
        q -> front = q -> rear = 0;
    }
    else{
        q -> front = ((q -> front -1 + MAX) % MAX);
    }
    q -> items[q ->front] = x;
    q -> counter +=1;
    return 1;
}

int delete_front(deque *q, int *x){
    if (isEmpty(q)) return 0;

    *x = q -> items[q ->front];
    q -> front = ((q -> front +1) %MAX);
    q ->counter -=1;
    return 1;
}

int delete_rear(deque * q, int *x){
    if (isEmpty(q)) return 0;

    *x = q ->items[q ->rear];
    q -> rear = ((q -> rear -1 + MAX) % MAX); 
    q -> counter -=1;
    return 1;
}

