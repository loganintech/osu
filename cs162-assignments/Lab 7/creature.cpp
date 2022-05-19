#include "creature.h"
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

Creature::Creature() {}

/*********************************************************************
** Function: Non-default constructor
** Description: Constructs what we know and love
** Parameters: health, damage max, name
** Pre-Conditions: none
** Post-Conditions: Creature object exists
*********************************************************************/
Creature::Creature(int health, int damage_max, string name)
{
	_health = health;
	_damage_max = damage_max;
	_name = name;
}

/*********************************************************************
** Function: Get health
** Description: returns health
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: returns health
*********************************************************************/
int Creature::getHitpoints() const
{
	return _health;
}

/*********************************************************************
** Function: get damage max
** Description: returns damage max
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: returns damage max
*********************************************************************/
int Creature::getDamage_max() const
{
	return _damage_max;
}

/*********************************************************************
** Function: get damage
** Description: returns damage
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: returns damage
*********************************************************************/
int Creature::getDamage() const
{
	return (int)rand() % _damage_max;
}

/*********************************************************************
** Function: get name
** Description: returns name
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: returns name
*********************************************************************/
string Creature::getSpecies() const
{
	return _name;
}

/*********************************************************************
** Function: set health
** Description: sets health
** Parameters: health
** Pre-Conditions: none
** Post-Conditions: health set
*********************************************************************/
void Creature::setHitpoints(const int health)
{
	_health = health;
}

/*********************************************************************
** Function: set damage max
** Description: sets damage max
** Parameters: int damage max
** Pre-Conditions: none
** Post-Conditions: sets damage max
*********************************************************************/
void Creature::setStrength(const int damage_max)
{
	_damage_max = damage_max;
}

/*********************************************************************
** Function: set name
** Description: sets name
** Parameters: string name
** Pre-Conditions: none
** Post-Conditions: returns name
*********************************************************************/
void Creature::set_name(const string name)
{
	_name = name;
}

/*********************************************************************
** Function: decrease health
** Description: decreases health
** Parameters: amount to decrease by
** Pre-Conditions: health set
** Post-Conditions: health decreased
*********************************************************************/
void Creature::decrease_health(const int health)
{
	_health -= health;
}

/*********************************************************************
** Function: get payoff
** Description: gets payoff
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: returns payoff
*********************************************************************/
int Creature::get_payoff() const
{
	return 10;
}

/*********************************************************************
** Function: get cost
** Description: gets cost
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: returns cost
*********************************************************************/
int Creature::get_cost() const
{
	return 5;
}