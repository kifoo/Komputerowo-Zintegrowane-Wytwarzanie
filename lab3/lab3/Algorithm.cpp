#include "header/Algorithm.h"


Algorithm::Algorithm() {
}

Algorithm::~Algorithm() {
}


void Algorithm::neh_algorithm() {
	list<Job> jobs = tasks;

    jobs.sort(compare_jobs);

    list<Job> schedule;
    schedule.push_back(jobs.front());

    for (auto it = next(jobs.begin()); it != jobs.end(); ++it) {
        Job new_job = *it;

        int best_position = 0;
        int best_completion_time = numeric_limits<int>::max();

        for (int j = 0; j <= distance(schedule.begin(), schedule.end()); j++) {
            list<Job> temp_schedule(schedule);
            auto jt = temp_schedule.begin();
            advance(jt, j);
            temp_schedule.insert(jt, new_job);

            if (const int completion_time = calculate_completion_time(temp_schedule); completion_time < best_completion_time) {
                best_completion_time = completion_time;
                best_position = j;
            }
        }
        auto jt = schedule.begin();
        advance(jt, best_position);
        schedule.insert(jt, new_job);
    }
    fullTime = calculate_completion_time(schedule);
	makeOrder(schedule);
}

void Algorithm::quick_neh_algorithm() {
    list<Job> jobs = tasks;

    jobs.sort(compare_jobs);

    list<Job> schedule;

    for (const auto& new_job : jobs) {
        list<Job> best_schedule = schedule;
        int min_completion_time = numeric_limits<int>::max();

        auto it = schedule.begin();
        for (size_t i = 0; i <= schedule.size(); ++i) {
            it = schedule.insert(it, new_job);

            if (int completion_time = calculate_completion_time(schedule); completion_time < min_completion_time) {
                min_completion_time = completion_time;
                best_schedule = schedule;
            }
            it = schedule.erase(it);
            if (it != schedule.end())
                ++it;
        }
        schedule = best_schedule;
    }
    fullTime = calculate_completion_time(schedule);
	makeOrder(schedule);
}

int Algorithm::calculate_completion_time(const list<Job>& schedule) {
    const auto num_machines = schedule.front().processing_times.size();
    vector<int> completion_times(num_machines, 0);

    for (const auto& job : schedule) {
        completion_times[0] += job.processing_times[0];
        for (size_t j = 1; j < num_machines; j++)
            completion_times[j] = max(completion_times[j], completion_times[j - 1]) + job.processing_times[j];
    }
    return completion_times.back();
}

void Algorithm::makeOrder(const list<Job>& jobs) {
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
    tasks.clear();
    for (int i = 0; i < taskCount; i++) {
        Job newTask;
        newTask.id = i;
        newTask.processing_times.clear(); // Clear the vector before adding new elements
        for (int j = 0; j < machineCount; j++) {
            int processingTime;
            file >> processingTime;
            newTask.processing_times.push_back(processingTime);
        }
        newTask.total_time = accumulate(newTask.processing_times.begin(), newTask.processing_times.end(), 0);
        tasks.push_back(newTask); // Add the new Task to the list
    }
    file >> tmp;
    file >> solution.value;
    solution.order.clear(); // Clear the vector before adding new elements
    for (int i = 0; i < taskCount; i++) {
        int order;
        file >> order;
        solution.order.push_back(order);
    }
    file.close();
    return;
}

// Na vectorze
//
//void Algorithm::neh_algorithm() {
//    vector<Job> copy = tasks;
//    sort(copy.begin(), copy.end(), compare_jobs);
//
//    vector<Job> schedule{ copy[0] };
//
//    for (int i = 1; i < taskCount; i++) {
//        Job new_job = copy[i];
//
//        int best_position = 0;
//        int best_completion_time = numeric_limits<int>::max();
//
//        for (int j = 0; j <= i; j++) {
//            vector<Job> temp_schedule(schedule);
//            temp_schedule.insert(temp_schedule.begin() + j, new_job);
//
//            const int completion_time = calculate_completion_time(temp_schedule);
//
//            if (completion_time < best_completion_time) {
//                best_completion_time = completion_time;
//                best_position = j;
//            }
//        }
//        schedule.insert(schedule.begin() + best_position, new_job);
//    }
//    fullTime = calculate_completion_time(schedule);
//    //makeOrder(schedule);
//}
//
//void Algorithm::quick_neh_algorithm() {
//    vector<Job> jobs = tasks;
//
//    /*for (int i = 0; i < taskCount; i++) {
//        jobs[i].id = i + 1;
//        jobs[i].processing_times = processing_times[i];
//        jobs[i].total_time = accumulate(jobs[i].processing_times.begin(), jobs[i].processing_times.end(), 0);
//    }
//    ranges::sort(jobs, compare_jobs);*/
//    sort(jobs.begin(), jobs.end(), compare_jobs);
//
//    vector<Job> schedule;
//
//    for (const auto& new_job : jobs) {
//        vector<Job> best_schedule = schedule;
//        int min_completion_time = numeric_limits<int>::max();
//
//        for (size_t i = 0; i <= schedule.size(); ++i) {
//            schedule.insert(schedule.begin() + i, new_job);
//
//            int completion_time = calculate_completion_time(schedule);
//            if (completion_time < min_completion_time) {
//                min_completion_time = completion_time;
//                best_schedule = schedule;
//            }
//            schedule.erase(schedule.begin() + i);
//        }
//        schedule = best_schedule;
//    }
//    fullTime = calculate_completion_time(schedule);
//    //makeOrder(schedule);
//}
//
//int Algorithm::calculate_completion_time(const vector<Job>& jobs) {
//    vector<int> completion_times(machineCount, 0);
//
//    for (const auto& job : jobs) {
//        completion_times[0] += job.processing_times[0];
//        for (size_t j = 1; j < machineCount; j++)
//            completion_times[j] = max(completion_times[j], completion_times[j - 1]) + job.processing_times[j];
//    }
//    return completion_times.back();
//}
//
//void Algorithm::makeOrder(const vector<Job>& jobs) {
//    order.clear();
//    for (const auto& job : jobs) {
//        order.push_back(job.id);
//    }
//}
//
//void Algorithm::readData(const string& path) {
//    string tmp;
//    ifstream file;
//    file.open(path);
//    if (!file.is_open()) {
//        cout << "Error: File not found" << endl;
//        return;
//    }
//    file >> tmp;
//    file >> taskCount >> machineCount;
//    tasks.resize(taskCount);
//    for (int i = 0; i < taskCount; i++) {
//        tasks[i].processing_times.resize(machineCount);
//        tasks[i].id = i;
//        for (int j = 0; j < machineCount; j++) {
//            file >> tasks[i].processing_times[j];
//        }
//        tasks[i].total_time = accumulate(tasks[i].processing_times.begin(), tasks[i].processing_times.end(), 0);
//    }
//    file >> tmp;
//    file >> solution.value;
//    for (int i = 0; i < taskCount; i++) {
//        solution.order.resize(taskCount);
//        file >> solution.order[i];
//    }
//    file.close();
//    return;
//}


