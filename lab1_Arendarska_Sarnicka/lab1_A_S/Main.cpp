#include <string>
#include <fstream>
#include <iostream>
#include <format>
#include <vector>
#include <algorithm>
#include <list>
#include <chrono>
#include "windows.h"

//include class 
#include "header\Algorithms.h"
#include "header\Result.h"
 
using namespace std;

int main() {

	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

	const string data_p[4] = { "data/p1.txt" ,"data/p2.txt" ,"data/p3.txt" ,"data/p4.txt" };
	const string data_s[4] = { "solutions/s1.txt" ,"solutions/s2.txt" ,"solutions/s3.txt" ,"solutions/s4.txt" };
	Result result;
	//case 1: sort_r
	// case 2: sort_rq
	// case 3: schrage
	// case 4: schrage2
	// case 5: My Own Algorithm
	// case 6: testy funkcji
	// case 7: Carlier

	for (int i = 0; i < 4; i++)
	{
		result.run(data_p[i], i);
		result.write_data(data_s[i]);
	}
	
	cout<< "\nSum of cmax: " << result.sum_c_max << endl;
	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	cout<< "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;

	return 0;

}