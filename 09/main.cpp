#include <fstream>
#include <regex>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using std::cout;
using std::endl;
using std::string;

int main() {
    std::unordered_map<string, std::unordered_map<string, int>> costs;
    std::regex filter{"to |= "};
    std::regex sep{" "};
    std::vector<string> nodes;
    std::string line;
    std::ifstream data("../09/data.txt");
    std::vector<std::vector<string>> paths;

    if (data.is_open()) {
        while (getline(data, line)) {
            line = std::regex_replace(line, filter, "");
            std::vector<std::string> out;

            std::sregex_token_iterator iter(line.begin(),
                                            line.end(),
                                            sep,
                                            -1);

            string start = *iter;
            string stop = *(++iter);
            int cost = std::stoi(*(++iter));
            costs[start][stop] = cost;
            costs[stop][start] = cost;
        }
    }
    data.close();
    for(auto &node : costs){
        nodes.push_back(node.first);
    }
    do {
        paths.push_back(nodes);
    } while(std::next_permutation(nodes.begin(), nodes.end()));

    std::vector<int> total_costs(paths.size(), 0);
    for(int path_idx = 0; path_idx < paths.size(); path_idx++){
        auto path = paths[path_idx];
        for(int nodex_idx = 0; nodex_idx < path.size() - 1; nodex_idx++){
            total_costs[path_idx] += costs[path[nodex_idx]][path[nodex_idx + 1]];
        }
    }
    return *std::max_element(total_costs.begin(), total_costs.end());
}
