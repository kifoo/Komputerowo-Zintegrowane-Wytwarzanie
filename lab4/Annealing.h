#ifndef ANNEALING_H
#define ANNEALING_H

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <random>
#include <chrono>
#include <numeric> // For std::iota
#include <fstream> // For file handling



class Annealing {
    int nodeN = 0;
    std::vector<std::pair<int, int>> node;
    std::vector<int> saPath;
    std::vector<double> saDataDist;
    std::vector<double> saDataPraw;
    std::vector<double> saDataTemp;
    double saBestDist = INT_MAX;
    std::vector<int> saBestPath;
    double saTempStart = 0;
    double saTempAlpha = 0;
    double saTemp = 0;

    int loopN = 0;
    const int loopDelay = 0;

    std::random_device rd;
    std::mt19937 rng;
public:
	Annealing(int _nodeN, int _loopDelay, double _saTempStart, double _saTempAlpha);
    void Run();
    void Loop();
    void SaStep(std::vector<int>& path, double temp);
    std::pair<int, int> RandAB();
    void PathMove(std::vector<int>& path, std::pair<int, int> move);
    double PathDist(const std::vector<int>& path);
    std::vector<int> RandPath();
    void NodeRand();
    void PrintNodes(std::ofstream& file);
    void PrintPath(const std::vector<int>& path, std::ofstream& file);

};

#endif // ANNEALING_H