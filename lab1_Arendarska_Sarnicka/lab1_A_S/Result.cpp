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
	int C_max = INT_MAX;
	alg.read_data(path);

	if (choice != 1) {
		this->task_list = alg.tabu_search(100, C_max);
		this->c_max = C_max;
	}
	else {
		// For second data st will be new function, 
		// if I have time I make it to work based on provided data insted hardcoded
		this->task_list = alg.tabu_search(100, C_max);
		this->c_max = C_max;
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
