/*********************************************************************
** Program Filename: pokestop.cpp
** Author: Logan Saso
** Date: May 29th
** Description: Pokestop functionality
** Input: None
** Output: Functions
*********************************************************************/

#include <iostream>
#include <cstdlib>
#include "pokestop.h"

/*********************************************************************
** Function: Get nearby string
** Description: Returns the nearby string
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: returns nearby string
*********************************************************************/
string Pokestop::get_nearby_string() const {
	return "There is a pokemon nearby, you might be able to find it.";
}

/*********************************************************************
** Function: Do event
** Description: Does the event
** Parameters: Trainer
** Pre-Conditions: Trainer exists
** Post-Conditions: Gives the trainer a reward
*********************************************************************/
void Pokestop::do_event(Trainer &trainer) {
	int pokeballs = (rand() % 7) + 3;
	cout << "You have received " << pokeballs << " pokeballs.";
	trainer.set_pokeballs(trainer.get_pokeballs() + pokeballs);
}