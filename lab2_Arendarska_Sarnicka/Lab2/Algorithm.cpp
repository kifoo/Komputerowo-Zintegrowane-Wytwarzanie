#include "header/Algorithm.h"

Algorithm::Algorithm() {
}

Algorithm::~Algorithm() {
}

Element Algorithm::return_task(int id) const {
	return task_list[id];
}

void Algorithm::delete_task(int id) {
	task_list.erase(task_list.begin() + id);
}

void Algorithm::delete_end() {
	task_list.erase(task_list.begin(), task_list.end());
}

void Algorithm::add_task(Element e) {
	task_list.push_back(e);
}

bool Algorithm::is_empty()const {
	return task_list.empty();
}

int Algorithm::get_size()const {
	return task_list.size();
}

int Algorithm::dynamicIteration() {
	vector<int> podproblemy(1 << n, dmax);
	vector<vector<int>> tmp(1 << n); 
	podproblemy[0] = 0;

	for (int i = 1; i < (1 << n); i++) {
		int minPenalty = dmax; 

		for (int j = 0; j < n; j++) {
			if (i & (1 << j)) { 
				int subset = i & ~(1 << j); 
				int czas_trwania = 0;
				for (int k = 0; k < n; k++) {
					if (i & (1 << k)) {
						czas_trwania += task_list[k].p;
					}
				}

				int kara = task_list[j].w * max(0, czas_trwania - task_list[j].d);
				int newPenalty = podproblemy[subset] + kara;

				if (newPenalty < minPenalty) {
					minPenalty = newPenalty;
					tmp[i] = tmp[subset];
					tmp[i].push_back(j);
				}
			}
		}
		podproblemy[i] = minPenalty;
	}

	vector<int> result_list = tmp.back();
	return podproblemy.back();
}

void Algorithm::sort_tasks_by_deadline() {
	sort(task_list.begin(), task_list.end(), [](const Element& a, const Element& b) {
		return a.d < b.d;
		});
	cout << "Tasks sorted by deadlines." << endl;
}


void Algorithm::kolejnosc(vector<Element>& task_list, vector<int>& res_list) {
	vector<Element> result;
	for (auto t : res_list) {
		auto it = find_if(task_list.begin(), task_list.end(), [t](Element& e) {return e.id == t; });
		result.push_back(*it);
	}
	this->task_list = result;
}	

void Algorithm::time_done_calculate(vector<Element>& task_list) {
	int time = 0;
	for (auto& t : task_list) {
		time += t.p;
		t.p_done = time;
	}
}

int Algorithm::sum_of_penalty(vector<Element>& task_list) {
	int sum = 0;
	for (auto& t : task_list) {
		if (t.p_done - t.d > 0)
			t.penalty = (t.p_done - t.d) * t.w;
		else
			t.penalty = 0;
		sum += t.penalty;
	}
	penalty_sum = sum;
	return sum;
}

// Read data from file
void Algorithm::read_data(const string& path) {
	ifstream data;
	data.open(path, ifstream::in);
	Element e;
	int a;

	if (data.is_open()) {
		data >> this->n;
		for (int i = 0; i < this->n; i++) {
			e.id = i + 1;
			data >> e.p;
			data >> e.w;
			data >> e.d;
			this->task_list.push_back(e);
		}
		for (int j = 0; j < this->n; j++) {
			data >> a;
			result_list.push_back(a);
		}
	}
	else {
		cout << "The file cannot be open." << endl;
	}
	cout << "Read data ok\n";

	data.close();
	return;
}

void Algorithm::write_data(const string& path) {
	//cout << path << "\t Suma kar: " << penalty_sum << std::endl;
	for (auto& t : task_list) {
		cout << t.id << " ";
	}
	cout << "\n";
	for (auto& t : result_list) {
		cout << t << " ";
	}
	cout << "\n";

	//ofstream file;
	//file.open(path);
	//if (file.is_open()) {
	//	cout << path << "\t Suma kar: " << penalty_sum << std::endl;
	//	//file << path << "\t cmax: " << c_max << std::endl;
	//	for (auto& t : task_list) {
	//		cout << t.id << " ";
	//		//file << t.id << " ";
	//	}
	//}
	//else {
	//	std::cout << "Error opening file: " << path << std::endl;
	//}
	//file.close();
}
