#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

typedef struct stack {
    char array[MAX];
    int top;
} Stack;

void init(Stack *s) {
    s->top = -1;
}

void push(Stack *s, char val) {
    if (s->top == MAX - 1) {
        printf("Stack Overflow!\n");
        return;
    }
    s->array[++(s->top)] = val;
}

void pop(Stack *s) {
    if (s->top == -1) {
        printf("Stack Underflow!\n");
        return;
    }
    s->top--;
}

int precedence(char op) {
    if (op == '^') {
        return 3;
    } else if (op == '*' || op == '/' || op == '%') {
        return 2;
    } else if (op == '+' || op == '-') {
        return 1;
    }
    return 0;
}

void infixToPostfix(char infix[], char postfix[]) {
    Stack s;
    init(&s);
    int i = 0, k = 0;

    while (infix[i] != '\0') {
        char ch = infix[i];

        if (!isspace((unsigned char)ch)) {
            if (isalnum(ch)) {
                postfix[k++] = ch;
            } else if (ch == '(') {
                push(&s, ch);
            } else if (ch == ')') {
                while (s.top != -1 && s.array[s.top] != '(') {
                    postfix[k++] = s.array[s.top];
                    pop(&s);
                }
                if (s.top != -1 && s.array[s.top] == '(') {
                    pop(&s);
                }
            } else {
                while (s.top != -1 && s.array[s.top] != '(' &&
                       (precedence(s.array[s.top]) > precedence(ch) ||
                       (precedence(s.array[s.top]) == precedence(ch) && ch != '^'))) {
                    postfix[k++] = s.array[s.top];
                    pop(&s);
                }
                push(&s, ch);
            }
        }
        i++;
    }

    while (s.top != -1) {
        if (s.array[s.top] != '(' && s.array[s.top] != ')') {
            postfix[k++] = s.array[s.top];
        }
        pop(&s);
    }

    postfix[k] = '\0';
}

int main() {
    char infix[MAX];
    char postfix[MAX];

    printf("Enter Infix Expression: ");
    if (fgets(infix, sizeof(infix), stdin) != NULL) {
        infix[strcspn(infix, "\n")] = '\0';

        infixToPostfix(infix, postfix);

        printf("Infix Expression   : %s\n", infix);
        printf("Postfix Expression : %s\n", postfix);
    }

    return 0;
}
