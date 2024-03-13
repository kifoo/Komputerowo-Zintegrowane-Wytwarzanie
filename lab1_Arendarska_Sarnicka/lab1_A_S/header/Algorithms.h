#pragma once
#include "task.h"
#include <list>
#include <iostream>
#include <algorithm>
#include <vector>

class Algorithms
{
private:
	list<task> task_list;
public:
	Algorithms();
	Algorithms(list<task> task_list);
	~Algorithms();

	void sort_r();
	void sort_rq();
	void schrage();
	void potts();
	void C100();
	void Carlier();

	list<task> get_task_list() {
		return this.task_list;
	}
	void set_task_list(list<task> tl) {
		this.task_list = tl;
	}
};

