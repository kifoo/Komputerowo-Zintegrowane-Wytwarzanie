#pragma once
#include <list>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include "Task.h"
#include "Result.h"

using namespace std;

class Algorithms
{
public:

	int n = 0;
	vector<task> task_list;
	Algorithms();
	~Algorithms();

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

	static bool comparator_rq(const task& t1, const task& t2) {
		if (t1.r != t2.r) return t1.r < t2.r;
		if (t1.q != t2.q) return t1.q > t2.q;
		return false;
	}

	void sort_r();
	void sort_rq();
	int schrage(vector<task>& t_list);
	int schrage2();

	void find_best_sum(vector<task>& tasks, task& long_task);
	void best_task_list(vector<task>& ready, task& l_task);
	void My_Own_Atgorithm(int& c_max, vector<task>& result_list);

	int Carlier(int& UB, int& min_U, vector<task>& result_list);
	int calculate_cmax(vector<task> t_list);
	int mark_A(int b);
	int mark_B(vector<task>& t_list);
	int mark_C(int a, int b);
	void read_data(const string& path);
	void write_data(const string& path);
	void clear_list();
};

