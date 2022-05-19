#include<iostream>
#include<string>
#include<vector>
#include<sstream>
#include<fstream>

std::string error_handler(std::string& word) {
	std::string temp;
	
	temp = word.substr(4, word.size());
	word.erase(4, word.size());

	return temp;
}

void read_file(std::string file) {
	std::fstream f;
	f.open(file.c_str(), std::ios::in);

	std::vector<std::string> row, out;
	std::string line, word, temp, filename;
	std::string newcol;

	while (std::getline(f, temp)) {
		row.clear();
		std::stringstream ss(temp);

		while (getline(ss, word, ',')) {
			row.push_back(word);
		}

		if (row.size() < 8) {
			newcol = error_handler(row[3]);
			out.push_back(row[0] + "," + row[1] + "," + row[2] + "," + row[3] + "," +
				newcol + "," + row[4] + "," + row[5] + "," + row[6] + "\n");
		}
		else
			out.push_back(row[0] + "," + row[1] + "," + row[2] + "," + row[3] + "," + 
				 row[4] + "," + row[5] + "," + row[6] + "," + row[7] + "\n");
		
	}
	f.close();
	f.open("output.csv", std::ios::out);

	for (int i = 0; i < out.size(); i++)
		f << out[i];

	f.close();
}

int main() {

	read_file("SFO_19.dat");

	return 0;
}