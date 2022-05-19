/*********************************************************************
** Program Filename: librarian.cpp
** Author: Logan Saso
** Date: May 1st
** Description: Handles librarian information
** Input: library class instance
** Output: some librarian stuff
*********************************************************************/

#include "librarian.h"
#include "library.h"
#include <iostream>


std::string Librarian::get_name() const{
	return _name;
}
void Librarian::set_name(const std::string name){
	_name = name;
}
int Librarian::get_id() const{
	return _id;
}
void Librarian::set_id(const int id){
	_id = id;
}

void Librarian::change_library_hours(Library &library){
	std::cout << "Changing library hours." << std::endl;
	std::cout << "_______________________" << std::endl;
	std::cout << "Starting Hour (0 - 24): ";
	hours the_hours;
	std::cin >> the_hours.begin_time;
	do{
		std::cout << "Ending Hour (0 - 24) Must be after Starting Hour: ";
		std::cin >> the_hours.end_time;
	} while (the_hours.begin_time > the_hours.end_time);

	library.change_library_hours(the_hours);
}

Librarian::Librarian(std::string name, int id){
	_name = name;
	_id = id;
}

/*********************************************************************
** Function: copy constructor
** Description: librarian copied
** Parameters: other librarian
** Pre-Conditions: librarian exists
** Post-Conditions: librarian copied
*********************************************************************/ 
Librarian::Librarian(const Librarian &other){
	_name = other.get_name();
	_id = other.get_id();
}