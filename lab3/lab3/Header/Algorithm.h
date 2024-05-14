#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <algorithm>
#include <numeric>
#include <limits>
#include <format>
#include <Windows.h>
#include <Psapi.h>
#undef max
#include "Element.h"

using namespace std;

class Algorithm {
	int taskCount = 0;		// Rows
	int machineCount = 0;	// Cols
	vector<Job> tasks; // All jobs 
	static bool compare_jobs(const Job& job1, const Job& job2) {
		return job1.total_time > job2.total_time;
	}
public:
	Algorithm();
	~Algorithm();

	int fullTime = 0;
	vector<int> order;
	Neh solution;

	void neh_algorithm();
	int calculate_completion_time(const vector<Job>& jobs);
	void quick_neh_algorithm();

	void makeOrder(const vector<Job>& jobs);
	//void calculateFullTime(const vector<Job>& jobs);
	void readData(const string& path);
};