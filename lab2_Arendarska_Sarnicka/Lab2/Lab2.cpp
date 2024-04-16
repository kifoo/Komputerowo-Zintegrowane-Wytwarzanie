#include <string>
#include <fstream>
#include <iostream>
#include <format>
#include <vector>
#include <algorithm>
#include <list>
#include <chrono>
#include "windows.h"

//include class 
#include "header\Algorithm.h"

void write_data(const string& path, const vector<Algorithm>& algorytmy) {
	ofstream file;
	file.open(path);
	if (file.is_open()) {
		for (const auto& alg : algorytmy) {
			cout << "\n Suma kar: " << alg.penalty_sum << std::endl;
			file << "\n Suma kar: " << alg.penalty_sum << std::endl;
			for (int id : alg.result_list) {
				cout << id + 1 << " "; 
				file << id + 1 << " ";
			}
			file << endl; 
		}
	}
	else {
		std::cout << "Error opening file: " << path << std::endl;
	}
	file.close();
}

int main()
{
	const string data_p[11] = { "data/p10.txt", "data/p11.txt", "data/p12.txt", "data/p13.txt", "data/p14.txt", "data/p15.txt", "data/p16.txt", "data/p17.txt", "data/p18.txt", "data/p19.txt", "data/p20.txt" };
	const string data_s[1] = { "data/solutions.txt" };
	vector<Algorithm> algorytmy;

	for (int i = 0; i < 11; i++)
	{
		Algorithm alg;
		alg.read_data(data_p[i]);
		int minPenalty = alg.dynamicIteration();

		std::cout << "File: " << data_p[i] << std::endl;
		std::cout << "Minimum Penalty using Dynamic Iteration: " << minPenalty << std::endl;

		alg.penalty_sum = minPenalty;
		algorytmy.push_back(alg);

	}
	write_data(data_s[0], algorytmy);
}






