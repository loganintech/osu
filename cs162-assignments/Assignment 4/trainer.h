/*********************************************************************
** Program Filename: trainer.h
** Author: Logan Saso
** Date: May 29th
** Description: Trainer definitions
** Input: None
** Output: Definitions
*********************************************************************/

#ifndef trainer_h
#define trainer_h

#include "pokemon.h"
#include <vector>

using namespace std;



class Trainer {
	private:
		vector<Pokemon *> _pokemon;
		int _pokeballs;
		int _stones;
		int _x_location;
		int _y_location;
	public:
		Trainer(int x_max, int y_max);
		~Trainer();
		Trainer(const Trainer &other);
		void operator=(const Trainer &other);

		void set_location(const int x_location, const int y_location);
		void set_y(const int y_location);
		void set_x(const int x_location);
		int y_location() const ;
		int x_location() const ;
		vector<Pokemon *> get_pokemon();
		void add_pokemon(Pokemon *);
		int get_pokeballs() const;
		void set_pokeballs(int);
		void set_stones(int);
		int get_stones();
};

#endif