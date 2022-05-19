/*********************************************************************
** Program Filename: pokemon.cpp
** Author: Logan Saso
** Date: May 29th
** Description: Pokemon base functions
** Input: Name
** Output: Functions
*********************************************************************/

#include "pokemon.h"

int Pokemon::get_evolution() const {
	return _evolution;
}
void Pokemon::set_evolution(const int evolution) {
	_evolution = evolution;
}

/*********************************************************************
** Function: Constructor
** Description: Constructs
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: Object created
*********************************************************************/
Pokemon::Pokemon(string name) {
	_name = name;
	_evolution = 0;
}

/*********************************************************************
** Function: Constructor
** Description: Constructs
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: Object created
*********************************************************************/
Pokemon::Pokemon() {
	Pokemon("Generic");
}

bool Pokemon::try_capture() {
	return false; //You can't catch a generic pokemon object
}

string Pokemon::get_name() const {
	return _name;
}