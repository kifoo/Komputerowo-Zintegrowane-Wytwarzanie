#pragma once
#include <list>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include "Task.h"

using namespace std;

class Algorithms
{
public:

	int n = 0;
	int c_max = 0;
	vector<task> task_list;
	Algorithms();
	~Algorithms();

	static bool comparator_id(const task& t1, const task& t2) {
		if (t1.id < t2.id) return true;
		if (t1.id > t2.id) return false;
		return false;
	}

	static bool comparator_equal(const vector<task>& t1, const vector<task>& t2) {
		for(int i = 0; i < t1.size(); i++)
			if (t1[i].id != t2[i].id) return false;
		return true;
	}

	static bool comparator_min_r(const task& t1, const task& t2) {
		if (t1.r < t2.r) return true;
		if (t1.r > t2.r) return false;
		return false;
	}

	static bool comparator_max_r(const task& t1, const task& t2) {
		if (t1.r > t2.r) return true;
		if (t1.r < t2.r) return false;
		return false;
	}

	static bool comparator_min_q(const task& t1, const task& t2) {
		if (t1.q < t2.q) return true;
		if (t1.q > t2.q) return false;
		return false;
	}

	static bool comparator_max_q(const task& t1, const task& t2) {
		if (t1.q > t2.q) return true;
		if (t1.q < t2.q) return false;
		return false;
	}
	// Compare R and Q
	void algorithm_rq(vector<task>& t_list, int size);


	// Tabu Search
	vector<vector<task>> permutations(vector<task> t_list);
	vector<task> tabu_search(int max_iter, int& c_max);

	//	For seraching best reault if there is one long lask and rest have time r and q = 0
	int find_best_sum(vector<task>& tasks, task& long_task);
	int find_best_sum_back(vector<task>& tasks, task& long_task);
	void one_long_task(int& c_max, vector<task>& result_list);

	// Algorithms form list
	int schrage(vector<task>& t_list);
	int schrage2();
	int Carlier(int& UB, vector<task>& result_list);
	int calculate_cmax(vector<task> t_list);
	int mark_A(int b);
	int mark_B(vector<task>& t_list);
	int mark_C(int a, int b);
	void read_data(const string& path);
	void write_data(const string& path);
};

