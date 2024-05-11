struct Job {
    int id = 0;
    std::vector<int> processing_times;
    int total_time = 0;
};


struct Data {
    int rows, cols;
    std::vector<std::vector<int>> values;
};

struct Neh {
    int value;
    std::vector<int> order;
};