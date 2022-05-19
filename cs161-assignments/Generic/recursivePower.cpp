#include <iostream>

using namespace std;

int pwr(int, int);
long double factorial(long double);

int main(){
	cout << pwr(2, 9) << endl;
	//cout << factorial(10) << endl;
	return 0;
}

int pwr(int a, int b){
	if(b == 0){
		return 1;
	} else if (b == 1) {
		return a;
	} else {
		return a * pwr(a, b - 1);
	}
}

long double factorial(long double a){
	cout << a << endl;
	if (a <= 1){
		return a;
	}
	return a * factorial(a-1);
}