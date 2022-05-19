#include "library.h"
#include "structs.h"
#include <fstream>

Library::Library(std::ifstream &file) {
	_books = new book[0];
	while(file.good()){
		
	}
}

int Library::get_num_books() const{
	return _num_books;
} 

bool Library::book_can_be_checked_out(book the_book){
	return the_book.checked_out_num < the_book.copies;
}

Library::Library(const Library &other){
	_books = new book[other.get_num_books()];
	book * other_books = other.get_all_books();
	for(int i = 0; i < other.get_num_books(); i++){
		_books[i].authors = new std::string[other_books[i].num_authors];
		_books[i] = other_books[i];
	}
}


Library::~Library() {
	for(int i = 0; i < _num_books; i++){
		delete[] _books[i].authors;
	}
	delete [] _books;
}

book * Library::get_available_books() const {
	//todo
}

book * Library::get_all_books() const {
	return _books;
}


void Library::operator= (const Library & other) {
	delete[] _books;
	book * other_books = other.get_all_books();
	for(int i = 0; i < other.get_num_books(); i++){
		_books[i].authors = new std::string[other_books[i].num_authors];
		_books[i] = other_books[i];
	}
}