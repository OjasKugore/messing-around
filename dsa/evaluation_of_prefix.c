#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

#define SIZE 20

struct stack {
    int top;
    float data[SIZE];
};

typedef struct stack STACK;

void push(STACK *s, float item) {
    if (s->top >= SIZE - 1) {
        printf("Error: Stack Overflow\n");
        exit(1);
    }
    s->data[++(s->top)] = item;
}

float pop(STACK *s) {
    if (s->top < 0) {
        printf("Error: Stack Underflow\n");
        exit(1);
    }
    return s->data[(s->top)--];
}

float operate(float op1, float op2, char symbol) {
    switch (symbol) {
        case '+': return op1 + op2;
        case '-': return op1 - op2;
        case '*': return op1 * op2;
        case '/': 
            if (op2 == 0) {
                printf("Error: Division by zero\n");
                exit(1);
            }
            return op1 / op2;
        case '^': return pow(op1, op2);
        default:
            printf("Error: Invalid operator '%c'\n", symbol);
            exit(1);
    }
}

float eval(STACK *s, char prefix[SIZE]) {
    int i;
    char symbol;
    float res, op1, op2;

    for (i = (int)strlen(prefix) - 1; i >= 0; i--) {
        symbol = prefix[i];
        if (isdigit(symbol)) {
            push(s, symbol - '0');
        } else {
            op1 = pop(s);
            op2 = pop(s);
            res = operate(op1, op2, symbol);
            push(s, res);
        }
    }
    return pop(s);
}

int main() {
    char prefix[SIZE];
    STACK s;
    float ans;

    s.top = -1;
    printf("Read prefix expr: ");
    if (scanf("%19s", prefix) != 1) {
        printf("Error reading input.\n");
        return 1;
    }

    ans = eval(&s, prefix);
    printf("\nThe final answer is: %f\n", ans);
    return 0;
}

