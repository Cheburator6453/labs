#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <vector>
#include <string>

using namespace std;

void my_read(vector<vector<string>>&  arr, string name){
	ifstream fin;
	fin.open(name);
	string line, word;
	getline(fin, line);
	while(!fin.eof()){
		vector<string> temp;
		temp.clear();
		stringstream s(line); 
		getline(fin, line);
		while(getline(s, word, ',')){
			temp.push_back(word);
		}
		arr.push_back(temp);
	}
	fin.close();
}

void selectValues(vector<vector<string>> arr, vector<double>& y, vector<double>& x, int column, int number, bool all = false){
	int m = 0;
	string s, s1;
	int j= 1;
	for(int i = 0; i < number ; i++, j++){
		s = arr[j][column];
		s1 = arr[j][m];
		if(atof(s.c_str()) == 999.9){
			if(!all){
				i = -1;
				x.clear();
				y.clear();
			}			
			continue;
		}
		y.push_back(atof(s.c_str()));
		x.push_back(atof(s1.c_str()));
	}
}

void plot(vector<double> T, string name, double min, double h){
	ofstream fout;
	fout.open(name); 
	for (int i = 0; i < T.size(); i++){
		fout << min << " " << T[i] << endl;
		min+=h;
	}
	fout.close();
}

void point(vector <double> x, vector<double> y, string name){
	ofstream fout;
	fout.open(name);
	for(int i = 0; i < x.size(); i++){
		fout << x[i] << " " << y[i] << endl;
	}
	fout.close();
}

double fmin(vector<double> a){
	double min = a[0];
	for (int i = 1; i < a.size(); i++){
		if(a[i]< min){
			min = a[i];
		}
	}
	return min;
}
double fmax(vector<double> a){
	double max = a[0];
	for (int i = 1; i < a.size(); i++){
		if(a[i] > max){
			max = a[i];
		}
	}
	return max;
}

double f(vector<double> l, double x, int i, int n){
	double res = 1;
	for(int j = 0; j < n; j++){
		if(i != j)
			res *= (x - l[j]) / (l[i] - l[j]); 
	}
	return res;
}

void lagrange(vector<double> x, vector<double> y, double h){
	vector<double> L;
	double sum = 0;
	double min = fmin(x), max = fmax(x);
	for(double k = min; k <= max; k+=h){
		for (int i = 0; i < y.size(); i++){
			sum += y[i] * f(x, k, i, x.size());
		}
		L.push_back(sum);
		sum = 0;
	}
	plot(L, "data.txt", min, h);
}


int main(){
	vector<vector<string>> arr;
	my_read(arr, "16.csv");
	double h = 0.1;
	int n=4, p=12;
	vector<double> y;
	vector<double> x;
	selectValues(arr, y, x, n, p);
	point(x, y, "points.txt");
	lagrange(x, y, h);
}
