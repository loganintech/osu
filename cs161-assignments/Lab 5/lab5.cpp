#include <string>
#include <iostream>

using namespace std;

void get_sentence(string &the_string);

int main(){

	string pointless_example;	
	get_sentence(pointless_example);
	cout << "This is what is returned: " << pointless_example;
	return 0;
}

void get_sentence(string &the_string){
	cout << "Input string: " ;
	getline(cin, the_string);

}