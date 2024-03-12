#include <string>
#include <fstream>
#include <iostream>
#include <format>
#include <vector>
#include <algorithm>
#include <list>
//#include "psapi.h"
#include "windows.h"

//include class 
#include "header\task.h"
#include "header\SortR.h"
#include "header\SortRQ.h"
#include "header\Schrage.h"
 
using namespace std;

struct task1 {
	int r{};
	int p{};
	int q{};
};

//function reading data from file and returning list of tasks
list<task> read_data(const string& path) {
	ifstream data;
	data.open(path, ifstream::in);
	int n = 0;

	list<task> task_list;
	task e;

	if (data.is_open()) {
		data >> n;
		for (int i = 0; i < n; i++) {
			data >> e.r;
			data >> e.p;
			data >> e.q;
			task_list.push_back(e);
		}
	}
	else {
		cout << "The file cannot be open." << endl;
	}

	data.close();
	return task_list;
}

// function writing data in file
void write_data(const string& path, list<task> task_list) {
	ofstream data;
	data.open(path, std::ios::out);
	if (data.is_open()) {
		for (const auto& t : task_list) {
			data << t.r << ' ' << t.p << ' ' << t.q << '\n';
		}
	}
	else {
		// cerr << "Error opening file: " << path << endl;
		cout << "Error opening file: " << path << endl;
	}
	data.close();
	return;
}

int main() {
	const string data_p[4] = { "data/p1.txt" ,"data/p2.txt" ,"data/p3.txt" ,"data/p4.txt" };
	const string data_s[4] = { "solutions/s1.txt" ,"solutions/s2.txt" ,"solutions/s3.txt" ,"solutions/s4.txt" };
	list<task> task_list;

	for (int i = 0; i < 4; i++)
	{
		task_list = read_data(data_p[i]);
		write_data(data_s[i], task_list);
		task_list.clear();
	}

	return 0;

}