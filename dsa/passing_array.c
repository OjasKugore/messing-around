#include <stdio.h>

#define SIZE 5

void reverse_array(int arr[], int size){
    int *first, *last;
    first = &arr[0];
    last = first + size - 1;
    int temp;
    while (first < last){
        temp = *first;
        *first = *last;
        *last = temp;

        first ++;
        last--;
    }
}

int main(){
    int arr[SIZE] = {34, 33, 422, 121, 44};

    printf("Before swapping\n");
    for (int i = 0; i<SIZE; i++)
    {
        printf("%d ", arr[i]);
    }

    reverse_array(arr, SIZE);

    printf("\nAfter swapping\n");
    for (int i = 0; i<SIZE; i++)
    {
        printf("%d ", arr[i]);
    }
}