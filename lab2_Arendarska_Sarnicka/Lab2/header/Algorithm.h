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

};

