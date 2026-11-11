#include <stdio.h>
#include <stdlib.h>

typedef struct round {
    int et;                  // Execution time remaining
    int jobno;               // Job number
    struct round *next;
} rr;

rr *roundrob(rr *head, int ts) {
    if (head == NULL || ts <= 0)
        return head;

    int tt = 0;
    int run;

    rr *cur = head;
    rr *prev = head;

    // Find the last node
    while (prev->next != head)
        prev = prev->next;

    while (head != NULL) {
        // Execute for the smaller of et and ts
        if (cur->et < ts)
            run = cur->et;
        else
            run = ts;

        cur->et -= run;
        tt += run;

        if (cur->et == 0) {
            printf("Finished job %d at time %d\n",
                   cur->jobno, tt);

            // Only one node remains
            if (cur->next == cur) {
                free(cur);
                return NULL;
            }

            // Remove the completed node
            rr *temp = cur;
            prev->next = cur->next;

            // Update head if the first node finishes
            if (cur == head)
                head = cur->next;

            cur = cur->next;
            free(temp);
        } else {
            // Job is unfinished; move to the next job
            prev = cur;
            cur = cur->next;
        }
    }

    return head;
}

int main(void) {
    rr *p1 = malloc(sizeof(rr));
    rr *p2 = malloc(sizeof(rr));
    rr *p3 = malloc(sizeof(rr));

    if (p1 == NULL || p2 == NULL || p3 == NULL) {
        free(p1);
        free(p2);
        free(p3);
        return 1;
    }

    p1->jobno = 1;
    p1->et = 5;

    p2->jobno = 2;
    p2->et = 3;

    p3->jobno = 3;
    p3->et = 1;

    // Create circular linked list
    p1->next = p2;
    p2->next = p3;
    p3->next = p1;

    rr *head = p1;
    int ts = 2;

    head = roundrob(head, ts);

    return 0;
}