/*********************************************************************
** Program Filename: psychic.h
** Author: Logan Saso
** Date: May 29th
** Description: Psychic type definitions
** Input: None
** Output: Definitions
*********************************************************************/

#ifndef psychic_h
#define psychic_h

#include "pokemon.h"

class Psychic : public Pokemon {
	public:
		Psychic();
		Psychic(string);
		bool try_capture();
};

#endif