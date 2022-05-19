/*********************************************************************
** Program Filename: cyberdemon.h
** Author: Logan Saso
** Date: May 14th
** Description: CyberDemon Class Definitions
** Input: Health, Damage_Max, Name
** Output: Stats
*********************************************************************/

#ifndef cyberdemon_h
#define cyberdemon_h

#include <string>
#include "demon.h"
#include "creature.h"

using namespace std;

class CyberDemon : public Demon
{
	public:
		CyberDemon();
		CyberDemon(int, int, string);
		int get_payoff() const;
		int get_cost() const;
};

#endif