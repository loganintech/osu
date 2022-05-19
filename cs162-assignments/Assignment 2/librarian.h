#ifndef librarian_h
#define librarian_h

#include <string> 
#include "cart.h"
#include "library.h"

class Librarian {
	private:
		std::string _name;
		int _id;
	public:
		void change_library_hours(Library &);

		std::string get_name() const;
		void set_name(const std::string);
		int get_id() const;
		void set_id(const int);

		Librarian(std::string, int);
		Librarian(const Librarian &);
};

#endif