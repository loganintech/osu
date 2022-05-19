#include <string>
#include <iostream>
#include <string>
#include <fstream>
#include <cstdio>

using namespace std;

int main(){

	string * to_be_deleted = new string [1];
	to_be_deleted[0] = "two";
	to_be_deleted[1] = "four";

	ifstream file;
	file.open("books.txt");

	ofstream out_file;
	out_file.open("temp.txt");

	string line;
	bool should_be_removed;
	
	while(file.good()){
		file >> line;
		should_be_removed = false;
		for(int i = 0; i < 2 ; i++){
			if(line == to_be_deleted[i]){
				should_be_removed = true;
				break;
			}
		}

		if(!should_be_removed){
			out_file << line << endl;
		}
	}

	remove("books.txt");
	rename("temp.txt", "books.txt");

}