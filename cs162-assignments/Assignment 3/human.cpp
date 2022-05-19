/*********************************************************************
** Program Filename: human.cpp
** Author: Logan Saso
** Date: May 14th
** Description: Human Class Implementations
** Input: Health, Damage_Max, Name
** Output: Stats
*********************************************************************/

#include "human.h"
#include "creature.h"
#include <string>
#include <iostream>

using namespace std;


/*********************************************************************
** Function: Human Non-Default Constructor
** Description: Creates a human object
** Parameters: health, damage_max, name
** Pre-Conditions: none
** Post-Conditions: Human object exists
*********************************************************************/
Human::Human(int health, int damage_max, string name) : Creature(health, damage_max, name) {}

/*********************************************************************
** Function: Human default constructor
** Description: Creates a human with default values.
** Parameters: None
** Pre-Conditions: None
** Post-Conditions: Human object exists
*********************************************************************/ 
Human::Human() : Creature(350, 30, "Human") {}

/*********************************************************************
** Function: Get payoff
** Description: returns the payoff of the type
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: returned payoff
*********************************************************************/ 
int Human::get_payoff() const {
	return Creature::get_payoff() + 30;
}

/*********************************************************************
** Function: Get cost
** Description: returns cost of the type
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: returned cost
*********************************************************************/ 
int Human::get_cost() const {
	return Creature::get_cost() + 5;
}