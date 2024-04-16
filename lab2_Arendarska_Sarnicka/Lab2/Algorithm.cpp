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


// Read data from file
void Algorithm::read_data(const string& path) {
	ifstream data;
	data.open(path, ifstream::in);
	Element e;

	if (data.is_open()) {
		data >> this->n;
		for (int i = 0; i < this->n; i++) {
			e.id = i + 1;
			data >> e.p;
			data >> e.w;
			data >> e.d;
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


