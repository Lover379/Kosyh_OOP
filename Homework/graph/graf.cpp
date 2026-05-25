#include "graf.h"
#include <fstream>
#include <queue>
#include <algorithm>
#include <set>

Graf::Graf() : max_vertex_id(-1) {}

Graf::Graf(const std::string& file_name) : max_vertex_id(-1) {
    std::ifstream file(file_name);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << file_name << std::endl;
        return;
    }

    std::string header;
    std::getline(file, header);

    int source, target;
    std::vector<std::pair<int, int>> edges;

    while (file >> source) {
        char ch;
        if (file.peek() == ',' || file.peek() == ';') {
            file >> ch;
        }
        if (file >> target) {
            edges.push_back({ source, target });
            if (source > max_vertex_id) max_vertex_id = source;
            if (target > max_vertex_id) max_vertex_id = target;
        }
    }
    file.close();

    adj_list.resize(max_vertex_id + 1);
    visited.resize(max_vertex_id + 1, false);

    for (const auto& edge : edges) {
        addEdge(edge.first, edge.second);
    }
}

void Graf::addEdge(int source, int target) {
    if (source <= max_vertex_id && target <= max_vertex_id) {
        adj_list[source].push_back(target);
        adj_list[target].push_back(source);
    }
}

bool Graf::runBFSTest(int start_node, int target_node) {
    if (start_node > max_vertex_id || target_node > max_vertex_id) return false;

    std::vector<bool> local_visited(max_vertex_id + 1, false);
    std::queue<int> q;

    q.push(start_node);
    local_visited[start_node] = true;

    while (!q.empty()) {
        int curr = q.front();
        q.pop();

        if (curr == target_node) return true;

        for (int neighbor : adj_list[curr]) {
            if (!local_visited[neighbor]) {
                local_visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
    return false;
}

std::vector<std::pair<int, int>> Graf::findComponentEdges(int start_node, std::vector<bool>& global_visited) {
    std::vector<std::pair<int, int>> component_edges;
    std::set<int> component_nodes;
    std::queue<int> q;

    q.push(start_node);
    global_visited[start_node] = true;

    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        component_nodes.insert(curr);

        for (int neighbor : adj_list[curr]) {
            if (!global_visited[neighbor]) {
                global_visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }

    for (int node : component_nodes) {
        for (int neighbor : adj_list[node]) {
            if (node < neighbor) {
                component_edges.push_back({ node, neighbor });
            }
        }
    }

    return component_edges;
}

void Graf::saveComponents(const std::string& input_file_name) {
    std::vector<bool> global_visited(max_vertex_id + 1, false);
    int component_count = 0;

    std::string base_name = input_file_name;
    size_t last_dot = base_name.find_last_of(".");
    if (last_dot != std::string::npos) {
        base_name = base_name.substr(0, last_dot);
    }

    for (int i = 0; i <= max_vertex_id; ++i) {
        if (!adj_list[i].empty() && !global_visited[i]) {
            auto edges = findComponentEdges(i, global_visited);
            if (!edges.empty()) {
                component_count++;
                std::string out_file_name = base_name + "_component_" + std::to_string(component_count) + ".txt";
                std::ofstream out_file(out_file_name);

                if (out_file.is_open()) {
                    out_file << "Source\tTarget\n";
                    for (const auto& edge : edges) {
                        out_file << edge.first << "\t" << edge.second << "\n";
                    }
                    out_file.close();
                }
            }
        }
    }
}