/*********************************************************************
** Program Filename: library.cpp
** Author: Logan Saso
** Date: May 1st
** Description: Handles library class and things
** Input: Some files
** Output: Some cart stuff
*********************************************************************/

#include "library.h"
#include "structs.h"
#include "book.h"
#include "cart.h"
#include <fstream>
#include <string>
#include <iostream>
#include <cstdio>
#include <stdio.h>


/*********************************************************************
** Function: non-default constructor
** Description: creates libraries
** Parameters: file and checked out file
** Pre-Conditions: files are open
** Post-Conditions: library created
*********************************************************************/ 
Library::Library(std::ifstream &file, std::ifstream &checked_out) {


	hours fakehours;
	fakehours.begin_time = 7;
	fakehours.end_time = 22;
	_library_hours = fakehours;

	_books = new Book[1];

	int book_array_location = 0;
	int junk;
	int num_checked_out;

	std::string line = "";
	std::string checked_out_line = "";

	Book * a_book;

	while(file.good()){
		if(book_array_location != 0) {
			extend_array(_books, book_array_location);
		}
		std::getline(file, line);
		if(line.length() < 3){
			continue;
		}
		a_book = new Book(line);
		checked_out.open("checked_out.txt");
		while(checked_out.good()){
			std::getline(checked_out, checked_out_line);
			if(checked_out_line.length() < 3){
				continue;
			}
			std::string * checked = split(checked_out_line, "|", junk);
			if(checked[0] == a_book->get_title()){
				std::string * ids = split(checked[1], ",", num_checked_out);
				a_book->set_checked_out_num(num_checked_out);
				a_book->set_checked_out_ids(ids);
				break;
			} else {
				a_book->set_checked_out_num(0);
				std::string * ids = new std::string[0];
				a_book->set_checked_out_ids(ids);
			}
			delete [] checked;
		}
		checked_out.close();
		_books[book_array_location++] = *a_book;
		delete a_book;
		// std::cout << _books[book_array_location - 1].to_string() << std::endl;
	}
	_num_books = book_array_location;
}

/*********************************************************************
** Function: get num books
** Description: returns number of books
** Parameters: none
** Pre-Conditions: num books assigned
** Post-Conditions: returns num books
*********************************************************************/ 
int Library::get_num_books() const{
	return _num_books;
}

/*********************************************************************
** Function: book can be checked out
** Description: returns if the checked out is less than copies
** Parameters: Book to check
** Pre-Conditions: book exists
** Post-Conditions: return boolean
*********************************************************************/ 
bool Library::book_can_be_checked_out(Book the_book){
	return the_book.get_checked_out() < the_book.get_copies();
}

/*********************************************************************
** Function: copy constructor
** Description: copies books
** Parameters: other library
** Pre-Conditions: other library exists
** Post-Conditions: other library copied
*********************************************************************/ 
Library::Library(const Library &other){
	_books = new Book[other.get_num_books()];
	Book * other_books = other.get_all_books();
	for(int i = 0; i < other.get_num_books(); i++){
		_books[i] = other_books[i];
	}
	_num_books = other.get_num_books();
}

/*********************************************************************
** Function: destructor
** Description: destroys library
** Parameters: none
** Pre-Conditions: library exists
** Post-Conditions: library destroyed
*********************************************************************/ 
Library::~Library() {
	std::ofstream checked_out_file;
	checked_out_file.open("temp.txt");
	for(int i = 0; i < _num_books; i++){
		if(_books[i].get_checked_out() < 1){
			continue;
		}
		// std::cout << "Starting to write: " << _books[i].to_string() << std::endl;
		checked_out_file << _books[i].get_title() << "|";
		// std::cout << "It's about to write the first ID" << std::endl;
		checked_out_file << _books[i].get_checked_out_ids()[0];
		
		for(int x = 1; x < _books[i].get_checked_out(); x++){
			// std::cout << "It's about to try to add a comma." << std::endl;
			checked_out_file << "," << _books[i].get_checked_out_ids()[x];
		}
		if(i < _num_books - 1){
			checked_out_file << std::endl;
		}

	}
	checked_out_file.close();
	std::remove("checked_out.txt");
	std::rename("temp.txt", "checked_out.txt");

	std::ofstream books_file;
	books_file.open("temp.txt");
	for(int i = 0; i < _num_books; i++){
		books_file << _books[i].to_string();
		if(i < _num_books - 1){
			books_file << std::endl;
		}
	}
	books_file.close();

	std::remove("book.txt");
	std::rename("temp.txt", "book.txt");

	delete [] _books;
}


/*********************************************************************
** Function: get available books
** Description: gets available books
** Parameters: array size
** Pre-Conditions: books assigned
** Post-Conditions: returns available books
*********************************************************************/ 
Book * Library::get_available_books() {
	int junk = 0;
	return get_available_books(junk);
}


/*********************************************************************
** Function: get available books
** Description: gets available books
** Parameters: array size
** Pre-Conditions: books assigned
** Post-Conditions: returns available books
*********************************************************************/ 
Book * Library::get_available_books(int &array_size) {

	Book * all_books = get_all_books();
	Book * available_books = new Book[1];
	int array_index = 0;
	for(int i = 0; i < _num_books; i++){
		if(all_books[i].get_copies() > all_books[i].get_checked_out()){
			if(i != 0){
				extend_array(available_books, array_index); 
			}
			available_books[array_index++] = all_books[i];
		}
	}
	array_size = array_index + 1;
	return available_books;
	
}


/*********************************************************************
** Function: get all books
** Description: returns books
** Parameters: none
** Pre-Conditions: books exists
** Post-Conditions: returned exists
*********************************************************************/ 
Book * Library::get_all_books() const {
	return _books;
}


/*********************************************************************
** Function: operator=
** Description: library set
** Parameters: library other
** Pre-Conditions: other library exists
** Post-Conditions: library assigned
*********************************************************************/ 
Library& Library::operator= (const Library & other) {

	_books = new Book[other.get_num_books()];
	Book * other_books = other.get_all_books();
	for(int i = 0; i < other.get_num_books(); i++){
		_books[i] = other_books[i];
	}
	_num_books = other.get_num_books();
	return *this;
}

/*********************************************************************
** Function: extend array
** Description: extends an array
** Parameters: book array, int size
** Pre-Conditions: books array exists
** Post-Conditions: books array longer
*********************************************************************/ 
void Library::extend_array(Book * &source, const int size){
	Book * array = new Book[size+1];
	for(int i = 0; i < size; i++){
		array[i] = source[i];
	}
	delete [] source;
	source = array;
}

/*********************************************************************
** Function: change library hours
** Description: changes library hours
** Parameters: hours to set
** Pre-Conditions: hours exists
** Post-Conditions: hours set
*********************************************************************/ 
void Library::change_library_hours(const hours the_hours){
	_library_hours = the_hours;
}

/*********************************************************************
** Function: get hours
** Description: gets hours
** Parameters: none
** Pre-Conditions: library hours set
** Post-Conditions: hours returned
*********************************************************************/ 
hours Library::get_hours() const{
	return _library_hours;
}

/*********************************************************************
** Function: extend array
** Description: makes an array longer
** Parameters: string array and int 
** Pre-Conditions: source exists
** Post-Conditions: array longer
*********************************************************************/ 
void Library::extend_array(std::string *&source, const int size){
	std::string * array = new std::string[size+1];
	for(int i = 0; i < size; i++){
		array[i] = source[i];
	}
	delete[] source;
	source = array;
}

/*********************************************************************
** Function: split
** Description: splits a string into an array
** Parameters: the string souce, string delimiter, and array size by reference
** Pre-Conditions: array size integer is made, source is a thing
** Post-Conditions: returns string array
*********************************************************************/ 
std::string * Library::split(std::string source, std::string delim, int &array_size){
	int delim_offset = delim.length();
	int previous_delim = -delim_offset;
	int array_location = 0;
	std::string * destination = new std::string[1];
	while (source.find(delim, previous_delim + delim_offset) != -1){
		if(array_location != 0){ //This makes sure the array is the correct size. We have to skip one or else strings with nothing to split segfault
			extend_array(destination, array_location);
		}

		destination[array_location++] = source.substr(previous_delim + delim_offset, source.find(delim, previous_delim + delim_offset) - previous_delim - delim_offset);
		previous_delim = source.find(delim, previous_delim + delim_offset);
	} 
	extend_array(destination, array_location);
	destination[array_location] = source.substr(previous_delim + delim_offset, source.find(delim, previous_delim + delim_offset) - previous_delim - delim_offset);

	array_size = array_location + 1;
	return destination;
}

/*********************************************************************
** Function: check out
** Description: book checked out
** Parameters: cart to id
** Pre-Conditions: cart exists
** Post-Conditions: books checked out 
*********************************************************************/ 
void Library::check_out(Cart &cart, int id){
	bool should_continue;
	for(int i = 0; i < cart.get_num_books(); i++){
		should_continue = false;
		for(int z = 0; z < cart.get_num_books(); z++){
			char buffer[50];
			sprintf(buffer, "%d", id);
			std::string placeholder = std::string(buffer);
			Book * cart_books = cart.get_books();
			std::string * ids = cart_books[i].get_checked_out_ids();
			if(cart_books[i].get_checked_out() != 0 && ids[z] == placeholder){
				std::cout << "You already have the book \"" << cart_books[i].get_title() << "\" checked out." << std::endl;
				should_continue = true;
			}
		}
		if(should_continue) continue;
		for(int x = 0; x < _num_books; x++){
			if(_books[x].to_string() == cart.get_books()[i].to_string()){
				std::string * ids = _books[x].get_checked_out_ids();
				if(_books[x].get_checked_out() != 0){
					extend_array(ids, _books[x].get_checked_out());
					char buffer[50];
					sprintf(buffer, "%d", id);
					std::string placeholder = std::string(buffer);

					ids[_books[x].get_checked_out()] = placeholder;
				} else {
					extend_array(ids, _books[x].get_checked_out());
					char buffer[50];
					sprintf(buffer, "%d", id);
					std::string placeholder = std::string(buffer);
					ids[0] = placeholder;
				}
				_books[x].increase_checked_out_num();
				_books[x].set_checked_out_ids(ids);
			}
		}
	}
}

/*********************************************************************
** Function: check in
** Description: checks books in from a cart with id
** Parameters: cart, user id
** Pre-Conditions: cart exists
** Post-Conditions: cart has new book
*********************************************************************/ 
void Library::check_in(Cart &cart, int id){
	bool should_continue;
	for(int cart_book_location = 0; cart_book_location < cart.get_num_books(); cart_book_location++){
		should_continue = true;
		for(int book_id_location = 0; book_id_location < cart.get_books()[cart_book_location].get_checked_out(); book_id_location++){

			char buffer[50];
			sprintf(buffer, "%d", id);
			std::string placeholder = std::string(buffer);

			if(cart.get_books()[cart_book_location].get_checked_out_ids()[book_id_location] == placeholder){
				should_continue = false;
			}
		}
		if(should_continue || cart.get_books()[cart_book_location].get_checked_out() == 0) {
			std::cout << "You don't have \"" << cart.get_books()[cart_book_location].get_title() << "\" checked out." << std::endl;
			continue;
		} //This ensures we actually have the book checked out. If we get past this point we assume it's checked out
		for(int book_array_location = 0; book_array_location < _num_books; book_array_location++){

			if(_books[book_array_location].to_string() == cart.get_books()[cart_book_location].to_string()){ //Find the book in the array of books that we need to modify
				std::string * ids = _books[book_array_location].get_checked_out_ids(); // The current ids. We need to remove id
				char buffer[50];
				sprintf(buffer, "%d", id);
				std::string placeholder = std::string(buffer);
				shorten_array(ids, _books[book_array_location].get_checked_out(), placeholder); // This should actually remove the id from it.
				_books[book_array_location].decrease_checked_out_num();
				_books[book_array_location].set_checked_out_ids(ids);
			}
		}
	}
}


/*********************************************************************
** Function: shorten array
** Description: array shorten
** Parameters: string array by reference, size, string to remove
** Pre-Conditions: string array exists
** Post-Conditions: shorten array
*********************************************************************/ 
void Library::shorten_array(std::string *&source, int size, std::string to_remove){
	std::string * array = new std::string[size - 1];
	int array_location = 0;
	for(int i = 0; i < size ; i++){
		if(source[i] != to_remove){
			array[array_location++] = source[i];
		}
	}
	// delete [] source;
	source = array;
}

/*********************************************************************
** Function: remove book
** Description: remove a book from library
** Parameters: book string
** Pre-Conditions: books exist
** Post-Conditions: books removed
*********************************************************************/ 
void Library::remove_book(std::string book){
	shorten_array(_books, _num_books, book);
	_num_books--;
}

/*********************************************************************
** Function: add book
** Description: add a book
** Parameters: book string
** Pre-Conditions: books exists
** Post-Conditions: book added
*********************************************************************/ 
void Library::add_book(std::string book){
	extend_array(_books, _num_books);
	Book a_book(book);
	_books[_num_books++] = a_book;
}


/*********************************************************************
** Function: shorten array
** Description: shortens an array
** Parameters: the array, size, and a string to remove
** Pre-Conditions: array exists
** Post-Conditions: array is shorter
*********************************************************************/ 
void Library::shorten_array(Book *&source, int size, std::string to_remove){
	Book * array = new Book[size - 1];
	int array_location = 0;
	for(int i = 0; i < size ; i++){
		if(source[i].get_title() != to_remove){
			array[array_location++] = source[i];
		} else {
			std::cout << "Not adding: " << source[i].get_title() << std::endl;
		}
	}
	// delete [] source;
	source = array;
}