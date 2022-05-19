/*********************************************************************
** Program Filename: human.cpp
** Author: Logan Saso
** Date: May 14th
** Description: Human Class Definitions
** Input: Health, Damage_Max, Name
** Output: Stats
*********************************************************************/

#ifndef human_h
#define human_h

#include <string>
#include "creature.h"

using namespace std;

class Human : public Creature
{
	public:
		Human();
		Human(int, int, string);
		int get_payoff() const;
		int get_cost() const;
};

#endif