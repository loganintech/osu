#ifndef cart_h
#define cart_h

#include "structs.h"

class Cart {
	private:
		void set_book(const int, const book &);
		book * _books;
		int _num_books;
		void resize_books(int);
	public:
		Cart();
		~Cart();
		Cart(const Cart &other);

		void operator=(const Cart &);
		void add_to_cart(const book &);
		void display_books();
		void empty_cart();
		book * get_books() const;
		void set_num_books(const int);
		int get_num_books() const;


};

#endif