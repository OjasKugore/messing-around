#include <stdio.h>

#define MAX 5

typedef struct stack{
    int array[MAX];
    int top;
} Stack;

void init(Stack *s) {
    s->top = -1;
}

void push(Stack *s, int val) {
    if (s->top == MAX - 1) {
        printf("Stack Overflow! Cannot push %d.\n", val);
        return;
    }
    s->array[++(s->top)] = val;
    printf("%d pushed to stack.\n", val);
}

void pop(Stack *s) {
    if (s->top == -1) {
        printf("Stack Underflow! Stack is empty.\n");
        return;
    }
    printf("%d popped from stack.\n", s->array[(s->top)--]);
}

void peek(Stack *s) {
    if (s->top == -1) {
        printf("Stack is empty! Nothing to peek.\n");
        return;
    }
    printf("Top element is: %d\n", s->array[s->top]);
}

void display(Stack *s) {
    if (s->top == -1) {
        printf("Stack is empty.\n");
        return;
    }
    printf("Stack elements (top to bottom):\n");
    for (int i = s->top; i >= 0; i--) {
        printf("| %d |\n", s->array[i]);
    }
    printf("-----\n");
}

int main() {
    Stack s;
    init(&s);

    int choice, val;

    while (1) {
        printf("\n--- STACK MENU ---\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Peek\n");
        printf("4. Display\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Exiting.\n");
            break;
        }

        switch (choice) {
            case 1:
                printf("Enter value to push: ");
                if (scanf("%d", &val) == 1) {
                    push(&s, val);
                } else {
                    printf("Invalid value.\n");
                    while (getchar() != '\n'); 
                }
                break;

            case 2:
                pop(&s);
                break;

            case 3:
                peek(&s);
                break;

            case 4:
                display(&s);
                break;

            case 5:
                printf("Exiting program.\n");
                return 0;

            default:
                printf("Invalid choice! Please select between 1 and 5.\n");
                break;
        }
    }

    return 0;
}