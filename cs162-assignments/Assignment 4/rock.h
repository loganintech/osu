/*********************************************************************
** Program Filename: rock.h
** Author: Logan Saso
** Date: May 29th
** Description: Rock type definitions
** Input: None
** Output: Definitions
*********************************************************************/

#ifndef rock_h
#define rock_h

#include "pokemon.h"

class Rock : public Pokemon {
	public:
		Rock();
		Rock(string);
		bool try_capture();
};

#endif