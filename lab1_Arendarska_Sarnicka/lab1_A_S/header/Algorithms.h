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
		int id;
		int r;
		int p;
		int q;		
	};

	vector<task> task_list;
	Algorithms();
	~Algorithms();

	static bool comparator_r(const task& t1, const task& t2) {
		if (t1.r < t2.r) return true;
		if (t1.r > t2.r) return false;
		return false;
	}

	static bool comparator_q(const task& t1, const task& t2) {
		if (t1.q > t2.q) return true;
		if (t1.q < t2.q) return false;
		return false;
	}

	static bool comparator_rq(const task& a, const task& b) {
		if (a.r != b.r) return a.r < b.r;
		if (a.q != b.q) return a.q > b.q;
		return false;
	}

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

