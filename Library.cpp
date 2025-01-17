#include"Library.h"
#include"Validation.h"
using namespace std;

void Library::addBook(Book& obj)
{
	string title; string author; string Isbn;
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

	bookObj.push_back(obj);
	count++;

	// Insert book into the database
	try {
		sql::PreparedStatement* pstmt;
		pstmt = con->prepareStatement("INSERT INTO Library(title, author, isbn) VALUES(?, ?, ?)");
		pstmt->setString(1, title);
		pstmt->setString(2, author);
		pstmt->setString(3, Isbn);
		pstmt->execute();
		delete pstmt;
		cout << "\nBook added successfully to the library database!\n";
	}
	catch (sql::SQLException& e) {
		cout << "SQL Exception: " << e.what() << endl;
	}


}


Book Library::findBook() const {
	string findThroughAnything;
	cout << "Enter any details of the book you want to find: ";
	getline(cin, findThroughAnything);
	string lowercaseInput = convertToLower(findThroughAnything);


	//adding mysql intergration to find the boo
	try
	{
		sql::PreparedStatement* pstmt;
		pstmt = con->prepareStatement(
                "SELECT * FROM Library WHERE LOWER(title) LIKE ? OR LOWER(author)LIKE ? OR LOWER (isbn)LIKE ?");
		string searchPattern = "%" + lowercaseInput + "%";
		pstmt->setString(1, searchPattern); //setstring assigns values
		pstmt->setString(2, searchPattern);
		pstmt->setString(3, searchPattern);

		sql::ResultSet* res = pstmt->executeQuery();

		if (res->next()) {
			// Book found, create and return a Book object
			Book foundBook(res->getString("title"),
				res->getString("author"),
				res->getString("isbn"));
			delete res;
			delete pstmt;
			return foundBook;
		}
		else {
			delete res;
			delete pstmt;
			cout << "Book not found in the library.\n";
			return Book(); // Return an empty book
		}

	}
	catch (sql::SQLException& e) {
		cout << "SQL Exception: " << e.what() << endl;
		return Book(); // Return an empty book in case of exception
	}

	/*-----------previous finding------------------*/
	//// Search through the vector of books in the library
	//for (const auto& book : bookObj) {
	//	string lowercaseTitle = convertToLower(book.getTitle());
	//	string lowercaseAuthor = convertToLower(book.getAuthor());
	//	string lowercaseIsbn = convertToLower(book.getIsbn());

	//	if (lowercaseTitle.find(lowercaseInput) != string::npos ||
	//		lowercaseAuthor.find(lowercaseInput) != string::npos ||
	//		lowercaseIsbn.find(lowercaseInput) != string::npos) {
	//		return book;  // Return the found book
	//	}
	//}

	//// If the book is not found, return a default Book or handle it as you need
	//// For example, returning an empty book:
	//cout << "Book not Found in the library.\n";
	//return Book(); // Calls the default constructor
}


void Library::removeBook()
{
	string findThroughTitle;
	cout << "Enter the title you want to delete: ";
	getline(cin, findThroughTitle);
	bool bookFound = false;
	for (int i = 0; i < bookObj.size(); i++)
	{
		if (bookObj[i].getTitle() == findThroughTitle)
		{
			bookObj.erase(bookObj.begin() + i);
			bookFound = true;
			cout << "Book with the titel " << bookObj[i].getTitle() << " has been removed.\n";
			break;
		}
	}
	if (!bookFound)
	{
		cout << "Book is not found in the library :(\n";
	}
	

}

void Library::displayAllBooks() const
{
	if (bookObj.empty())
	{
		cout << "The library is empty. No books to display.\n";
		return;
	}
	int bookNumber = 1; //Just to display book number 
	for (const auto & book:bookObj)
	{
		cout << "Book " << bookNumber++ << " details:\n";
		book.displayAllBook(); // Call the Book class's display function
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

void to_json(json& j, const Library& lib) {
	j = json{
		{"count", lib.bookObj.size()},  // Use size of vector
		{"books", json::array()}
	};

	// Serialize each book in the library and add it to the books array in JSON
	for (const auto& book : lib.bookObj) {
		json bookJson;
		to_json(bookJson, book);  // Serialize Book
		j["books"].push_back(bookJson);
	}
}

void Library::loadFromFile(const string& fileName) {
	ifstream inFile(fileName);
	if (!inFile) {
		cout << "Error: Could not open the file " << fileName << " for reading!\n";
		return;
	}

	json jLibrary;
	inFile >> jLibrary;

	// Clear the existing vector before loading new data
	bookObj.clear();  // Now we're using bookObj as the vector

	// Deserialize books data from JSON and add them to the vector
	const json& booksJson = jLibrary["books"];

	for (const auto& bookJson : booksJson) {
		Book book;
		from_json(bookJson, book);  // Deserialize into a Book object
		bookObj.push_back(book);    // Add the Book to the bookObj vector
	}

	inFile.close();
	cout << "Library data has been loaded from " << fileName << "\n";
}
