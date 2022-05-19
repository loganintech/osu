#ifndef run_facts_h
#define run_facts_h

// This takes the arguments and sees if they are the right number
bool is_valid_arguments(char *[], int);

//This takes a number and returns a state pointer
state * create_states(int);

//This takes a state pointer, line number, and file to populate the state pointer
void get_state_data(state *, int, std::ifstream &);

//This takes a number and returns a county pointer
county * create_counties(int);

//This takes a county pointer, number, and file to populate the county
void get_county_data(county *, int, std::ifstream &);

//This deletes the list of states and counties to not leak memory
void delete_info(state **, int);

int get_num_states(char *[], int);

int get_filename_location(char *[], int);

std::string * split_state_line(std::string);


std::string get_state_largest_pop(state *, int);
std::string get_county_largest_pop(state *, int);
county * get_rich_counties(state *, int, int);
int * avg_household_costs(state *, int);
state * sort_by_population(state *, int);
state * sort_by_name(state *, int);
county * sort_counties_name(state *, int);
county * sort_counties_population(state *, int);
void print_data(state * , int );
void write_data(state * , int );

bool is_printing_to_screen();

void delete_county(county *);

#endif