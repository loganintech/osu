/*********************************************************************
** Program Filename: assignment3.cpp
** Author: Logan Saso
** Date: January 31st, 2017
** Description: This is a grade calculator for CS. It can work with others too.
** Input: Asks for numbers.
** Output: Outputs class averages.
*********************************************************************/

#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdlib>

using namespace std;

double simple_calc(string type);
double recitation_calc();
bool get_done_status(); 
void do_calc(int choice); 
double get_number_items();
double class_calc();
double three_item_average(double quiz_weight, double design_weight, double critique_weight, int items);
double average_calc(double quiz_scores[], double design_scores[], double critique_scores[], int items, double quiz_weight, double design_weight, double critique_weight);


/*********************************************************************
** Function: main
** Description: Picks what grade you have to calculate
** Parameters: none 
** Pre-Conditions: none
** Post-Conditions: know what grade to calculate
** Return: success code 0 
*********************************************************************/ 
int main(){
	int choice = 0;
	bool done = false;
	cout << fixed << setprecision(10);
	while(!done){
		cout << "Note: All grades are # / 100 aka a percentage";
		cout << "What grade would you like to calculate? [0 - test, 1 - recitation, 2 - lab, 3 - assignment, other - class calc]: ";
		cin >> choice;
		do_calc(choice);
		done = get_done_status();
	}
	
	return 0;
}


/*********************************************************************
** Function: do_calc
** Description: Picks and run the calculation method
** Parameters: Choice of what we want to run
** Pre-Conditions: We have asked and picked a choice
** Post-Conditions: We output the calculation
** Return: void
*********************************************************************/ 
void do_calc(int choice){
	switch(choice){
		case 0: 
			cout << simple_calc("Test") << endl;
			break;
		case 1: 
			cout << recitation_calc() << endl;
			break;
		case 2: 
			cout << simple_calc("Lab") << endl;
			break;
		case 3: 
			cout << simple_calc("Assignment") << endl;
			break;
		default:
			cout << "Your class average is: " << class_calc() << endl;
	}
}


/*********************************************************************
** Function: get_done_status
** Description: Gets whether or not user wants to continue
** Parameters: none
** Pre-Conditions: iostream is imported
** Post-Conditions: we continue or dont
** Return: bool
*********************************************************************/ 
bool get_done_status(){
	double done = 0;
	cout << "Do you want to continue? [0 - no, 1 - true]: ";
	cin >> done;
	if(done == 0)
		return true; //runs this line if done is 0
	return false; //runs this line if done is not 0
}

/*********************************************************************
** Function: simple_calc
** Description: Does a calculation of an average without a weight
** Parameters: string type
** Pre-Conditions: type selected
** Post-Conditions: average calculated
** Return: average
*********************************************************************/ 
double simple_calc(string type){
	double scores = 0.0;
	double items = get_number_items();
	int same_values_input;
	cout << "Are all the values the same? [0 - no, 1 - yes]: ";
	cin >> same_values_input;
	if(same_values_input == 1){
		cout << type << " " << " scores: "; // Quiz 1 score: [input]
		cin >> scores;
		scores = scores * items;
	} else {
		for(int i = 0; i < items; i++){
			double input;
			cout << type << " " << i << " score: "; // Quiz 1 score: [input]
			cin >> input;
			scores += input;
		}
	}
	cout << "Your " << type << " average is " << scores / items << endl;
	return scores / items;
}

/*********************************************************************
** Function: get_number_items
** Description: Gets the number of items
** Parameters: None
** Pre-Conditions: iostream imported
** Post-Conditions: we have assignment num
** Return: return an int
*********************************************************************/ 
double get_number_items(){
	double assignment_num = 0;
	cout << "Input the number of items to calculate: ";
	cin >> assignment_num;
	return assignment_num;
}

/*********************************************************************
** Function: class_calc
** Description: Runs all previous calc types
** Parameters: none
** Pre-Conditions: we selected class calc
** Post-Conditions: we have a class average
** Return: class average
*********************************************************************/ 
double class_calc(){
	cout << "Class Clac\n--------------" << endl;
	double lab_weight = 0.0;
	double assignment_weight = 0.0;
	double test_weight = 0.0;
	double recitation_weight = 0.0;
	cout << "Enter lab weight: ";
	cin >> lab_weight;
	cout << "Enter assignment weight: ";
	cin >> assignment_weight;
	cout << "Enter test weight: ";
	cin >> test_weight;
	cout << "Enter recitation weight: ";
	cin >> recitation_weight;
	double lab_avg, assignment_avg, test_avg, recitation_avg, average;
	double total_weight = lab_weight + assignment_weight + test_weight + recitation_weight;
	if(lab_weight != 0.0) {lab_avg = simple_calc("Lab"); average = average + (lab_avg * (lab_weight / total_weight));}
	if(assignment_weight != 0.0) {assignment_avg = simple_calc("Assignment"); average = average + (assignment_avg * (assignment_weight / total_weight));}
	if(test_weight != 0.0){test_avg = simple_calc("Test"); average = average + (test_avg * (test_weight / total_weight));}
	if(recitation_weight != 0.0){recitation_avg = recitation_calc(); average = average + (recitation_avg * (recitation_weight / total_weight));}
	return average;
}

/*********************************************************************
** Function: recitation_calc
** Description: Calculates recitation average grade
** Parameters: none
** Pre-Conditions: iostream included
** Post-Conditions: we know recitation grade
** Return: average
*********************************************************************/ 
double recitation_calc(){
	double quiz_weight = 0;
	double design_weight = 0;
	double critique_weight = 0;
	int items = 0;
	cout << "Please input the weight of quizes, designs, and critiques." << endl;
	cout << "Quiz Weight: ";
	cin >> quiz_weight;
	cout << "Design Weight: ";
	cin >> design_weight;
	cout << "Critique Weight: ";
	cin >> critique_weight;
	cout << "Please input number of items to calculate: ";
	cin >> items;
	double average =  three_item_average(quiz_weight, design_weight, critique_weight, items);
	cout << "Your recitation average is: " << average << endl;
	return average;
}

/*********************************************************************
** Function: three_item_average
** Description: This was only used to make my code less than 20 lines per method
** Parameters: weightss and items
** Pre-Conditions: we have weights
** Post-Conditions: we know scores
** Return: average calc 
*********************************************************************/ 
double three_item_average(double quiz_weight, double design_weight, double critique_weight, int items){
	double quiz_scores[items];
	double design_scores[items];
	double critique_scores[items];
	double temp = 0;
	for(int i = 0; i < items; i++){
		if(quiz_weight != 0){
			cout << "Quiz Score: ";
			cin >> temp;
			quiz_scores[i] = temp;
		} if(design_weight != 0){
			cout << "Design Score: ";
			cin >> temp;
			design_scores[i] = temp;
		} if(critique_weight != 0){
			cout << "Critique Score: ";
			cin >> temp;
			critique_scores[i] = temp;
		}
	}
	return average_calc(quiz_scores, design_scores, critique_scores, items, quiz_weight, design_weight, critique_weight) ;/// things_calculating;
}

/*********************************************************************
** Function: average_calc
** Description: only used to make my methods less than 20 lines per. Actually makes it way longer overall
** Parameters: scores, items, weights
** Pre-Conditions: we have scores, items, weights
** Post-Conditions: we know the recitation average
** Return: average
*********************************************************************/ 
double average_calc(double quiz_scores[], double design_scores[], double critique_scores[], int items, double quiz_weight, double design_weight, double critique_weight){
	double total_weight = quiz_weight + design_weight + critique_weight;
	double quiz_total = 0;
	double design_total = 0;
	double critique_total = 0;
	for(int i = 0; i < items; i++){
		quiz_total = quiz_total + quiz_scores[i];
		design_total = design_total + design_scores[i];
		critique_total = critique_total + critique_scores[i];
	}
	double average = 0;
	if(quiz_weight != 0) average = average + (quiz_total * (quiz_weight / total_weight) / items);
	if(design_weight != 0) average = average + (design_total * (design_weight / total_weight) / items);
	if(critique_weight != 0) average = average + (critique_total * (critique_weight / total_weight) / items);
	return average;
}
