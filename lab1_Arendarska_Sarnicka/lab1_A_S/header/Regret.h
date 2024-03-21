#pragma once
#include <list>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include "Task.h"
#include "Tree_Node.h"

using namespace std;


// this is the most not optimal thing to do XD
class Regret
{
public:
	int n = 0;
	vector<task> task_list;

	Tree_Node* root = nullptr;

	Regret();
	~Regret();

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

	void run(int& c_max, vector<task>& result_list);

	void test_tree();
	Tree_Node* Tree_Schrage(vector<task> t_list, Tree_Node* tmp, int& Best_Time);

	void find_best_sum(vector<task>& tasks, task& long_task);
	void Task_List_Before_Long_Task(vector<task>& ready, task& l_task);
	void Kill_Me_Now(int& c_max, vector<task>& result_list);


	int calculate_cmax(vector<task> t_list);
	void read_data(const string& path);
	void write_data(const string& path);
};

