#include <iostream>
#include <string>

using namespace std;


void get_string(string *);
void set_replace_string(string, string *);
int get_search_replace(string, string &);

int main(){
	string theString = "test test";
	string emptyString = "";
	string *emptyStringPtr = &emptyString;
	set_replace_string(theString, emptyStringPtr);
	cout << get_search_replace("test test", emptyString) << endl;
	cout << theString << endl << emptyString << endl;
	return 0;
}

void set_replace_string(string theString, string *replaceString){

	string build_me = "";
	for(int i = 0; i < theString.size(); i++){
		if( theString.at(i) != ' ' ){
			build_me+="_";
		} else {
			build_me+=" ";
		}
	}
	*replaceString = build_me;
}

int get_search_replace(string realString, string &blankString){
	char theLetter;
	cout << "Give me a letter to replace in the string: " ;
	cin >> theLetter;
	string build_me = "";
	int found = 0;
	for(int i = 0; i < realString.size(); i++){

		if(realString.at(i) == theLetter){
			found++;
			build_me += theLetter;
		} else {
			build_me += blankString.at(i);
		}
	}
	blankString = build_me;
	return found;
}