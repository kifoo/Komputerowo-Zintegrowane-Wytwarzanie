#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <random>
#include <chrono>
#include <numeric> // For std::iota
#include <fstream> // For file handling

const int nodeN = 40;             // number of cities
std::vector<std::pair<int, int>> node; // instance data
std::vector<int> saPath;          // solution
std::vector<double> saDataDist;   // Dist data
std::vector<double> saDataPraw;   // Praw data
std::vector<double> saDataTemp;   // Temp data
double saBestDist;                // best found solution (Dist)
std::vector<int> saBestPath;      // best found solution (path)
double saTempStart = 10000;       // starting temperature
double saTempAlpha = 0.976;       // temperature change coefficient
double saTemp;                    // current temperature

int loopN = 0;                    // number of remaining steps
const int loopDelay = 10;         // loop delay

std::random_device rd;
std::mt19937 rng(rd());

// Function prototypes
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

int main() {
    std::ofstream file("output.txt");
    if (!file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    NodeRand();
    PrintNodes(file); // Print the generated nodes to the file
    Run();

    file.close();
    return 0;
}

void Run() {
    auto startPath = RandPath();
    double startDist = PathDist(startPath);
    saPath = startPath;
    saDataDist.clear();
    saDataDist.push_back(startDist);
    saBestDist = startDist;
    saBestPath = startPath;

    loopN = 400;
    saTemp = saTempStart;
    saDataTemp.clear();
    saDataPraw.clear();
    Loop();

    // Print the final best distance found and path to the file
    std::ofstream file("output.txt", std::ios_base::app);
    if (!file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return;
    }

    file << "Final Best Distance: " << saBestDist << std::endl;
    PrintPath(saBestPath, file); // Print the final best path to the file
    file.close();
}

void Loop() {
    if (loopN == 0) {
        saDataDist.push_back(saBestDist);
        saPath = saBestPath;
        return;
    }
    loopN--;
    SaStep(saPath, saTemp);
    saTemp *= saTempAlpha;
    if (loopN == 0) {
        saDataDist.push_back(saBestDist);
        saPath = saBestPath;
    }

    // Print the current best distance after each iteration
    std::cout << "Current Best Distance: " << saBestDist << std::endl;

    // Add a delay if needed (using sleep_for, omitted here for simplicity)
    // std::this_thread::sleep_for(std::chrono::milliseconds(loopDelay));
    Loop();
}

void SaStep(std::vector<int>& path, double temp) {
    double c0 = PathDist(path);
    double praw = 0, akce = 0;
    for (int i = 0; i < 100; i++) {
        auto move = RandAB();
        PathMove(path, move);
        double c1 = PathDist(path);
        if (c1 > c0) {
            praw = std::exp((c0 - c1) / temp);
            akce = (std::uniform_real_distribution<>(0, 1)(rng) < praw);
        }
        if (c1 <= c0 || akce) {
            c0 = c1; // accept move
        }
        else {
            PathMove(path, move); // reject move
        }
        if (saBestDist > c0) {
            saBestDist = c0;
            saBestPath = path;
        }
    }
    saDataDist.push_back(c0);
    saDataTemp.push_back(saTemp);
    saDataPraw.push_back(praw);
}

std::pair<int, int> RandAB() {
    int a = std::uniform_int_distribution<>(0, node.size() - 1)(rng);
    int b = std::uniform_int_distribution<>(0, node.size() - 2)(rng);
    if (b >= a) b++;
    if (a > b) std::swap(a, b);
    return { a, b };
}

void PathMove(std::vector<int>& path, std::pair<int, int> move) {
    int a = move.first, b = move.second;
    while (a < b) std::swap(path[a++], path[b--]);
}

double PathDist(const std::vector<int>& path) {
    double dist = 0;
    for (size_t i = 0; i < path.size(); i++) {
        int n0 = path[i];
        int n1 = path[(i + 1) % path.size()];
        int x0 = node[n0].first;
        int y0 = node[n0].second;
        int x1 = node[n1].first;
        int y1 = node[n1].second;
        dist += std::round(std::sqrt((x0 - x1) * (x0 - x1) + (y0 - y1) * (y0 - y1)));
    }
    return dist;
}

std::vector<int> RandPath() {
    std::vector<int> path(nodeN);
    std::iota(path.begin(), path.end(), 0);
    std::shuffle(path.begin(), path.end(), rng);
    return path;
}

void NodeRand() {
    loopN = 0;
    node.clear();
    saPath.clear();
    saBestPath.clear();
    saDataDist.clear();
    saDataPraw.clear();
    saDataTemp.clear();
    for (int i = 0; i < nodeN; i++) {
        node.push_back({ std::uniform_int_distribution<>(0, 400)(rng), std::uniform_int_distribution<>(0, 200)(rng) });
    }
}

void PrintNodes(std::ofstream& file) {
    file << "Generated Nodes:" << std::endl;
    for (size_t i = 0; i < node.size(); i++) {
        file << "Node; " << i << ";" << node[i].first << "; " << node[i].second << ";" << std::endl;
    }
}

void PrintPath(const std::vector<int>& path, std::ofstream& file) {
    file << "Path Order:" << std::endl;
    for (size_t i = 0; i < path.size(); i++) {
        file << path[i] << " ";
    }
    file << std::endl;
}
