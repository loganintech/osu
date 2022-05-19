#include <iostream>

using namespace std;

int fib(int x, int y, int index, int max){
	cout << "X: " << x << "\nY: " << y << "\nIndex: " << index << "\nMax: " << max << endl; 
	if(index >= max){
		return x;
	} else {
		return fib(y, x+y, index+1, max);
	}

}

int main(){

	cout << fib(0,1,0,10);
	return 0;
}

