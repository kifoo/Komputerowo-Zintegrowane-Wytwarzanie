//#include "header/Algorithm.h"
//
//
//Algorithm::Algorithm() {
//}
//
//Algorithm::~Algorithm() {
//}
//
//
//void Algorithm::neh_algorithm(const int num_jobs, const vector<vector<int>>& processing_times) {
//    vector<job> jobs(num_jobs);
//
//    for (int i = 0; i < num_jobs; i++) {
//        jobs[i].processing_times = processing_times[i];
//        jobs[i].total_time = accumulate(jobs[i].processing_times.begin(), jobs[i].processing_times.end(), 0);
//    }
//    ranges::sort(jobs, compare_jobs);
//
//    vector<job> schedule{ jobs[0] };
//
//    for (int i = 1; i < num_jobs; i++) {
//        job new_job = jobs[i];
//
//        int best_position = 0;
//        int best_completion_time = numeric_limits<int>::max();
//
//        for (int j = 0; j <= i; j++) {
//            vector<job> temp_schedule(schedule);
//            temp_schedule.insert(temp_schedule.begin() + j, new_job);
//
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
//    calculate_completion_time(schedule);
//}
//
//int Algorithm::calculate_completion_time(const vector<job>& jobs) {
//    const auto num_machines = jobs[0].processing_times.size();
//    vector<int> completion_times(num_machines, 0);
//
//    for (const auto& job : jobs) {
//        completion_times[0] += job.processing_times[0];
//        for (size_t j = 1; j < num_machines; j++)
//            completion_times[j] = max(completion_times[j], completion_times[j - 1]) + job.processing_times[j];
//    }
//    return completion_times.back();
//}
//
//bool Algorithm::compare_jobs(const job& job1, const job& job2) {
//    return job1.total_time > job2.total_time;
//}
