/*********************************************************************
** Program Filename: elf.h
** Author: Logan Saso
** Date: May 14th
** Description: Elf Class Definitions
** Input: Health, Damage_Max, Name
** Output: Stats
*********************************************************************/

#ifndef elf_h
#define elf_h

#include <string>
#include "creature.h"

using namespace std;

class Elf : public Creature
{
	public:
		Elf();
		Elf(int, int, string);
		int get_damage() const;
		int get_payoff() const;
		int get_cost() const;
};

#endif