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
#include "header\Algorithm.h"
using namespace std;

void write_data(const string& path, const vector<Algorithm>& algorytmy, string title) {
	ofstream file;
	file.open(path);
	if (file.is_open()) {
		cout << title << endl;
		file << title << endl;
		for (const auto& alg : algorytmy) {
			cout << "\n Suma kar: " << alg.penalty_sum << endl;
			file << "\n Suma kar: " << alg.penalty_sum << endl;
			for (int id : alg.result_list) {
				cout << id + 1 << " "; 
				file << id + 1 << " ";
			}
			file << endl; 
		}
	}
	else {
		cout << "Error opening file: " << path << endl;
	}
	file.close();
}

int main()
{
	const string data_p[11] = { "data/p10.txt", "data/p11.txt", "data/p12.txt", "data/p13.txt", "data/p14.txt", "data/p15.txt", "data/p16.txt", "data/p17.txt", "data/p18.txt", "data/p19.txt", "data/p20.txt" };
	const string data_s[3] = { "data/solutions.txt", "data/solutions2.txt", "data/solutions3.txt" };
	vector<Algorithm> algorytmy;
	vector<Algorithm> algorytmy2;
	vector<Algorithm> algorytmy3;
	int sum1 = 0, sum2 = 0, sum3 = 0;
	for (int i = 0; i < 11; i++)
	{
		Algorithm alg1, alg2, alg3;
		alg1.read_data(data_p[i]);
		alg2 = alg1;
		alg3 = alg1;
		int minPenalty1 = alg1.dynamicIteration();
		int minPenalty2 = alg2.tabuSearch(100, INT_MAX);
		int minPenalty3 = alg3.dummyCode();
		//cout << "File: " << data_p[i] << endl;
		//cout << "Minimum Penalty using Dynamic Iteration: " << minPenalty << endl;

		alg1.penalty_sum = minPenalty1;
		alg2.penalty_sum = minPenalty2;
		alg3.penalty_sum = minPenalty3;
		algorytmy.push_back(alg1);
		algorytmy2.push_back(alg2);
		algorytmy3.push_back(alg3);
		sum1 += minPenalty1;
		sum2 += minPenalty2;
		sum3 += minPenalty3;
	}
	cout << "Suma kar 1: " << sum1 << endl;
	cout << "Suma kar 2: " << sum2 << endl;
	cout << "Suma kar 3: " << sum3 << endl;
	write_data(data_s[0], algorytmy, "\t*****\nDynamic Iterations\n\t*****");
	write_data(data_s[1], algorytmy2, "\n\t*****\nTabu Search\n\t*****");
	write_data(data_s[2], algorytmy3, "\n\t*****\nDummy Code\n\t*****");
}





