/*********************************************************************
** Program Filename: paladin.cpp
** Author: Logan Saso
** Date: May 14th
** Description: Paladin Class Implementations
** Input: Health, Damage_Max, Name
** Output: Stats
*********************************************************************/

#include "paladin.h"
#include "creature.h"

/*********************************************************************
** Function: Paladin Non-Default Constructor
** Description: Creates a paladin object
** Parameters: health, damage_max, name
** Pre-Conditions: none
** Post-Conditions: Paladin object exists
*********************************************************************/ 
Paladin::Paladin(int health, int damage_max, string name) : Creature(health, damage_max, name) {}


/*********************************************************************
** Function: get damage
** Description: Gets damage
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: returns damage
*********************************************************************/ 
int Paladin::get_damage() const
{
	int damage = Creature::get_damage() ;
	if (rand() % 100 == 50) // 1% chance to do 1000x the damage
	{
		damage *= 1000;
	}
	return damage;
}

/*********************************************************************
** Function: Paladin default constructor
** Description: Creates a paladin with default values.
** Parameters: None
** Pre-Conditions: None
** Post-Conditions: Paladin object exists
*********************************************************************/ 
Paladin::Paladin() : Creature(500, 20, "Paladin") {}

/*********************************************************************
** Function: Get payoff
** Description: returns the payoff of the type
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: returned payoff
*********************************************************************/ 
int Paladin::get_payoff() const {
	return Creature::get_payoff() + 50;
}

/*********************************************************************
** Function: Get cost
** Description: returns cost of the type
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: returned cost
*********************************************************************/ 
int Paladin::get_cost() const {
	return Creature::get_cost() + 2;
}