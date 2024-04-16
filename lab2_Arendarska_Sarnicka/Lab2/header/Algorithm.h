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

	void kolejnosc(vector<Element>& task_list, vector<int>& res_list);
	void time_done_calculate(vector<Element>& task_list);
	int sum_of_penalty(vector<Element>& task_list);

	void read_data(const string& path);
	void write_data(const string& path);
	void sort_tasks_by_deadline();
	
	Element return_task(int id)const;
	void delete_task(int id);
	void delete_end();
	void add_task(Element e);
	bool is_empty()const;
	int get_size()const;
	
	int dynamicIteration();

};

