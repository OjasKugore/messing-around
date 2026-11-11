
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

int stack[MAX];
int top = -1;

void push(int x) {
    if (top < MAX - 1)
        stack[++top] = x;
}

int pop(void) {
    if (top == -1) {
        printf("Stack Underflow!\n");
        exit(1);
    }
    return stack[top--];
}

int evaluatePrefix(char exp[]) {
    int len = strlen(exp);
    top = -1;

    for (int i = len - 1; i >= 0; i--) {
        char c = exp[i];

        if (isspace((unsigned char)c))
            continue;

        if (isdigit((unsigned char)c)) {
            push(c - '0');
        }
        else {
            int a = pop();
            int b = pop();
            int result;

            switch (c) {
                case '+': result = a + b; break;
                case '-': result = a - b; break;
                case '*': result = a * b; break;

                case '/':
                    if (b == 0) {
                        printf("Division by zero!\n");
                        exit(1);
                    }
                    result = a / b;
                    break;

                default:
                    printf("Invalid operator!\n");
                    exit(1);
            }

            push(result);
        }
    }

    return pop();
}

int main(void) {
    char exp[MAX];

    printf("Enter prefix expression: ");
    fgets(exp, MAX, stdin);

    printf("Result = %d\n", evaluatePrefix(exp));

    return 0;
}
