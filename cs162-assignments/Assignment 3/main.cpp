/*********************************************************************
** Program Filename: main.cpp
** Author: Logan Saso
** Date: May 14th
** Description: Entry point for your program
** Input: Health, Damage_Max, Name
** Output: Stats
*********************************************************************/

#include "creature.h"
#include "demon.h"
#include "cyberdemon.h"
#include "balrog.h"
#include "human.h"
#include "elf.h"
#include "world.h"
#include <string>
#include <iostream>
#include <cstdlib>

using namespace std;

/*********************************************************************
** Function: Keep playing
** Description: asks to keep playing
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: returns a bool
*********************************************************************/ 
bool keep_playing() {
	cout << "Do you want to keep playing? [0] yes [1] no: ";
	int choice;
	cin >> choice;
	while(cin.fail()){
		cout << "That was not a number, please input a number: ";
		cin >> choice;
	}
	return choice == 0;
}

/*********************************************************************
** Function: main
** Description: is main
** Parameters: argc argv
** Pre-Conditions: none 
** Post-Conditions: game over
*********************************************************************/ 
int main(int argc, char *argv[])
{
	World a_whole_new_world;
	do {
		a_whole_new_world.play();
	} while (keep_playing());

	return 0;
}