# C Learning Roadmap & Practice Challenges

---

## Step 1: Pass by Value vs. Pass by Reference

### Objective
Understand how data moves in and out of functions in C.

### Key Concepts
1. **Pass by Value:**
   - Function receives an independent copy of the variable's value.
   - Any modifications inside the function do **NOT** affect the caller's variable.
   - Used for primitive data when the original value must remain unchanged.
2. **Pass by Reference (using Pointers):**
   - Function receives the memory address (`&variable`) instead of a copy.
   - Uses pointer syntax (`*`) to dereference and modify the original variable.
   - Used when a function needs to mutate data or return multiple outputs.

### Challenge Problem
Write a function:
```c
void swap_and_square(int *a, int *b);
```
- Swaps the values of two integers and replaces each with its square.
- Call it from `main()` with two variables and print their values before and after to prove that the caller's variables actually changed.

---

## Step 2: Passing Array Elements (Pass by Value vs. Reference)

### Objective
Learn how individual items inside an array behave when passed.

### Key Concepts
1. **Passing an element by value:**
   - e.g., `func(arr[0])` passes just the value stored at index 0.
   - Function cannot alter the element inside the original array.
2. **Passing an element by reference:**
   - e.g., `func(&arr[0])` passes the address of that specific slot.
   - Function can directly overwrite the value in the array.

### Challenge Problem
Given an integer array:
```c
int scores[5] = {45, 88, 32, 95, 60};
```
Write:
1. `void check_pass(int score)`: prints whether a single score is `>= 50` (pass by value).
2. `void apply_curve(int *score, int bonus)`: adds `bonus` points directly to a score, capped at 100 (pass by reference).

Pass `scores[2]` to `apply_curve(&scores[2], 25)` and verify the array slot was updated.

---

## Step 3: Passing a Whole Array

### Objective
Understand array decay and how arrays are received by functions.

### Key Concepts
1. **Array Decay:**
   - In C, an array name decays into a pointer to its first element when passed to a function (`arr` decays to `&arr[0]`).
2. **Syntax:**
   - `func(int arr[], int size)` OR `func(int *arr, int size)`.
3. **Important Rule:**
   - Arrays are **ALWAYS** passed by reference in C; modifying `arr[i]` inside the function modifies the original array!
   - You must always pass the size/length as a separate argument because the function only sees a pointer, not the array bounds.

### Challenge Problem
Write a function:
```c
void reverse_array(int arr[], int size);
```
- Reverses the elements of the array in-place without allocating a second array.
- In `main()`, print the array before and after calling `reverse_array()` to confirm in-place mutation.
- What does `sizeof(arr)` evaluate to inside `reverse_array` vs. in `main()`?

---

## Step 4: Structures (Basics & Definition)

### Objective
Learn how to group heterogeneous data types into a single unit.

### Key Concepts
1. **Defining a struct:**
   ```c
   struct student {
       int id;
       char name[50];
       float gpa;
   };
   ```
2. **Using typedef:**
   - Creating a clean alias:
     ```c
     typedef struct student Student;
     ```
     so you can declare variables as `Student s;` instead of `struct student s;`.
3. **Dot operator (`.`):**
   - Accessing fields directly on a struct variable (e.g., `s.id = 10;`).

### Challenge Problem
- Define a `typedef struct` named `Book` containing fields:
  - `title` (char array)
  - `author` (char array)
  - `pages` (int)
  - `price` (float)
- In `main()`, instantiate two `Book` variables—one initialized using designated initializers and the other populated field-by-field using the dot operator.
- Print out both book summaries.

---

## Step 5: Passing Individual Members of a Struct

### Objective
Treat struct fields like standard standalone variables.

### Key Concepts
1. **Passing by value:**
   - `func(s.id)` sends only the integer value of `id`.
2. **Passing by reference:**
   - `func(&s.id)` sends the memory address of the `id` field inside the struct, allowing the function to update that specific field.

### Challenge Problem
Using your `Book` struct from Step 4, write:
1. `void print_price(float price)`: prints the formatted price with currency.
2. `void apply_discount(float *price, float percent)`: takes a pointer to the price field and lowers it by `percent`.

In `main()`, pass `my_book.price` to `print_price`, then call `apply_discount(&my_book.price, 20.0f)`, and print `my_book.price` again to verify only that field changed.

---

## Step 6: Passing a Whole Struct (Pass by Value)

### Objective
Understand what happens when an entire struct is sent by value.

### Key Concepts
1. **Syntax:**
   ```c
   void display(Student s);
   ```
2. **Mechanism:**
   - C copies every single byte of the entire struct onto the call stack.
3. **Pros & Cons:**
   - **Pro:** Protects the caller's struct from accidental modification.
   - **Con:** Memory & performance overhead if the struct is large.

### Challenge Problem
Write a function:
```c
void inspect_and_tamper(Book b);
```
- Prints all details of `b`, then internally modifies `b.price = 0.0f` and `b.pages = 0`.
- In `main()`, print the book's details after calling `inspect_and_tamper(my_book)`.
- Confirm why the original book's fields remained intact despite the tampering.

---

## Step 7: Structure as a Pointer (Pass by Reference)

### Objective
Pass structs efficiently and enable in-place updates.

### Key Concepts
1. **Syntax:**
   ```c
   void update(Student *s);
   // Caller calls:
   update(&s);
   ```
2. **The Arrow Operator (`->`):**
   - Used to access fields through a pointer: `s->id` is shorthand for `(*s).id`.
3. **The `const` Qualifier:**
   ```c
   void print(const Student *s);
   ```
   - **Best Practice:** Fast like pass-by-reference (passes only an 8-byte address), safe like pass-by-value (compiler prevents changes to the struct).

### Challenge Problem
Write two functions:
1. `void print_book_fast(const Book *b)`: safely prints book info via arrow operator `->` without copying the entire struct, ensuring read-only safety.
2. `void update_price(Book *b, float new_price)`: mutates the book's price in-place.

Test both in `main()` using the address-of operator `&my_book`.

---

## Step 8: Array of Structures

### Objective
Manage multiple records in a single contiguous collection.

### Key Concepts
1. **Declaration:**
   ```c
   Student roster[50];
   ```
2. **Accessing elements & fields:**
   - `roster[i].id` (first index into the array, then dot into the struct).
3. **Passing array of structs to a function:**
   - `void print_roster(const Student roster[], int count);`
   - Combines array decay (decays to `Student*`) with struct indexing.
   - Passing an individual struct from the array:
     - By value: `func(roster[i]);`
     - By reference: `func(&roster[i]);`

### Challenge Problem
1. Create an array `Book inventory[3];` in `main()` and populate it.
2. Write a function:
   ```c
   const Book* find_most_expensive(const Book inventory[], int count);
   ```
   that iterates through the array and returns a pointer to the book with the highest price. In `main()`, print the title and price of the returned book using `->`.
3. Write a function:
   ```c
   void apply_storewide_discount(Book inventory[], int count, float percent);
   ```
   that applies a discount to all books in-place.

---

## Recommended Study Sequence

1. **Step 1 & 2:** Pointers with primitive variables and array elements.
2. **Step 3:** Pointers with whole arrays (array decay).
3. **Step 4 & 5:** Struct basics and passing individual fields.
4. **Step 6 & 7:** Struct pass-by-value vs. struct pointers (`->` operator).
5. **Step 8:** Combine everything into an array of structs.
