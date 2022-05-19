#include <iostream>

using namespace std;

void do_hanoi(int disks, int** b, int from_col, int spare, int to_col, int some_length);
void print_hanoi(int **array, int some_length);
void move_disk(int **array, int from_col, int to_col, int some_length);

int main(int argc, char *argv[]){
	int some_length = 10;
	unsigned int iterations = 0;
	int **array = new int*[3];
	for(int i = 0; i < 3; i++){
		array[i] = new int[some_length];
	}
	for(int i = 0; i < some_length; i++){
		array[0][i] = i + 1;
		array[1][i] = 0;
		array[2][i] = 0;
	}
	do_hanoi(some_length, array, 0, 1, 2, some_length);
}

void do_hanoi(int disks, int** b, int from_col, int spare, int to_col, int some_length){

	if(disks == 1){
		cout << "Move " << from_col << " to " << to_col << "." << endl;
		move_disk(b, from_col, to_col, some_length);
		print_hanoi(b, some_length);
		return;
	}
	do_hanoi(disks - 1, b, from_col, to_col, spare, some_length);
	cout << "Move " << from_col << " to " << to_col << "." << endl;
	move_disk(b, from_col, to_col, some_length);
	print_hanoi(b, some_length);
	do_hanoi(disks - 1, b, spare, from_col, to_col, some_length);

}


void print_hanoi(int **array, int some_length){
	for(int i = 0; i < some_length; i++){
		cout << " " << array[0][i] << " " << array[1][i] << " " << array[2][i] << endl;
	}
}

void move_disk(int **array, int from_col, int to_col, int some_length){
	int temp = 0;
	for(int i = 0; i < some_length; i++){
		if(array[from_col][i] != 0){
			temp = array[from_col][i];
			array[from_col][i] = 0;
			break;
		}
	}
	for(int i = 0; i < some_length; i++){
		if(i == some_length - 1 || (array[to_col][i] == 0 && array[to_col][i + 1] != 0)){
			array[to_col][i] = temp;
			break;
		}
	}
}