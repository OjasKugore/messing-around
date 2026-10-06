#include <stdio.h>
#include <stdlib.h>
#define MAX 100

typedef struct {
    int data[MAX];
    int top;
} Stack;

void push(Stack *s, int item){
    if (s->top == MAX - 1){
        printf("Stack Overflow!\n");
        return;
    }
    s -> top += 1;
    s -> data[s -> top] = item;
    printf("%d pushed to stack.\n", item);
}

void print_stack(Stack *s){
    printf("Stack is: \n");
    for(int i = s-> top; i > -1; i--){
        printf("%d\n", s -> data[i]);
    }
}

void pop(Stack *s){
    if (s -> top == -1){
        printf("Stack Underflow!\n");
        return;
    }
    printf("Item %d popped from stack.\n", s -> data[s -> top]);
    s -> top = s -> top - 1;
}

int peek(Stack * s){
    if (s -> top == -1){
        printf("Stack Underflow!\n");
        return -1;
    }
    return s -> data[s -> top];
}

int main(){
    Stack *s = malloc(sizeof(Stack));
    s -> top = -1;
    push(s, 10);
    push(s, 20);
    push(s, 30);
    print_stack(s);

    pop(s);
    print_stack(s);

    printf("Item at the top of the stack is %d\n", peek(s));
    print_stack(s);

    free(s);
}