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
	int getDamage() const;
	int get_payoff() const;
	int get_cost() const;
};

#endif