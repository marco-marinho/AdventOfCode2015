#include <iostream>
#include <fstream>
#include <regex>
#include <vector>
#include <set>
#include <algorithm>
#include <tuple>
#include <random>

auto rd = std::random_device {};
auto rng = std::default_random_engine { rd() };

using std::vector;
using std::string;
using std::cout;
using std::unordered_map;
using std::set;

typedef unordered_map<int, unordered_map<string, vector<string>>> table;

std::regex sep{" => "};

table getData(const string &path){
    table output = table();
    std::ifstream data(path);
    string line;
    if (data.is_open())
    {
        while(getline(data, line))
        {
            std::sregex_token_iterator iter(line.begin(),
                                            line.end(),
                                            sep,
                                            -1);
            std::sregex_token_iterator end;
            string first = *iter++;
            int len = (int)first.length();
            output[len][first].push_back(*iter);
        }
    }
    return output;
}

table getDataReverse(const string &path){
    table output = table();
    std::ifstream data(path);
    string line;
    if (data.is_open())
    {
        while(getline(data, line))
        {
            std::sregex_token_iterator iter(line.begin(),
                                            line.end(),
                                            sep,
                                            -1);
            std::sregex_token_iterator end;
            string first = *iter++;
            string second = *iter;
            int len = (int)second.length();
            output[len][second].push_back(first);
        }
    }
    return output;
}

int getNumReclaments(table &subs, const string &target){
    set<string> answers;
    int len = (int)target.length();
    for(int slice_start = 0; slice_start < len; slice_start++){
        for( auto& entry : subs){
            if (slice_start + entry.first <= len){
                string slice = target.substr(slice_start, entry.first);
                if (entry.second.find(slice) != entry.second.end()){
                    for (const auto& possible_sub : entry.second[slice]){
                        string out = target.substr(0, slice_start) + possible_sub + target.substr(slice_start + slice.length(), len);
                        answers.insert(out);
                    }
                }
            }
        }
    }
    return (int)answers.size();
}

int getNumGenerate(table &subs, string target){
    int count = 0;
    int len = (int)target.length();
    string default_target = target;
    vector<int> lens = vector<int>();
    for (const auto& entry : subs){
        lens.push_back(entry.first);
    }
    std::sort(lens.begin(), lens.end(), std::greater<>());
    while (target != "e"){
        target = default_target;
        int round_total = 1;
        count = 0;
        do {
            round_total = 0;
            std::shuffle(std::begin(lens), std::end(lens), rng);
            for (auto len_sub: lens) {
                auto cur_subs = subs[len_sub];
                vector<int> idxs = vector<int>();
                std::generate_n(std::back_inserter(idxs), cur_subs.size(), [n{0}]() mutable { return n++; });
                std::shuffle(std::begin(idxs), std::end(idxs), rng);
                for (auto idx: idxs) {
                    auto it = cur_subs.begin();
                    std::advance(it, idx);
                    auto found_idx = target.find(it->first);
                    if (found_idx != std::string::npos) {
                        target = target.substr(0, found_idx) + it->second[0] +
                                 target.substr(found_idx + it->first.length(), len);
                        round_total++;
                        count++;
                    }
                }
            }
        }while (round_total > 0);
    }
    return count;
}

int main(){
    string input = "ORnPBPMgArCaCaCaSiThCaCaSiThCaCaPBSiRnFArRnFArCaCaSiThCaCaSiThCaCaCaCaCaCaSiRnFYFArSiRnMgArCaSiRnPTiTiBFYPBFArSiRnCaSiRnTiRnFArSiAlArPTiBPTiRnCaSiAlArCaPTiTiBPMgYFArPTiRnFArSiRnCaCaFArRnCaFArCaSiRnSiRnMgArFYCaSiRnMgArCaCaSiThPRnFArPBCaSiRnMgArCaCaSiThCaSiRnTiMgArFArSiThSiThCaCaSiRnMgArCaCaSiRnFArTiBPTiRnCaSiAlArCaPTiRnFArPBPBCaCaSiThCaPBSiThPRnFArSiThCaSiThCaSiThCaPTiBSiRnFYFArCaCaPRnFArPBCaCaPBSiRnTiRnFArCaPRnFArSiRnCaCaCaSiThCaRnCaFArYCaSiRnFArBCaCaCaSiThFArPBFArCaSiRnFArRnCaCaCaFArSiRnFArTiRnPMgArF";
    table data = getData("data.txt");
    int num = getNumReclaments(data, input);
    cout << "Task 01: " << num << std::endl;
    table data_2 = getDataReverse("data.txt");
    num = getNumGenerate(data_2, input);
    cout << "Task 02: " << num << std::endl;
}
