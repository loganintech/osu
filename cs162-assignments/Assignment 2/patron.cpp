/*********************************************************************
** Program Filename: patron.cpp
** Author: Logan Saso
** Date: May 1st
** Description: Handles some patron logic
** Input: Constructor takes a string
** Output: A few things
*********************************************************************/

#include "patron.h"
#include <string>


/*********************************************************************
** Function: get name
** Description: name got
** Parameters: none
** Pre-Conditions: name set
** Post-Conditions: name returned
*********************************************************************/ 
std::string Patron::get_name() const {
	return _name;
}

/*********************************************************************
** Function: set name
** Description: name is set
** Parameters: name
** Pre-Conditions: name exists
** Post-Conditions: name set
*********************************************************************/ 
void Patron::set_name(const std::string name){
	_name = name;
}

/*********************************************************************
** Function: get id
** Description: id got
** Parameters: none
** Pre-Conditions: id set
** Post-Conditions: return id
*********************************************************************/ 
int Patron::get_id() const {
	return _id;
}

/*********************************************************************
** Function: set id
** Description: id set
** Parameters: id
** Pre-Conditions: id exists
** Post-Conditions: id set
*********************************************************************/ 
void Patron::set_id(const int id){
	_id = id;
}

/*********************************************************************
** Function: Non-default Constructor
** Description: Makes a patron
** Parameters: username and identity
** Pre-Conditions: username and id exists
** Post-Conditions: name and id set
*********************************************************************/ 
Patron::Patron(std::string username, int id){
	_name = username;
	_id = id;
}

/*********************************************************************
** Function: Copy constructor
** Description: Copies a patron object
** Parameters: takes a patron object
** Pre-Conditions: A patron exists
** Post-Conditions: An identical patron exists
*********************************************************************/ 
Patron::Patron(const Patron &other){
	_name = other.get_name();
	_id = other.get_id();
}
