/*********************************************************************
** Program Filename: flying.h
** Author: Logan Saso
** Date: May 29th
** Description: Flying type definitions
** Input: None
** Output: Definitions
*********************************************************************/

#ifndef flying_h
#define flying_h

#include "pokemon.h"

class Flying : public Pokemon {
	public:
		Flying();
		Flying(string);
		bool try_capture();
};

#endif