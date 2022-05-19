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
	int getDamage() const;
	int get_payoff() const;
	int get_cost() const;
};

#endif