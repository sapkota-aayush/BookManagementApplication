#include"Library.h"
#include"Validation.h"
using namespace std;

void Library::addBook(Book& obj)
{
	string title; string author; string Isbn;
	if (count < maxCount)
	{
		do 
		{
			cout << "Enter a book title: ";
			getline(cin, title);
			if (!isValidString(title))
			{
				cout << "Invalid Input.Enter again: ";
			}
			
		} while (!isValidString(title));
		obj.setTitle(title);

		do
		{
			cout << "Enter a book Author: ";
			getline(cin, author);
			if (!isValidString(author))
			{
				cout << "Invalid Input. Enter again: ";
			}
		} while (!isValidString(author));
		obj.setAuthor(author);

		cout << "Enter a book Isbn: ";
		getline(cin, Isbn);
		obj.setIsbn(Isbn);

		bookObj[count] = obj;
		count++;
	}
	else
	{
		cout << "Library is full. Can't add more Books :(\n";
	}
}

Book Library::findBook() const {
	string findThroughAnything;
	cout << "Enter any details of book you want to find: ";
	getline(cin, findThroughAnything);
	string lowercaseInput = convertToLower(findThroughAnything);

	// Search through the array of books in the library
	for (int i = 0; i < count; i++) {
		string lowercaseTitle = convertToLower(bookObj[i].getTitle());
		string lowercaseAuthor = convertToLower(bookObj[i].getAuthor());
		string lowercaseIsbn = convertToLower(bookObj[i].getIsbn());

		if (lowercaseTitle.find(lowercaseInput) != string::npos ||
			lowercaseAuthor.find(lowercaseInput) != string::npos ||
			lowercaseIsbn.find(lowercaseInput) != string::npos) {
			return bookObj[i];  // Return the found book
		}
	}

	// If book is not found, return a default Book or handle it as you need
	// For example, returning an empty book:
	cout << "Book not Found in the library.\n";
	return Book(); //Calls the default constructor
}


void Library::removeBook()
{
	string findThroughTitle;
	cout << "Enter the title you want to delete: ";
	getline(cin, findThroughTitle);
	bool bookFound = false;

	for (int i = 0; i < count; i++)
	{
		if (bookObj[i].getTitle() == findThroughTitle)
		{
			for (int j = i; j < count - 1; j++)
			{
				bookObj[j] = bookObj[j + 1];
			}
			count--;
			bookFound = true;
			cout << "Book with the title " << findThroughTitle << " has been removed\n";
			break;
		}
	}
	if (!bookFound)
	{
		cout << "Book is not found in the Library :(\n";
	}

}

void Library::displayAllBooks() const
{
	if (count == 0)
	{
		cout << "The library is empty. No books to display.\n";
		return;
	}

	for (int i = 0; i < count; i++)
	{
		cout << "Book " << i + 1 << " details:\n";
		bookObj[i].displayAllBook(); // Call the Book class's display function
		cout << "---------------------------------\n";
	}
}


//using seletion sort But using built-in function library is recommanded and make code looks clear and improve the performance as well
void Library::sortByIsbn()
{

	for (int i = 0; i < count - 1; i++)
	{
		int minIndex = i;
		for (int j = i + 1; j < count; j++)
		{
			if (bookObj[j].getIsbn() < bookObj[minIndex].getIsbn())
			{
				minIndex = j;
			}
		}
		if (minIndex != i)
		{
			swap(bookObj[i], bookObj[minIndex]);
		}
	}
}  //Will visualizing this a bit better later 

void to_json(json& j, const Library& lib)
{
	j = json{ {"maxCount",lib.maxCount},{"count",lib.count},{"books",json::array()}};
	//seriallizing each book in the library and addiding it to the books array in JSON
	for (int i = 0; i < lib.count; i++)
	{
		json bookJson;
		to_json(bookJson, lib.bookObj[i]);
		j["books"].push_back(bookJson);
	}
}

void Library::loadFromFile(const string& fileName)
{
	ifstream inFile(fileName);
	if (!inFile)
	{
		cout << "Error: Could not open the file " << fileName << " for reading!\n";
		return;
	}

	json jLibrary;
	inFile >> jLibrary;

	// Allocate and initialize book array
	delete[] bookObj;
	count = 0; // Reset count, you want to re-populate from file
	maxCount = jLibrary.at("maxCount").get<int>(); // Ensure this exists
	count = jLibrary.at("count").get<int>(); // Ensure this exists
	bookObj = new Book[maxCount];

	// Deserialize books data
	for (int i = 0; i < count; ++i) {
		Book book;
		from_json(jLibrary["books"][i], book); // Deserialize each book
		bookObj[i] = book;  // Assign to bookObj
	}

	inFile.close();
	cout << "Library data has been loaded from " << fileName << "\n";
}
