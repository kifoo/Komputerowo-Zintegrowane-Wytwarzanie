#pragma once
#include <list>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include "Task.h"

using namespace std;


struct Tree_Node
{
	vector<Tree_Node*> children;
    Tree_Node* parent;
	task job;
	int p_time = 0;
    int q_time = 0;

    void print_tree() {
        cout << job.id << " " << job.r << " " << job.p << " " << job.q << "\n";
        for (auto& child : children) {
            child->print_tree();
        }
    }
};

