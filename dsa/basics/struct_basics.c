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


void inspect_and_tamper(Book b){
    printf("INSIDE TAMPERING FUNCTION(PBV)=====\n");
    printf("Title: %s\n", b.title);
    printf("Author: %s\n", b.author);
    printf("Pages: %d\n", b.pages);
    printf("Price: %f\n", b.price);
    b.price = 0.0f;
    b.pages = 0;
}

void print_book_fast(const Book *b){
    printf("INSIDE CHECKING FUNCTION(PBR)=====\n");
    printf("Title: %s\n", b -> title);
    printf("Author: %s\n", b -> author);
    printf("Pages: %d\n", b -> pages);
    printf("Price: %f\n", b -> price);
}

void update_price(Book *b)
{
    b -> price = 1000.00;
}

const Book* most_expensive(const Book book_array[], int size){
    const Book* pricey;
    float max = 0;
    for (int i = 0; i < size; i++){
        if (book_array[i].price > max){
            pricey = &book_array[i];
            max = book_array[i].price;
        }
    }
    return pricey;
}

void apply_discount_for_array(Book book_array[], int size, float discount){
    for (int i = 0; i < size; i++)
    {
        book_array[i].price = book_array[i].price - (discount/100)*(book_array[i].price);
    }
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

    inspect_and_tamper(b1);
    printf("After tampering using PBV=====\n");
    printf("Title: %s\n", b1.title);
    printf("Author: %s\n", b1.author);
    printf("Pages: %d\n", b1.pages);
    printf("Price: %f\n", b1.price);

    print_book_fast(&b2);

    update_price(&b2);
    printf("Price of Book 2 after updation(PBR): %0.2f\n", b2.price);


    //array of structs
    Book inventory[3] = {
        {"1984", "George Orwell", 328, 299.99},
        {"To Kill a Mockingbird", "Harper Lee", 281, 399.50},
        {"The Great Gatsby", "F. Scott Fitzgerald", 180, 249.00}
    };

    printf("Priciest book is: %s\n", most_expensive(inventory, 3) -> title);
    printf("Price: %.2f\n", most_expensive(inventory, 3) -> price);

    printf("After applying 50 percent discount:\n");
    apply_discount_for_array(inventory, 3, 50);
    for (int i = 0; i < 3; i++){
        printf("Price of Book %d: %.2f\n", i, inventory[i].price);
    }
}