#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;
void read_record()
{
	fstream fin;
	fin.open("16.csv", ios::in);
	int count;
	vector<vector<double>> row;
	string line, word, temp;
	getline(fin, line);
	while (!fin.eof()) {
		vector<double> n;
		n.clear();
		getline(fin, line);
		stringstream s(line);
		while (getline(s, word, ',')) {
			count = stoi(word);
			n.push_back(count);
			cout << count << "    ";
		}
		cout << endl;
		row.push_back(n);
	}
}
int main() {

	read_record();

	return 0;
}