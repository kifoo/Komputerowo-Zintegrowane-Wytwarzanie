#pragma once

struct task {
	int id;		// number of task
	int r;		// ready time
	int p;		// processing time
	int q;		// post-procesing time
	int done_p;		// ready time + processing time 
	int finished;	// ready time + processing time + post-procesing time
};