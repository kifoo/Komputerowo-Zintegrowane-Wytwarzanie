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
#include "header\Algorithms.h"
 
using namespace std;

int main() {
	const string data_p[4] = { "data/p1.txt" ,"data/p2.txt" ,"data/p3.txt" ,"data/p4.txt" };
	const string data_s[4] = { "solutions/s1.txt" ,"solutions/s2.txt" ,"solutions/s3.txt" ,"solutions/s4.txt" };
	int sum_c_max = 0;

	//case 1: Schrage
	// case 2: Compare R and Q
	// case 3: Tabu Search
	// case 4: One long task ( only on data/p2.txt)
	// case 5: Carlier
	int choice = 4;

	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

	for (int i = 0; i < 4; i++)
	{
		Algorithms alg;
		int C_max = INT_MAX;
		int non_important = 0;
		alg.read_data(data_p[i]);
		vector<task> Tasks = alg.task_list;
		switch (choice)
		{
			case 1:
				C_max = alg.schrage(Tasks);
				alg.task_list = Tasks;
				alg.c_max = C_max;
				break;
			case 2:
				alg.algorithm_rq(Tasks, alg.n);
				alg.task_list = Tasks;
				alg.c_max = alg.calculate_cmax(alg.task_list);
				break;
			case 3:
				Tasks = alg.tabu_search(100, C_max);
				alg.task_list = Tasks;
				alg.c_max = C_max;
				break;
			case 4:
				if (i != 1) {
					Tasks = alg.tabu_search(100, C_max);
					alg.task_list = Tasks;
					alg.c_max = C_max;
				}
				else {
					alg.one_long_task(C_max, Tasks);
					alg.task_list = Tasks;
					alg.c_max = C_max;
				}
				break;
			case 5:
				non_important = alg.Carlier(C_max, Tasks);
				alg.task_list = Tasks;
				alg.c_max = alg.calculate_cmax(alg.task_list);
				break;
			default:
				cout << "Wrong choice" << endl;
				break;
		}
		sum_c_max += alg.c_max;
		alg.write_data(data_s[i]);
	}

	cout << "\nSum of cmax: " << sum_c_max << endl;
	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	cout<< "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;


	return 0;

}