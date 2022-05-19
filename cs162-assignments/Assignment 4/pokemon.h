/*********************************************************************
** Program Filename: pokemon.h
** Author: Logan Saso
** Date: May 29th
** Description: Pokemon definitions
** Input: None
** Output: Definitions
*********************************************************************/

#ifndef pokemon_h
#define pokemon_h

#include <string>

using namespace std;

class Pokemon {
	protected:
		int _evolution;
		string _name;
	public:
		int get_evolution() const ;
		void set_evolution(const int evolution) ;
		Pokemon();
		Pokemon(string);
		virtual bool try_capture();
		string get_name() const;
};

#endif