#include <iostream>

using namespace std;

// void print_num(int=12);

// int main(){

// 	print_num();
// 	return 0;
// }

// void print_num(int thing){
// 	cout << thing;
// }

int main(){
	int what = 9;
	int *test = &what;
	cout << test << endl;
	int value = *test;
	cout << value << endl;

}