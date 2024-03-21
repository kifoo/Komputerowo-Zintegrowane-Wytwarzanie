#include "header/Result.h"

Result::Result()
{
	c_max = INT_MAX;
}

Result::~Result()
{
}


void Result::run(const std::string& path, int choice)
{
	Algorithms alg;
	Regret regret;
	int C_max = INT_MAX;
	vector<task>  res_list;
	//alg.read_data(path);
	switch (choice)
	{
		case 1:
			alg.sort_r();
			this->task_list = alg.task_list;
			this->c_max = alg.calculate_cmax(this->task_list);
		break;
		case 2:
			alg.sort_rq();
			this->task_list = alg.task_list;
			this->c_max = alg.calculate_cmax(this->task_list);
		break;
		case 3:
			this->c_max = alg.schrage(res_list);
			this->task_list = res_list;
		break;
		case 4:
			this->c_max = alg.schrage2();
			this->task_list = alg.task_list;
		break;
		case 5:
			alg.My_Own_Atgorithm(C_max, res_list);
			this->task_list = res_list;
			this->c_max = C_max;
		break;
		case 6:
			regret.read_data(path);
			regret.run(C_max, res_list);
			this->task_list = res_list;
			this->c_max = C_max;
		break;
		case 7:
			int UB = INT_MAX;
			int min_U = INT_MAX;
			vector<task>  result_list;
			this->c_max = alg.Carlier(UB, min_U, result_list);
			this->task_list = result_list;
			this->c_max = min_U;  
			cout<< "Cmax: min_U: " << min_U << endl;
		break;
		
	}

	this->sum_c_max += this->c_max;

}

void Result::write_data(const std::string& path)
{
	std::ofstream file;
	file.open(path);
	if (file.is_open()) {
		cout << path << "\t cmax: " << c_max << std::endl;
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
