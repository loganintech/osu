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
	int getDamage() const;
	int get_payoff() const;
	int get_cost() const;
};

#endif