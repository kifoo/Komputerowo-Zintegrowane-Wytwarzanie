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
 
using namespace std;

int main() {
	const string data_p[4] = { "data/p1.txt" ,"data/p2.txt" ,"data/p3.txt" ,"data/p4.txt" };
	const string data_s[4] = { "solutions/s1.txt" ,"solutions/s2.txt" ,"solutions/s3.txt" ,"solutions/s4.txt" };
	Algorithms alg;
	
	// there will be loop for every sort algorithm

	for (int i = 0; i < 4; i++)
	{
		alg.read_data(data_p[i]);
		alg.sort_r();
		//coœ mi tutaj nie dzia³a :((
		alg.write_data(data_s[i]);
		//alg.clear_list();
	}

	return 0;

}