/*********************************************************************
** Program Filename: trainer.cpp
** Author: Logan Saso
** Date: May 29th
** Description: Trainer functionality
** Input: None
** Output: Functions
*********************************************************************/

#include <vector>
#include <cstdlib>
#include <ctime>
#include "pokemon.h"
#include "trainer.h"
#include "flying.h"
#include "rock.h"
#include "psychic.h"

using namespace std;

/*********************************************************************
** Function: Constructor
** Description: Constructs
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: Object created
*********************************************************************/
Trainer::Trainer(int x_max, int y_max){
	_pokeballs = 0;
	_stones = 0;
	srand(time(0));			
	_x_location = rand() % x_max;
	_y_location = rand() % y_max;
}

/*********************************************************************
** Function: Constructor
** Description: Constructs
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: Object created
*********************************************************************/
Trainer::Trainer() {
	Trainer(12, 12);
}

/*********************************************************************
** Function: Destructor
** Description: Destructs
** Parameters: none
** Pre-Conditions: Object exists
** Post-Conditions: Object destroyed
*********************************************************************/
Trainer::~Trainer(){
	for(int i = 0; i < _pokemon.size(); i++){
		delete _pokemon[i];
	}
	_pokemon.clear();
}
Trainer::Trainer(const Trainer &other){
	for(int i = 0; i < other._pokemon.size(); i++){
		_pokemon.push_back(other._pokemon[i]);
	}
	_pokeballs = other._pokeballs;
	_stones = other._stones;
	_x_location = other._x_location;
	_y_location = other._y_location;
}

/*********************************************************************
** Function: Operator=
** Description: Object set
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: Object set to other object
*********************************************************************/
void Trainer::operator=(const Trainer &other){
	for(int i = 0; i < _pokemon.size(); i++){
		delete _pokemon[i];
	}
	_pokemon.clear(); //sets array size to nothin
	for(int i = 0; i < other._pokemon.size(); i++){
		_pokemon.push_back(other._pokemon[i]);
	}
	_pokeballs = other._pokeballs;
	_stones = other._stones;
	_x_location = other._x_location;
	_y_location = other._y_location;
}

/*********************************************************************
** Function: set location
** Description: sets x and y locations
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: sets x and y locations
*********************************************************************/
void Trainer::set_location(const int x_location, const int y_location){
	_x_location = x_location;
	_y_location = y_location;
}

/*********************************************************************
** Function: set y
** Description: sets y
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: y location set
*********************************************************************/
void Trainer::set_y(const int y_location){
	_y_location = y_location;
}

/*********************************************************************
** Function: set x
** Description: sets x
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: x location set
*********************************************************************/
void Trainer::set_x(const int x_location){
	_x_location = x_location;
}

/*********************************************************************
** Function: y location
** Description: gets y location
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: y location returned
*********************************************************************/
int Trainer::y_location() const {
	return _y_location;
}

/*********************************************************************
** Function: x location
** Description: gets x location
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: x location returned
*********************************************************************/
int Trainer::x_location() const {
	return _x_location;
}

/*********************************************************************
** Function: get pokemon
** Description: gets pokemon
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: pokemon got
*********************************************************************/
vector<Pokemon *> Trainer::get_pokemon() {
	return _pokemon;
}

/*********************************************************************
** Function: get pokeballs
** Description: gets pokeballs
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: Pokeballs got
*********************************************************************/
int Trainer::get_pokeballs() const {
	return _pokeballs;
}

/*********************************************************************
** Function: add pokemon
** Description: adds a pokemon
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: Pokemon added
*********************************************************************/
void Trainer::add_pokemon(Pokemon * pokemon){
	_pokemon.push_back(pokemon);
}

/*********************************************************************
** Function: set pokeballs
** Description: sets pokeballs
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: Sets pokeballs
*********************************************************************/
void Trainer::set_pokeballs(int pokeballs){
	_pokeballs = pokeballs;
}

/*********************************************************************
** Function: get stones
** Description: gets stones
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: Gets the stones
*********************************************************************/
int Trainer::get_stones() {
	return _stones;
}

/*********************************************************************
** Function: set stones
** Description: sets stones
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: stones is set
*********************************************************************/
void Trainer::set_stones(int stones) {
	_stones = stones;
}