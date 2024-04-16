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

void write_data(const string& path, const vector<Algorithm> alg) {
	ofstream file;
	file.open(path);
	if (file.is_open()) {
		for (auto& a : alg) {
			cout << "\n Suma kar: " << a.penalty_sum << std::endl;
			file << "\n Suma kar: " << a.penalty_sum << std::endl;
			for (auto& t : a.task_list) {
				cout << t.id << " ";
				file << t.id << " ";
			}

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
		alg.kolejnosc(alg.task_list, alg.result_list);
		alg.time_done_calculate(alg.task_list);
		alg.sum_of_penalty(alg.task_list);

		std::cout << "File: " << data_p[i] << std::endl;
		std::cout << "Minimum Penalty using Dynamic Iteration: " << minPenalty << std::endl;

		alg.penalty_sum = minPenalty;
		algorytmy.push_back(alg);
		// alg.write_data(data_p[i]);
	}
	write_data(data_s[0], algorytmy);

	//cout << "\nSum of cmax: " << sum_c_max << endl;
}






