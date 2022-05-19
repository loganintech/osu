/*********************************************************************
** Program Filename: balrog.h
** Author: Logan Saso
** Date: May 14th
** Description: Balrog Class Definitions
** Input: Health, Damage_Max, Name
** Output: Stats
*********************************************************************/

#ifndef balrog_h
#define balrog_h

#include <string>
#include "demon.h"

using namespace std;

class Balrog : public Demon
{
	public:
		Balrog();
		Balrog(int, int, string);
		int get_damage() const;
		int get_payoff() const;
		int get_cost() const;
};

#endif