#ifndef LIBRARY_H
#define LIBRARY_H

#include <vector>
#include <memory>
#include "inventoryy.h"
#include "Book.h"
#include "filestorage.h"

// Library Class: Adheres to the Liskov Substitution Principle (LSP)
// Can be used interchangeably with the InventoryManager interface.
class Library : public InventoryManager {
public:
    // Constructor to initialize the library with a storage mechanism
    Library(unique_ptr<FileStorageBase> storage) : storage(std::move(storage)) {}

    // Add a book to the library inventory
    void addBook(const Book& book) override {
        inventory.push_back(book);
    }

    // Display the library inventory
    void displayInventory() const override {
        for (const auto& book : inventory) {
            cout << "Title: " << book.getTitle() << ", Author: " << book.getAuthor()
                 << ", Price: " << book.getPrice() << ", Quantity: " << book.getQuantity() << endl;
        }
    }

    // Update the stock of a book
    bool updateStock(const string& title, int quantity) override {
        for (auto& book : inventory) {
            if (book.getTitle() == title) {
                book.setQuantity(book.getQuantity() + quantity);
                return true;
            }
        }
        return false;
    }

    // Sell a book from the library
    bool sellBook(const string& title) {
        for (auto& book : inventory) {
            if (book.getTitle() == title && book.getQuantity() > 0) {
                book.setQuantity(book.getQuantity() - 1);
                storage->saveToFile(inventory, "inventory.txt");  // Save changes to storage
                return true;
            }
        }
        return false;
    }

    // Get the library inventory
    const vector<Book>& getInventory() const { return inventory; }

    // Load inventory from a file
    void loadInventory(const string& filename) {
        auto books = storage->loadFromFile(filename);
        for (const auto& book : books) {
            addBook(book);
        }
        storage->saveToFile(inventory, "inventory.txt");
    }

private:
    vector<Book> inventory;  // Collection of books in the library
    unique_ptr<FileStorageBase> storage;  // Storage mechanism (local or cloud)
};



#endif // LIBRARY_H
