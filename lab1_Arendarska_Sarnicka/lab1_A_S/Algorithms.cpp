#include "header/Algorithms.h"


Algorithms::Algorithms() {
}

Algorithms::~Algorithms() {
}

// Search for best result by comparing R and Q times
void Algorithms::algorithm_rq(vector<task>& t_list, int size) {
	int tmp1 = 0;
	int tmp2 = 1;
	vector<task> table = t_list;

	for (int i = 0; i < size; i++)
	{
		if (i % 2 == 0)
		{
			sort(t_list.begin(), t_list.end(), comparator_max_r);
			table[tmp1] = t_list[t_list.size() - 1];
			t_list.pop_back();
			tmp1 += 1;
		}

		if (i % 2 != 0)
		{
			sort(t_list.begin(), t_list.end(), comparator_max_q);
			table[size - tmp2] = t_list[t_list.size() - 1];
			t_list.pop_back();
			tmp2 += 1;
		}
	}
	t_list = table;
}

// Calculate full time of all tasks
int Algorithms::calculate_cmax(vector<task> t_list) {
	int c_max = 0;
	int t = 0;
	for (const auto& tl : t_list) {
		if (t < tl.r)
			t = tl.r + tl.p;
		else
			t = t + tl.p;
		c_max = max(c_max, t + tl.q);
	}
	return c_max;
}


/* Create neighbor permutations */
vector<vector<task>> Algorithms::permutations(vector<task> t_list) {
	vector<vector<task>> all_permutations;
	for(size_t i = 0; i < t_list.size(); i++) {
		for(size_t j = i + 1; j < t_list.size(); j++){
			vector<task> tmp = t_list;
			swap(tmp[i], tmp[j]);
			all_permutations.push_back(tmp);
		}
	}
	return all_permutations;
}

/* Tabu Search */
vector<task> Algorithms::tabu_search(int max_iter, int& c_max) {
	int actual_cmax = schrage(task_list);
	vector<task> best_list = this->task_list;
	vector<task> actual_list = this->task_list;

	//Task with the longest finished time
	task long_task = *max_element(best_list.begin(), best_list.end(), [](const task& t1, const task& t2) {return t1.finished < t2.finished; });

	vector<vector<task>> tabu_list;

	for (int iter = 0; iter < max_iter; iter++) {
		//Create permutations of actual_list 
		vector<vector<task>> all_permutations = permutations(actual_list);
		vector<task> best_permutation;


		for (const vector<task>& neighbor : all_permutations) {
			// Check if all_permutation has new lists 
			if (find_if(tabu_list.begin(), tabu_list.end(),
				[&neighbor](const vector<task>& v)
				{return comparator_equal(v, neighbor); }) == tabu_list.end()) {
				int cmax = calculate_cmax(neighbor);
				// Check if new list is better cmax than actual_cmax  
				if (cmax < actual_cmax) {
					best_permutation = neighbor;
					actual_cmax = cmax;
				}
			}
		}

		// If not better permutation than break
		if (best_permutation.empty()) {
			break;
		}

		// Update actual_list and tabu_list
		actual_list = best_permutation;
		tabu_list.push_back(best_permutation);
		if (tabu_list.size() > 12) {
			// Removing the oldest list 
			tabu_list.erase(tabu_list.begin());
		}

		// Update best_list if best_permutation is better 
		if (calculate_cmax(best_permutation) < calculate_cmax(best_list)) {
			best_list = best_permutation;
			c_max = calculate_cmax(best_list);
			if(c_max == long_task.finished)
				return best_list;
		}
	}	
	return best_list;
}

// Find best sum less than long_task R time
int Algorithms::find_best_sum(vector<task>& tasks, task& long_task) {
	vector<task> best_permutation;
	int sum, sum2;
	int best_sum = 0, best_it = 0 ;
	for (size_t i = 0; i < tasks.size(); i++) {
		for (size_t j = i + 1; j < tasks.size(); j++) {
			vector<task> tmp = tasks;
			sum = 0;
			swap(tmp[i], tmp[j]);
			for (int k = 0; k < tmp.size(); k++) {
				task t = tmp[k];
				sum2 = sum;
				if (sum < t.r)
					sum = t.r + t.p;
				else
					sum += t.p;

				if (sum == long_task.r)
				{
					tasks = tmp;
					return k;
				}
				else if (sum > long_task.r and sum2 > best_sum) {
					best_sum = sum2;
					best_permutation = tmp;
					best_it = k;
					break;
				}
				else if (sum > long_task.r)
					break;
			}
		}
	}
	tasks = best_permutation;
	return best_it;
}

// Find best sum less than long_task Q time
int Algorithms::find_best_sum_back(vector<task>& tasks, task& long_task) {
	vector<task> best_permutation;
	int sum, sum2;
	int best_sum = 0, best_it = 0;
	for (size_t i = 0; i < tasks.size(); i++) {
		for (size_t j = i + 1; j < tasks.size(); j++) {
			vector<task> tmp = tasks;
			sum = 0;
			swap(tmp[i], tmp[j]);
			for (int k = 0; k < tmp.size(); k++) {
				task t = tmp[k];
				sum2 = sum;
				if (sum < t.r)
					sum = t.r + t.p;
				else
					sum += t.p;

				if (sum == long_task.q)
				{
					tasks = tmp;
					return k;
				}
				else if (sum > long_task.q and sum2 > best_sum) {
					best_sum = sum2;
					best_permutation = tmp;
					best_it = k;
					break;
				}
				else if (sum > long_task.q)
					break;
			}
		}
	}
	tasks = best_permutation;
	return best_it;
}

// Search for the best result if there is only one long task
void Algorithms::one_long_task(int& C_max, vector<task>& result_list){
	vector<task> copy = this->task_list;
	vector<task> best_list;
	vector<task> res_list;
	int it;
	int s = int(this->task_list.size());

	task long_task = *max_element(copy.begin(), copy.end(), [](const task& t1, const task& t2) {return t1.finished < t2.finished; });

	result_list = this->task_list;
	C_max = calculate_cmax(this->task_list);

	for (auto& t : copy) {
		if (t.done_p <= long_task.r) {
			best_list.push_back(t);
		}
		
	}

	//sort(best_list.begin(), best_list.end(), comparator_max_r);
	it = find_best_sum_back(best_list, long_task);
	
	for (auto& t : best_list) {
		if(t.id == best_list[it].id)
			res_list.push_back(long_task);
		res_list.push_back(t);
	}
	reverse(res_list.begin(), res_list.end());
	result_list = res_list;
	C_max = calculate_cmax(result_list);
}

// Schrage algorithm
int Algorithms::schrage(vector<task>& t_list) {
	vector<task> ready = t_list;
	vector<task> proces, done_list;
	sort(ready.begin(), ready.end(), comparator_max_r);
	task e;
	int t = 0;
	int c_max = 0;

	while (!ready.empty() || !proces.empty()) {
		while ((!ready.empty()) && (ready.back().r <= t)) {
			proces.push_back(ready.back());
			ready.pop_back();
		}
		sort(proces.begin(), proces.end(), comparator_min_q);
		if (proces.empty()) t = ready.back().r;
		else {
			e = proces.back();
			e.done_p = t + e.p;
			proces.pop_back();
			done_list.push_back(e);

			t = t + e.p;
			c_max = max(c_max, t + e.q);
		}
	}
	// update task_list with the new order
	t_list = done_list;
	return c_max;
}

// Schrage with parity 
int Algorithms::schrage2() {
	vector<task> ready;
	copy(task_list.begin(), task_list.end(), back_inserter(ready));
	vector<task> proces, done_list;
	sort(ready.begin(), ready.end(), comparator_max_r);
	task l{0, 0, 0, numeric_limits<int>::max() };
	int t = 0;
	int c_max = 0;

	while (!ready.empty() || !proces.empty()) {
		while ((!ready.empty()) && (ready.back().r <= t)) {
			proces.push_back(ready.back());
			ready.pop_back();
			if (proces.back().q > l.q) {
				l.p = t - proces.back().r;
				t = proces.back().r;
				if (l.p > 0) {
					proces.push_back(l);
				}
			}
		}
		sort(proces.begin(), proces.end(), comparator_min_q);
		if (proces.empty()) t = ready.back().r;
		else {
			l = proces.back();
			proces.pop_back();
			done_list.push_back(l);
			t = t + l.p;
			c_max = max(c_max, t + l.q);
		}
	}
	return c_max;
}

// Carlier algorithm - using recursion
int Algorithms::Carlier(int& UB, vector<task>& result_list){
	int U = 0;
	int LB = 0;

	int A = -1;
	int B = -1;
	int C = -1;

	// time of ...prims?
	int r_prim = INT_MAX;
	int q_prim = INT_MAX;
	int p_prim = 0;

	// C parameters
	int r_C = 0;
	int r_id_C = 0;
	int q_C = 0;
	int q_id_C = 0;

	U = schrage(task_list);

	if (U < UB) {
		UB = U;
		result_list = task_list;
	}

	B = mark_B(task_list);
	A = mark_A(B);
	C = mark_C(A, B);

	if (C == -1) {
		return UB;
	}

	for (int i = C + 1; i <= B; i++) {
		r_prim = min(r_prim, task_list[i].r);
		q_prim = min(q_prim, task_list[i].q);
		p_prim += task_list[i].p;
	}

	//R part
	// remember C parameters before modification
	r_C = task_list[C].r;
	r_id_C = task_list[C].id;

	// modify ready time for task C -> make it be after the last task from the "block"
	task_list[C].r = max(task_list[C].r, r_prim + p_prim);


	LB = schrage2();

	if (LB < UB) {
		Carlier(UB, result_list);
	}

	// restore task C r parameter
	auto it_r = find_if(task_list.begin(), task_list.end(), [r_id_C](const task& t) {return t.id == r_id_C; });
	it_r->r = r_prim;


	// Q part
	// remember C parameters before modification
	q_C = task_list[C].q;
	q_id_C = task_list[C].id;

	// modify post-processing time for task C -> make it be after the last task from the "block"
	task_list[C].q = max(task_list[C].q, q_prim + p_prim);

	LB = schrage2();

	if (LB < UB) {
		Carlier(UB, result_list);
	}

	// restore task C q parameter
	auto it_q = find_if(task_list.begin(), task_list.end(), [q_id_C](const task& t) {return t.id == q_id_C; });
	it_q->q = q_prim;


	return UB;

}

// Looks for the smallest element 
// Cmax = a.r + suma(a,b)p + b.q
int  Algorithms::mark_A(int b) {
	int c_max = schrage(task_list);
	int sum = 0;

	for (int i = 0; i < task_list.size(); i++) {
		sum = 0;
		for (int j = i; j <= b; j++) {
			sum += task_list[j].p;
		}
		if (c_max == task_list[i].r + sum + task_list[b].q) {
			return i;
		}
	}
	return -1; // requested a does not exist
}

// Looks for the bigest element (with the longest time of post-processing)
// Cmax = b.c + b.q
int  Algorithms::mark_B(vector<task>& t_list) {
	int c_max = schrage(t_list);

	for (int i = int(t_list.size()) - 1; i >= 0; i--) {
		if (c_max == t_list[i].done_p + t_list[i].q ) {
			return i;
		}
	}
	return -1; // requested b does not exist
}

// Looks for the bigest element between a and b with the time of post-processing shorter than b.q
// j.q < b.q 
int  Algorithms::mark_C(int a, int b) {
	for (int i = b-1; i > a; i--) {
		if (task_list[i].q < task_list[b].q) {
			return i;
		}
	}
	return -1; // requested c does not exist
}

// Read data from file
void Algorithms::read_data(const string& path) {
	ifstream data;
	data.open(path, ifstream::in);
	task e;

	if (data.is_open()) {
		data >> this->n;
		for (int i = 0; i < this->n; i++) {
			e.id = i + 1;
			data >> e.r;
			data >> e.p;
			data >> e.q;
			e.done_p = e.r + e.p;
			e.finished = e.r + e.p + e.q;
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
	ofstream file;
	file.open(path);
	if (file.is_open()) {
		cout << path << "\t cmax: " << c_max << std::endl;
		file << path << "\t cmax: " << c_max << std::endl;
		for (auto& t : task_list) {
			cout<< t.id << " ";
			file << t.id << " ";
		}
	}
	else {
		std::cout << "Error opening file: " << path << std::endl;
	}
	file.close();
}