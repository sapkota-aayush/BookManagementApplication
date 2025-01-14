#ifndef BOOK_H
#define BOOK_H
 


#include<iostream>
#include<string>
#include"include/json.hpp"

using json = nlohmann::json;
using namespace std;

class Book {
private:
	string title;
	string author;
	string Isbn;
	
public:
	Book() { title = "NA"; author = "NA"; Isbn = "NA"; }
	Book(string, string, string, int);
	//setter
	void setTitle(const string&);
	void setAuthor(const string&);
	void setIsbn(const string&);
	

	//getter(in-line)

	string getTitle()const { return title; }
	string getAuthor() { return author; }
	string getIsbn() { return Isbn; }
	
	//Member Functions

	void displayAllBook()const;

	//Friend functionn for JSON serialization
	friend void to_json(json& j, const Book& b);
	friend void from_json(const json& j, Book& b);
};

#endif 