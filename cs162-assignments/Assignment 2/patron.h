#ifndef patron_h
#define patron_h

#include "cart.h"
#include "structs.h"

class Patron {
	private:
		std::string _name;
		int _id;
	public:
		Patron(std::string, int);
		Patron(const Patron &);




		void set_name(const std::string);
		std::string get_name() const;
		int get_id() const;
		void set_id(const int id);
};

#endif