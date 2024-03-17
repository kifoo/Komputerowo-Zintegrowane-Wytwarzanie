#pragma once

struct task {
	int id;		// number of task
	int r;		// ready time
	int p;		// processing time
	int q;		// post-procesing time
	int c;		// completion time (without post procesing) -  for Carlier Algorithm
};