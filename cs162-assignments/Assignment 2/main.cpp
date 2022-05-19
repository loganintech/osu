/*********************************************************************
** Program Filename: main.cpp
** Author: Logan Saso
** Date: May 1st
** Description: Includes a bunch of things to be a library
** Input: username, password 
** Output: Everything
*********************************************************************/

#include <string>
#include "main.h"
#include "book.h"
#include "structs.h"
#include "library.h"
#include "patron.h"
#include "librarian.h"
#include "cart.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <stdio.h>


using namespace std;


int main(int argc, char * argv[]){


	ifstream books_file;
	books_file.open("book.txt");
	ifstream checked_out_file;
	Library library(books_file, checked_out_file);
	ifstream login_file;
	login_file.open("login.txt");

	
	if(!is_valid_arguments(argc, argv)){
		cout << "Library Hours\n----------" << endl;
		cout << library.get_hours().begin_time << " to " << library.get_hours().end_time << endl;
		cout << "You need to enter a user and password with -u and -p for more functionality." << endl;
		return 0;
	}




	books_file.close();
	checked_out_file.close();

	program_start(get_username(argc, argv), get_password(argc, argv), login_file, library);

	return 0;
}

bool is_valid_arguments(int argc, char *argv[]){

	if(argc < 5){
		return false;
	}

	if((argv[1][0] == '-' && argv[1][1] == 'u' && argv[3][0] == '-' && argv[3][1] == 'p') || (argv[3][0] == '-' && argv[3][1] == 'p' && argv[1][0] == '-' && argv[1][1] == 'u')) {
		return true;
	}
	return false;
}

string get_username(int argc, char *argv[]){
	for(int i = 0; i < argc-1; i++){
		if(argv[i][0] == '-' && argv[i][1] == 'u'){
			return argv[i+1];
		}
	}
	return "none";
}

string get_password(int argc, char *argv[]){
	for(int i = 0; i < argc-1; i++){
		if(argv[i][0] == '-' && argv[i][1] == 'p'){
			return argv[i+1];
		}
	}
	return "none";
}

void librarian_menu(Library &library, Librarian &librarian){
	bool should_quit = false;
	do{
		cout << "You are a librarian. Pick from the following" << endl;
		cout << "____________________________________________" << endl;
		cout << "[0] View Hours" << endl << "[1] Change Hours" << endl;
		cout << "[2] Add Books" << endl << "[3] Remove Books" << endl;
		cout << "[4] View Checked Out Books" << endl << "[5] Exit" << endl;
		cout << "Choose Now: ";

		int choice = 0;
		while(!(cin >> choice)){
			cout << "Please put a number 0 - 4" << endl;
			cout << "Choose Now: ";
		}

		switch(choice){
			case 0:
				cout << "Beginning Hours: " << library.get_hours().begin_time << endl << "Ending Hours: " << library.get_hours().end_time << endl;
				break;
			case 1:
				librarian.change_library_hours(library);
				break;
			case 2:
				add_books(library);
				break;
			case 3:
				remove_books(library);
				break;
			case 4:
				view_checked_out_books();
				break;
			case 5:
				should_quit = true;
		}
	} while (!should_quit);
}

void patron_menu(Library &library, Patron &patron){
	bool should_quit = false;
	Cart cart;
	do{
		cout << "You are a patron. Pick from the following" << endl;
		cout << "_________________________________________" << endl;
		cout << "[0] View Hours" << endl << "[1] View All Books" << endl;
		cout << "[2] Search By Title" << endl << "[3] Search By Author" << endl;
		cout << "[4] Search By Year" << endl << "[5] Add To Cart" << endl;
		cout << "[6] Remove From Cart" << endl << "[7] Check In" << endl;
		cout << "[8] Check Out" << endl << "[9] View Checked Out" << endl;
		cout << "[10] View Cart" << endl;
		cout << "[11] Exit" << endl;
		cout << "Choose Now: ";
		int choice = -1;
		while(!(cin >> choice)){
			cout << "Please put a number 0 - 7" << endl;
			cout << "Choose Now: ";
		}
		switch(choice){
			case 0:
				cout << "Beginning Hours: " << library.get_hours().begin_time << endl << "Ending Hours: " << library.get_hours().end_time << endl;
				break;
			case 1:
				for(int i = 0; i < library.get_num_books(); i++){
					cout << "[" << i << "] " << library.get_all_books()[i].to_string() << endl; 
				}
				break;
			case 2:
				search_title(library);
				break;
			case 3:
				search_author(library);
				break;
			case 4:
				search_year(library);
				break;
			case 5:
				add_book_to_cart(cart, library);
				break;
			case 6:
				remove_book_from_cart(cart, library);
				break;
			case 7:
				library.check_in(cart, patron.get_id());
				break;
			case 8:
				library.check_out(cart, patron.get_id());
				break;
			case 9:
				view_checked_out(library, patron);
				break;
			case 10:
				view_cart(cart);
				break;
			case 11:
				should_quit = true;
		}
	} while (!should_quit);
}

void search_title(Library &library){
	string query = "";
	cout << "Enter your search query: ";
	cin >> query;
	string title ;
	for(int i = 0; i < library.get_num_books(); i++){
		title = library.get_all_books()[i].get_title();
		if(title.find(query) != -1){
			cout << "[" << i << "] " << title << endl; 
		}
	}
}

void search_year(Library &library){
	string query = "";
	cout << "Enter your search query: ";
	cin >> query;
	string year ;
	for(int i = 0; i < library.get_num_books(); i++){
		char buffer[50];
		sprintf(buffer, "%d", library.get_all_books()[i].get_year());
		string placeholder = string(buffer);

		year = placeholder;
		if(year.find(query) != -1){
			cout << "[" << i << "] " << library.get_all_books()[i].get_title() << endl; 
		}
	}
}

void search_author(Library &library){
	string query = "";
	cout << "Enter your search query: ";
	cin >> query;
	bool author_in_authors;
	string * authors ;
	string title;
	for(int i = 0; i < library.get_num_books(); i++){
		author_in_authors = false;
		for(int x = 0; x < library.get_all_books()[i].get_num_authors(); x++){
			if(library.get_all_books()[i].get_authors()[x].find(query) != -1){
				author_in_authors = true;
			}
		}
		title = library.get_all_books()[i].get_title();
		authors = library.get_all_books()[i].get_authors();
		if(author_in_authors){
			cout << "[" << i << "] " << title << endl; 
		}
	}
}

void view_checked_out(Library &library, Patron &patron){

	char buffer[50];
	sprintf(buffer, "%d", patron.get_id());
	string placeholder = string(buffer);
	string id = placeholder;
	string * ids;
	bool is_checked_out = false;
	string title;
	for(int i = 0; i < library.get_num_books(); i++){
		is_checked_out = false;
		ids = library.get_all_books()[i].get_checked_out_ids();
		title = library.get_all_books()[i].get_title();

		for(int x = 0; x < library.get_all_books()[i].get_checked_out(); x++){
			if(ids[x].find(id) != -1){
				is_checked_out = true;
			}
		}

		if(is_checked_out){
			cout << "[" << i << "] " << title << endl; 
		}
	}
}

void extend_array(string *&source, const int size){
	string * array = new std::string[size+1];
	for(int i = 0; i < size; i++){
		array[i] = source[i];
	}
	delete[] source;
	source = array;
}

string * split(string source, string delim, int &array_size){
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

void program_start(string username, string password, ifstream &login_file, Library &library){
	string line;
	string * user = new string[4];
	string * cut_line;
	int size = 0;
	bool login_successful = false;
	while(login_file.good()){
		getline(login_file, line);

		cut_line = split(line, "|", size);
		if(username == cut_line[0] && password == cut_line[1]){
			login_successful = true;
			break;
		}
	}
	login_file.close();
	if(!login_successful){
		cout << "Wrong username and password." << endl;
		return;
	}

	if(cut_line[2] == "patron"){
		Patron patron(username, atoi(cut_line[3].c_str()));
		patron_menu(library, patron);
	} else if (cut_line[2] == "librarian"){
		Librarian librarian(username, atoi(cut_line[3].c_str()));
		librarian_menu(library, librarian);
	}
	delete [] user;
	delete [] cut_line;

}

void add_book_to_cart(Cart &cart, Library &library){
	cout << "You are adding a book to cart." << endl;
	cout << "Enter ID of Book to Add. Enter -1 if you need to view the books again: " << endl;
	int id;
	cin >> id;
	if(id == -1) return;
	bool already_in_cart = false;
	for(int i = 0; i < cart.get_num_books(); i++){
		if(cart.get_books()[i].to_string() == library.get_all_books()[id].to_string()){
			already_in_cart = true;
		}
	}
	if(!already_in_cart){
		cart.add_to_cart(library.get_all_books()[id]);
	} else {
		cout << "That is already in your cart." << endl;
	}
	
}

void remove_book_from_cart(Cart &cart, Library &library){
	cout << "You are removing a book from the cart." << endl;
	cout << "Here are your books in the cart: " << endl;
	for(int i = 0; i < cart.get_num_books(); i++){
		cout << "[" << i << "] " << cart.get_books()[i].to_string() << endl;
	}
	cout << "Enter the ID of the book you want to remove: ";
	int id;
	cin >> id;
	cart.remove_from_cart(cart.get_books()[id]);
}

void view_cart(Cart &cart){
	for(int i = 0; i < cart.get_num_books(); i++){
		cout << "[" << i << "] " << cart.get_books()[i].to_string() << endl;
	}
}

void add_books(Library &library){
	bool keep_adding = true;
	string title = "";
	string year = "";
	string authors = "";
	string copies = "";
	int entry;
	cin.clear();
	cin.ignore();
	do{
		cout << "You have chosen to add books to the library." << endl << "Please provide a few pieces of information..." << endl;
		cout << "[0] Title: ";
		getline(cin, title);
		cout << "[1] Year: ";
		getline(cin, year);
		cout << "[2] ' and ' sepparated authors. IE, Bob and Joe: ";
		getline(cin, authors);
		cout << "[3] Copies: ";
		getline(cin, copies);
		library.add_book(title + "|" + year + "|" + authors + "|" + copies);
		cout << "Book added. Enter 1 to add another or 0 to quit." << endl;
		cin >> entry;
		keep_adding = entry == 1;
	} while (keep_adding);
	cin.clear();
	cin.ignore();


}

void remove_books(Library &library){
	bool keep_removing = true;
	int entry;

	do{
		cout << "Here are the books: " << endl;
		for(int i = 0; i < library.get_num_books(); i++){
			cout << "[" << i << "] " << library.get_all_books()[i].get_title() << endl;
		}
		cout << "Enter the number of the book from above." << endl;
		cin >> entry;
		cout << "Removing: " << library.get_all_books()[entry].get_title() << endl;
		library.remove_book(library.get_all_books()[entry].get_title());
		keep_removing = entry == 1;
	} while (keep_removing);


}

void view_checked_out_books(){
	ifstream login_file;
	login_file.open("login.txt");

	ifstream checked_out;

	string login_line;
	string checked_out_line;

	int junk;
	int array_size;
	string * checked_out_split;
	string * checked_out_ids;

	string * user;
	while(login_file.good()){
		getline(login_file, login_line);
		checked_out.open("checked_out.txt");
		user = split(login_line, "|", junk);
		while(checked_out.good()){
			getline(checked_out, checked_out_line);
			checked_out_split = split(checked_out_line, "|", junk);
			checked_out_ids = split(checked_out_split[1], ",", array_size);
			for(int i = 0; i < array_size; i++){
				if(user[3] == checked_out_ids[i]){
					cout << checked_out_split[0] << " is checked out by " << user[0] << endl;
				}
			}
		}
		checked_out.close();
	}
	login_file.close();
}