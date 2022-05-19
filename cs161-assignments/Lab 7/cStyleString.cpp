#include <iostream>
#include <string>

using namespace std;

void set_replace_string(char *, char *);
int get_search_replace(char *, char *);

int main(){
	char theString[] = "test test";
	char emptyString[] = "";
	char *emptyStringPtr = emptyString;
	set_replace_string(theString, emptyStringPtr);
	cout << get_search_replace(theString, emptyString) << endl;
	cout << theString << endl; //<< emptyString << endl;
	return 0;
}

void set_replace_string(char *theString, char *replaceString){

	char *build_me = new char [255];
	for(int i = 0; i < sizeof(theString); i++){
		if( theString[i] != ' ' ){
			build_me[i] = '-';
		} else {
			build_me[i] = ' ';
		}
	}
	*replaceString = *build_me;
}

int get_search_replace(char *realString, char *blankString){
	char theLetter;
	cout << "Give me a letter to replace in the string: " ;
	cin >> theLetter;
	char *build_me = new char[255];
	int found = 0;
	for(int i = 0; i < sizeof(realString); i++){

		if(realString[i] == theLetter){
			found++;
			build_me += theLetter;
		} else {
			build_me += blankString[i];
		}
	}
	blankString = build_me;
	return found;
}