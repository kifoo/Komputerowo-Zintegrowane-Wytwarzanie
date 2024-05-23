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

bool checkOrder(const list<int>& ourOrder, const vector<int>& solutionOrder) {
	int i = 0;
	for (auto our: ourOrder) {
		if (our != solutionOrder[i]) {
			return false;
		}
		i++;
	}
	return true;
}

void write_data(const string& path, const vector<Algorithm>& algorytmy, string title) {
	long int ourFullTime = 0;
	long int SolutionTime = 0;
	vector<pair<Algorithm, Algorithm>> wrongOrders;
	ofstream file;
	file.open(path);
	if (file.is_open()) {
		int i = 0;
		file << "\\begin{longtable}[H]{|l|l|l|p{7cm}|l|} \n";
		file << "\\caption{} \n";
		file << "\\label{ tab:my - table }\\\\ \n \\hline";
		file << "\\textbf{Dane} &  \n \\textbf{Nasz czas} &  \n \\textbf{Oczekiwany czas} &  \n \\textbf{Kolejnoœæ} &  \n \\textbf{Czas alg.} \\\\ \\hline";
		file << "\\endfirsthead \n % \n \\endhead \n % \n";
		file << "Dane & Nasz czas & Oczekiwany czas & Kolejnoœæ & Czas alg. \\\\  \\hline" << endl;

		for (const auto& alg : algorytmy) {
			// Comparizon
			ourFullTime += alg.fullTime;
			SolutionTime += alg.solution.value;
			if (!checkOrder(alg.order, alg.solution.order)) {
				wrongOrders.push_back({ alg, alg });
			}
			if (alg.fullTime < alg.solution.value) {
				file << "\\rowcolor[HTML]{67FD9A} \n";
			}
			else if (alg.fullTime > alg.solution.value){
				file << " \\rowcolor[HTML]{FD6864} \n";
			}
			file << i << ". & " << alg.fullTime << " & " << alg.solution.value << " & ";

			
			for (int id : alg.order) {
				
				file << id + 1 << " ";
			}
			
			file << " & " << alg.time_ms << "\\\\ \\hline \n";

			i++;

		}
		file << "\t\\end{longtable}";
		i = 0;
		int ourBest = 0;
		int MakBest = 0;
		for (const auto& [our, solution] : wrongOrders) {
			i++;
			if (our.fullTime < solution.solution.value) {
				ourBest++;
			}
			else if (our.fullTime > solution.solution.value){
				MakBest++;
			}
		}
		std::cout << "Diffrent: " << i << endl;
		std::cout << "Our best: " << ourBest << endl;
		std::cout << "MakBest: " << MakBest << endl;
	}
	else {
		std::cout << "Error opening file: " << path << endl;
	}
	file.close();
}

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
		alg.time_ms = (int)std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
		algorithms.push_back(alg);
    }
	
	/*int sumTime = 0;
	for (auto jobTime : JobsTime) {
		sumTime += jobTime;
		std::cout << "Time =  " << jobTime << endl;
	}*/
	//cout << "Sum time = " << sumTime << endl;
	write_data("Dane/Wyniki.txt", algorithms, "Wyniki");
    
}
