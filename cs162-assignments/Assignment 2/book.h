#ifndef book_h
#define book_h

#include <string>

class Book {

	private:
		std::string _title;
		int _num_authors;
		std::string *_authors;
		int _year;
		int _copies;
		int _checked_out_num;
		std::string * _checked_out_ids;

		void set_num_authors(const int);
		void set_title(const std::string);
		void set_authors(const std::string *, const int num_authors);
		void set_year(const int);

		void extend_array(std::string *&, const int);
		std::string * split(const std::string, const std::string, int &);

	public:
		Book();
		Book(const std::string);
		~Book();
		Book(const Book &);
		Book& operator=(const Book &);
		void set_checked_out_num(const int);
		std::string get_title() const;
		int get_num_authors() const;
		std::string * get_authors() const;
		int get_year() const;
		int get_copies() const;
		int get_checked_out() const;
		void set_copies(const int);
		std::string * get_checked_out_ids() const;
		void set_checked_out_ids(const std::string *);
		void increase_checked_out_num();
		void decrease_checked_out_num();

		std::string to_string();


};


#endif