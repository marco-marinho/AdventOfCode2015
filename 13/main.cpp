#include <fstream>
#include <regex>
#include <iostream>
#include <algorithm>

using std::cout;
using std::string;
using std::vector;
using std::unordered_map;
using change_map = unordered_map<string, unordered_map<string, int>>;

std::regex filter{" would| happiness units by sitting next to|\\.|\\r"};
std::regex gain{"gain "};
std::regex lose{"lose "};
std::regex sep{"[ ]+"};

string filter_string(string input){
    string output = std::regex_replace(input, filter, "");
    output = std::regex_replace(output, gain, "");
    output = std::regex_replace(output, lose, "-");
    return output;
}

void add_self(change_map &costs){
    vector<string> names;
    for (auto &node: costs) {
        names.push_back(node.first);
    }
    for(auto &name: names){
        costs["Self"][name] = 0;
        costs[name]["Self"] = 0;
    }
}

change_map get_changes(string path){
    change_map output;
    std::ifstream data(path);
    string line;

    if (data.is_open())
    {
        while(getline(data, line))
        {
            string buffer = filter_string(line);
            std::sregex_token_iterator iter(buffer.begin(),
                                            buffer.end(),
                                            sep,
                                            -1);
            string source = *iter;
            int change = stoi(*(++iter));
            string destination = *(++iter);
            output[source][destination] = change;
        }
        data.close();
    }
    return output;
}
vector<vector<string>> get_possible_tables(change_map costs) {
    vector<string> names;
    vector<vector<string>> arrangements;
    for (auto &node: costs) {
        names.push_back(node.first);
    }
    std::sort(names.begin(), names.end());
    do {
        arrangements.push_back(names);
    } while (std::next_permutation(names.begin(), names.end()));
    return arrangements;
}

int get_hapiness(vector<string> arrangement, change_map costs){
    int hapiness = 0;
    for(int idx = 0; idx < arrangement.size(); idx++){
        int previous;
        if(idx == 0){
            previous = arrangement.size() - 1;
        }
        else{
            previous = idx - 1;
        }
        int next;
        if(idx == arrangement.size() - 1){
            next = 0;
        }
        else{
            next = idx + 1;
        }
        hapiness += costs[arrangement[idx]][arrangement[previous]];
        hapiness += costs[arrangement[idx]][arrangement[next]];
    }
    return hapiness;
}

int main(){

    change_map changes = get_changes("data.txt");
    add_self(changes);
    vector<vector<string>> arrangements = get_possible_tables(changes);
    vector<int> outputs;
    for(auto arrangment: arrangements){
        outputs.push_back(get_hapiness(arrangment, changes));
    }
    auto result = std::max_element(outputs.begin(), outputs.end());
    int idx = std::distance(outputs.begin(), result);
    cout << outputs[idx];
}



