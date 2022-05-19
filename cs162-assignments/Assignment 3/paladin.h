/*********************************************************************
** Program Filename: paladin.cpp
** Author: Logan Saso
** Date: May 14th
** Description: Paladin Class Definitions
** Input: Health, Damage_Max, Name
** Output: Stats
*********************************************************************/

#ifndef paladin_h
#define paladin_h

#include <string>
#include "creature.h"

using namespace std;

class Paladin : public Creature
{
	public:
		Paladin();
		Paladin(int, int, string);
		int get_damage() const;
		int get_payoff() const;
		int get_cost() const;
};

#endif