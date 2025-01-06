#ifndef filestorage_H
#define filestorage_H

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <fstream>
#include <sstream>
#include"book.h"
using namespace std;

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


#endif