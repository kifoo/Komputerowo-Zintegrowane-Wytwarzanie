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

int Algorithms::schrage() {
	vector<task> ready;
	copy(task_list.begin(), task_list.end(), back_inserter(ready));
	vector<task> proces, done_list;
	sort(ready.begin(), ready.end(), comparator_r);
	task e;
	int t = 0;
	int c_max = 0;

	while (!ready.empty() || !proces.empty()) {
		while ((!ready.empty()) && (ready.front().r <= t)) {
			proces.push_back(ready.front());
			ready.erase(ready.begin());
		}
		sort(proces.begin(), proces.end(), comparator_q);
		if (proces.empty()) t = ready.front().r;
		else {
			e = proces.front();
			e.c = t + e.p;
			proces.erase(proces.begin());
			done_list.push_back(e);

			t = t + e.p;
			c_max = max(c_max, t + e.q);
		}
	}
	// update task_list with the new order
	this->task_list = done_list;
	return c_max;
}

// Schrage with parity 
int Algorithms::schrage2() {
	vector<task> ready;
	copy(task_list.begin(), task_list.end(), back_inserter(ready));
	vector<task> proces, done_list;
	sort(ready.begin(), ready.end(), comparator_r);
	task l{0, 0, 0, numeric_limits<int>::max() };
	int t = 0;
	int c_max = 0;

	while (!ready.empty() || !proces.empty()) {
		while ((!ready.empty()) && (ready.front().r <= t)) {
			proces.push_back(ready.front());
			ready.erase(ready.begin());
			if (proces.back().q > l.q) {
				l.p = t - proces.back().r;
				t = proces.back().r;
				if (l.p > 0) {
					proces.push_back(l);
					sort(proces.begin(), proces.end(), comparator_q);
				}
			}
		}
		sort(proces.begin(), proces.end(), comparator_q);
		if (proces.empty()) t = ready.front().r;
		else {
			l = proces.front();
			proces.erase(proces.begin());

			t = t + l.p;
			c_max = max(c_max, t + l.q);
		}
	}
	// update task_list with the new order
	//cout<< c_max << endl;
	return c_max;
}

void Algorithms::potts(){

}

void Algorithms::C100(){

}

// Carlier algorithm - using recursion
int Algorithms::Carlier(int& UB, int& min_U, vector<task>& result_list){
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

	U = schrage();

	if (U < UB) {
		UB = U;
		min_U = U;
		result_list = task_list;
	}

	B = mark_B();
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
		Carlier(UB, min_U, result_list);
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
		Carlier(UB, min_U, result_list);
	}

	// restore task C q parameter
	auto it_q = find_if(task_list.begin(), task_list.end(), [q_id_C](const task& t) {return t.id == q_id_C; });
	it_q->q = q_prim;


	return UB;

}

int Algorithms::calculate_cmax() {
	int c_max = 0;
	int t = 0;
	for (const auto& tl : this->task_list) {
		if(t < tl.r)
			t = tl.r + tl.p;
		else
			t = t + tl.p;
		c_max = max(c_max, t + tl.q);
	}
	return c_max;
}


// looks for the smallest element 
// Cmax = a.r + suma(a,b)p + b.q
int  Algorithms::mark_A(int b) {
	int c_max = schrage();
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

// looks for the bigest element (with the longest time of post-processing)
// Cmax = b.c + b.q
int  Algorithms::mark_B() {
	int c_max = schrage();

	for (int i = int(task_list.size()) - 1; i >= 0; i--) {
		if (c_max == task_list[i].c + task_list[i].q ) {
			return i;
		}
	}
	return -1; // requested b does not exist
}


// looks for the bigest element between a and b with the time of post-processing shorter than b.q
// j.q < b.q 
int  Algorithms::mark_C(int a, int b) {
	for (int i = b-1; i > a; i--) {
		if (task_list[i].q < task_list[b].q) {
			return i;
		}
	}
	return -1; // requested c does not exist
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
			e.c = e.r + e.p;
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
	data.open(path, ios::out);
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