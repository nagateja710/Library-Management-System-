#include<iostream>
#include<bits/stdc++.h>
#include"library.h"
using namespace std;


int main ()
{
    unique_ptr<FileStorageBase> fileStorage = make_unique<FileStorageFromFile>();

    Library library(move(fileStorage));
    string title,author;
    int n,price,quantity;
    cout<<"enter number of unique books you want to add to shelf: ";
    cin>>n;
    for(int i=0;i<n ;i++){
        cout<<"enter title of the book: ";
        cin>>title;
        cout<<"enter author of the book: ";
        cin>>author;
        cout<<"enter price of the book: ";
        cin>>price;
        cout<<"number of quatity to be added: ";
        cin>>quantity;
        cout<<"enter title of the book: ";
        library.addBook(Book(title,author,price,quantity));
    }

    // Load inventory from file
    library.loadInventory("inventory.txt");

    // Display inventory
    cout << "Current Inventory:\n";
    library.displayInventory();
return 0;
}