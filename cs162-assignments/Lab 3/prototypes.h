#ifndef prototypes_h
#define prototypes_h

struct hours {
	int begin_time;
	int end_time;
};

struct book {
	string title;
	int num_authors;
	string *authors;
	int year;
	int copies;
};

class Cart {
	private:
		void set_book(const int, const book &);
		book * books;
		int num_books;
		void resize_books(int);
	public:
		Cart();

		void add_to_cart(const book &);
		void display_books();
		void empty_cart();
		book * get_books() const;
		void set_num_books(const int);
		int get_num_books() const;


};

class Library {
	private:
		book * books;
		bool book_can_be_checked_out(book);
		void switch_can_be_checked_out(book &);
	public:
		Library();
		book * get_available_books();
};

class Patron {
	private:
		string name;
		int id;
		int books_checked_out;
	public:
		void check_out_books(const Cart &);
		void check_in_books(const Cart &);
		void view_my_books_out();
		void set_name(const string);
		string get_name();
		int get_id();
		void set_id(const int id);
		int get_books_checked_out();
		void set_books_checked_out(int);
};



class Librarian {
	private:
		string name;
		int id;
	public:
		void change_library_hours();
		void add_new_books(const Cart &);
		void remove_old_books();
		void view_all_books_checked_out();
		void view_specific_book_checked_out(string);

		string get_name();
		void set_name(string);
		int get_id();
		void set_id(int);
};
#endif
