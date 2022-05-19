/*********************************************************************
** Program Filename: pokemon_encounter.h
** Author: Logan Saso
** Date: May 29th
** Description: pokemon_encounter definitions
** Input: None
** Output: Definitions
*********************************************************************/

#ifndef pokemon_encounter_h
#define pokemon_encounter_h

#include "pokemon.h"
#include "event.h"

using namespace std;

class Pokemon_Encounter : public Event {
	public:
		string get_nearby_string() const;
		void do_event(Trainer &);

};

#endif