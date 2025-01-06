#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <fstream>
#include <sstream>
#include "Library.h"
// #include "filestorage.h"
// #include"book.h"
// #include "inventoryy.h"
using namespace std;


// Payment Interface: Adheres to the Dependency Inversion Principle (DIP)
// High-level modules depend on abstractions, not concrete implementations.
class Payment {
public:
    virtual bool processPayment(double amount) = 0;  // Process a payment
    virtual ~Payment() = default;  // Virtual destructor
};

// CashPayment Class: Implements the Payment interface for cash payments
class CashPayment : public Payment {
public:
    bool processPayment(double amount) override {
        cout << "Processing cash payment of $" << amount << endl;
        return true;
    }
};

// OnlinePayment Class: Implements the Payment interface for online payments
class OnlinePayment : public Payment {
public:
    bool processPayment(double amount) override {
        cout << "Processing online payment of $" << amount << endl;
        return true;
    }
};

// Customer Class: Manages customer interactions with the library
class Customer {
public:
    // Constructor to initialize customer with a payment method
    Customer(const string& name, shared_ptr<Payment> paymentMethod) : name(name), paymentMethod(paymentMethod) {}

    // Buy a book from the library
    bool buyBook(Library& library, const string& title) {
        for (const auto& book : library.getInventory()) {
            if (book.getTitle() == title) {
                if (paymentMethod->processPayment(book.getPrice())) {
                    if (library.sellBook(title)) {
                        cout << name << " bought " << title << endl;
                        return true;
                    } else {
                        cout << "Book out of stock!" << endl;
                    }
                }
            }
        }
        cout << "Book not found in inventory!" << endl;
        return false;
    }

private:
    string name;  // Customer name
    shared_ptr<Payment> paymentMethod;  // Payment method
};

int main() {
    // Create a unique pointer to file storage
    unique_ptr<FileStorageBase> fileStorage = make_unique<FileStorageFromFile>();

    Library library(move(fileStorage));

    // Load inventory from file
    library.loadInventory("inventory.txt");

    // Customer buys a book
    shared_ptr<Payment> payment = make_shared<CashPayment>();
    string name,title;


    cout<<"enter your name: ";
    std::getline(std::cin,name);
    cout<<"welcome to library! "<<name<<endl;
    cout << "Current Inventory:\n";
    library.displayInventory();
    cout<<"enter book you want to buy: ";
    std::getline(std::cin,title);
    

    Customer customer(name, payment);
    customer.buyBook(library, title);
    cout<<"\nthank you for visiting!!";

    return 0;
}
