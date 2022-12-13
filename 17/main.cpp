#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <unordered_map>
#include <climits>

using std::vector;
using std::string;
using std::cout;
using std::unordered_map;

unordered_map<int, int> getData(const string &path){
    unordered_map<int, int> output;
    std::ifstream data(path);
    string line;
    int idx = 0;
    if (data.is_open())
    {
        while(getline(data, line))
        {
            output[idx] = stoi(line);
            idx++;
        }
    }
    return output;
}

void dfs(const unordered_map<int, int> &avaliable, const unordered_map<int, int> &sofar, int target, int total, vector<unordered_map<int, int>> &ans){
    for (auto it : avaliable){
        if(total + it.second == target) {
            auto buff = sofar;
            buff[it.first] = it.second;
            if (std::find(ans.begin(), ans.end(), buff) == ans.end()) {
                ans.push_back(buff);
                cout << ans.size() << std::endl;
            }
        }
        else if(total + it.second < target) {
            auto buff_av = avaliable;
            auto buff_sf = sofar;
            buff_av.erase(it.first);
            for (auto in = buff_av.begin(); in != buff_av.end();) {
                if(in->second > it.second) {
                    in = buff_av.erase(in);
                }
                else
                in++;
            }
            buff_sf[it.first] = it.second;
            dfs(buff_av, buff_sf, target, total + it.second, ans);
        }
    }
}

int num_min_size(vector<unordered_map<int, int>> &ans){
    int min = INT_MAX;
    int num = 0;
    for (const auto& sol : ans){
        if (sol.size() < min){
            min = (int)sol.size();
        }
    }
    for (const auto& sol : ans){
        if (sol.size() == min){
            num++;
        }
    }
    return num;
}

int main() {
    unordered_map<int, int> avaliable = getData("data.txt");
    unordered_map<int, int> sofar = unordered_map<int, int>();
    vector<unordered_map<int, int>> ans = vector<unordered_map<int, int>>();
    dfs(avaliable, sofar, 150, 0, ans);
    cout << "Task 01: " << ans.size() << std::endl;
    cout << "Task 02: " << num_min_size(ans) << std::endl;
}