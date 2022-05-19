#ifndef cart_h
#define cart_h

#include "structs.h"
#include "book.h"

class Cart {
	private:
		void set_book(const int, const Book &);
		Book * _books;
		int _num_books;
		void resize_books(int);
	public:
		Cart();
		~Cart();
		Cart(const Cart &);

		Cart& operator=(const Cart &);
		void add_to_cart(const Book &);
		void remove_from_cart(const Book &);
		void display_books();
		void empty_cart();
		Book * get_books() const;
		void set_num_books(const int);
		int get_num_books() const;

		void extend_array(Book *&, const int);


};

#endif