/*********************************************************************
** Program Filename: demon.h
** Author: Logan Saso
** Date: May 14th
** Description: Demon Class Definitions
** Input: Health, Damage_Max, Name
** Output: Stats
*********************************************************************/

#ifndef demon_h
#define demon_h

#include <string>
#include <cstdlib>
#include "creature.h"
using namespace std;

class Demon : public Creature
{
	public:
		Demon();
		Demon(int, int, string);
		int get_damage() const;
		int get_payoff() const;
		int get_cost() const;
};

#endif