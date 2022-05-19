/******************************************************
** Program: main.cpp
** Author: Logan Saso
** Date: 04/14/2017
** Description: This is a state and county sorter using structs
** Input: A file and number of states
** Output: A file (states.txt) or printed state information 
******************************************************/


#include <string>
#include "state_facts.h"
#include "run_facts.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>

using namespace std;

/*********************************************************************
** Function: main
** Description: entry point
** Parameters: argv argc 
** Pre-Conditions: we have an argv
** Post-Conditions: printed details or file
*********************************************************************/
int main(int argc, char *argv[]){
	if (!is_valid_arguments(argv, argc)) {
		cout << "Those are not valid arguments. Please rerun the program with the right parameters." << endl;
		exit(1);
	}
	//open the file 
	ifstream file;
	int filename_location = get_filename_location(argv, argc);

	file.open(argv[filename_location], ifstream::in);
	while(!file.is_open()){
		cout << "That is not the right file name. Please try again. Make sure to include the extension." << endl;
		cout << "Input file location: ";
		cin >> filename_location;
		file.open(argv[filename_location], ifstream::in);
	}


	int states_num = get_num_states(argv, argc);
	while(states_num < 1){
		cout << "You put that you have " << states_num << " states. You need at least 1." << endl;
		cout << "Input the number of states: ";
		cin >> states_num;
	}


	state * states = create_states(states_num);
	get_state_data(states, states_num, file);

	if(is_printing_to_screen()){
		print_data(states, states_num);
	} else {
		write_data(states, states_num);
	}
	state ** state_pointer = new state*[states_num];
	state_pointer[0] = states;
	delete_info(state_pointer, states_num);

	return 0;
}



/*

This following section is so that I can see the information in the minimap of my text editor.
It looks like this :) http://i.imgur.com/Aju23w5.png
No reason to use terminal only text editors anymore. Seriously, why do people do that?

*/




/*
RRRRRRRRRRRRRRRRR   EEEEEEEEEEEEEEEEEEEEEE     QQQQQQQQQ     UUUUUUUU     UUUUUUUUIIIIIIIIIIRRRRRRRRRRRRRRRRR   EEEEEEEEEEEEEEEEEEEEEEDDDDDDDDDDDDD        
R::::::::::::::::R  E::::::::::::::::::::E   QQ:::::::::QQ   U::::::U     U::::::UI::::::::IR::::::::::::::::R  E::::::::::::::::::::ED::::::::::::DDD     
R::::::RRRRRR:::::R E::::::::::::::::::::E QQ:::::::::::::QQ U::::::U     U::::::UI::::::::IR::::::RRRRRR:::::R E::::::::::::::::::::ED:::::::::::::::DD   
RR:::::R     R:::::REE::::::EEEEEEEEE::::EQ:::::::QQQ:::::::QUU:::::U     U:::::UUII::::::IIRR:::::R     R:::::REE::::::EEEEEEEEE::::EDDD:::::DDDDD:::::D  
  R::::R     R:::::R  E:::::E       EEEEEEQ::::::O   Q::::::Q U:::::U     U:::::U   I::::I    R::::R     R:::::R  E:::::E       EEEEEE  D:::::D    D:::::D 
  R::::R     R:::::R  E:::::E             Q:::::O     Q:::::Q U:::::D     D:::::U   I::::I    R::::R     R:::::R  E:::::E               D:::::D     D:::::D
  R::::RRRRRR:::::R   E::::::EEEEEEEEEE   Q:::::O     Q:::::Q U:::::D     D:::::U   I::::I    R::::RRRRRR:::::R   E::::::EEEEEEEEEE     D:::::D     D:::::D
  R:::::::::::::RR    E:::::::::::::::E   Q:::::O     Q:::::Q U:::::D     D:::::U   I::::I    R:::::::::::::RR    E:::::::::::::::E     D:::::D     D:::::D
  R::::RRRRRR:::::R   E:::::::::::::::E   Q:::::O     Q:::::Q U:::::D     D:::::U   I::::I    R::::RRRRRR:::::R   E:::::::::::::::E     D:::::D     D:::::D
  R::::R     R:::::R  E::::::EEEEEEEEEE   Q:::::O     Q:::::Q U:::::D     D:::::U   I::::I    R::::R     R:::::R  E::::::EEEEEEEEEE     D:::::D     D:::::D
  R::::R     R:::::R  E:::::E             Q:::::O  QQQQ:::::Q U:::::D     D:::::U   I::::I    R::::R     R:::::R  E:::::E               D:::::D     D:::::D
  R::::R     R:::::R  E:::::E       EEEEEEQ::::::O Q::::::::Q U::::::U   U::::::U   I::::I    R::::R     R:::::R  E:::::E       EEEEEE  D:::::D    D:::::D 
RR:::::R     R:::::REE::::::EEEEEEEE:::::EQ:::::::QQ::::::::Q U:::::::UUU:::::::U II::::::IIRR:::::R     R:::::REE::::::EEEEEEEE:::::EDDD:::::DDDDD:::::D  
R::::::R     R:::::RE::::::::::::::::::::E QQ::::::::::::::Q   UU:::::::::::::UU  I::::::::IR::::::R     R:::::RE::::::::::::::::::::ED:::::::::::::::DD   
R::::::R     R:::::RE::::::::::::::::::::E   QQ:::::::::::Q      UU:::::::::UU    I::::::::IR::::::R     R:::::RE::::::::::::::::::::ED::::::::::::DDD     
RRRRRRRR     RRRRRRREEEEEEEEEEEEEEEEEEEEEE     QQQQQQQQ::::QQ      UUUUUUUUU      IIIIIIIIIIRRRRRRRR     RRRRRRREEEEEEEEEEEEEEEEEEEEEEDDDDDDDDDDDDD        
                                                       Q:::::Q                                                                                             
                                                        QQQQQQ                                                                                             
*/


/*********************************************************************
** Function: is_valid_arguments
** Description: Checks if the arguments are valid
** Parameters: argv argc
** Pre-Conditions: we are in main and have argv and argc
** Post-Conditions: We know if the args are valid
*********************************************************************/
bool is_valid_arguments(char *argv[], int argc){

	if(argc < 5){
		return false;
	}

	if((argv[1][0] == '-' && argv[1][1] == 'f' && argv[3][0] == '-' && argv[3][1] == 's') || (argv[3][0] == '-' && argv[3][1] == 'f' && argv[1][0] == '-' && argv[1][1] == 's')) {
		return true;
	}
	return false;
}

/*********************************************************************
** Function: create_states
** Description: Creates state docs
** Parameters: num_states
** Pre-Conditions: We have a states pointer waiting for return value
** Post-Conditions: states pointer is populated
*********************************************************************/
state * create_states(int num_states){
	state * states = new state[num_states];
	for(int i = 0; i < num_states; i++){
		states[i].population = 0;
		states[i].counties = 0;
		states[i].name = "";
	}
	return states;
}

/*********************************************************************
** Function: get_state_data
** Description: Get state data from file
** Parameters: state_pointer, number of states, file object
** Pre-Conditions: We have opened the file and know states number
** Post-Conditions: States array is populated with data
*********************************************************************/
void get_state_data(state * state_pointer, int number, ifstream &file){
	string line;
	string * line_params = new string[3];
	for(int i = 0; i < number; i++){

		getline(file, line);
		line_params = split_state_line(line);
		state_pointer[i].name = line_params[0];
		state_pointer[i].population = stoi(line_params[1]);
		state_pointer[i].counties = stoi(line_params[2]);
		state_pointer[i].c = create_counties(state_pointer[i].counties);
		get_county_data(state_pointer[i].c, state_pointer[i].counties, file);

	}
}

/*********************************************************************
** Function: create_counties
** Description: We create the county structs
** Parameters: Number of counties
** Pre-Conditions: We have a state struct waiting for a county pointer
** Post-Conditions: We have an empty county struct in the state
*********************************************************************/
county * create_counties(int num_counties){
	county * counties = new county[num_counties];
	for(int i = 0; i < num_counties; i++){
		counties[i].name = "";
		counties[i].cities = 0;
		counties[i].population = 0;
		counties[i].avg_income = 0.0;
		counties[i].avg_house = 0.0;
	}
	return counties;
}

/*********************************************************************
** Function: get_county_data
** Description: Gets county data from file
** Parameters: county_pointer, number of counties, file
** Pre-Conditions: We know the number of counties and have a file and county pointer
** Post-Conditions: We have a populated county
*********************************************************************/
void get_county_data(county * county_pointer, int num_counties, ifstream &file){
	stringstream ss;
	string line;
	for(int i = 0; i < num_counties; i++){
		getline(file, line);
		ss << line;
		ss >> county_pointer[i].name;
		ss >> county_pointer[i].population;
		ss >> county_pointer[i].avg_income;
		ss >> county_pointer[i].avg_house;
		ss >> county_pointer[i].cities;
		county_pointer[i].city = new string[county_pointer[i].cities];
		for(int x = 0; x < county_pointer[i].cities; x++){
			ss >> county_pointer[i].city[x];
		}
	}
}

/*********************************************************************
** Function: delet_this
** Description: https://cdn.meme.am/instances/66270527.jpg
** Parameters: States list and number of states
** Pre-Conditions: We have a states list and states number
** Post-Conditions: everything delet
*********************************************************************/
void delete_info(state ** states_list, int length){
	for(int i = 0; i < length; i++){
		delete_county(states_list[i]->c);
		delete[] states_list[i];
	}
	delete[] states_list;
}

/*
        CCCCCCCCCCCCCUUUUUUUU     UUUUUUUU   SSSSSSSSSSSSSSS TTTTTTTTTTTTTTTTTTTTTTT     OOOOOOOOO     MMMMMMMM               MMMMMMMM
     CCC::::::::::::CU::::::U     U::::::U SS:::::::::::::::ST:::::::::::::::::::::T   OO:::::::::OO   M:::::::M             M:::::::M
   CC:::::::::::::::CU::::::U     U::::::US:::::SSSSSS::::::ST:::::::::::::::::::::T OO:::::::::::::OO M::::::::M           M::::::::M
  C:::::CCCCCCCC::::CUU:::::U     U:::::UUS:::::S     SSSSSSST:::::TT:::::::TT:::::TO:::::::OOO:::::::OM:::::::::M         M:::::::::M
 C:::::C       CCCCCC U:::::U     U:::::U S:::::S            TTTTTT  T:::::T  TTTTTTO::::::O   O::::::OM::::::::::M       M::::::::::M
C:::::C               U:::::D     D:::::U S:::::S                    T:::::T        O:::::O     O:::::OM:::::::::::M     M:::::::::::M
C:::::C               U:::::D     D:::::U  S::::SSSS                 T:::::T        O:::::O     O:::::OM:::::::M::::M   M::::M:::::::M
C:::::C               U:::::D     D:::::U   SS::::::SSSSS            T:::::T        O:::::O     O:::::OM::::::M M::::M M::::M M::::::M
C:::::C               U:::::D     D:::::U     SSS::::::::SS          T:::::T        O:::::O     O:::::OM::::::M  M::::M::::M  M::::::M
C:::::C               U:::::D     D:::::U        SSSSSS::::S         T:::::T        O:::::O     O:::::OM::::::M   M:::::::M   M::::::M
C:::::C               U:::::D     D:::::U             S:::::S        T:::::T        O:::::O     O:::::OM::::::M    M:::::M    M::::::M
 C:::::C       CCCCCC U::::::U   U::::::U             S:::::S        T:::::T        O::::::O   O::::::OM::::::M     MMMMM     M::::::M
  C:::::CCCCCCCC::::C U:::::::UUU:::::::U SSSSSSS     S:::::S      TT:::::::TT      O:::::::OOO:::::::OM::::::M               M::::::M
   CC:::::::::::::::C  UU:::::::::::::UU  S::::::SSSSSS:::::S      T:::::::::T       OO:::::::::::::OO M::::::M               M::::::M
     CCC::::::::::::C    UU:::::::::UU    S:::::::::::::::SS       T:::::::::T         OO:::::::::OO   M::::::M               M::::::M
        CCCCCCCCCCCCC      UUUUUUUUU       SSSSSSSSSSSSSSS         TTTTTTTTTTT           OOOOOOOOO     MMMMMMMM               MMMMMMMM
*/


/*********************************************************************
** Function: Delete county
** Description: Deletes a county
** Parameters: DELET THIS (the county)
** Pre-Conditions: we have a county
** Post-Conditions: we don't have a county
*********************************************************************/
void delete_county(county * the_county){
	delete[] the_county->city;
	delete the_county;
}

/*********************************************************************
** Function: get_filename_location
** Description: Checks for file name in the arguments
** Parameters: Argv, argc
** Pre-Conditions: valid parameters
** Post-Conditions: we know file location in parameter list
*********************************************************************/
int get_filename_location(char *argv[], int argc){
	for(int i = 0; i < argc-1; i++){
		if(argv[i][0] == '-' && argv[i][1] == 'f'){
			return i + 1;
		}
	}
	return -1;
}

/*********************************************************************
** Function: get_num_states
** Description: Extracts number of states from param list
** Parameters: argv, argc
** Pre-Conditions: We have parameters
** Post-Conditions: We know the number of states
*********************************************************************/
int get_num_states(char *argv[], int argc){
	for(int i = 0; i < argc-1; i++){
		if(argv[i][0] == '-' && argv[i][1] == 's'){
			return atoi(argv[i+1]);
		}
	}
	return 0;
}

/*********************************************************************
** Function: split_state_line
** Description: This is a helper function to split the words in a state line
** Parameters: the line as a string
** Pre-Conditions: we are reading from the file
** Post-Conditions: returns an array of strings
*********************************************************************/
string * split_state_line(string line){

	int first_space = line.find(" ");
	int second_space = line.find(" ", first_space+1);
	string * the_words = new string[3];
	the_words[0] = line.substr(0, first_space);
	the_words[1] = line.substr(first_space + 1, second_space - (first_space + 1));
	the_words[2] = line.substr(second_space + 1);
	return the_words;

}

/*********************************************************************
** Function: is_printing_to_screen
** Description: Ask the user if they want to print to the screen
** Parameters: nothing
** Pre-Conditions: nothing
** Post-Conditions: we know if we are writing to a file or to the screen
*********************************************************************/
bool is_printing_to_screen(){
	cout << "Would you like to print to the screen [0] or to a file [1]. Insert choice: " << endl;
	int choice = 0;
	cin >> choice;
	cin.clear();
	cin.ignore();
	return choice == 0;
}

/*
        GGGGGGGGGGGGGEEEEEEEEEEEEEEEEEEEEEETTTTTTTTTTTTTTTTTTTTTTT
     GGG::::::::::::GE::::::::::::::::::::ET:::::::::::::::::::::T
   GG:::::::::::::::GE::::::::::::::::::::ET:::::::::::::::::::::T
  G:::::GGGGGGGG::::GEE::::::EEEEEEEEE::::ET:::::TT:::::::TT:::::T
 G:::::G       GGGGGG  E:::::E       EEEEEETTTTTT  T:::::T  TTTTTT
G:::::G                E:::::E                     T:::::T        
G:::::G                E::::::EEEEEEEEEE           T:::::T        
G:::::G    GGGGGGGGGG  E:::::::::::::::E           T:::::T        
G:::::G    G::::::::G  E:::::::::::::::E           T:::::T        
G:::::G    GGGGG::::G  E::::::EEEEEEEEEE           T:::::T        
G:::::G        G::::G  E:::::E                     T:::::T        
 G:::::G       G::::G  E:::::E       EEEEEE        T:::::T        
  G:::::GGGGGGGG::::GEE::::::EEEEEEEE:::::E      TT:::::::TT      
   GG:::::::::::::::GE::::::::::::::::::::E      T:::::::::T      
     GGG::::::GGG:::GE::::::::::::::::::::E      T:::::::::T      
        GGGGGG   GGGGEEEEEEEEEEEEEEEEEEEEEE      TTTTTTTTTTT      
*/


/*********************************************************************
** Function: get_state_largest_pop
** Description: Get largest state by population
** Parameters: states, number of states
** Pre-Conditions: we have stats
** Post-Conditions: we know largest
*********************************************************************/
string get_state_largest_pop(state * states, int num_states){
	string largest_pop = states[0].name;
	int population = states[0].population;
	for(int i = 0; i < num_states; i++){
		if(states[i].population > population){
			population = states[i].population;
			largest_pop = states[i].name;
		}
	}
	return largest_pop;
}

/*********************************************************************
** Function: get_county_largest_pop
** Description: get largest county by pop
** Parameters: states, num states
** Pre-Conditions: We have states
** Post-Conditions: we know largest county
*********************************************************************/
string get_county_largest_pop(state * states, int num_states){
	string largest_pop = states[0].c[0].name;
	int population = states[0].c[0].population;
	for(int i = 0; i < num_states; i++){
		for(int x = 0; x < states[i].counties; x++){
			if(states[i].c[x].population > population){
				population = states[i].c[x].population;
				largest_pop = states[i].c[x].name;
			}
		}
	}
	return largest_pop;
}

/*********************************************************************
** Function: get_rich_counties
** Description: Gets counties above a dollar value
** Parameters: states, dollar value, number of states, array length
** Pre-Conditions: we have counties and dollar value
** Post-Conditions: we know county and length of array of counties
*********************************************************************/
county * get_rich_counties(state * states, int dollar_value, int num_states, int &array_length){

	county * rich_counties = new county[128];
	int previous_added_county = 0;
	for(int i = 0; i < num_states; i++){
		for(int x = 0; x < states[i].counties; x++){
			if(states[i].c[x].avg_income > dollar_value){
				rich_counties[previous_added_county++] = states[i].c[x];
			}
		}
	}
	county * real_length_county = new county[previous_added_county];
	for(int i = 0; i < previous_added_county; i++){
		real_length_county[i] = rich_counties[i];
	}
	array_length = previous_added_county;
	return real_length_county;
}

/*********************************************************************
** Function: avg_household_costs
** Description: Gets average house cost for each county
** Parameters: states, number of states, array length
** Pre-Conditions: we have counties
** Post-Conditions: we know averages
*********************************************************************/
int * avg_household_costs(state * states, int num_states, int &array_length){
	int * averages = new int[128];
	int previous_added_average = 0;
	for(int i = 0; i < num_states; i++){
		for(int x = 0; x < states[i].counties; x++){
			averages[previous_added_average++] = states[i].c[x].avg_house;
		}
	}
	array_length = previous_added_average;
	return averages;
}

/*********************************************************************
** Function: sort_by_population
** Description: we sort states by population
** Parameters: states, num states, array_length
** Pre-Conditions: we know the states
** Post-Conditions: we know them sorted by pop
*********************************************************************/
state * sort_by_population(state * states, int num_states, int &array_length){
	state * sorted = new state[num_states];
	for(int i = 0; i < num_states; i++){
		sorted[i] = states[i];
	}
	state swap;
	for (int x = 0 ; x < ( num_states - 1 ); x++){
		for (int i = 0 ; i < num_states - x - 1; i++){
			if (sorted[i].population < sorted[i+1].population){
				swap = sorted[i];
				sorted[i] = sorted[i+1];
				sorted[i+1] = swap;
			}
		}
	}
	array_length = num_states;
	return sorted;
}

/*********************************************************************
** Function: sort_by_name
** Description: sort states by name
** Parameters: states, num states, array length
** Pre-Conditions: we have stats
** Post-Conditions: we know them in ABC order (roughly, it's actually lexicographical order but whatever)
*********************************************************************/
state * sort_by_name(state * states, int num_states, int &array_length){
	state * sorted = new state[num_states];
	for(int i = 0; i < num_states; i++){
		sorted[i] = states[i];
	}
	state swap;
	for (int x = 0 ; x < ( num_states - 1 ); x++){
		for (int i = 0 ; i < num_states - x - 1; i++){
			if ((char)sorted[i].name[0] > (char)sorted[i+1].name[0]){ //This actually works because it can compare ASCII values
				swap = sorted[i];
				sorted[i] = sorted[i+1];
				sorted[i+1] = swap;
			}
		}
	}
	array_length = num_states;
	return sorted;
}

/*********************************************************************
** Function: sort_counties_name
** Description: Sort counties by name
** Parameters: states, num states, array length
** Pre-Conditions: we have counties
** Post-Conditions: we know abc order of counties (lexicographic order again but again whatever)
*********************************************************************/
county * sort_counties_name(state * states, int num_states, int &array_length){
	county * sorted = new county[128];
	int county_count = 0;
	int num_counties;
	for(int i = 0; i < num_states; i++){
		num_counties = states[i].counties;
		for(int x = 0; x < num_counties; x++){
			sorted[county_count++] = states[i].c[x];
		}
	}
	county swap;
	for (int x = 0 ; x < ( county_count - 1 ); x++){
		for (int c = 0 ; c < county_count - x - 1; c++){
			if ((char)sorted[c].name[0] > (char)sorted[c+1].name[0]){ //This actually works because it can compare ASCII values
				swap = sorted[c];
				sorted[c] = sorted[c+1];
				sorted[c+1] = swap;
			}
		}
	}
	array_length = county_count;
	return sorted;
}

/*********************************************************************
** Function: sort_counties_population
** Description: Sorts counties by pop
** Parameters: states, number of states, array_length
** Pre-Conditions: we have counties
** Post-Conditions: we know the counties in order of population
*********************************************************************/
county * sort_counties_population(state * states, int num_states, int &array_length){

	county * sorted = new county[128];
	int county_count = 0;
	int num_counties;
	for(int i = 0; i < num_states; i++){
		num_counties = states[i].counties;
		for(int x = 0; x < num_counties; x++){
			sorted[county_count++] = states[i].c[x];
		}
	}
	county swap;
	for (int x = 0 ; x < ( county_count - 1 ); x++){
		for (int c = 0 ; c < county_count - x - 1; c++){
			if (sorted[c].population > sorted[c+1].population){ //This actually works because it can compare ASCII values
				swap = sorted[c];
				sorted[c] = sorted[c+1];
				sorted[c+1] = swap;
			}
		}
	}
	array_length = county_count;
	return sorted;
}

/*********************************************************************
** Function: print_data
** Description: Print everything
** Parameters: states, number of states
** Pre-Conditions: we have state and county data
** Post-Conditions: we print that data
*********************************************************************/
void print_data(state * states, int states_num){

	cout << "State with Largest Population: " << get_state_largest_pop(states, states_num) << endl;
	cout << "The county with the Largest Population: " << get_county_largest_pop(states, states_num) << endl;
	cout << "Please input the money minimum bar: ";

	int array_length = 0;


	int lowest = 0;
	cin >> lowest;
	cout << "These counties are the richest: ";
	county * rich_counties = get_rich_counties(states, lowest, states_num, array_length);
	for(int i = 0; i < array_length; i++){
		cout << rich_counties[i].name << " ";
	} 
	cout << endl;


	array_length = 0;
	cout << "These are the average household costs for each county: ";
	int * average_costs = avg_household_costs(states, states_num, array_length);
	for(int i = 0; i < array_length; i++){
		cout << average_costs[i] << " ";
	} 
	cout << endl;


	array_length = 0;
	cout << "These are the states sorted by population: ";
	state * population_sorted_states = sort_by_population(states, states_num, array_length);
	for(int i = 0; i < array_length; i++){
		cout << population_sorted_states[i].name << " ";
	} 
	cout << endl;


	array_length = 0;
	//sort_by_name
	cout << "These are the states sorted by name: ";
	state * name_sorted_states = sort_by_name(states, states_num, array_length);
	for(int i = 0; i < array_length; i++){
		cout << name_sorted_states[i].name << " ";
	} 
	cout << endl;


	array_length = 0;
	//sort_counties_name
	cout << "These are the counties sorted by name: ";
	county * name_sorted_county = sort_counties_name(states, states_num, array_length);
	for(int i = 0; i < array_length; i++){
		cout << name_sorted_county[i].name << " ";
	} 
	cout << endl;


	array_length = 0;
	//sort_counties_population
	cout << "These are the counties sorted by population: ";
	county * population_sorted_county = sort_counties_population(states, states_num, array_length);
	for(int i = 0; i < array_length; i++){
		cout << population_sorted_county[i].name << " ";
	} 
	cout << endl;
}

/*********************************************************************
** Function: write_data
** Description: Writes data to a file
** Parameters: states, number of states
** Pre-Conditions: We have states
** Post-Conditions: We write data to a file
*********************************************************************/
void write_data(state * states, int states_num){

	ofstream out_file;
	out_file.open("states.txt", ofstream::out);


	out_file << "State with Largest Population: " << get_state_largest_pop(states, states_num) << endl;
	out_file << "The county with the Largest Population: " << get_county_largest_pop(states, states_num) << endl;
	cout << "Please input the money minimum bar: ";

	int array_length = 0;


	int lowest = 0;
	cin >> lowest;
	out_file << "These counties are the richest: ";
	county * rich_counties = get_rich_counties(states, lowest, states_num, array_length);
	for(int i = 0; i < array_length; i++){
		out_file << rich_counties[i].name << " ";
	} 
	out_file << endl;


	array_length = 0;
	out_file << "These are the average household costs for each county: ";
	int * average_costs = avg_household_costs(states, states_num, array_length);
	for(int i = 0; i < array_length; i++){
		out_file << average_costs[i] << " ";
	} 
	out_file << endl;


	array_length = 0;
	out_file << "These are the states sorted by population: ";
	state * population_sorted_states = sort_by_population(states, states_num, array_length);
	for(int i = 0; i < array_length; i++){
		out_file << population_sorted_states[i].name << " ";
	} 
	out_file << endl;


	array_length = 0;
	//sort_by_name
	out_file << "These are the states sorted by name: ";
	state * name_sorted_states = sort_by_name(states, states_num, array_length);
	for(int i = 0; i < array_length; i++){
		out_file << name_sorted_states[i].name << " ";
	} 
	out_file << endl;


	array_length = 0;
	//sort_counties_name
	out_file << "These are the counties sorted by name: ";
	county * name_sorted_county = sort_counties_name(states, states_num, array_length);
	for(int i = 0; i < array_length; i++){
		out_file << name_sorted_county[i].name << " ";
	} 
	out_file << endl;


	array_length = 0;
	//sort_ counties_population
	out_file << "These are the counties sorted by population: ";
	county * population_sorted_county = sort_counties_population(states, states_num, array_length);
	for(int i = 0; i < array_length; i++){
		out_file << population_sorted_county[i].name << " ";
	} 
	out_file << endl;

}
