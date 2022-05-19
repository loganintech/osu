#include <string>
#include <cstdlib>
#include <iostream>


using namespace std;

#include "prototypes.h"

int main(int argc, char * argv[]){

	return 0;
}

// void Librarian::change_library_hours();
// void Librarian::add_new_books(const cart &);
// void Librarian::remove_old_books();
// void Librarian::view_all_books_checked_out();
// void Librarian::view_specific_book_checked_out(string);

string Librarian::get_name(){
	return this->name;
}
void Librarian::set_name(string name){
	this->name = name;
}
int Librarian::get_id(){
	return this->id;
}
void Librarian::set_id(int id){
	this->id = id;
}





// void Cart::set_book(const int, const book &);
// void Cart::resize_books(int);
// Cart::Cart();

// void Cart::add_to_cart(const book &);
// void Cart::display_books();
// void Cart::empty_cart();
book * Cart::get_books() const {
	return this->books;
}
void Cart::set_num_books(const int num_books) {
	this->num_books = num_books;
}

int Cart::get_num_books() const {
	return this->num_books;
}





string Patron::get_name() {
	return this->name;
}
void Patron::set_name(const string name){
	this->name = name;
}

int Patron::get_id() {
	return this->id;
}
void Patron::set_id(const int id){
	this->id = id;
}

int Patron::get_books_checked_out() {
	return this->books_checked_out;
}
void Patron::set_books_checked_out(const int books_checked_out){
	this->books_checked_out = books_checked_out;
} 