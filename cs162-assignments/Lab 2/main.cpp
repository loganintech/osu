#include <string>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include "webpage.h"

using namespace std;

int main(int argc, char * argv[]){

	ifstream file;
	file.open("input.txt", ifstream::in);
	create_html(file);
	file.close();
}

void create_header(ifstream & input, ofstream & output){
	output << "<html>" << endl;
	output << "<head>" << endl;
	string line;
	getline(input, line);
	output << "<title>" << line << "</title>" << endl;
	output << "</head>" << endl;
}
void create_body(ifstream & input, ofstream & output){
	string line;
	getline(input, line);
	output << "<body bgcolor=\"" << line << "\">" << endl;
	getline(input, line);
	output << "<font color=\"" << line.substr(0, line.find(" ")) << "\" size=\"" << line.substr(line.find(" ") + 1, 1) << "\" face=\"" << line.substr(line.find(" ", line.find(" ") + 1) + 1) << "\">" << endl;
	getline(input, line);
	output << line << "<br>" << endl << "<br>" << endl;
	getline(input, line);
	getline(input, line);
	output << line << "<br>" << endl << "<br>" << endl;
	output << "</font>" << endl << "</body>" << endl << "</html>";
}
void create_html(ifstream & input){

	ofstream out_file;
	out_file.open("../../public_html/index.html", ofstream::out);
	create_header(input, out_file);
	create_body(input, out_file);
	out_file.close();

}
