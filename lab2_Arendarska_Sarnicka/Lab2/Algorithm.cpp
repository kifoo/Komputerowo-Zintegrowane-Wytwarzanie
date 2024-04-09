#include "header/Algorithm.h"

Algorithm::Algorithm() {
}

Algorithm::~Algorithm() {
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
	cout << path << "\t Suma kar: " << penalty_sum << std::endl;
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
