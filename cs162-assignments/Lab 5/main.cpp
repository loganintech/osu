#include <iostream>

using namespace std;

int main(){

	#ifdef DEBUG
		cout << "Testing debug" << endl;
	#endif
	cout << "Out of debug" << endl;

	return 0;
}