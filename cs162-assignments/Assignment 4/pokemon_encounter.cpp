/*********************************************************************
** Program Filename: pokemon_encounter.cpp
** Author: Logan Saso
** Date: May 29th
** Description: pokemon_encounter functionality
** Input: None
** Output: Functions
*********************************************************************/

#include <cstdlib>
#include <iostream>
#include "pokemon_encounter.h"
#include "pokemon.h"

#include "rock.h"
#include "flying.h"
#include "psychic.h"

using namespace std;

/*********************************************************************
** Function: Get nearby string
** Description: Returns the nearby string
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: returns nearby string
*********************************************************************/
string Pokemon_Encounter::get_nearby_string() const {
	return "There is a pokemon nearby, you might be able to find it.";
}

/*********************************************************************
** Function: Do event
** Description: Does the event
** Parameters: Trainer
** Pre-Conditions: Trainer exists
** Post-Conditions: Gives the trainer a reward
*********************************************************************/
void Pokemon_Encounter::do_event(Trainer &trainer) {

	if(trainer.get_pokeballs() < 1){
		cout << "You have no pokeballs!" << endl;
		return;
	}

	Pokemon * reward;

	switch(rand() % 6) {
		case 0:
			reward = new Flying("Rayquaza");
			break;
		case 1:
			reward = new Flying("Charizard");
			break;
		case 2:
			reward = new Psychic("Espeon");
			break;
		case 3:
			reward = new Psychic("Mewtwo");
			break;
		case 4:
			reward = new Rock("Geodude");
			break;
		case 5:
			reward = new Rock("Onyx");
	}

	bool playing = true;
	int choice = 0;
	cout << "You are playing for a " << reward->get_name() << endl; 
	
	if(trainer.get_pokeballs() < 1){
		cout << "You have no pokeballs!" << endl;
		delete reward;
		return;
	}

	do {
		cout << "Throw a pokeball? [0] yes [1] no: ";
		cin >> choice;
		if(choice == 0) {
			trainer.set_pokeballs(trainer.get_pokeballs() - 1);
			cout << "You threw a pokeball, you now have " << trainer.get_pokeballs() << " pokeballs.";
			if(reward->try_capture()){
				cout << "You caught " << reward->get_name() << endl;
				trainer.add_pokemon(reward);
				playing = false;
				return;
			}
		} else {
			playing = false;
			cout << "You have run away." << endl;
			delete reward;
			return;
		}

	} while (trainer.get_pokeballs());

	cout << "You ran out of pokeballs!" << endl;
	delete reward;
}