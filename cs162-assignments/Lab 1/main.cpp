#include "main.h"
#include <iostream>

using namespace std;

int main(int argc, char * argv[]){

	if(!is_valid_dimensions(argv[1], argv[2])){
		cout << "You need to pass at least two numbers." << endl;
	}

	int row = atoi(argv[1]);
	int col = atoi(argv[2]);

	mult_div_values ** the_table = create_table(row, col);
	set_mult_values(the_table, row, col);
	set_div_values(the_table, row, col);
	print_table(the_table, row, col);
	delete_table(the_table, row);
	delete[] the_table;
}


bool is_valid_dimensions(char *m, char *n){
	return !(atoi(m) == 0 || atoi(n) == 0);
}

mult_div_values** create_table(int row, int col){
	mult_div_values ** the_table = new mult_div_values*[row];
	for(int i = 0; i < col; i++){
		the_table[i] = new mult_div_values[col];
	}
	return the_table;
}

void set_mult_values(mult_div_values **table, int row, int col){
	for(int i = 0; i < row; i++){
		for(int x = 0; x < col; x++){
			table[i][x].mult = (i+1) * (x+1);
		}
	}
}

void set_div_values(mult_div_values **table, int row, int col){
	for(int i = 0; i < row; i++){
		for(int x = 0; x < col; x++){
			table[i][x].div = (float)(i+1) / (x+1);
		}
	}
}

void delete_table(mult_div_values **table, int row){
	
	for(int i = 0; i < row; i++){
		delete[] table[i];
	}

}

void print_table(mult_div_values **table, int row, int col){
	for(int i = 0; i < row; i++){
		for (int x = 0; x < col; x++){
			cout << table[x][i].mult << " | ";
		}
		cout << endl;
	}

	for(int i = 0; i < row; i++){
		for (int x = 0; x < col; x++){
			cout << table[x][i].div << " | ";
		}
		cout << endl;
	}
}