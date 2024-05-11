#include <iostream>
#include <fstream>
#include <format>
#include <vector>
#include <string>
#include <algorithm>
#include <limits> // For std::numeric_limits

#include "Header\Algorithm.h"

using namespace std;

void write_data(const string& path, const vector<Algorithm>& algorytmy, string title) {
	ofstream file;
	file.open(path);
	if (file.is_open()) {
		cout << title << endl;
		//file << title << endl;
		for (const auto& alg : algorytmy) {
			cout << "\n Czas: " << alg.fullTime << "\t\t";
			cout << "\n Solution time: " << alg.solution.value << endl;
			//file << "\n Czas: " << alg.fullTime << endl;
			//file << "\n Kolejnoœæ:\n";
			cout << "Kolejnosc:\n";
			for (int id : alg.order) {
				cout << id + 1 << " ";
				//file << id + 1 << " ";
			}
			cout << "\nSolution Order:\n";
			for (int id : alg.solution.order) {
				cout << id<< " ";
			}
			cout << endl;
			//file << endl;
		}
	}
	else {
		cout << "Error opening file: " << path << endl;
	}
	file.close();
}

int main() {
    string path;
	string extension = ".txt";
	vector<Algorithm> algorithms;

    for (int i = 0; i <= 10; i++) {
		path = "Dane/all/data_";
		if (i < 10) {
			path += "00" + to_string(i) + extension;
        }
        else if (i < 100) {
			path += "0" + to_string(i) + extension;
        }
        else {
			path += to_string(i) + extension;
		}
		cout << path << endl;
		Algorithm alg;
		alg.readData(path);
		alg.neh_algorithm();
		algorithms.push_back(alg);
    }
	write_data("Dane/Wyniki.txt", algorithms, "Wyniki");
    
}
