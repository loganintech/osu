/*********************************************************************
** Program Filename: elf.cpp
** Author: Logan Saso
** Date: May 14th
** Description: Elf Class Implementations
** Input: Health, Damage_Max, Name
** Output: Stats
*********************************************************************/

#include "elf.h"
#include "creature.h"

/*********************************************************************
** Function: Elf Non-Default Constructor
** Description: Creates a elf object
** Parameters: health, damage_max, name
** Pre-Conditions: none
** Post-Conditions: Elf object exists
*********************************************************************/ 
Elf::Elf(int health, int damage_max, string name) : Creature(health, damage_max, name) {}

/*********************************************************************
** Function: get damage
** Description: Gets damage
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: returns damage
*********************************************************************/ 
int Elf::get_damage() const
{
	int damage = Creature::get_damage() ;
	if (rand() % 10 == 5) // 10% chance to double the damage
	{
		damage *= 2;
	}
	return damage;
}

/*********************************************************************
** Function: Elf default constructor
** Description: Creates a elf with default values.
** Parameters: None
** Pre-Conditions: None
** Post-Conditions: Elf object exists
*********************************************************************/ 
Elf::Elf() : Creature(250, 35, "Elf") {}

/*********************************************************************
** Function: Get payoff
** Description: returns the payoff of the type
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: returned payoff
*********************************************************************/ 
int Elf::get_payoff() const {
	return Creature::get_payoff() + 25;
}

/*********************************************************************
** Function: Get cost
** Description: returns cost of the type
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: returned cost
*********************************************************************/ 
int Elf::get_cost() const {
	return Creature::get_cost() + 12;
}

