#include <string>
#include <fstream>
#include <iostream>
#include <format>
#include <vector>
#include <algorithm>
#include <list>
#include "windows.h"

//include class 
#include "header\Algorithms.h"
#include "header\Result.h"
 
using namespace std;

int main() {
	const string data_p[4] = { "data/p1.txt" ,"data/p2.txt" ,"data/p3.txt" ,"data/p4.txt" };
	const string data_s[4] = { "solutions/s1.txt" ,"solutions/s2.txt" ,"solutions/s3.txt" ,"solutions/s4.txt" };
	Result result;
	
	//case 1: sort_r
	// case 2: sort_rq
	// case 3: schrage
	// case 4: schrage2
	// case 5: potts
	// case 6: C100
	// case 7: Carlier

	for (int i = 0; i < 4; i++)
	{
		result.run(data_p[i], 7);
		result.write_data(data_s[i]);
	}
	cout<< "\nSum of cmax: " << result.sum_c_max << endl;

	return 0;

}