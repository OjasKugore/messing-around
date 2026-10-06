#include <stdio.h>

void pbv(int a, int b){
   int temp;
   temp = a;
   a = b;
   b = temp;
   printf("Inside pass by value function\n");
   printf("Value of a: %d\n", a);
   printf("Value of b: %d\n", b);
}

void pbr(int *a, int *b){
   int temp;
   temp = *a;
   *a = *b;
   *b = temp;
   printf("Inside pass by reference function\n");
   printf("Value of a: %d\n", *a);
   printf("Value of b: %d\n", *b);
}

int main(){
   int a = 5;
   int b = 10;

   printf("Values before swapping: \n");
   printf("A: %d\n", a);
   printf("B: %d\n", b);

   pbv(a, b);

   printf("Values after swapping(pbv): \n");
   printf("A: %d\n", a);
   printf("B: %d\n", b);
   
   pbr(&a, &b);

   printf("Values after swapping(pbr): \n");
   printf("A: %d\n", a);
   printf("B: %d\n", b);

}