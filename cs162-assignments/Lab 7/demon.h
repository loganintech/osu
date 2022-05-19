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
	int getDamage() const;
	int get_payoff() const;
	int get_cost() const;
};

#endif