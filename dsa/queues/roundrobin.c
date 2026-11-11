#include <stdio.h>
#include <stdio.h>

#define MAX 100

typedef struct{
    int items[MAX]; //stores pids
    int front; 
    int rear;
    int counter;
} queue;

void init(queue * q){ q -> front = 0; q -> rear = -1; q -> counter = 0;}
int isEmpty(queue * q){return q -> counter == 0;}
int isFull (queue * q){ return q ->counter == MAX;}

void enqueue(queue * q, int x){
    if (isFull(q)) return;
    q -> rear = ((q -> rear +1) % MAX);
    q -> items[q -> rear] = x;
    q ->counter +=1;
}

int dequeue(queue *q){
    if (isEmpty(q)) return 0;

    int process = q -> items[q -> front];
    q -> front = ((q -> front +1 + MAX) % MAX);
    q -> counter -=1;
    return process;
}

void round_robin(int burst[], int finish[], int quantum, int n){
    int remaining[MAX];
    int time = 0;
    queue ready;
    init(&ready);

    //copy from burst to reamining
    for (int i = 0; i < n; i++){
        remaining[i] = burst[i];
        enqueue(&ready, i);
    }

    while(!isEmpty(&ready)){
        int p = dequeue(&ready);

        int run;
        if(remaining[p] >= quantum){
            run = quantum;
        }
        else{
            run = remaining[p];
        }

        time += run;
        remaining[p] -= run; //deduct runtime from remaining

        if (remaining[p] > 0){
            enqueue(&ready, p);
        }
        else{
            finish[p] = time;
        }
    }
}