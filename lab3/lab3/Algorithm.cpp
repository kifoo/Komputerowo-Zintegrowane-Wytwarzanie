#include "header/Algorithm.h"


Algorithm::Algorithm() {
}

Algorithm::~Algorithm() {
}


void Algorithm::neh_algorithm() {
	vector<Job> copy = tasks;
    sort(copy.begin(), copy.end(), compare_jobs);

    vector<Job> schedule{ copy[0] };

    for (int i = 1; i < taskCount; i++) {
        Job new_job = copy[i];

        int best_position = 0;
        int best_completion_time = numeric_limits<int>::max();

        for (int j = 0; j <= i; j++) {
            vector<Job> temp_schedule(schedule);
            temp_schedule.insert(temp_schedule.begin() + j, new_job);

            const int completion_time = calculate_completion_time(temp_schedule);

            if (completion_time < best_completion_time) {
                best_completion_time = completion_time;
                best_position = j;
            }
        }
        schedule.insert(schedule.begin() + best_position, new_job);
    }
    fullTime = calculate_completion_time(schedule);
	makeOrder(schedule);
}

int Algorithm::calculate_completion_time(const vector<Job>& jobs) {
    vector<int> completion_times(machineCount, 0);

    for (const auto& job : jobs) {
        completion_times[0] += job.processing_times[0];
        for (size_t j = 1; j < machineCount; j++)
            completion_times[j] = max(completion_times[j], completion_times[j - 1]) + job.processing_times[j];
    }
    return completion_times.back();
}

void Algorithm::makeOrder(const vector<Job>& jobs) {
	order.clear();
	for (const auto& job : jobs) {
		order.push_back(job.id);
	}
}

void Algorithm::readData(const string& path) {
    string tmp;
	ifstream file;
	file.open(path);
    if (!file.is_open()) {
		cout << "Error: File not found" << endl;
		return;
	}
    file >> tmp;
	file >> taskCount >> machineCount;
	tasks.resize(taskCount);
    for (int i = 0; i < taskCount; i++) {
		tasks[i].processing_times.resize(machineCount);
		tasks[i].id = i;
        for (int j = 0; j < machineCount; j++) {
			file >> tasks[i].processing_times[j];
		}
        tasks[i].total_time = accumulate(tasks[i].processing_times.begin(), tasks[i].processing_times.end(), 0);
	}
    file >> tmp;
	file >> solution.value;
    for (int i = 0; i < taskCount; i++) {
        solution.order.resize(taskCount);
		file >> solution.order[i];
    }
	file.close();
    return;
}
