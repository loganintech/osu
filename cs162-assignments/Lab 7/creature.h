#ifndef creature_h
#define creature_h

#include <string>
#include <cstdlib>
using namespace std;

class Creature
{
protected:
	int _health;
	int _damage_max;
	string _name;

public:
	Creature();
	Creature(int, int, string);

	int getHitpoints() const;
	int getDamage_max() const;
	virtual int getDamage() const;
	string getSpecies() const;
	int get_payoff() const;
	int get_cost() const;
	void setHitpoints(const int);
	void setStrength(const int);
	void set_name(const string);
	void decrease_health(const int);
};

#endif