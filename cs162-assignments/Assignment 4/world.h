/*********************************************************************
** Program Filename: world.h
** Author: Logan Saso
** Date: May 29th
** Description: World definitions
** Input: None
** Output: Definitions
*********************************************************************/

#ifndef world_h
#define world_h

#include "pokemon.h"
#include "event.h"
#include "trainer.h"
#include "location.h"

class World {

	private:
		Trainer * _trainer;
		Location *** _board;
		int _x_max;
		int _y_max;
	public:

		World();
		World(int x, int y);
		~World();
		World(const World &);
		void operator=(const World &);

		bool keep_playing();
		void play();
		bool check_with_oak();
		void evolve_pokemon();
		void move(int);
		void percept();
		void check_stats();
};







#endif