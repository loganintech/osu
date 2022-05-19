#include <iostream>
#include <cmath>
#include <cstdlib>
#include <cstdint>
#include <ctime>

using namespace std;

bool ask_continue();
bool make_decision();
bool random_chance();
void main_loop();
void intro();
bool leave_bed();
bool walk_down_hall();
bool brave_nuclear_winter();
bool crash_the_plane();
void this_was_actually_a_dream();


int main(){

	bool should_continue = true;

	while(should_continue){
		main_loop();
		should_continue = ask_continue();
	}

	return 0;
}

bool ask_continue(){
	cout << "\n\nDo you want to continue?";
	return make_decision();
}

bool make_decision(){
	int input = 0;
	cout << " [Enter 0 for No or 1 for Yes]: ";
	cin >> input;
	if(input == 0) return false;
	return true;
}

bool random_chance(){
	 if((rand() % 10) == 7) return true;
	 return false;
}

void main_loop(){

	intro();
	if(!leave_bed()) return;
	if(!walk_down_hall()) return;
	if(!brave_nuclear_winter()) return;
	if(!crash_the_plane()) return;
	this_was_actually_a_dream();
	

}

void intro(){
	cout << "Dazed and confused in a hospital, you wake up abruptly." << endl;
	cout << "Medibot 065: You.. you@$%re you%20RE awa*ke." << endl;
	cout << "Medibot 065: You.. you@$%re you%20RE awa*ke." << endl;
	cout << "Medibot 065: You.. you@$%re you%20RE awa*ke." << endl;
	cout << "Medibot 065: You.. you@$%re you%20RE awa*ke." << endl;
	cout << "Medibot 065: You.. you@$%re you%20RE awa*ke." << endl;
	cout << "Medibot 065: You.. you@$%re you%20RE awa*ke." << endl;
	cout << "The medibot had a malfunction." << endl;
	cout << "There's a bit of snow outside... It was summer when you went to sleep." << endl;
}

bool leave_bed(){
	cout << "I guess I should probably get out of bed... Should I?";
	if(!make_decision()){
		cout << "No, I think I'll just stay here until I die." << endl;
		if(!random_chance()) return false;
		cout << "Actually no I'm gonna get out of bed I really want to know why it's snowing." << endl;
	}
	cout << "Whelp, here goes nothing." << endl;
	return true;
}

bool walk_down_hall(){
	cout << "Upon exiting the room, you notice the hallway is empty.\n";
	cout << "Nobody is in the hospital... at all. That's strange.\n";
	cout << "Well I guess there is nothing I can do about that." << endl;

	cout << "You realize you've woken in a radiation ward in the near future." << endl;
	cout << "You probably need some tools. You see a closet over there, do you want to search it?";
	if(make_decision()){
		cout << "You go to the closet looking for some tools." << endl;
		if(random_chance()){
			cout << "UNLUCKY FOR YOU THERE WAS A MUTANT IN THERE THAT MAULS YOU TO DEATH... Oh well." << endl;
			return false;
		} 
		cout << "The only thing in the closet is some burn salve and a flashlight. You grabbed the flashlight, but probably won't need it." << endl;
	} else {
		cout << "You decide to move on. You doubt there's much you can find of interest in there." << endl;
	}
	cout << "You continue to walk down the hallway. You're trying to find your way out of the hospital." << endl;
	return true;
}

bool brave_nuclear_winter(){
	cout << "You made it to the front door. One thing that doesn't sit right on your mind is the medibot.\n";
	cout << "Why would the staff let a medibot break like that. And on top of that, where was the staff?\n";
	cout << "You see an advertisement for Vault Tech, \"A nuclear winter is cold, but stay warm with vault tech\" it reads." << endl;
	cout << "You start to remember... in the news. The nukes dropped on Portland and Las Vegas.\nNorth Korea had finally made their missiles long enough to reach the west coast." << endl;

	cout << "Do you want to seek a vault or try and travel to Washington DC. You're the governer after all... Travel to Washington?";
	if(!make_decision()){
		cout << "You head to a vault near the Santa Cruz Mountains. Once you're there you realize it's too late\nThey've already closed the gate. Time to head to DC." << endl;
	}
	cout << "You remember as the governer you have a private jet waiting for you at SJC. \nI guess it's time to remember your flight training." << endl;
	cout << "One abandoned motorcycle ride later you've made it in the air flying to DC.\nOnce you've made it in the air you realize you only have " << rand() % 5 << " hours of fuel." << endl;
	cout << "You're going to crash." << endl;
	return true;
}

bool crash_the_plane(){

	cout << "The plane is GOING DOWN AHHHHHH" << endl;
	cout << "As you fall out of the sky, you sit down and pray to Sarah Conner, saying I'll be back." << endl;
	cout << "The plane crashes. It's not very affective. Your HP drops only 2 points." << endl;
	cout << "You realize that you are actually the terminator." << endl;

	cout << "You're taken aback by the horror of your existance. Do you want to sit and contemplate life?";
	if(make_decision()){
		cout << "You sit for way to long and your circuits freeze in nuclear winter.\n You have to keep moving to stay alive." << endl;
		if(!random_chance()){
			cout << "You pass away quietly contemplating life." << endl;				
			return false;
		}
		cout << "As you sit there a pair of explorers come by and rescue you from your frozen contemplation." << endl;
	}
	cout << "It's time to move on..." << endl;
	return true;

}
void this_was_actually_a_dream(){
	cout << "Suddenly you realize none of this makes sense..." << endl;
	cout << "How could you be the terminator..." << endl;
	cout << "But, you don't remember going to sleep..." << endl;
	cout << "Do you want to wake up?";
	if(make_decision()){
		cout << "Welcome back Neo, did it work?" << endl;
	}
}