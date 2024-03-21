#pragma once
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include "Task.h"
#include "Algorithms.h"

class Result
{
public:
	int c_max;
	int sum_c_max = 0;
	std::vector<task> task_list;

	Result();
	~Result();

	void run(const std::string& path, int choice);
	void write_data(const std::string& path);
};

