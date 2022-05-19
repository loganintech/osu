#include "balrog.h"
#include "demon.h"

using namespace std;

/*********************************************************************
** Function: Balrog Non-Default Constructor
** Description: Creates a balrog object
** Parameters: health, damage_max, name
** Pre-Conditions: none
** Post-Conditions: Balrog object exists
*********************************************************************/
Balrog::Balrog(int health, int damage_max, string name) : Demon(health, damage_max, name) {}

/*********************************************************************
** Function: get_damange
** Description: Returns damage of type demon
** Parameters: none
** Pre-Conditions: demon object exists
** Post-Conditions: returned 2x damage
*********************************************************************/
int Balrog::getDamage() const
{
	return Demon::getDamage() + Demon::getDamage();
}

/*********************************************************************
** Function: Balrog default constructor
** Description: Creates a balrog with default values.
** Parameters: None
** Pre-Conditions: None
** Post-Conditions: Balrog object exists
*********************************************************************/
Balrog::Balrog() : Demon(150, 50, "Balrog") {}

/*********************************************************************
** Function: Get payoff
** Description: returns the payoff of the type
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: returned payoff
*********************************************************************/
int Balrog::get_payoff() const
{
	return Demon::get_payoff() + 12;
}

/*********************************************************************
** Function: Get cost
** Description: returns cost of the type
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: returned cost
*********************************************************************/
int Balrog::get_cost() const
{
	return Demon::get_cost() + 10;
}