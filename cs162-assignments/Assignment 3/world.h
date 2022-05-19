/*********************************************************************
** Program Filename: world.h
** Author: Logan Saso
** Date: May 14th
** Description: World Class Definitions
** Input: Health, Damage_Max, Name
** Output: Stats
*********************************************************************/

#ifndef world_h
#define world_h

#include "creature.h"
#include "balrog.h"
#include "cyberdemon.h"
#include "demon.h"
#include "elf.h"
#include "paladin.h"
#include "human.h"

using namespace std;

class World
{
	private:
		Balrog *_balrogs;
		CyberDemon *_cyberdemons;
		Human *_humans;
		Elf *_elves;
		Paladin *_paladins;
		int _balrogs_num;
		int _cyberdemons_num;
		int _humans_num;
		int _elves_num;
		int _paladins_num;
		int _creature_num;
		int _money;

	public:

		//Big Importants
		World();			  //default constructor
		~World();			  //destructor
		World(const World &); //copy constructor
		void operator=(const World &); //operator overload

		//Adders
		void add_balrog(const Balrog);
		void add_cyberdemon(const CyberDemon);
		void add_elf(const Elf);
		void add_human(const Human);
		void add_paladin(const Paladin);

		//Getters
		Balrog *get_balrogs() const;
		CyberDemon *get_cyberdemons() const;
		Elf *get_elves() const;
		Human *get_humans() const;
		Paladin *get_paladins() const;
		int get_money() const;

		//Functional
		void extend_paladins();
		void extend_elves();
		void extend_humans();
		void extend_cyberdemons();
		void extend_balrogs();
		void play();
		void buy_characters();
		void set_money(const int);
		void instructions();
		void buy_choice_character(int);
		bool keep_going(string);
		void play_game();



	template <class T, class X> void do_round(T&, X&);
};

#endif