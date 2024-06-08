#include "Annealing.h"

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <random>
#include <chrono>
#include <numeric> // For std::iota
#include <fstream> // For file handling

int main() {
    std::ofstream file("output.txt");
    if (!file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    Annealing annealing(40, 10, 10000, 0.976);
    annealing.NodeRand(); // Print the generated nodes to the file
    annealing.Run();

    file.close();
    return 0;
}

