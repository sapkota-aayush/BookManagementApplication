#include <iostream>
#include "Book.h"
#include "Validation.h"
#include <iomanip>
#include <string>
#include<fstream>
#include<vector>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/statement.h>
#include <mysql_connection.h>
#include <mysql_driver.h>
#include"include/json.hpp"

using json = nlohmann::json;

#ifndef LIBRARY_H
#define LIBRARY_H


// MYSQL Connection settings
const string DB_HOST = "tcp://127.0.0.1:3306"; // MySQL server address
const string DB_USER = "root";
const string DB_PASSWORD = "Happy@890123";
const string DB_NAME = "shopping_cart";

class Library {
private:
    vector<Book> bookObj;     // Dynamic array for storing books (allocated on heap)
    int count;         // Current number of books in the library

public:
    // Constructor
    Library()
    {
        count = 0;
    };

    // Destructor (No need of Destructor as vector can manage the memory automatically)
    //~Library() {
    //    delete[] bookObj;  // Release memory to avoid memory leaks
    //}

    // Methods
    void addBook(Book& obj);
    void removeBook();
    Book findBook() const;
    void displayAllBooks() const;
    void sortByIsbn();
    friend void to_json(json& j, const Library& lib); //Method to serialize Library to JSON
    //File Operations
    void loadFromFile(const string& fileName);
    

    // Getters (if needed)
    int getCount() const { return count; }
};

#endif


/*

One issue we got:
Initially we declared arrary of 100 objects Book bookobj[100];
which lead to stack overflow. As we are not using the allocated memory.

Reason for Stack Overflow and Solution
The stack overflow occurred because the program used a fixed-size array Book bookObj[MAX_COUNT] in the Library class,
which allocated memory on the stack. The stack has limited space, and large arrays combined with other stack usage caused
the program to exceed the limit, resulting in an overflow.

To fix this, we switched to dynamic memory allocation, storing the array on the heap instead of the stack. 
The heap has a much larger capacity, making the program more scalable and preventing stack overflow.




*/
