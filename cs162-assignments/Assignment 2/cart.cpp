/*********************************************************************
** Program Filename: cart.cpp
** Author: Logan Saso
** Date: May 1st
** Description: Handles cart information
** Input: Needs no input
** Output: Prints some stuff
*********************************************************************/

#include "structs.h"
#include "book.h"
#include "cart.h"
#include <string>


/*********************************************************************
** Function: get books
** Description: returns books
** Parameters: none
** Pre-Conditions: books exists
** Post-Conditions: return books
*********************************************************************/ 
Book * Cart::get_books() const {
	return _books;
}

/*********************************************************************
** Function: set num books
** Description: sets the number of books
** Parameters: num books
** Pre-Conditions: none
** Post-Conditions: number books is set
*********************************************************************/ 
void Cart::set_num_books(const int num_books) {
	_num_books = num_books;
}

/*********************************************************************
** Function: get num books
** Description: get num books
** Parameters: none
** Pre-Conditions: num books set
** Post-Conditions: num books returned
*********************************************************************/ 
int Cart::get_num_books() const {
	return _num_books;
}

/*********************************************************************
** Function: copy constructor
** Description: copies cart array
** Parameters: other cart
** Pre-Conditions: a cart exists
** Post-Conditions: a duplicate cart exists
*********************************************************************/ 
Cart::Cart(const Cart &other){
	_books = new Book[other.get_num_books()];
	Book * other_books = other.get_books();
	for(int i = 0; i < other.get_num_books(); i++){
		_books[i] = other_books[i];
	}
}

/*********************************************************************
** Function: destructor
** Description: destroys the cart
** Parameters: none
** Pre-Conditions: cart built
** Post-Conditions: books and cart are gonners
*********************************************************************/ 
Cart::~Cart(){
	delete [] _books;
}

/*********************************************************************
** Function: default constructor
** Description: constructs books
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: books constructor
*********************************************************************/ 
Cart::Cart(){
	_books = new Book[0];
	_num_books = 0;
}

/*********************************************************************
** Function: operator=
** Description: Sets a book to a new book
** Parameters: other cart
** Pre-Conditions: other cart exists
** Post-Conditions: a duplicate cart exists
*********************************************************************/ 
Cart& Cart::operator= (const Cart & other) {

	Book * other_books = other.get_books();
	for(int i = 0; i < other.get_num_books(); i++){
		_books[i] = other_books[i];
	}
	return *this;
}


/*********************************************************************
** Function: add to cart
** Description: add book to cart
** Parameters: book
** Pre-Conditions: the book is added to cart
** Post-Conditions: books array has new book
*********************************************************************/ 
void Cart::add_to_cart(const Book &the_book){
	extend_array(_books, _num_books);
	_books[_num_books++] = the_book;
}

/*********************************************************************
** Function: remove from cart
** Description: cart is removed
** Parameters: book to remove
** Pre-Conditions: book exists in array
** Post-Conditions: book doesn't exists in the array anymore
*********************************************************************/ 
void Cart::remove_from_cart(const Book &the_book){

	Book * array = new Book[_num_books-1];
	int book_tracker = 0;
	for(int i = 0; i < _num_books; i++){
		if(the_book.get_title() != _books[i].get_title()){
			array[book_tracker++] = _books[i];
		}
	}
	_books = array;
	_num_books--;

}

/*********************************************************************
** Function: extend array
** Description: array is extended
** Parameters: book source, size
** Pre-Conditions: book array exists
** Post-Conditions: book array is longer
*********************************************************************/ 
void Cart::extend_array(Book * &source, const int size){
	Book * array = new Book[size+1];
	for(int i = 0; i < size; i++){
		array[i] = source[i];
	}
	source = array;
}

