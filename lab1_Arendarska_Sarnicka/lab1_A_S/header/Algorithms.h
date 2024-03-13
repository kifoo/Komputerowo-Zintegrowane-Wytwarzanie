#pragma once
#include <list>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class Algorithms
{
public:
	struct task {
		int r;
		int p;
		int q;
	};

	list<task> task_list;
	Algorithms();
	~Algorithms();

	void sort_r();
	void sort_rq();
	void schrage();
	void potts();
	void C100();
	void Carlier();
	void read_data(const string& path);
	void write_data(const string& path);
	void clear_list();
};

