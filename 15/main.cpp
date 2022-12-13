#include <fstream>
#include <regex>
#include <iostream>
#include <algorithm>

using std::cout;
using std::string;
using std::vector;
using matrix = vector<vector<int>>;

std::regex filter{": capacity| durability| flavor| texture| calories|,|\\r"};
std::regex sep{" "};

string filter_string(const string &input){
    string output = std::regex_replace(input, filter, "");
    return output;
}

matrix get_data(const string &path){
    matrix output;
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
            string name = *iter;
            int capacity = stoi(*(++iter));
            int durability = stoi(*(++iter));
            int flavor = stoi(*(++iter));
            int texture = stoi(*(++iter));
            int calories = stoi(*(++iter));
            vector<int> current{capacity, durability, flavor, texture, calories};
            output.push_back(current);
        }
        data.close();
    }
    return output;
}

matrix gen_combinations(int max_value, int num_elements){
    matrix output;
    vector<int> current(num_elements, 0);
    auto incr_idx = num_elements - 1;
    while(current[0]<max_value){
        int sum_of_elems = 0;
        for (auto& n : current) {
            sum_of_elems += n;
        }
        if(sum_of_elems==max_value) {
            output.push_back(current);
        }
        while(current[incr_idx] == max_value){
            current[incr_idx] = 0;
            incr_idx--;
        }
        current[incr_idx] = current[incr_idx] + 1;
        incr_idx =  num_elements - 1;
    }
    return output;
}

vector<int> get_scores(matrix combinations, matrix stats){
    auto stats_size = stats[0].size();
    vector<int> output;
    for (auto &combination: combinations) {
        vector<int> buffer(stats_size, 0);
        for (int idx = 0; idx < combination.size(); idx++) {
            auto count = combination[idx];
            auto stat = stats[idx];
            for(int stat_idx = 0; stat_idx < stats_size; stat_idx++){
                buffer[stat_idx] += count * stat[stat_idx];
            }
        }
        if(buffer.back() == 500) {
            int result = 1;
            for (auto it = buffer.begin(); it != buffer.end() - 1; ++it) {
                if (*it >= 0) {
                    result *= *it;
                } else {
                    result *= 0;
                }
            }
            output.push_back(result);
        }
    }
    return output;
}


int main(){
    matrix combinations = gen_combinations(100, 4);
    matrix stats = get_data("data.txt");
    auto scores = get_scores(combinations, stats);
    auto result = std::max_element(scores.begin(), scores.end());
    auto idx = std::distance(scores.begin(), result);
    cout << scores[idx];
}



