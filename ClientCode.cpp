#include "Book.h"
#include "Library.h"
#include <iostream>
#include <fstream>
#include "Validation.h"
#include "include/json.hpp"  

using json = nlohmann::json;
using namespace std;

// Function to clear screen
void clearScreen()
{
    system("CLS"); // Clear screen for Windows
}

int main()
{
    clearScreen(); // Clear the screen at the start
    cout << "------------------------------ Welcome to Online Library ----------------------------------------\n";

    Library books;
    Book newBook;

    // Load the library data from file (if the file exists)
    books.loadFromFile("library_data.json");  // Make sure 'loadFromFile' is implemented correctly

    int choice;

    do
    {
        cout << "\nEnter a choice:\n"
            << "1. Add a Book\n"
            << "2. Find a Book\n"
            << "3. Remove a Book\n"
            << "4. Display All Books\n"
            << "5. Sort by Isbn\n"
            << "6. Save Library to JSON\n"
            << "7. Exit\n";
        cout << "Your Choice: ";
        cin >> choice;
        cin.ignore();  // Ignore the newline left behind by 'cin'

        clearScreen(); // Clear screen after user enters choice

        switch (choice)
        {
        case 1:
            cout << "-------------------------- Add a Book --------------------------\n";
            books.addBook(newBook);
            break;

        case 2:
            cout << "-------------------------- Find a Book --------------------------\n";
            {
                Book foundBook = books.findBook();
                if (!foundBook.getTitle().empty())
                {
                    cout << "Found Book Details:\n";
                    foundBook.displayAllBook();
                }
                else
                {
                    cout << "Book not found.\n";
                }
            }
            break;

        case 3:
            cout << "-------------------------- Remove a Book --------------------------\n";
            books.removeBook();
            break;

        case 4:
            cout << "-------------------------- Display All Books --------------------------\n";
            books.displayAllBooks();
            break;

        case 5:
            cout << "-------------------------- Sort Books by ISBN --------------------------\n";
            books.sortByIsbn();
            books.displayAllBooks();
            break;

        case 6:
        {
            // Save the library data to a JSON file
            ofstream outFile("library_data.json");
            json jLibrary;
            to_json(jLibrary, books);  // Serialize library data
            outFile << jLibrary.dump(4);  // Save as pretty JSON
            outFile.close();
            cout << "Library data has been saved to library_data.json\n";
        }
        break;

        case 7:
            cout << "Thank you for using the Online Library. Goodbye!\n";
            break;

        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }

    } while (choice != 7);

    return 0;
}
