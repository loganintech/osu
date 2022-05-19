#include "structs.h"
#include "cart.h"
#include <string>

book * Cart::get_books() const {
	return _books;
}
void Cart::set_num_books(const int num_books) {
	_num_books = num_books;
}

int Cart::get_num_books() const {
	return _num_books;
}

Cart::Cart(){
	_books = new book[1];
}
Cart::Cart(const Cart &other){
	_books = new book[other.get_num_books()];
	book * other_books = other.get_books();
	for(int i = 0; i < other.get_num_books(); i++){
		_books[i].authors = new std::string[other_books[i].num_authors];
		_books[i] = other_books[i];
	}
}

Cart::~Cart(){
	delete [] _books;
}

void Cart::operator= (const Cart & other) {
	delete[] _books;
	book * other_books = other.get_books();
	for(int i = 0; i < other.get_num_books(); i++){
		_books[i].authors = new std::string[other_books[i].num_authors];
		_books[i] = other_books[i];
	}
}

