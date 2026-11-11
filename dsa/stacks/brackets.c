#include <stdio.h>
#include <stdlib.h>
#define MAX 100
int matches (char open, char close){
    return ((open == '(' && close == ')') ||
        (open == '{' && close == '}') ||
        (open == '[' && close == ']'));
}

int balanced(const char *text){
    char stack[MAX];
    int top = -1;
    for (int i = 0; text[i] != '\0'; i++){
        char c = text[i];
        if(c == '(' || c == '{' || c == '['){
            if (top == MAX-1){
                return 0;
            }
            stack[++top] = c;
        }
        else if (c == ')' || c == '}' || c == ']'){
            if (top == -1 || !matches(stack[top], c)) return 0;
            --top;
        }
    }
    return top == -1;
}

int main(){
    /* Edit this expression to try another example. */
    const char text[] = "{a + [b * (c - d";
    puts(balanced(text) ? "Balanced" : "Not balanced");
    return 0;
}