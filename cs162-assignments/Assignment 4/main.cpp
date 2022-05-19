/*********************************************************************
** Program Filename: main.cpp
** Author: Logan Saso
** Date: May 29th
** Description: Play pokegomon
** Input: None
** Output: Create everything
*********************************************************************/

#include <iostream>
#include "world.h"
#include <iostream>
#include <cstdlib>

using namespace std;


/*********************************************************************
** Function: keep playing
** Description: keeps playing
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: returns bool with answer
*********************************************************************/
bool keep_playing() {
	cout << "Do you want to play again? [0] yes [1] no: ";
	int choice; 
	cin >> choice;
	return choice == 0;
}


/*********************************************************************
** Function: Main
** Description: entry point for our program
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: program over
*********************************************************************/
int main(int argc, char *argv[]){

	if(argc < 3){
		cout << "You need to give an X and Y size for the world." << endl;
		return 0;
	}

	do {
		World * a_whole_new_world = new World(atoi(argv[1]), atoi(argv[2]));
		a_whole_new_world->play();
		delete a_whole_new_world;
	} while(keep_playing());

	return 0;	
}