#pragma once
#include <iostream>
#include <vector>
#include <string>

struct Node {
    int id;
    Node(int _id) : id(_id) {}
};

class Graf {
private:
    int max_vertex_id;
    std::vector<std::vector<int>> adj_list;
    std::vector<bool> visited;

public:
    Graf();
    Graf(const std::string& file_name);

    void addEdge(int source, int target);
    std::vector<std::pair<int, int>> findComponentEdges(int start_node, std::vector<bool>& global_visited);
    void saveComponents(const std::string& input_file_name);
    bool runBFSTest(int start_node, int target_node);
};