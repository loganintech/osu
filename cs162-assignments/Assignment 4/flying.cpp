/*********************************************************************
** Program Filename: flying.cpp
** Author: Logan Saso
** Date: May 29th
** Description: Flying type functionality
** Input: None
** Output: Functions
*********************************************************************/

#include "pokemon.h"
#include "flying.h"
#include <cstdlib>

/*********************************************************************
** Function: Constructor
** Description: Constructs
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: Object created
*********************************************************************/
Flying::Flying(string name) : Pokemon::Pokemon(name) {}

/*********************************************************************
** Function: Constructor
** Description: Constructs
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: Object created
*********************************************************************/
Flying::Flying() : Pokemon::Pokemon("Flying") {}

bool Flying::try_capture() {
	return rand() % 4 == 0; //25 % chance (1 / 4)
}