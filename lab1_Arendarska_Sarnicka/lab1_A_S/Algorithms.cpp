#include "header/Algorithms.h"

Algorithms::Algorithms() {
}

Algorithms::~Algorithms() {
}

void Algorithms::sort_r() {
	sort(task_list.begin(), task_list.end(), comparator_r);
}

void Algorithms::sort_rq() {
	sort(task_list.begin(), task_list.end(), comparator_rq);
}

void Algorithms::schrage() {
	vector<task> ready;
	copy(task_list.begin(), task_list.end(), back_inserter(ready));
	vector<task> proces, done_list;
	sort(ready.begin(), ready.end(), comparator_r);
	task e;
	int t = 0;
	int c_max = 0;

	while (!ready.empty() || !proces.empty()) {
		while ((!ready.empty()) && (ready.front().r <= t)) {
			e = ready.front();
			ready.erase(ready.begin());
			proces.push_back(e);
			sort(proces.begin(), proces.end(), comparator_q);
		}
		if (proces.empty()) t = ready.front().r;
		else {
			e = proces.front();
			proces.erase(proces.begin());

			done_list.push_back(e);

			t = t + e.p;
			c_max = max(c_max, t + e.q);
		}
	}
	// update task_list with the new order
	cout<< c_max << endl;
	this->task_list = done_list;

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
	task e;

	if (data.is_open()) {
		data >> n;
		for (int i = 0; i < n; i++) {
			e.id = i + 1;
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
	return;
}

void Algorithms::write_data(const string& path) {
	ofstream data;
	data.open(path, std::ios::out);
	if (data.is_open()) {
		cout <<  path << '\t';
		for (const auto& t : this->task_list) {
			//data << t.r << ' ' << t.p << ' ' << t.q << '\n';
			data << t.id << ' ';
			cout << t.id << ' ';
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