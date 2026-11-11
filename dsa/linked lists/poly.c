
#include <stdio.h>
#include <stdlib.h>

typedef struct Poly {
    int exp, coef;
    struct Poly *next;
} poly;

poly* add(poly *head, int coef, int exp) {
    if (coef == 0)
        return head;

    poly *prev = NULL, *cur = head;

    while (cur != NULL && cur->exp > exp) {
        prev = cur;
        cur = cur->next;
    }

    if (cur != NULL && cur->exp == exp) {
        cur->coef += coef;

        if (cur->coef == 0) {
            if (prev == NULL)
                head = cur->next;
            else
                prev->next = cur->next;

            free(cur);
        }

        return head;
    }

    poly *term = malloc(sizeof(poly));
    if (term == NULL)
        return head;

    term->coef = coef;
    term->exp = exp;
    term->next = cur;

    if (prev == NULL)
        return term;

    prev->next = term;
    return head;
}

poly* mult(poly *a, poly *b) {
    poly *result = NULL;

    for (poly *p = a; p != NULL; p = p->next) {
        for (poly *q = b; q != NULL; q = q->next) {
            result = add(result,
                         p->coef * q->coef,
                         p->exp + q->exp);
        }
    }

    return result;
}

void print(poly *head) {
    poly *cur = head;

    while (cur != NULL) {
        printf("%dx^%d ", cur->coef, cur->exp);
        cur = cur->next;
    }

    printf("\n");
}

int main(void) {
    poly *head = NULL;

    head = add(head, 3, 2);
    head = add(head, 4, 1);
    head = add(head, 2, 0);

    print(head);

    return 0;
}
