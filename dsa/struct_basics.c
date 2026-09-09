#include <stdio.h>
#include <string.h>

#define SIZE 50

typedef struct Book{
    char title[SIZE];
    char author[SIZE];
    int pages;
    float price;
} Book;

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
}