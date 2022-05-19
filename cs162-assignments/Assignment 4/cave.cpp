/*********************************************************************
** Program Filename: cave.cpp
** Author: Logan Saso
** Date: May 29th
** Description: Cave functionality
** Input: None
** Output: Functions
*********************************************************************/

#include <iostream>
#include <cstdlib>
#include "cave.h"

/*********************************************************************
** Function: Get nearby string
** Description: Returns the nearby string
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: returns nearby string
*********************************************************************/
string Cave::get_nearby_string() const {
	return "There is a cave nearby, you might be able to find it.";
}

/*********************************************************************
** Function: Do event
** Description: Does the event
** Parameters: Trainer
** Pre-Conditions: Trainer exists
** Post-Conditions: Gives the trainer a reward
*********************************************************************/
void Cave::do_event(Trainer & trainer) {
	int reward = (rand() % 5);
	cout << "You have received " << reward << " stones.";
	trainer.set_stones(trainer.get_stones() + reward);
}