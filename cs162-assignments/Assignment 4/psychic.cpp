/*********************************************************************
** Program Filename: psychic.cpp
** Author: Logan Saso
** Date: May 29th
** Description: Psycic type functionality
** Input: None
** Output: Functions
*********************************************************************/

#include "pokemon.h"
#include "psychic.h"

#include <cstdlib>

/*********************************************************************
** Function: Constructor
** Description: Constructs
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: Object created
*********************************************************************/
Psychic::Psychic() : Pokemon::Pokemon() {}

/*********************************************************************
** Function: Constructor
** Description: Constructs
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: Object created
*********************************************************************/
Psychic::Psychic(string name) : Pokemon::Pokemon(name) {}

bool Psychic::try_capture() {
	return rand() % 2 == 0; //50%
}