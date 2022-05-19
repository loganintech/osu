#ifndef library_h
#define library_h

#include "structs.h"

class Library {
	private:
		book * _books;
		int _num_books;
		bool book_can_be_checked_out(book);
	public:
		Library(std::ifstream &file);
		~Library();
		Library(const Library &other);


		void operator=(const Library &);
		int get_num_books() const;
		book * get_available_books() const;
		book * get_all_books() const;
};

#endif