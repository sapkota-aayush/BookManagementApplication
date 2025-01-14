#include"Book.h"
//Implementation file for Book

Book::Book(string initialTitle, string initialAuthor, string initialIsbn, int initialId)
{
	title = (initialTitle.empty()) ? "Title is empty" : initialTitle;
	title = (initialAuthor.empty()) ? "Title is empty" : initialAuthor;
	title = (initialIsbn.empty()) ? "Title is empty" : initialIsbn;
}

void Book::displayAllBook()const
{

	cout  << "Title: " << title << "\nAuthor: " << author
		<< "\nISBN: " << Isbn << endl;

}
// Setter Methods
void Book::setTitle(const string & t) {
    title = t;
}

void Book:: setAuthor(const string& a) {
    author = a;
}

void Book:: setIsbn(const string& i) {
    Isbn = i;
}

void to_json(json& j, const Book& b)
{
	j = json{
		{"title",b.title},
		{"author",b.author},
		{"isbn",b.Isbn}
	};
}

// Deserialization from JSON
void from_json(const json& j, Book& b){
{
	j.at("title").get_to(b.title);    // Deserialize title from JSON
	j.at("author").get_to(b.author);  // Deserialize author from JSON
	j.at("isbn").get_to(b.Isbn);      // Deserialize ISBN from JSON
};
}




