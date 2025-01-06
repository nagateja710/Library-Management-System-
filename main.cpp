#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <fstream>
#include <sstream>
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

// Inventory Management Interface: Adheres to the Interface Segregation Principle (ISP)
// Provides a specific interface for managing inventory-related operations.
class InventoryManager {
public:
    virtual void addBook(const Book& book) = 0;  // Adds a book to the inventory
    virtual void displayInventory() const = 0;  // Displays the inventory
    virtual bool updateStock(const string& title, int quantity) = 0;  // Updates stock for a book
    virtual ~InventoryManager() = default;  // Virtual destructor
};

// FileStorageBase Class: Adheres to the Open/Closed Principle (OCP)
// This class can be extended for different storage mechanisms without modifying existing code.
class FileStorageBase {
public:
    virtual void saveToFile(const vector<Book>& inventory, const string& filename) = 0;  // Save inventory to a file
    virtual vector<Book> loadFromFile(const string& filename) = 0;  // Load inventory from a file
    virtual ~FileStorageBase() = default;  // Virtual destructor
};

// FileStorageFromFile Class: Implements local file storage functionality
// Extends FileStorageBase for local file-based storage.
class FileStorageFromFile : public FileStorageBase {
public:
    // Save the inventory to a file (overwrites existing data)
    void saveToFile(const vector<Book>& inventory, const string& filename) override {
        ofstream file(filename);
        if (!file.is_open()) {
            cerr << "Error opening file!" << endl;
            return;
        }
        int id = -1;
        for (const auto& book : inventory) {
            file << ++id << "," << book.getTitle() << "," << book.getAuthor() << ","
                 << book.getPrice() << "," << book.getQuantity() << "\n";
        }
        file.close();
    }

    // Load inventory data from a file
    vector<Book> loadFromFile(const string& filename) override {
        vector<Book> inventory;
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Error opening file!" << endl;
            return inventory;
        }
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string id, title, author;
            double price;
            int quantity;
            getline(ss, id, ',');
            getline(ss, title, ',');
            getline(ss, author, ',');
            ss >> price;
            ss.ignore(1);  // Ignore the comma
            ss >> quantity;
            inventory.emplace_back(title, author, price, quantity);
        }
        file.close();
        return inventory;
    }
};

// FileStorageFromCloud Class: Simulates cloud-based storage
// Extends FileStorageBase for cloud storage operations.
class FileStorageFromCloud : public FileStorageBase {
public:
    // Simulate saving inventory to the cloud
    void saveToFile(const vector<Book>& inventory, const string& filename) override {
        cout << "[Cloud] Saving to cloud..." << endl;
    }

    // Simulate loading inventory from the cloud
    vector<Book> loadFromFile(const string& filename) override {
        cout << "[Cloud] Loading data from cloud..." << endl;
        return {};  // Returning empty inventory for simulation
    }
};

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
