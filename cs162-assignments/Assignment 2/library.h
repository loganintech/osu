#ifndef library_h
#define library_h

#include "structs.h"
#include "book.h"
#include "cart.h"
class Library {
	private:
		Book * _books;
		int _num_books;
		hours _library_hours;
		bool book_can_be_checked_out(Book);
		void extend_array(Book *&source, const int size);
		void extend_array(std::string *&, int);
		void write_checked_out_to_file(std::ofstream &);
	public:
		Library(std::ifstream &, std::ifstream &);
		~Library();
		Library(const Library &);

		std::string * split(std::string, std::string, int &);
		Library& operator=(const Library &);
		int get_num_books() const;
		Book * get_available_books();
		Book * get_available_books(int &);
		Book * get_all_books() const;
		hours get_hours() const;
		void change_library_hours(const hours);
		void shorten_array(std::string *&, int, std::string);
		void shorten_array(Book *&, int, std::string);
		
		void remove_book(std::string);
		void add_book(std::string);

		void check_out(Cart &, int);
		void check_in(Cart &, int);
};

#endif