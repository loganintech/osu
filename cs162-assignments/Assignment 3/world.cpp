/*********************************************************************
** Program Filename: world.cpp
** Author: Logan Saso
** Date: May 14th
** Description: World Class Implementations
** Input: Health, Damage_Max, Name
** Output: Stats
*********************************************************************/

#include "creature.h"
#include "balrog.h"
#include "cyberdemon.h"
#include "demon.h"
#include "elf.h"
#include "human.h"
#include "paladin.h"
#include "world.h"
#include <iostream>

using namespace std;

/*********************************************************************
** Function: World()
** Description: Constructor
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: Creates the world
*********************************************************************/
World::World()
{
	srand(time(0));
	_balrogs = new Balrog[0];
	_balrogs_num = 0;
	_cyberdemons = new CyberDemon[0];
	_cyberdemons_num = 0;
	_humans = new Human[0];
	_humans_num = 0;
	_elves = new Elf[0];
	_elves_num = 0;
	_paladins = new Paladin[0];
	_paladins_num = 0;
	_money = 50;
}

/*********************************************************************
** Function: Destructor
** Description: Destroys world
** Parameters: none
** Pre-Conditions: World exists
** Post-Conditions: World destroyed
*********************************************************************/
World::~World()
{
	delete[] _balrogs;
	delete[] _cyberdemons;
	delete[] _humans;
	delete[] _elves;
	delete[] _paladins;
}

/*********************************************************************
** Function: add balrog
** Description: Adds balrog to balrog array
** Parameters: Balrog object
** Pre-Conditions: Balrog object exists
** Post-Conditions: Balrog added to array
*********************************************************************/
void World::add_balrog(const Balrog balrog)
{
	extend_balrogs();
	_balrogs[_balrogs_num++] = balrog;
	_creature_num++;
}

/*********************************************************************
** Function: add cyberdemon
** Description: Adds cyberdemon
** Parameters: cyberdemon object
** Pre-Conditions: cyberdemon
** Post-Conditions: cyberdemon added to array
*********************************************************************/
void World::add_cyberdemon(const CyberDemon cyberdemon)
{
	extend_cyberdemons();
	_cyberdemons[_cyberdemons_num++] = cyberdemon;
	_money -= cyberdemon.get_cost();
	_creature_num++;
}

/*********************************************************************
** Function: add elf
** Description: Adds elf to elf array
** Parameters: Elf object
** Pre-Conditions: Elf object exists
** Post-Conditions: Elf added to array
*********************************************************************/
void World::add_elf(const Elf elf)
{
	extend_elves();
	_elves[_elves_num++] = elf;
	_money -= elf.get_cost();
	_creature_num++;
}

/*********************************************************************
** Function: add human
** Description: Adds human to human array
** Parameters: Human object
** Pre-Conditions: Human object exists
** Post-Conditions: Human added to array
*********************************************************************/
void World::add_human(const Human human)
{
	extend_humans();
	_humans[_humans_num++] = human;
	_money -= human.get_cost();
	_creature_num++;
}

/*********************************************************************
** Function: add paladin
** Description: Adds paladin to paladin array
** Parameters: Paladin object
** Pre-Conditions: Paladin object exists
** Post-Conditions: Paladin added to array
*********************************************************************/
void World::add_paladin(const Paladin paladin)
{
	extend_paladins();
	_paladins[_paladins_num++] = paladin;
	_money -= paladin.get_cost();
	_creature_num++;
}

/*********************************************************************
** Function: get balrogs
** Description: Get balrog array
** Parameters: none
** Pre-Conditions: balrog array exists
** Post-Conditions: returned
*********************************************************************/
Balrog *World::get_balrogs() const
{
	return _balrogs;
}

/*********************************************************************
** Function: get cyberdemons
** Description: Get cyberdemons array
** Parameters: none
** Pre-Conditions: cyberdemon array exists
** Post-Conditions: returned
*********************************************************************/
CyberDemon *World::get_cyberdemons() const
{
	return _cyberdemons;
}

/*********************************************************************
** Function: get elves
** Description: Get elf array
** Parameters: none
** Pre-Conditions: efl array exists
** Post-Conditions: returned
*********************************************************************/
Elf *World::get_elves() const
{
	return _elves;
}

/*********************************************************************
** Function: get humans
** Description: Get human array
** Parameters: none
** Pre-Conditions: human array exists
** Post-Conditions: returned
*********************************************************************/
Human *World::get_humans() const
{
	return _humans;
}

/*********************************************************************
** Function: get paladins
** Description: Get paladin array
** Parameters: none
** Pre-Conditions: paladin array exists
** Post-Conditions: returned
*********************************************************************/
Paladin *World::get_paladins() const
{
	return _paladins;
}

/*********************************************************************
** Function: extend balrogs
** Description: Increases the length of the balrog array
** Parameters: none
** Pre-Conditions: balrog array exists
** Post-Conditions: balrog array one longer
*********************************************************************/
void World::extend_balrogs()
{
	Balrog *temp = new Balrog[_balrogs_num + 1]; //creates new array on the heap of one larger
	for (int i = 0; i < _balrogs_num; i++)		 //copies old array to new array
	{
		temp[i] = _balrogs[i];
	}
	delete[] _balrogs; //deletes old array
	_balrogs = temp;   //sets old array pointer to new array
}

/*********************************************************************
** Function: extend cyberdemons
** Description: Increases the length of the cyberdemon array
** Parameters: none
** Pre-Conditions: cyberdemon array exists
** Post-Conditions: cyberdemon array one longer
*********************************************************************/
void World::extend_cyberdemons()
{
	CyberDemon *temp = new CyberDemon[_cyberdemons_num + 1]; //creates new array on the heap of one larger
	for (int i = 0; i < _cyberdemons_num; i++)				 //copies old array to new array
	{
		temp[i] = _cyberdemons[i];
	}
	delete[] _cyberdemons; //deletes old array
	_cyberdemons = temp;   //sets old array pointer to new array
}

/*********************************************************************
** Function: extend elves
** Description: Increases the length of the elf array
** Parameters: none
** Pre-Conditions: elf array exists
** Post-Conditions: elf array one longer
*********************************************************************/
void World::extend_elves()
{
	Elf *temp = new Elf[_elves_num + 1]; //creates new array on the heap of one larger
	for (int i = 0; i < _elves_num; i++) //copies old array to new array
	{
		temp[i] = _elves[i];
	}
	delete[] _elves; //deletes old array
	_elves = temp;   //sets old array pointer to new array
}

/*********************************************************************
** Function: extend humans
** Description: Increases the length of the human array
** Parameters: none
** Pre-Conditions: human array exists
** Post-Conditions: human array one longer
*********************************************************************/
void World::extend_humans()
{
	Human *temp = new Human[_humans_num + 1]; //creates new array on the heap of one larger
	for (int i = 0; i < _humans_num; i++) //copies old array to new array
	{
		temp[i] = _humans[i];
	}
	delete[] _humans; //deletes old array
	_humans = temp;   //sets old array pointer to new array
}

/*********************************************************************
** Function: extend paladins
** Description: Increases the length of the paladin array
** Parameters: none
** Pre-Conditions: paladin array exists
** Post-Conditions: paladin array one longer
*********************************************************************/
void World::extend_paladins()
{
	Paladin *temp = new Paladin[_paladins_num + 1]; //creates new array on the heap of one larger
	for (int i = 0; i < _paladins_num; i++) 		//copies old array to new array
	{
		temp[i] = _paladins[i];
	}
	delete[] _paladins; //deletes old array
	_paladins = temp;   //sets old array pointer to new array
}

/*********************************************************************
** Function: do round
** Description: Does a round
** Parameters: none
** Pre-Conditions: game is setup
** Post-Conditions: damage is dealt or ignored
*********************************************************************/
template <class T, class X> void World::do_round(T &one, X &two)
{
	if(one.get_health() < 0 || two.get_health() < 0) return; //For some reason something with no health was passed, this round is forfeit.

	cout << "Starting Healths" << endl
		 << "________________" << endl;
	cout << one.get_name() << ": " << one.get_health() << endl;
	cout << two.get_name() << ": " << two.get_health() << endl;

	cout << one.get_name() << " is fighting " << two.get_name() << endl ;
	int onedamage = one.get_damage();
	two.decrease_health(onedamage); //You attack them and decrease their health
	cout << one.get_name() << " hit " << two.get_name() << " for " << onedamage << endl;
	if(two.get_health() > 0){ //If they aren't dead
		int twodamage = two.get_damage();
		cout << two.get_name() << " hit " << one.get_name() << " for " << twodamage << endl;
		one.decrease_health(twodamage); //They attack you and decrease your health
	} else { //If they are dead
		cout << one.get_name() << " killed " << two.get_name() << endl;
		_money += one.get_payoff(); //Increase your money by how much you get for a win
	}

	if(one.get_health() <= 0){
		cout << one.get_name() << " was killed by " << two.get_name() << endl;
		_creature_num--;
	}

	cout << "Ending Healths" << endl
		 << "______________" << endl;
	cout << one.get_name() << ": " << one.get_health() << endl;
	cout << two.get_name() << ": " << two.get_health() << endl;
	cout << endl << endl;
	//Money was already taken out when they bought characters so

}

/*********************************************************************
** Function: play
** Description: Starts the game
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: game is over
*********************************************************************/
void World::play()
{
	instructions();
	buy_characters();
	play_game();
	cout << "You have: " << _money << " in the bank." << endl;
}

/*********************************************************************
** Function: instructions
** Description: prints instructions
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: instructions printed
*********************************************************************/
void World::instructions()
{
	cout << "Thanks for playing this game, you have " << get_money() << " gold to play with." << endl;
	cout << "The rules are simple, you are player one and the computer is player two." << endl;
	cout << "You have to buy characters to play with and they will be faced against one balrog and one elf each time." << endl;
}

/*********************************************************************
** Function: buy characters
** Description: Prompts to buy characters
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: characters bought
*********************************************************************/
void World::buy_characters()
{
	cout << "You are buying characters now. I will list each one and their cost." << endl;
	CyberDemon cyberdemon;
	cout << "[0] " << cyberdemon.get_name() << " Cost: " << cyberdemon.get_cost() << " Payoff: " << cyberdemon.get_payoff() << endl;
	Balrog balrog;
	cout << "[1] " << balrog.get_name() << " Cost: " << balrog.get_cost() << " Payoff: " << balrog.get_payoff() << endl;
	Elf elf;
	cout << "[2] " << elf.get_name() << " Cost: " << elf.get_cost() << " Payoff: " << elf.get_payoff() << endl;
	Human human;
	cout << "[3] " << human.get_name() << " Cost: " << human.get_cost() << " Payoff: " << human.get_payoff() << endl;
	Paladin paladin;
	cout << "[4] " << paladin.get_name() << " Cost: " << paladin.get_cost() << " Payoff: " << paladin.get_payoff() << endl;
	int choice;
	do {
		cout << "Purchase: ";
		cin >> choice;
		buy_choice_character(choice);
	} while (keep_going("picking"));
}

/*********************************************************************
** Function: play game
** Description: Does the actual rounds
** Parameters: none
** Pre-Conditions: arrays exist, characters bought
** Post-Conditions: Game over
*********************************************************************/
void World::play_game() 
{
	Balrog their_balrog;
	Elf their_elf;
	while(_creature_num > 0 && (their_balrog.get_health() > 0 || their_balrog.get_health() > 0)){
		for(int i = 0; i < 5; i++) {
			switch (i){
				case 0:
					for(int x = 0; x < _balrogs_num; x++){
						their_balrog.get_health() > 0 ? do_round(_balrogs[x], their_balrog) : do_round(_balrogs[x], their_elf);
					}
					break;
				case 1:
					for(int x = 0; x < _cyberdemons_num; x++){
						their_balrog.get_health() > 0 ? do_round(_cyberdemons[x], their_balrog) : do_round(_cyberdemons[x], their_elf);
					}
					break;
				case 2:
					for(int x = 0; x < _humans_num; x++){
						their_balrog.get_health() > 0 ? do_round(_humans[x], their_balrog) : do_round(_humans[x], their_elf);
					}
					break;
				case 3:
					for(int x = 0; x < _elves_num; x++){
						their_balrog.get_health() > 0 ? do_round(_elves[x], their_balrog) : do_round(_elves[x], their_elf);
					}
					break;
				case 4:
					for(int x = 0; x < _paladins_num; x++){
						their_balrog.get_health() > 0 ? do_round(_paladins[x], their_balrog) : do_round(_paladins[x], their_elf);
					}
			}
		}
	}
}

/*********************************************************************
** Function: buy choice character
** Description: Pass a number to buy a character. This is only to decrease method length and has no other practical purpose.
** Parameters: none
** Pre-Conditions: a choice is picked
** Post-Conditions: A character is added
*********************************************************************/
void World::buy_choice_character(int choice) {
	Paladin paladin;
	Human human;
	Elf elf;
	CyberDemon cyberdemon;
	Balrog balrog;
	switch(choice) {
		case 0:
			add_cyberdemon(cyberdemon);
			break;
		case 1:
			add_balrog(balrog);
			break;
		case 2:
			add_elf(elf);
			break;
		case 3:
			add_human(human);
			break;
		case 4:
			add_paladin(paladin);
			break;
	}
}

/*********************************************************************
** Function: Keep going
** Description: asks to keep [something]
** Parameters: thing to keep doing as a string
** Pre-Conditions: none
** Post-Conditions: returns a bool
*********************************************************************/ 
bool World::keep_going(string thing) {
	cout << "Do you want to keep " << thing << "? [0] yes [1] no: ";
	int choice;
	cin >> choice;
	while(cin.fail()){
		cout << "That was not a number, please input a number: ";
		cin >> choice;
	}
	return choice == 0;
}

/*********************************************************************
** Function: get money
** Description: gets money
** Parameters: none
** Pre-Conditions: money gotten
** Post-Conditions: money returned
*********************************************************************/ 
int World::get_money() const
{
	return _money;
}

/*********************************************************************
** Function: set money
** Description: sets money
** Parameters: none
** Pre-Conditions: money set
** Post-Conditions: money returned
*********************************************************************/
void World::set_money(const int money)
{
	_money = money;
}

/*********************************************************************
** Function: World(const World &other)
** Description: Copy Constructor
** Parameters: none
** Pre-Conditions: A world object exists
** Post-Conditions: World copied
*********************************************************************/
World::World(const World &other){
	_balrogs = new Balrog[other._balrogs_num];
	for(int i = 0; i < other._balrogs_num; i++){
		_balrogs[i] = other._balrogs[i];
	}
	_cyberdemons = new CyberDemon[other._balrogs_num];	
	for(int i = 0; i < other._cyberdemons_num; i++){
		_cyberdemons[i] = other._cyberdemons[i];
	}
	_humans = new Human[other._humans_num];
	for(int i = 0; i < other._humans_num; i++){
		_humans[i] = other._humans[i];
	}
	_elves = new Elf[other._elves_num];
	for(int i = 0; i < other._elves_num; i++){
		_elves[i] = other._elves[i];
	}
	_paladins = new Paladin[other._paladins_num];
	for(int i = 0; i < other._paladins_num; i++){
		_paladins[i] = other._paladins[i];
	}
}

/*********************************************************************
** Function: operator= overload
** Description: = overload
** Parameters: World object
** Pre-Conditions: Other world object exists
** Post-Conditions: World set
*********************************************************************/
void World::operator=(const World &other){
	delete[] _balrogs;
	delete[] _cyberdemons;
	delete[] _humans;
	delete[] _elves;
	delete[] _paladins;
	_balrogs = new Balrog[other._balrogs_num];
	for(int i = 0; i < other._balrogs_num; i++){
		_balrogs[i] = other.get_balrogs()[i];
	}
	_cyberdemons = new CyberDemon[other._balrogs_num];	
	for(int i = 0; i < other._cyberdemons_num; i++){
		_cyberdemons[i] = other.get_cyberdemons()[i];
	}
	_humans = new Human[other._humans_num];
	for(int i = 0; i < other._humans_num; i++){
		_humans[i] = other.get_humans()[i];
	}
	_elves = new Elf[other._elves_num];
	for(int i = 0; i < other._elves_num; i++){
		_elves[i] = other.get_elves()[i];
	}
	_paladins = new Paladin[other._paladins_num];
	for(int i = 0; i < other._paladins_num; i++){
		_paladins[i] = other.get_paladins()[i];
	}
}