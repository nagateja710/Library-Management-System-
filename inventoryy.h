#ifndef INVENTORY_MANAGER_H
#define INVENTORY_MANAGER_H

#include <string>
#include <vector>
#include "Book.h"

// Inventory Management Interface: Adheres to the Interface Segregation Principle (ISP)
// Provides a specific interface for managing inventory-related operations.
class InventoryManager {
public:
    virtual void addBook(const Book& book) = 0;  // Adds a book to the inventory
    virtual void displayInventory() const = 0;  // Displays the inventory
    virtual bool updateStock(const string& title, int quantity) = 0;  // Updates stock for a book
    virtual ~InventoryManager() = default;  // Virtual destructor
};

#endif // INVENTORY_MANAGER_H
