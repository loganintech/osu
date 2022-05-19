#include <iostream>
#include <string>

using namespace std;

int main(){
	string name;

	bool guessed_correct = false;
	int questions_asked = 0;
	int response;
	string name_response;
	while(!guessed_correct){

		cout << "Do you want to guess [0] or ask a question [1]: " << endl;
		cin >> response;

		if(response == 0){
			cout << "Guess the TA name now (all lowercase): " << endl;
			cin >> name_response;
			if(name_response == "lily"){
				cout << "You did it in " << questions_asked << " questions asked." << endl;
				return 0;
			} else {
				cout << "No, try again." << endl;
			}
		} else if (response == 1){
			response = 0;
			questions_asked++;
			cout << "Would you like to know their hair color [0], shirt color [1], or gender [2]: " << endl;
			cin >> response;
			
			switch(response){
				case 0:
					cout << "The TA has blond hair." << endl;
					break;
				case 1:
					cout << "The TA is wearing a white shirt." << endl;
					break;
				case 2:
					cout << "The TA is female." << endl;
					break;
			}

		}

	}

	return 0;
}