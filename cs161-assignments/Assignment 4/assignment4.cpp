/*********************************************************************
** Program Filename: assignment4.cpp
** Author: Logan Saso
** Date: 2/19/2017
** Description: Plays wheel of fortune
** Input: Strings ahd characters
** Output: Some wheel of fortune
*********************************************************************/
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;

void set_replace_string(string, string *);
int get_search_replace(string, string &, bool);
void start_game();
string get_string();
bool should_continue();
bool spin_wheel( string& , string  , int& );
void start_round(string *, int *, int);
int get_wheel_num();
void change_player(int&, int);
void do_round(string *players, int *scores, string &guessing_string, string answer_string, int num_players);
void buy_vowel(string &guessing_string, string answer_string, int &round_score);
bool solve_puzzle(string &guessing_string, string answer_string);

/*********************************************************************
** Function: main
** Description: start program
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
** Return: 0
*********************************************************************/ 
int main(){
	srand(time(NULL));
	do{
		start_game();
	} while (should_continue());
	
	return 0;
}

/*********************************************************************
** Function: get_string
** Description: This gets the string you want to play with 
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
** Return: returns a string
*********************************************************************/ 
string get_string(){
	cout << "Input the string you want to play with: ";
	string work_please = "";
	getline(cin, work_please);
//	cout << "DEBUG INPUT TEXT: " << work_please << endl;
	return work_please;
}


/*********************************************************************
** Function: get_num_players
** Description: Gets a number of players
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
** Return: temp
*********************************************************************/ 
int get_num_players(){
	cout << "Input number of players: ";
	int temp;
	cin >> temp;
	cin.ignore(100000, '\n');
	return temp;
}

/*********************************************************************
** Function: start_game
** Description: Starts the game
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
** Return: none
*********************************************************************/ 
void start_game(){
	int num_players = get_num_players();
	string *players = new string[num_players];
	int *scores = new int[num_players] ; 
	for(int i = 0; i < num_players; i++){
		cout << "Input player " << i + 1 << "'s name: ";
		cin >> players[i];
		cin.ignore(100000, '\n');
		scores[i] = 0;
	}
    cout << "How many rounds would you like to play? Rounds: ";
    int rounds;
    cin >> rounds;
	cin.ignore(100000, '\n');
    for(int i = 0; i < rounds; i++) {
        start_round(players, scores, num_players);
    }
}

/*********************************************************************
** Function: start_round
** Description: Starts the round
** Parameters: players array, scores array, number of players
** Pre-Conditions: none 
** Post-Conditions: none 
** Return: none
*********************************************************************/ 
void start_round(string *players, int *scores, int num_players){

	string answer_string = get_string();
	string guessing_string = "";
	string* guessing_pointer = &guessing_string;
	set_replace_string(answer_string, guessing_pointer); //Essentially this just makes the guessing_pointer value into ---- versions of whatever string was implemented.
	do_round(players, scores, guessing_string, answer_string, num_players);
}

/*********************************************************************
** Function: do_round
** Description: does round
** Parameters: players, scores, guessing string, answer string, number of players
** Pre-Conditions: none
** Post-Conditions: none
** Return: none
*********************************************************************/ 
void do_round(string *players, int *scores, string &guessing_string, string answer_string, int num_players){
	bool word_guessed = false;
	int current_player = 0;
	int the_decision = 0;
	bool turn_skipped = false;
    int round_score = 0;
	do{
        cout << "\n\n\n\n" << endl;
		cout << "Here is the current word: " << guessing_string << endl;
		the_decision = 0;
        turn_skipped = false;
		cout << "------MENU------"  << endl << players[current_player] << ", what would you like to do?\n[0] Spin the wheel\n[1] Buy a vowel\n[2] Solve the puzzle\nChoose now: ";
		cin >> the_decision;
		cin.ignore(100000, '\n');
		switch(the_decision){
			case 0:
				turn_skipped = spin_wheel(guessing_string, answer_string, round_score);
				break;
			case 1:
				buy_vowel(guessing_string, answer_string, round_score);
				break;
			case 2:
				turn_skipped = solve_puzzle(guessing_string, answer_string);
				break;
			default:
				cout << "Now now, that was not an option." << endl;
				turn_skipped = true;

		}
		if(turn_skipped){
            scores[current_player] = scores[current_player] + round_score;
			cout << "You earned $" << round_score << "." << endl;
            round_score = 0;
            change_player(current_player, num_players);
            continue;
        }
        word_guessed = (answer_string == guessing_string);
	} while (!word_guessed);
    cout << "Congratulations to " << players[current_player] << " for winning with the guess " << answer_string << endl;
    scores[current_player] = scores[current_player] + round_score;
    cout << "You have made " << round_score << " dollars this round.\nCurrent scores are:" << endl;
    for(int i = 0; i < num_players; i++){
        cout << players[i] << ": " << scores[i] << endl;
    }
}


/*********************************************************************
** Function: solve_puzzle
** Description: Lets you guess on starting the puzzle
** Parameters: guessing string, answer string
** Pre-Conditions: none
** Post-Conditions: guessing_string = answer_string or doesn't
** Return: bool (if you solved the puzzle)
*********************************************************************/ 
bool solve_puzzle(string &guessing_string, string answer_string){
    cout << "You have decided to solve the puzzle. Be careful, if you get it wrong your turn is forfeit. Good luck." << endl;
    string the_guess = "";
    cout << "Please enter your guess here: ";
    getline(cin, the_guess);
    for(int i = 0; i < the_guess.length(); i++){
        the_guess[i] = tolower(the_guess[i]);
    }
    if(the_guess == answer_string){
        guessing_string = answer_string;
        return false;
    }
    cout << "Sorry, that is incorrect." << endl;
    return true;
}

/*********************************************************************
** Function: buy_vowel
** Description: You can buy a vowel
** Parameters: guessing_string, answer_string, round_score
** Pre-Conditions: you have at least 10 round score
** Post-Conditions: round score is equal or 10 less, guessing_string could be changed
** Return: none
*********************************************************************/ 
void buy_vowel(string &guessing_string, string answer_string, int &round_score){
	cout << "You chose to buy a vowel. Great choice!" << endl;
	if(round_score < 10){
		cout << "You do not have enough money to do that.";
		return;
	}
	int found = get_search_replace(answer_string, guessing_string, true);
	if(found == 0){
		cout << "Sorry, that isn't in the word." << endl;
		round_score -= 10;
	}
	cout << "You found " << found << " vowels." << endl;
}

/*********************************************************************
** Function: spin_wheel
** Description: spins the wheel
** Parameters: guessing_string, answer_string, round_score
** Pre-Conditions: none
** Post-Conditions: none
** Return: whether or not we went bankrupt (as a bool)
*********************************************************************/ 
bool spin_wheel(string &guessing_string, string answer_string,  int &round_score){
    cout << "You have decided to spin the wheel!\nLet's see what you get!" << endl;
    int wheel_num = get_wheel_num();
    if(wheel_num == 0){
        cout << "Oh darn your turn is skipped!" << endl;
		round_score = 0;
        return true;
    } else if (wheel_num == 21){
        cout << "Oh no you went bankrupt!" << endl;
        round_score = 0;
        return true;
    } else {
        cout << "The wheel spun a " << wheel_num << " so you'll get " << wheel_num << " dollars for every correctly guessed letter." << endl;
        int found = get_search_replace(answer_string, guessing_string, false);
        if(found == 0){
            cout << "Ooh tough luck, that isn't in the word." << endl;
            return true;
        } else {
            round_score += (wheel_num * found);
            cout << "There were " << found << " of that letter in the answer so you added " << found * wheel_num << " to your round score." << endl;
            return false;
        }
    }
}

/*********************************************************************
** Function: get_wheel_num
** Description: gets wheel num
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
** Return: wheel num
*********************************************************************/ 
int get_wheel_num(){
	return rand() % 22;
}

/*********************************************************************
** Function: set_replace_string
** Description: sets up guessing_string with '-' 
** Parameters: answer_string, guessing_string (pointer form)
** Pre-Conditions: answer_string is a thing and guessing_string is empty
** Post-Conditions: guessing_string is a combo of ' ' and '-'
** Return: nothing
*********************************************************************/ 
void set_replace_string(string answer_string, string* guessing_string){

	string build_me = "";
	for(int i = 0; i < answer_string.size(); i++){
		if( answer_string[i] != ' ' ){
			build_me+="-";
		} else {
			build_me+=" ";
		}
	}
	*guessing_string = build_me;
}

/*********************************************************************
** Function: get_search_replace
** Description: searches for the where a guess is in the guessing_string and replaces it
** Parameters: answer_string, guessing_string, checking_vowels
** Pre-Conditions: none
** Post-Conditions: guess replaces '-' in the string
** Return: the number of found numbers
*********************************************************************/ 
int get_search_replace(string answer_string, string &guessing_string, bool checking_vowels){
	char theLetter;
	cout << "What is your guess: " ;
	cin >> theLetter;
    cin.ignore(10000, '\n');
	theLetter = tolower(theLetter);
	string vowels = "aeiouy";
	if(checking_vowels && (vowels.find(theLetter) == string::npos)){
		cout << "Oooh that's not a vowel." << endl;
		return 0;
	}
	if(!checking_vowels && (vowels.find(theLetter) != string::npos)){
		cout << "You have to buy vowels." << endl;
		return 0;
	}
	string build_me = "";
	int found = 0;
	for(int i = 0; i < answer_string.size(); i++){

		if(answer_string[i] == theLetter && guessing_string[i] == '-'){
			found++;
			build_me += theLetter;
		} else {
			build_me += guessing_string[i];
		}
	}
	guessing_string = build_me;
	return found;
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
** Function: change_player
** Description: Changes the player number
** Parameters: current_player, max players
** Pre-Conditions: none
** Post-Conditions: current is changed
** Return: none
*********************************************************************/ 
void change_player(int &current, int max){

	if(current >= max-1){
		current = 0;
	} else {
		current+=1;
	}
}
