#include <iostream>

using namespace std;

void dynamic_memory_assignment(int *one, int *two, int *three);
void dynamic_memory_delete(int *one, int *two, int *three);

int main(){
	int *one;
	int *two;
	int *three;
	dynamic_memory_assignment(one, two, three);
	cout << one << endl << two << endl << three << endl;
	cout << *one << endl << *two << endl << *three << endl;
	dynamic_memory_delete(one, two, three);
}

void dynamic_memory_assignment(int *one, int *two, int *three){
	one = new int[1];
	two = new int[2];
	three = new int[3];
}

void dynamic_memory_delete(int *one, int *two, int *three){
	one = 0x0;
	two = 0x0;
	three = 0x0;
}