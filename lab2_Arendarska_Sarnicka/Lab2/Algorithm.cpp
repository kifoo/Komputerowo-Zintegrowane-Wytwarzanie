#include "header/Algorithm.h"

Algorithm::Algorithm() {
}

Algorithm::~Algorithm() {
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

	result_list = tmp.back();
	return podproblemy.back();
}

int Algorithm::calculatePenalty(vector<Element>& taskList) {
	int time = 0;
	int penalty = 0;

	for (auto& t : taskList) {
		time += t.p;
		t.p_done = time;
		if (t.p_done - t.d > 0)
			penalty += (t.p_done - t.d) * t.w;
	}
	return penalty;
}

int Algorithm::dummyCode() {
	
	sort(task_list.begin(), task_list.end(), [](const Element& a, const Element& b) {
		return ((a.w * (a.d - a.p)) < (b.w * (b.d - b.p)) or (a.w * ((a.d - a.p)) == (b.w * (b.d - b.p)) and (a.w > b.w)));
		// return a.d < b.d;
		});
	result_list.clear();
	for (const auto& task : task_list) {
		result_list.push_back(task.id);
	}
	return calculatePenalty(task_list);;
}

// =====================================
/* Create neighbor permutations */
vector<vector<Element>> Algorithm::permutations(vector<Element> t_list) {
	vector<vector<Element>> all_permutations;
	for (size_t i = 0; i < t_list.size(); i++) {
		for (size_t j = i + 1; j < t_list.size(); j++) {
			vector<Element> tmp = t_list;
			swap(tmp[i], tmp[j]);
			all_permutations.push_back(tmp);
		}
	}
	return all_permutations;
}

/* Tabu Search */
int Algorithm::tabuSearch(int max_iter, int penalty) {
	int actual_penalty = calculatePenalty(task_list);
	vector<Element> best_list = this->task_list;
	vector<Element> actual_list = this->task_list;

	vector<vector<Element>> tabuList;

	for (int iter = 0; iter < max_iter; iter++) {
		//Create permutations of actual_list 
		vector<vector<Element>> all_permutations = permutations(actual_list);
		vector<Element> best_permutation;

		for (vector<Element>& neighbor : all_permutations) {
			// Check if all_permutation has new lists 
			if (find_if(tabuList.begin(), tabuList.end(),
				[&neighbor](const vector<Element>& v)
				{return comparator_equal(v, neighbor); }) == tabuList.end()) {
				int penalty = calculatePenalty(neighbor);
				// Check if new list has better penalty than actual_penalty  
				if (penalty < actual_penalty) {
					best_permutation = neighbor;
					actual_penalty = penalty;
				}
			}
		}

		// If not better permutation than break
		if (best_permutation.empty()) {
			break;
		}

		// Update actual_list and tabuList
		actual_list = best_permutation;
		tabuList.push_back(best_permutation);
		if (tabuList.size() > 12) {
			// Removing the oldest list 
			tabuList.erase(tabuList.begin());
		}

		// Update best_list if best_permutation is better 
		if (calculatePenalty(best_permutation) < calculatePenalty(best_list)) {
			best_list = best_permutation;
			penalty = calculatePenalty(best_list);
			// Update result_list
			this->result_list.clear();
			for (const auto& task : best_list) {
				this->result_list.push_back(task.id);
			}
		}
	}
	return penalty;
}
// =====================================

// Read data from file
void Algorithm::read_data(const string& path) {
	ifstream data;
	data.open(path, ifstream::in);
	Element e;

	if (data.is_open()) {
		data >> this->n;
		for (int i = 0; i < this->n; i++) {
			e.id = i;
			data >> e.p;
			data >> e.w;
			data >> e.d;
			this->task_list.push_back(e);
		}
	}
	else {
		cout << "The file cannot be open." << endl;
	}
	//cout << "Read data ok\n";

	data.close();
	return;
}


