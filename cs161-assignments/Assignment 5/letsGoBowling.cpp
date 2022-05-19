#include <iostream>
#include <limits>

using namespace std;

void get_usernames(char**, int);
void start_game();
int get_player_num();
bool should_continue();
void print_board(int**, char**, int);
void play_turn(int**, char**, int, int);
int get_total(int*);

/*********************************************************************
** Function: main
** Description: starts program
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
** Return: int
*********************************************************************/ 
int main(){
	srand(time(NULL));
	do{
		start_game();
	} while (should_continue());
	return 0;
}

/*********************************************************************
** Function: get_usernames
** Description: Gets player names
** Parameters: player name array and num players
** Pre-Conditions: we don't have player names
** Post-Conditions:  we have player names
** Return: nothing
*********************************************************************/ 
void get_usernames(char** player_names, int num_players){
	for(int i = 0; i < num_players; i++){
		cout << "Enter player " << i << "'s name: ";
		cin >> player_names[i];
	}
}

/*********************************************************************
** Function: start game
** Description: starts game
** Parameters: none
** Pre-Conditions: nothing
** Post-Conditions: game over
** Return: nothing
*********************************************************************/
void start_game(){
	//CREATE VARIABLES
	int num_players = get_player_num();
	char** player_names = new char*[num_players];
	for(int i = 0; i < num_players; i++){
		player_names[i] = new char[15];
	}
	int** player_scores = new int*[num_players];
	for(int i = 0; i < num_players; i++){
		player_scores[i] = new int[21];
	}
	get_usernames(player_names, num_players);

	for(int frame = 0; frame < 10; frame++){
		for(int current_player = 0; current_player < num_players; current_player++){
			play_turn(player_scores, player_names, current_player, frame);
			print_board(player_scores, player_names, num_players);	
		}
	}

	//DELETE VARIABLES
	for(int i = 0; i < num_players; i++){
		delete[] player_names[i];
	}
	delete[] player_names;
	for(int i = 0; i < num_players; i++){
		delete[] player_scores[i];
	}
	delete[] player_scores;

}

/*********************************************************************
** Function: get_player_num
** Description: Get player number
** Parameters: nothing
** Pre-Conditions: nothing
** Post-Conditions: nothing
** Return: gets number of players
*********************************************************************/
int get_player_num(){
	int temp = 0;
	while(temp <= 0){
		cout << "Insert a positive number of players: ";
		cin >> temp;
		cout << endl;
	}
	return temp;
}

/*********************************************************************
** Function: should_continue
** Description: asks if we should continue
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
** Return: bool
*********************************************************************/ 
bool should_continue(){
	cout << "Would you like to play another game?\n[0] Play Again\n[1] Quit" << endl;
	int decision = 1;
	cin >> decision;
	cin.ignore(100000, '\n');
	return decision == 0;
}

/*********************************************************************
** Function: player turn
** Description: plays the player turn
** Parameters: player scores, names, current player number, and frame
** Pre-Conditions: scores, names, current_player, frame
** Post-Conditions: we got one more score for that player and frame
** Return: nothing
*********************************************************************/
void play_turn(int** player_scores, char** player_names, int current_player, int frame){
	
	for(int i = 0; i < 15; i++){
		cout << player_names[current_player][i];
	}
	cout  <<", press enter to play your turn: ";
	cin.ignore(std::numeric_limits<streamsize>::max(),'\n');

	int points_left = 10;
	int score = rand() % (points_left + 1);
	if(frame == 10){
		player_scores[current_player][(frame * 2)] = score;
		if(score != 10){
			points_left -= score;
			score = rand() % (points_left + 1);
		}
		player_scores[current_player][(frame * 2)+1] = score;
		if(player_scores[current_player][(frame * 2)] == 10 && player_scores[current_player][(frame * 2)+1] == 10){
			score = rand() % (points_left + 1);
			player_scores[current_player][(frame * 2)+2] = score;
		}
	} else {
		player_scores[current_player][(frame * 2)] = score;
		points_left -= score;
		score = rand() % (points_left + 1);
		player_scores[current_player][(frame * 2)+1] = score;
	}

	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
	
}
/*
*********************************************************************
** Function: print_board
** Description: Prints the board
** Parameters: player scores and names and number of players
** Pre-Conditions: we have scores names and number of players
** Post-Conditions: We print the board
** Return: none
*********************************************************************/
void print_board(int** player_scores, char** player_names, int num_players){
	cout << "\n\nNames | R 1 | R 2 | R 3 | R 4 | R 5 | R 6 | R 7 | R 8 | R 9 | R 10  | Total" << endl;
	for(int i = 0; i < num_players; i++){
		cout << "---------------------------------------------------------------------\n";
		for(int x = 0; x < 5; x++){
			if(player_names[i][x] == '\0'){
				cout << " ";
			} else {
				cout << player_names[i][x];
			}
		}
		cout << " |";
		for(int x = 0; x < 21; x++){
			if(player_scores[i][x] != 0 && player_scores[i][x] != 10){
				if(x % 2 == 1 && player_scores[i][x]+player_scores[i][x-1] == 10){
					cout << " /";
				} else {
					cout << " " << player_scores[i][x];
				}
				
			} else if(player_scores[i][x] == 0 && player_scores[i][x-1] != 10){
				cout << " -";
			} else if(player_scores[i][x] == 10 ){
				cout << "  X ";
			} else {
				continue;
			}
			if( x < 19 && (x % 2 == 1 || player_scores[i][x] == 10)){
				cout << " |";
			}
		}
		cout << " | ";
		cout << get_total(player_scores[i]);
		cout << endl;
	}
	cout << endl;

}

/*********************************************************************
** Function: get_total
** Description: Get total running score of a score array
** Parameters: a score array
** Pre-Conditions: we have a score
** Post-Conditions: we have a total
** Return: the number total
*********************************************************************/
int get_total(int* scores){

	int total = 0;

	for(int frame = 0; frame < 10; frame++){

		if(frame < 8){

			if(scores[(2*frame)] == 10){
				total+= 10 + scores[(2*(frame + 1))] + scores[(2*(frame + 1))+1] + scores[(2*(frame + 2))] + scores[(2*(frame + 2))+1];
			} else if (scores[(2*frame)]+scores[(2*frame)+1] == 10) {
				total+= 10 + scores[(2*(frame + 1))] + scores[(2*(frame + 1))+1];
			} else {
				total += scores[(2*frame)] + scores[(2*frame)+1];
			}

		} else if (frame == 8){
			if(scores[(2*frame)] == 10){
				total+= 10 + scores[(2*(frame + 1))] + scores[(2*(frame + 1))+1] + scores[(2*(frame + 2))] + scores[(2*(frame + 2))+1] +  scores[(2*(frame + 2))+2];
			} else if (scores[(2*frame)]+scores[(2*frame)+1] == 10) {
				total+= 10 + scores[(2*(frame + 1))] + scores[(2*(frame + 1))+1];
			} else {
				total += scores[(2*frame)] + scores[(2*frame)+1];
			}
		} else if (frame == 9) {
			if(scores[(2*frame)] == 10 || scores[(2*frame)]+scores[(2*frame)+1] == 10){
				total += 10 + scores[(2*(frame + 1))] + scores[(2*(frame + 1))+1] + scores[(2*(frame + 1))+2];
			} else {
				total += scores[(2*frame)] + scores[(2*frame)+1];
			}
		} else {
			total += scores[(2*frame)] + scores[(2*frame)+1] + scores[(2*frame)+2];
		}

	}

	return total;

}