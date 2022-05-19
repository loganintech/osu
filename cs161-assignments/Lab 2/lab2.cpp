#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

int main(){
	int x;
	srand(time(0));

	x = rand();
	cout << "x = " << x << endl;
	
	x = rand();
	cout << "x = " << x << endl;
}