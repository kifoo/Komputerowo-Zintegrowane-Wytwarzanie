#include "header/Regret.h"

Regret::Regret()
{
}

Regret::~Regret()
{
}

void Regret::run(int& c_max, vector<task>& result_list) {
	//this->Kill_Me_Now(c_max, result_list);
	this->root = new Tree_Node();
	this->test_tree();
	//this->root->print_tree();
}

void Regret::test_tree() {
	int C_max = INT_MAX;
	sort(this->task_list.begin(), this->task_list.end(), comparator_min_r);
	this->root->job = this->task_list[0];
	this->root->p_time = this->task_list[0].done_p;
	this->root->p_time = this->task_list[0].finished;
	vector<task> clone;
	copy(this->task_list.begin() + 1, this->task_list.end(), back_inserter(clone));
	this->root = Tree_Schrage(clone, this->root, C_max);
}

Tree_Node* Regret::Tree_Schrage(vector<task> t_list, Tree_Node* tmp, int& Best_Time) {
	vector<task> ready = t_list;
	vector<task> loop_ready = t_list;
	vector<task> process;
	task e;
	int time = tmp->p_time;


	if ((!ready.empty()) and (ready.back().r > time)) {
		time = ready.back().r;
	}
	while ((!ready.empty()) and (ready.back().r <= time)) {
		e = ready.back();

		process.push_back(e);
		loop_ready.pop_back();
		ready.pop_back();
		Tree_Node* S_tree = new Tree_Node();
		S_tree->job = e;
		S_tree->p_time = max(time, e.r) + e.p;
		S_tree->q_time = S_tree->p_time + e.q;
		S_tree->parent = tmp;
		auto subtree = Tree_Schrage(loop_ready, S_tree, Best_Time);
		tmp->children.push_back(subtree);
		if (ready.empty() and time < Best_Time) {
			Best_Time = time;
			const string path = "solutions/solution.txt";
			ofstream data;
			data.open(path, ios::out);
			if (data.is_open()) {
				data << " Best time: " << S_tree->q_time << "\n";
			}
			data.close();
		}
		loop_ready.push_back(e);
	}
	

	//// Recursively create subtrees for the subtasks
	//for (auto& task : process) {
	//	auto subtree = Tree_Schrage(ready, tmp);

	//	// Add the subtree as a child of the root task
	//	tmp->children.push_back(subtree);
	//}

	return tmp;
}







void Regret::find_best_sum(vector<task>& tasks, task& long_task) {
	vector<task> process;
	vector<task> best;
	task e;
	task l{ 0, 0, 0, numeric_limits<int>::max() };
	int l_p = 0;
	int t = 0;
	int t2 = 0;
	int c_max = 0;

	while (!tasks.empty() or !process.empty()) {
		while ((!tasks.empty()) and (tasks.back().r <= t)) {
			process.push_back(tasks.back());
			tasks.pop_back();
			if ((process.back().q > l.q and process.back().id != long_task.id) or (process.back().done_p < long_task.r and t + process.back().p > long_task.r)) {
				e = l;
				l.p = t2 - process.back().r;
				t2 = process.back().r;
				if (l.p > 0) {
					process.push_back(e);
					auto it = find_if(best.begin(), best.end(), [e](const task& t) {return t.id == e.id; });
					best.erase(it);
					t -= l.p;

				}
			}
		}
		sort(process.begin(), process.end(), comparator_min_q);
		if (process.empty()) {
			t = tasks.back().r;
			t2 = t;
		}
		else {
			l = process.back();
			process.pop_back();

			best.push_back(l);

			t += l.p;
			t2 = t;
			c_max = max(c_max, t + l.q);

		}
	}
	tasks = best;

}

void Regret::Task_List_Before_Long_Task(vector<task>& tasks, task& long_task) {
	vector<task> process;
	vector<task> best;
	task e;
	task l{ 0, 0, 0, numeric_limits<int>::max() };
	int l_p = 0;
	int t = 0;
	int t2 = 0;
	int c_max = 0;

	while (!tasks.empty() || !process.empty()) {
		while ((!tasks.empty()) && (tasks.back().r <= t)) {
			process.push_back(tasks.back());
			tasks.pop_back();
			if (process.back().q > l.q || t + process.back().p > long_task.r) {
				e = l;
				l.p = t2 - process.back().r;
				t2 = process.back().r;
				if (l.p > 0) {
					process.push_back(e);
					auto it = find_if(best.begin(), best.end(), [e](const task& t) {return t.id == e.id; });
					best.erase(it);
					t -= l.p;

				}
			}
		}
		sort(process.begin(), process.end(), comparator_min_q);
		if (process.empty()) {
			t = tasks.back().r;
			t2 = t;
		}
		else {
			l = process.back();
			process.pop_back();

			best.push_back(l);

			t += l.p;
			t2 = t;
			c_max = max(c_max, t + l.q);

		}
	}

	vector<task> tmp;
	for (task& tt : best) {
		auto it = find_if(best.begin(), best.end(), [tt](const task& t) {return t.id == tt.id; });
		copy(best.begin(), it + 1, back_inserter(tmp));
		if (calculate_cmax(tmp) - tt.q > long_task.r) {
			tmp.pop_back();
			tasks = tmp;
			return;
		}
		tmp.clear();
	}
}

void Regret::Kill_Me_Now(int& C_max, vector<task>& result_list) {
	vector<task> copy = this->task_list;
	vector<task> before_long_task;
	vector<task> bft;
	vector<task> ready_list;
	vector<task> processed_list;

	sort(copy.begin(), copy.end(), comparator_max_r);
	find_best_sum(copy, copy.back());
	//best_task_list(copy, copy.back());
	result_list = copy;
	C_max = calculate_cmax(result_list);
	for (auto& t : copy) {
		cout << t.id << " " << t.r << " " << t.p << " " << t.q << "\n";
	}
	/*int s = int(this->task_list.size());

	task long_task = *max_element(copy.begin(), copy.end(), [](const task& t1, const task& t2) {return t1.finished < t2.finished; });

	result_list = this->task_list;
	C_max = calculate_cmax(this->task_list);

	for (auto& t : copy) {
		if (t.done_p <= long_task.r) {
			before_long_task.push_back(t);
		}
	}

	sort(before_long_task.begin(), before_long_task.end(), comparator_max_r);
	best_task_list(before_long_task, long_task);

	for (auto& t : before_long_task) {
		cout<< t.id << " " << t.r << " " << t.p << " " << t.q << "\n";
	}
	int B = mark_B(before_long_task);
	cout << " B : \t " << B << endl;
	result_list = before_long_task;
	C_max = calculate_cmax(result_list);
	cout<< "Longest task: " << long_task.id << "\tfinished: "<< long_task.finished << endl;*/
}





int Regret::calculate_cmax(vector<task> t_list) {
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

void Regret::read_data(const string& path) {
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

void Regret::write_data(const string& path) {
	ofstream data;
	data.open(path, ios::out);
	if (data.is_open()) {
		cout << path << '\t';
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