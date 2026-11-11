
#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    int items[MAX];
    int front;
    int rear;
    int counter;
} cq;

void init(cq *c) {
    c->front = 0;
    c->rear = -1;
    c->counter = 0;
}

int isFull(cq *c) {
    return c->counter == MAX;
}

int isEmpty(cq *c) {
    return c->counter == 0;
}

int enqueue(cq *c, int x) {
    if (isFull(c))
        return 0;

    c->rear = (c->rear + 1) % MAX;
    c->items[c->rear] = x;
    c->counter++;
    return 1;
}

int dequeue(cq *c) {
    if (isEmpty(c))
        return 0;

    c->front = (c->front + 1) % MAX;
    c->counter--;
    return 1;
}

void display(cq *c) {
    if (isEmpty(c)) {
        printf("Queue is empty\n");
        return;
    }

    for (int i = 0; i < c->counter; i++) { //retrryyyyyy
        int index = (c->front + i) % MAX;
        printf("%d -> ", c->items[index]);
    }
    printf("NULL\n");
}
