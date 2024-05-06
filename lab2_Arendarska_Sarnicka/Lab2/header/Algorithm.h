#pragma once
#include <list>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include "Element.h"

using namespace std;

class Algorithm
{
	int calculatePenalty(vector<Element>& taskList);
	vector<vector<Element>> permutations(vector<Element> taskList);

	static bool comparator_equal(const vector<Element>& t1, const vector<Element>& t2) {
		for (int i = 0; i < t1.size(); i++)
			if (t1[i].id != t2[i].id) return false;
		return true;
	}
public:
	int n = 0;
	int penalty_sum = 0;
	static const int dmax = 1000000000;
	vector<Element> task_list;
	vector<int> result_list;

	Algorithm();
	~Algorithm();

	void read_data(const string& path);
	int dynamicIteration();

	int dummyCode();
	int tabuSearch(int max_iter, int penalty);
};

