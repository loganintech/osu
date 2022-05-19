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