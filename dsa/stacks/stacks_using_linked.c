#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *next;
} Node;

typedef struct {
    Node *top;
} Stack;

void push(Stack *s, int item) {
    Node *newNode = malloc(sizeof(Node));

    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }

    newNode->data = item;
    newNode->next = s->top;
    s->top = newNode;

    printf("%d pushed to stack.\n", item);
}

void print_stack(Stack *s) {
    Node *temp = s->top;

    printf("Stack is:\n");

    while (temp != NULL) {
        printf("%d\n", temp->data);
        temp = temp->next;
    }
}

void pop(Stack *s) {
    if (s->top == NULL) {
        printf("Stack Underflow!\n");
        return;
    }

    Node *temp = s->top;

    printf("Item %d popped from stack.\n", temp->data);

    s->top = s->top->next;
    free(temp);
}

int peek(Stack *s) {
    if (s->top == NULL) {
        printf("Stack Underflow!\n");
        return -1;
    }

    return s->top->data;
}

int main(void) {
    Stack *s = malloc(sizeof(Stack));

    if (s == NULL)
        return 1;

    s->top = NULL;

    push(s, 10);
    push(s, 20);
    push(s, 30);

    print_stack(s);

    pop(s);
    print_stack(s);

    printf("Item at the top of the stack is %d\n", peek(s));

    print_stack(s);

    // Free remaining nodes
    while (s->top != NULL)
        pop(s);

    free(s);

    return 0;
}