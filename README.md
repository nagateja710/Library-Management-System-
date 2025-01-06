# Library Management System 📚

A C++ Library Management System designed with a modular structure, adhering to the SOLID principles. The system supports inventory management, payment handling, and user interactions, making it scalable and efficient.

---

## 🚀 Features

- **Book Inventory Management**: Add, display, update, and sell books in the library.
- **Modular File Storage**: Support for local file storage and simulated cloud storage.
- **Payment Options**: Flexible payment processing with cash and online payment methods.
- **User-Friendly Interface**: Easily interact with the system to manage books and handle transactions.

---

## 🗂️ Repository Structure

```
📂 LibraryManagementSystem
├── 📜 book.h             # Contains the `Book` class definition.
├── 📜 filestorage.h      # Contains file storage classes for inventory data handling.
├── 📜 library.h          # Contains the `Library` class definition.
├── 📜 inventoryy.h       # Contains the inventory management interface.
├── 📜 main_compact.cpp   # Main program utilizing modular header files.
├── 📜 main.cpp           # Standalone implementation of all classes and logic.
├── 📜 add_book_to_shelf.cpp # Utility for adding books to the inventory.
├── 📜 inventory.txt      # Sample inventory file with book data.
├── 📜 README.md          # Documentation for the project.
```

---

## 🛠️ Setup Instructions

### Clone the Repository

```bash
git clone https://github.com/<your-username>/LibraryManagementSystem.git
cd LibraryManagementSystem
```

### Compile and Run

#### Using Modular Files:

1. Compile the program:
   ```bash
   g++ -o library main_compact.cpp
   ```
2. Run the executable:
   ```bash
   ./library
   ```

#### Using the Standalone File (`main.cpp`):

1. Compile the program:
   ```bash
   g++ -o library main.cpp
   ```
2. Run the executable:
   ```bash
   ./library
   ```

---

## 📄 Inventory File Format (`inventory.txt`)

- Each line in the file represents a book with the following format:
  ```
  ID,Title,Author,Price,Quantity
  ```
- Example:
  ```
  0,The Kite Runner,Khaled Hosseini,200.00,5
  1,Icebreakers,Grace Smith,250.00,10
  ```

---

## 🧩 How to Use

1. **Load Inventory**: The program loads books from `inventory.txt` upon startup.
2. **Manage Books**: Add new books or update stock using `add_book_to_shelf.cpp`.
3. **Sell Books**: Process customer transactions using the available payment methods.
4. **Save Inventory**: All updates are saved back to `inventory.txt`.


Feel free to enhance this documentation further or reach out for additional assistance!
