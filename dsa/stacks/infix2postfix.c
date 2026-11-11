#include <stdio.h>
#include <ctype.h>
#define MAX 100

char stack[MAX];
int top = -1;

void push(char c) {
    if (top < MAX - 1)
        stack[++top] = c;
}

char pop(void) {
    if (top == -1)
        return '\0';
    return stack[top--];
}

char peek(void) {
    if (top == -1)
        return '\0';
    return stack[top];
}

int precedence(char op) {
    if (op == '^') return 3;
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

int isOperator(char c) {
    return c == '+' || c == '-' || c == '*' ||
           c == '/' || c == '^';
}

void infixToPostfix(char infix[]) {
    char postfix[MAX];
    int j = 0;

    top = -1;

    for (int i = 0; infix[i] != '\0'; i++) {
        char c = infix[i];

        if (isspace((unsigned char)c))
            continue;

        if (isalnum((unsigned char)c)) {
            postfix[j++] = c;
        }
        else if (c == '(') {
            push(c);
        }
        else if (c == ')') {
            while (top != -1 && peek() != '(')
                postfix[j++] = pop();

            if (top != -1)
                pop();  // Remove '('
        }
        else if (isOperator(c)) {
            while (top != -1 && peek() != '(' &&
                  (precedence(peek()) > precedence(c) ||
                  (precedence(peek()) == precedence(c)
                   && c != '^'))) {
                postfix[j++] = pop();
            }

            push(c);
        }
    }

    while (top != -1)
        postfix[j++] = pop();

    postfix[j] = '\0';

    printf("Postfix expression: %s\n", postfix);
}

int main(void) {
    char infix[MAX];

    printf("Enter infix expression: ");
    scanf("%99s", infix);

    infixToPostfix(infix);

    return 0;
}
