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
			cout << path << "\t Suma kar: " << a.penalty_sum << std::endl;
			//file << path << "\t cmax: " << c_max << std::endl;
			for (auto& t : a.task_list) {
				cout << t.id << " ";
				//file << t.id << " ";
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
	const string data_p[5] = { "data/p10.txt" ,"data/p11.txt" ,"data/p12.txt" ,"data/p13.txt" ,"data/p14.txt" };
	const string data_s[5] = { "data/solutions.txt" };
	vector<Algorithm> algorytmy;

	for (int i = 0; i < 1; i++)
	{
		Algorithm alg;
		alg.read_data(data_p[i]);
		alg.kolejnosc(alg.task_list, alg.result_list);
		alg.time_done_calculate(alg.task_list);
		alg.sum_of_penalty(alg.task_list);
		algorytmy.push_back(alg);
	}

	//cout << "\nSum of cmax: " << sum_c_max << endl;
}


