#ifndef main_h
#define main_h

#include "library.h"
#include "patron.h"
#include "librarian.h"

std::string * split(std::string, std::string, int&);
void extend_array(std::string **, int);
bool is_valid_arguments(int, char *[]);
std::string get_username(int, char *[]);
std::string get_password(int, char *[]);
void program_start(std::string, std::string, std::ifstream&, Library&);
void extend_array(std::string *&, int);

void librarian_menu(Library &, Librarian &);
void patron_menu(Library &, Patron &);

void search_title(Library &);
void search_year(Library &);
void search_author(Library &);
void view_checked_out(Library &, Patron &);

void add_book_to_cart(Cart &, Library &);
void remove_book_from_cart(Cart &, Library &);
void view_cart(Cart &);

void add_books(Library &);

void remove_books(Library &);
void view_checked_out_books();
#endif