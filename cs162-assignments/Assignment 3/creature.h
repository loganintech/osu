/*********************************************************************
** Program Filename: creature.h
** Author: Logan Saso
** Date: May 14th
** Description: Creature Class Definitions
** Input: Health, Damage_Max, Name
** Output: Stats
*********************************************************************/

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

		int get_health() const;
		int get_damage_max() const;
		int get_damage() const;
		string get_name() const;
		int get_payoff() const;
		int get_cost() const;
		void set_health(const int);
		void set_damage_max(const int);
		void set_name(const string);
		void decrease_health(const int);
};

#endif