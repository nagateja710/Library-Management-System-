#ifndef BOOK_H
#define BOOK_H

#include <string>  // Include only necessary headers
using namespace std;
// Book Class: Adheres to the Single Responsibility Principle (SRP)
// The Book class is responsible only for holding and managing book-related data.
class Book {
public:
    Book(const string& title, const string& author, double price, int quantity)
        : title(title), author(author), price(price), quantity(quantity) {}

    // Getter for the book title
    string getTitle() const { return title; }

    // Getter for the book author
    string getAuthor() const { return author; }

    // Getter for the book price
    double getPrice() const { return price; }

    // Getter for the book quantity
    int getQuantity() const { return quantity; }

    // Setter to update the quantity of the book
    void setQuantity(int qty) { quantity = qty; }

private:
    string title;   // Book title
    string author;  // Book author
    double price;   // Book price
    int quantity;   // Book quantity
};

#endif // BOOK_H
