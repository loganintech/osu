#include <iostream>

using namespace std;

double rectangle_func(double x);
bool ask_continue();
double area(double left_bound, double right_bound, int num_rectangles);
double rectangle_func(double x);

int main(){

	bool should_continue = true;
	while(should_continue){
		int left_bound = 0;
		int right_bound = 0;
		int num_rectangles = 1;
		cout << "Please input your left bound: ";
		cin >> left_bound;

		cout << "Please input your right bound: ";
		cin >> right_bound;

		cout << "Please input the number of rectangles for approximation: ";
		cin >> num_rectangles;

		double total_area = area(left_bound, right_bound, num_rectangles);
		cout << "Area under curve: " << total_area << endl;

		should_continue = ask_continue();
	}


}

/*
Name: rectangle_func
Description: Gets and x and returns the function value at x
Pre Conditions: X is known
Post Conditions: f(x) is known
Return: f(x)
*/
double rectangle_func(double x){
	return 2*x;
}


double area(double left_bound, double right_bound, int num_rectangles){

	double total_area = 0.0;
	double rectangle_width = (right_bound - left_bound) / num_rectangles;
	
	//cout << "Rectangle Width: " << rectangle_width;
	for(double i = 0; i < num_rectangles; i++){
		total_area += rectangle_func((i * rectangle_width)+ left_bound);
	}
	return total_area * rectangle_width;

}

bool ask_continue(){
	int input = 0;
	cout << "Do you want to continue? [0 - yes, other - no]: ";
	cin >> input;
	if(input == 0) return true;
	return false;
}