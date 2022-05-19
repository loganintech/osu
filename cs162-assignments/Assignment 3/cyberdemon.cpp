/*********************************************************************
** Program Filename: cyberdemon.cpp
** Author: Logan Saso
** Date: May 14th
** Description: Cyberdemon Class Implementations
** Input: Health, Damage_Max, Name
** Output: Stats
*********************************************************************/

#include "cyberdemon.h"
#include "demon.h"

using namespace std;

/*********************************************************************
** Function: Cyberdemon Non-Default Constructor
** Description: Creates a cyberdemon object
** Parameters: health, damage_max, name
** Pre-Conditions: none
** Post-Conditions: Cyberdemon object exists
*********************************************************************/ 
CyberDemon::CyberDemon(int health, int damage_max, string name) : Demon(health, damage_max, name) {}

/*********************************************************************
** Function: Cyberdemon default constructor
** Description: Creates a cyberdemon with default values.
** Parameters: None
** Pre-Conditions: None
** Post-Conditions: Cyberdemon object exists
*********************************************************************/ 
CyberDemon::CyberDemon() : Demon(200, 50, "CyberDemon") {}


/*********************************************************************
** Function: Get payoff
** Description: returns the payoff of the type
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: returned payoff
*********************************************************************/ 
int CyberDemon::get_payoff() const {
	return Demon::get_payoff() + 20;
}

/*********************************************************************
** Function: Get cost
** Description: returns cost of the type
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: returned cost
*********************************************************************/ 
int CyberDemon::get_cost() const {
	return Demon::get_cost() + 10;
}