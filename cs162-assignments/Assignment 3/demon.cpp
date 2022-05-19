/*********************************************************************
** Program Filename: demon.cpp
** Author: Logan Saso
** Date: May 14th
** Description: Demon Class Implementations
** Input: Health, Damage_Max, Name
** Output: Stats
*********************************************************************/

#include "creature.h"
#include "demon.h"
#include <iostream>

using namespace std;

/*********************************************************************
** Function: Demon Non-Default Constructor
** Description: Creates a demon object
** Parameters: health, damage_max, name
** Pre-Conditions: none
** Post-Conditions: Demon object exists
*********************************************************************/ 
Demon::Demon(int health, int damage_max, string name) : Creature(health, damage_max, name) {}

/*********************************************************************
** Function: get damage
** Description: Gets damage
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: returns damage
*********************************************************************/ 
int Demon::get_damage() const
{
	int damage = Creature::get_damage();
	if (rand() % 20 == 10) // 5% chance to increase damage by 50
	{
		damage += 50;
	}
	return damage;
}

/*********************************************************************
** Function: Demon default constructor
** Description: Creates a demon with default values.
** Parameters: None
** Pre-Conditions: None
** Post-Conditions: Demon object exists
*********************************************************************/ 
Demon::Demon() : Creature(200, 35, "Demon"){}

/*********************************************************************
** Function: Get payoff
** Description: returns the payoff of the type
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: returned payoff
*********************************************************************/ 
int Demon::get_payoff() const {
	return Creature::get_payoff(); //These are redundant but follow good OOP style if I want to edit this in the future
}

/*********************************************************************
** Function: Get cost
** Description: returns cost of the type
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: returned cost
*********************************************************************/ 
int Demon::get_cost() const {
	return Creature::get_cost(); //These are redundant but follow good OOP style if I want to edit this in the future
}