#include <cstdlib>
#include "cave.h"
#include "pokestop.h"
#include "pokemon_encounter.h"
/*********************************************************************
** Program Filename: world.cpp
** Author: Logan Saso
** Date: May 29th
** Description: World functionality
** Input: None
** Output: Functions
*********************************************************************/

#include "location.h"
#include "pokemon.h"
#include "world.h"
#include "trainer.h"
#include <vector>
#include <iostream>

using namespace std;

/*********************************************************************
** Function: Constructor
** Description: Constructs
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: Object created
*********************************************************************/
World::World(int x, int y) {
	_board = new Location**[x];
	for(int i = 0; i < x; i++){
		_board[i] = new Location*[y];
		for(int z = 0; z < y; z++){
			
			switch(rand() % 5){
				case 0:
				case 1:
					_board[i][z] = new Location();
					break;
				case 2:
					_board[i][z] = new Location(new Pokemon_Encounter());					
					break;
				case 3:
					_board[i][z] = new Location(new Pokestop());
					break;
				case 4:
					_board[i][z] = new Location(new Cave());
			}
		}
	}

	_trainer = new Trainer(x, y);
	_x_max = x;
	_y_max = y;
}

/*********************************************************************
** Function: Constructor
** Description: Constructs
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: Object created
*********************************************************************/
World::World() {
	World(12, 12);
}

/*********************************************************************
** Function: Destructor
** Description: Destructs
** Parameters: none
** Pre-Conditions: Object exists
** Post-Conditions: Object destroyed
*********************************************************************/
World::~World() {
	for(int i = 0; i < _x_max; i++){
		for(int z = 0; z < _y_max; z++){
			delete _board[i][z];
		}
		delete[] _board[i];
	}
	delete [] _board;
	delete _trainer;
}

/*********************************************************************
** Function: Play
** Description: Plays the game
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: game is played
*********************************************************************/
void World::play() {
	int choice;
	bool won_game = false;
	do {
		cout << "You are at: " << _trainer->x_location() << ", " << _trainer->y_location() << endl;
		cout << "You are playing POKEGOMON." << endl
			<< "__________________________" << endl
			<< "[0] Move Up" << endl
			<< "[1] Move Down" << endl
			<< "[2] Move Right" << endl
			<< "[3] Move Left" << endl
			<< "[4] Check with Oak" << endl
			<< "[5] Evolve Pokemon" << endl
			<< "[6] Check Stats" << endl
			<< "Input: ";
		cin >> choice;
		switch (choice){
			case 0:
			case 1:
			case 2:
			case 3:
				move(choice);
				break;
			case 4:
				won_game = check_with_oak();
				break;
			case 5:
				evolve_pokemon();
				break;
			default:
				check_stats();
		}
		if(_board[_trainer->x_location()][_trainer->y_location()]->get_has_event() && choice < 4){
			_board[_trainer->x_location()][_trainer->y_location()]->get_event()->do_event(*_trainer);
		}
		percept();
		cout << endl << endl << endl << endl;
	} while (/*keep_playing() &&*/ !won_game);

}

/*********************************************************************
** Function: Percept
** Description: Percepts
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: prints some percepts
*********************************************************************/
bool World::keep_playing() {
	cout << "Would you like to keep playing? [0] yes [1] no." << endl;
	int choice;
	cin >> choice;
	return choice == 0;
}

/*********************************************************************
** Function: Evolve pokemon
** Description: Evolves pokemon
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: PICKACHEWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
*********************************************************************/
void World::evolve_pokemon() {
	vector<Pokemon *> pokemon = _trainer->get_pokemon();
	if(pokemon.size() < 1){
		cout << "You don't have any pokemon yet, go grab some!" << endl;
		return;
	}
	if(_trainer->get_stones() < 1) {
		cout << "You don't have any evolution stones yet, go find a cave." << endl;
		return;
	}
	cout << "You have " << _trainer->get_stones() << " evolution stones." << endl;
	for(int i = 0; i < pokemon.size(); i++){
		if(pokemon[i]->get_evolution() < 2) cout << "[" << i << "] " << pokemon[i]->get_name() << " - " << pokemon[i]->get_evolution() << endl;
	}
	cout << "Pick which pokemon to evolve: " << endl;
	int choice;
	cin >> choice;
	if(pokemon[choice]->get_evolution() < 2) {
		pokemon[choice]->set_evolution(pokemon[choice]->get_evolution() + 1);
	} else {
		cout << "That pokemon is already fully evolved." << endl;
	}
}

/*********************************************************************
** Function: Check with oak
** Description: Checks with oak
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: Wins game, or doesn't
*********************************************************************/
bool World::check_with_oak() {
	int pokemon_fully_evolved = 0;
	vector<Pokemon *> pokemon = _trainer->get_pokemon();
	for(int i = 0; i < pokemon.size(); i++){
		if(pokemon[i]->get_evolution() >= 2) pokemon_fully_evolved++;
	}
	if(pokemon_fully_evolved >= 6){
		cout << "Oak: Congrats student, you have become a pokemon master!" << endl;
		return true;
	} else {
		cout << "Not quite student, you need " << 6 - pokemon_fully_evolved << " more fully evolved pokemon. Go hunting!" << endl;
		check_stats();
	}
	return false;
}

/*********************************************************************
** Function: move
** Description: moves character
** Parameters: post direction
** Pre-Conditions: none
** Post-Conditions: trainer moved
*********************************************************************/
void World::move(int direction) {
	switch(direction){
		case 0:
			if(_trainer->y_location() > 0){ //up
				_trainer->set_y(_trainer->y_location() - 1);
			}
			break;
		case 1:
			if(_trainer->y_location() < _y_max - 1){ // down
				_trainer->set_y(_trainer->y_location() + 1);
			}
			break;
		case 2:
			if(_trainer->x_location() < _x_max - 1){ // right
				_trainer->set_x(_trainer->x_location() + 1);
			}
			break;
		case 3:
			if(_trainer->x_location() > 0){ //left
				_trainer->set_x(_trainer->x_location() - 1);
			}
	}
}


/*********************************************************************
** Function: Percept
** Description: Percepts
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: prints some percepts
*********************************************************************/
void World::percept() {
	cout << "YOU CAN PERCEPT THINGS AND STUFF" << endl;
	if(_trainer->y_location() > 0 && _trainer->x_location() > 0){ //top left
		if(_board[_trainer->x_location() - 1][_trainer->y_location() - 1]->get_has_event()){
			cout << _board[_trainer->x_location() - 1][_trainer->y_location() - 1]->get_event()->get_nearby_string() << endl;
		}
	}

	if(_trainer->y_location() > 0){ //up
		if(_board[_trainer->x_location()][_trainer->y_location() - 1]->get_has_event()){
			cout << _board[_trainer->x_location()][_trainer->y_location() - 1]->get_event()->get_nearby_string() << endl;
		}
	}

	if(_trainer->y_location() > 0 && _trainer->x_location() < _x_max - 1){ //top right
		if(_board[_trainer->x_location() + 1][_trainer->y_location() - 1]->get_has_event()){
			cout << _board[_trainer->x_location() + 1][_trainer->y_location() - 1]->get_event()->get_nearby_string() << endl;
		}
	}
	
	if( _trainer->x_location() < _x_max - 1){ //right
		if(_board[_trainer->x_location() + 1][_trainer->y_location()]->get_has_event()){
			cout << _board[_trainer->x_location() + 1][_trainer->y_location()]->get_event()->get_nearby_string() << endl;
		}
	}

	if(_trainer->y_location() < _y_max - 1 && _trainer->x_location() < _x_max - 1){ //bottom right
		if(_board[_trainer->x_location() + 1][_trainer->y_location() + 1]->get_has_event()){
			cout << _board[_trainer->x_location() + 1][_trainer->y_location() + 1]->get_event()->get_nearby_string() << endl;
		}
	}


	if(_trainer->y_location() < _y_max - 1){ //down
		if(_board[_trainer->x_location()][_trainer->y_location() + 1]->get_has_event()){
			cout << _board[_trainer->x_location()][_trainer->y_location() + 1]->get_event()->get_nearby_string() << endl;
		}
	}

	if(_trainer->y_location() < _y_max - 1 && _trainer->x_location() < 0){ //bottom left
		if(_board[_trainer->x_location() - 1][_trainer->y_location() + 1]->get_has_event()){
			cout << _board[_trainer->x_location() - 1][_trainer->y_location() + 1]->get_event()->get_nearby_string() << endl;
		}
	}

	if(_trainer->x_location() > 0){ //bottom right
		if(_board[_trainer->x_location() - 1][_trainer->y_location()]->get_has_event()){
			cout << _board[_trainer->x_location() - 1][_trainer->y_location()]->get_event()->get_nearby_string() << endl;
		}
	}
}

/*********************************************************************
** Function: check status
** Description: Checks all of your information
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: Checks stats
*********************************************************************/
void World::check_stats() {
	cout << "You have " << _trainer->get_pokeballs() << " pokeballs and " << _trainer->get_stones() << " stones." << endl;
	cout << "Your Pokemon: " << endl;
	for(int i = 0; i < _trainer->get_pokemon().size(); i++){
		cout << _trainer->get_pokemon()[i]->get_name() << ": " << _trainer->get_pokemon()[i]->get_evolution() << endl;
	}

}

/*********************************************************************
** Function: Operator=
** Description: Object set
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: Object set to other object
*********************************************************************/
void World::operator=(const World &other){

}

/*********************************************************************
** Function: Copy Constructor
** Description: Copies
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: Object set to other object
*********************************************************************/
World::World(const World &other){

}