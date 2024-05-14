#include <iostream>
#include <fstream>
#include <format>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>
#include <limits> // For std::numeric_limits

#include "Header\Algorithm.h"

using namespace std;

//bool checkOrder(const vector<int>& ourOrder, const vector<int>& solutionOrder) {
//	for (int i = 0; i < ourOrder.size(); i++) {
//		if (ourOrder[i] != solutionOrder[i]) {
//			return false;
//		}
//	}
//	return true;
//}

//void write_data(const string& path, const vector<Algorithm>& algorytmy, string title) {
//	long int ourFullTime = 0;
//	long int SolutionTime = 0;
//	vector<pair<Algorithm, Algorithm>> wrongOrders;
//	ofstream file;
//	file.open(path);
//	if (file.is_open()) {
//		cout << title << endl;
//		//file << title << endl;
//		for (const auto& alg : algorytmy) {
//			cout << "\n Czas: " << alg.fullTime << "\t\t";
//			cout << "\n Solution time: " << alg.solution.value << endl;
//			//file << "\n Czas: " << alg.fullTime << endl;
//			//file << "\n Kolejnoœæ:\n";
//			cout << "Kolejnosc:\n";
//			for (int id : alg.order) {
//				cout << id + 1 << " ";
//				//file << id + 1 << " ";
//			}
//			cout << "\nSolution Order:\n";
//			for (int id : alg.solution.order) {
//				cout << id<< " ";
//			}
//			cout << endl;
//			//file << endl;
//
//			// Comparizon
//			ourFullTime += alg.fullTime;
//			SolutionTime += alg.solution.value;
//			if (!checkOrder(alg.order, alg.solution.order)) {
//				wrongOrders.push_back({alg, alg});
//			}
//
//		}
//		int i = 0;
//		int ourBest = 0;
//		int MakBest = 0;
//		for (const auto& [our, solution] : wrongOrders) {
//			cout << "Wrong order: " << endl;
//			cout << "Our order: ";
//			cout << "Our time: " << our.fullTime << endl;
//			for (int id : our.order) {
//				cout << id + 1 << " ";
//			}
//			cout << endl;
//			cout << "Solution order: ";
//			cout << "Solution time: " << solution.solution.value << endl;
//			for (int id : solution.solution.order) {
//				cout << id + 1 << " ";
//			}
//			cout << endl;
//			i++;
//			if (our.fullTime < solution.solution.value) {
//				ourBest++;
//			}
//			else {
//				MakBest++;
//			}
//		}
//		cout << "Diffrent: " << i << endl;
//		cout << "Our best: " << ourBest << endl;
//		cout << "MakBest: " << MakBest << endl;
//	}
//	else {
//		cout << "Error opening file: " << path << endl;
//	}
//	file.close();
//}

int main() {
    string path;
	string extension = ".txt";
	vector<Algorithm> algorithms;

	vector<int> JobsTime;

    for (int i = 0; i <= 120; i++) {
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
		//cout << path << endl;
		Algorithm alg;
		alg.readData(path);
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
		//alg.neh_algorithm();
		alg.quick_neh_algorithm();
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		JobsTime.push_back((int)std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count());
		algorithms.push_back(alg);
    }
	
	int sumTime = 0;
	for (auto jobTime : JobsTime) {
		sumTime += jobTime;
		cout << "Time =  " << jobTime << endl;
	}
	cout << "Sum time = " << sumTime << endl;
	//write_data("Dane/Wyniki.txt", algorithms, "Wyniki");
    
}
