/*********************************************************************
** Program Filename: rock.cpp
** Author: Logan Saso
** Date: May 29th
** Description: Rock type functionality
** Input: None
** Output: Functions
*********************************************************************/

#include "pokemon.h"
#include "rock.h"

#include <cstdlib>

/*********************************************************************
** Function: Constructor
** Description: Constructs
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: Object created
*********************************************************************/
Rock::Rock() : Pokemon::Pokemon() {}

/*********************************************************************
** Function: Constructor
** Description: Constructs
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: Object created
*********************************************************************/
Rock::Rock(string name) : Pokemon::Pokemon(name) {}

bool Rock::try_capture() {
	return rand() % 4 != 0; //75 % chance (1 / 4)
}