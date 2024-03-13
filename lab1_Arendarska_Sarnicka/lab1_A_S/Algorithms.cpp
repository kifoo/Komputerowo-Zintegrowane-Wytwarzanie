#include "header/Algorithms.h"

Algorithms::Algorithms() {
}

Algorithms::~Algorithms() {
}

// Does this work?
void Algorithms::sort_r() {
	this->task_list.sort([](const task& a, const task& b) {
		return a.r < b.r;
		});
}


void Algorithms::sort_rq(){

}

// Need to be fixed
void Algorithms::schrage(){
	list<task> G;
	list<task> N = this->task_list;
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
	this->task_list = G;
}

void Algorithms::potts(){

}

void Algorithms::C100(){

}

void Algorithms::Carlier(){

}

void Algorithms::read_data(const string& path) {
	ifstream data;
	data.open(path, ifstream::in);
	int n = 0;

	list<task> task_list;
	task e;

	if (data.is_open()) {
		data >> n;
		for (int i = 0; i < n; i++) {
			data >> e.r;
			data >> e.p;
			data >> e.q;
			this->task_list.push_back(e);
		}
	}
	else {
		cout << "The file cannot be open." << endl;
	}
	cout << "Read data ok\n";

	data.close();
	this->task_list = task_list;
	return;
}

void Algorithms::write_data(const string& path) {
	ofstream data;
	data.open(path, std::ios::out);
	if (data.is_open()) {
		for (const auto& t : this->task_list) {
			data << t.r << ' ' << t.p << ' ' << t.q << '\n';
		}
		cout << "Write data ok\n";
	}
	else {
		cout << "Error opening file: " << path << endl;
	}
	data.close();
	return;
}

void Algorithms::clear_list() {
	this->task_list.clear();
	return;
}