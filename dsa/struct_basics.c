#include <stdio.h>
#include <string.h>

#define SIZE 50

typedef struct Book{
    char title[SIZE];
    char author[SIZE];
    int pages;
    float price;
} Book;

void print_price(float price){
    printf("Book price: %.2f\n", price);
}

void apply_discount(float *price, float percent){
    *price = *price - ((percent / 100) * (*price));
}

int main()
{
    
    Book b1 = {
        .title = "Moby Dick",
        .pages = 450,
        .author = "Herman Melville",
        .price = 670.00
    };

    Book b2;
    strcpy(b2.title, "Dracula");
    strcpy(b2.author, "Bram Stoker");
    b2.pages = 550;
    b2.price = 434.50;

    printf("Book 1 details==========\n");
    printf("Title: %s\n", b1.title);
    printf("Author: %s\n", b1.author);
    printf("Page count: %d\n", b1.pages);
    printf("Price: %f\n", b1.price);

    printf("Book 2 details==========\n");
    printf("Title: %s\n", b2.title);
    printf("Author: %s\n", b2.author);
    printf("Page count: %d\n", b2.pages);
    printf("Price: %f\n", b2.price);

    print_price(b1.price);
    print_price(b2.price);

    apply_discount(&b2.price, 50.00);
    printf("Price after discount: \n");
    print_price(b2.price);
}