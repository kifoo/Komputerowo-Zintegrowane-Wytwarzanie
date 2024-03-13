#include "Algorithms.h"

using namespace std;

Algorithms::Algorithms() {
}

Algorithms::Algorithms(list<task> tl) {
	this.task_list = tl;
}

Algorithms::~Algorithms() {
}

// Does this work?
void Algorithms::sort_r(){
	this.task_list.sort([](const task& a, const task& b) {
		return a.r < b.r;
		});
}


void Algorithms::sort_rq(){

}

// Need to be fixed
void Algorithms::schrage(){
	list<task> G;
	list<task> N = this.task_list;
	task e;
	int t = 0;
	while (!G.empty() || !N.empty()) {
		while (!N.empty() && N.front().r <= t) {
			e = N.front();
			G.push_front(e);
			N.pop_front();
		}
		if (G.empty()) {
			t = N.front().r;
		}
		else {
			e = G.front();
			G.pop_front();
			t = t + e.p;
		}
	}
	this.task_list = G;
}

void Algorithms::potts(){

}

void Algorithms::C100(){

}

void Algorithms::Carlier(){

}
