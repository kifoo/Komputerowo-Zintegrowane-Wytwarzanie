#include "header/Result.h"

Result::Result()
{
}

Result::~Result()
{
}

void Result::run(const std::string& path, int choice)
{
	Algorithms alg;
	int iteration = 0;
	alg.read_data(path);
	switch (choice)
	{
		case 1:
			alg.sort_r();
			this->task_list = alg.task_list;
			this->c_max = alg.calculate_cmax();
		break;
		case 2:
			alg.sort_rq();
			this->task_list = alg.task_list;
		break;
		case 3:
			this->c_max = alg.schrage();
			this->task_list = alg.task_list;
		break;
		case 4:
			this->c_max = alg.schrage2();
			this->task_list = alg.task_list;
		break;
		case 5:
			alg.potts();
			this->task_list = alg.task_list;
		break;
		case 6:
			alg.C100();
			this->task_list = alg.task_list;
		break;
		case 7:
			int UB = INT_MAX;
			int min_U = INT_MAX;
			vector<task>  result_list;
			this->c_max = alg.Carlier(UB, min_U, result_list);
			this->task_list = result_list;
			this->c_max = min_U;  
			cout<< "Cmax: min_U: " << min_U << "\t U :" << UB << endl;
		break;
		
	}

	this->sum_c_max += this->c_max;

}

void Result::write_data(const std::string& path)
{
	std::ofstream file;
	file.open(path);
	if (file.is_open()) {
		file << path << "\t cmax: " << c_max << std::endl;
		for (auto& t : task_list) {
			file << t.id << " ";
		}
	}
	else {
		std::cout << "Error opening file: " << path << std::endl;
	}
	file.close();
}
