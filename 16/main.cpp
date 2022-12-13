#include <fstream>
#include <regex>
#include <iostream>
#include <algorithm>
#include <utility>
#include <unordered_map>

using std::cout;
using std::string;
using std::vector;
using std::unordered_map;
using aunt_list = vector<unordered_map<string, int>>;


std::regex filter{"Sue [0-9]+: |:|\\r"};
std::regex sep{", "};
std::regex inner_sep{" "};

string filter_string(const string &input){
    string output = std::regex_replace(input, filter, "");
    return output;
}

aunt_list get_data(const string &path){
    aunt_list output;
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
            std::sregex_token_iterator end;
            unordered_map<string, int> buff_map;
            for ( ; iter != end; ++iter){
                string inner_buffer = *iter;
                std::sregex_token_iterator inner_iter(inner_buffer.begin(),
                                                inner_buffer.end(),
                                                      inner_sep,
                                                -1);
                string att = *inner_iter;
                auto value = stoi(*(++inner_iter));
                buff_map[att] = value;
            }
            output.push_back(buff_map);
            }
        }
        data.close();

    return output;
}

int main(){
    unordered_map<string, int> target;
    target["children"] = 3;
    target["cats"] = 7;
    target["samoyeds"] = 2;
    target["pomeranians"] = 3;
    target["akitas"] = 0;
    target["vizslas"] = 0;
    target["goldfish"] = 5;
    target["trees"] = 3;
    target["cars"] = 2;
    target["perfumes"] = 1;

    int aunt_nr = -1;
    auto aunts = get_data("data.txt");

    for (int aunt_idx = 0; aunt_idx < aunts.size(); aunt_idx++){
        int hits = 0;
        for(auto iter = target.begin(); iter != target.end(); ++iter)
        {
            auto key =  iter->first;
            auto value = iter->second;

            if (!(aunts[aunt_idx].find(key) == aunts[aunt_idx].end())) {
                if(aunts[aunt_idx][key] == value){
                    hits++;
                }
            }
        }
        if(hits == 3){
            aunt_nr = aunt_idx+1;
            break;
        }
    }
    cout << "Task 01: " << aunt_nr << std::endl;

    for (int aunt_idx = 0; aunt_idx < aunts.size(); aunt_idx++){
        int hits = 0;
        for(auto iter = target.begin(); iter != target.end(); ++iter)
        {
            auto key =  iter->first;
            auto value = iter->second;

            if(key == "trees" or key == "cats"){
                if (!(aunts[aunt_idx].find(key) == aunts[aunt_idx].end())) {
                    if(aunts[aunt_idx][key] > value){
                        hits++;
                    }
                }
            }
            else if(key == "pomeranians" or key == "goldfish"){
                if (!(aunts[aunt_idx].find(key) == aunts[aunt_idx].end())) {
                    if(aunts[aunt_idx][key] < value){
                        hits++;
                    }
                }
            }
            else {
                if (!(aunts[aunt_idx].find(key) == aunts[aunt_idx].end())) {
                    if (aunts[aunt_idx][key] == value) {
                        hits++;
                    }
                }
            }
        }
        if(hits == 3){
            aunt_nr = aunt_idx+1;
            break;
        }
    }
    cout << "Task 02: " << aunt_nr << std::endl;
}



