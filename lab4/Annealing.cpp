#include "annealing.h"


Annealing::Annealing(int _nodeN, int _loopDelay, double _saTempStart, double _saTempAlpha) :
    nodeN(_nodeN), loopDelay(_loopDelay), saTempStart(_saTempStart), saTempAlpha(_saTempAlpha), rd(), rng(rd()) {}


void Annealing::Run() {
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

    // Print the final best distance found and path to the file
    std::ofstream file("output.txt", std::ios_base::app);
    if (!file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return;
    }

    PrintNodes(node, file);

    Loop();
    
    file << "Final Best Distance: " << saBestDist << std::endl;
	UpdateNodesPath(saBestPath);
	PrintUpdatedNodes(nodeResult, file);
    file << std::endl;
    PrintPath(saBestPath, file); // Print the final best path to the file
    file.close();
}

void Annealing::Loop() {
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
    // std::cout << "Current Best Distance: " << saBestDist << std::endl;
    Loop();
}

void Annealing::SaStep(std::vector<int>& path, double temp) {
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

std::pair<int, int> Annealing::RandAB() {
    int a = std::uniform_int_distribution<>(0, node.size() - 1)(rng);
    int b = std::uniform_int_distribution<>(0, node.size() - 2)(rng);
    if (b >= a) b++;
    if (a > b) std::swap(a, b);
    return { a, b };
}

void Annealing::PathMove(std::vector<int>& path, std::pair<int, int> move) {
    int a = move.first, b = move.second;
    while (a < b) std::swap(path[a++], path[b--]);
}

double Annealing::PathDist(const std::vector<int>& path) {
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

std::vector<int> Annealing::RandPath() {
    std::vector<int> path(nodeN);
    std::iota(path.begin(), path.end(), 0);
    std::shuffle(path.begin(), path.end(), rng);
    return path;
}

void Annealing::NodeRand() {
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

void Annealing::PrintNodes(std::vector<std::pair<int, int>> nodes, std::ofstream& file) {
    file << "Generated Nodes:" << std::endl;
    for (size_t i = 0; i < nodes.size(); i++) {
        file << "Node; " << i << ";" << nodes[i].first << "; " << nodes[i].second << ";" << std::endl;
    }
}

void Annealing::PrintPath(const std::vector<int>& path, std::ofstream& file) {
    file << "Path Order:" << std::endl;
    for (size_t i = 0; i < path.size(); i++) {
        file << path[i] << " \n";
    }
    file << std::endl;
}

void Annealing::UpdateNodesPath(const std::vector<int>& path)
{
	for (size_t i = 0; i < path.size(); i++) {
		nodeResult.push_back(node[path[i]]);
	}
}

void Annealing::PrintUpdatedNodes(std::vector<std::pair<int, int>> nodes, std::ofstream& file) {
    file << "Generated Nodes:" << std::endl;
    for (size_t i = 0; i < nodes.size(); i++) {
        file << "(" << nodes[i].first << ", " << nodes[i].second << ")" << std::endl;
    }
}
