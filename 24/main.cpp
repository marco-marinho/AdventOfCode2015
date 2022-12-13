#include <vector>
#include <unordered_map>
#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <numeric>
#include <set>

using std::vector;
using std::unordered_map;
using std::string;
using std::cout;
using std::set;

struct answer {
    vector<unsigned long> weights;
    int len;
    unsigned long prod;
};

vector<unsigned long> get_data(const string &path) {
    std::ifstream data(path);
    string line;
    vector<unsigned long> output;
    if (data.is_open()) {
        while (getline(data, line)) {
            output.push_back(std::stoi(line));
        }
    }
    return output;
}

void dfs(const vector<unsigned long>& available, vector<unsigned long> current, int target, vector<answer> &ans){
    unsigned long min = !current.empty() ? *std::min_element(current.begin(), current.end()) : INT32_MAX;
    int cur_total = std::accumulate(current.begin(), current.end(), 0);
    for (auto element : available){
        if (element < min){
            if (element + cur_total == target){
                auto next = current;
                next.push_back(element);
                std::sort(next.begin(), next.end());
                unsigned long multi = 1;
                for(unsigned long i : next)
                {
                    multi *= i;
                }
                answer nans = {next, (int) next.size(), multi};
                ans.push_back(nans);
            }
            else {
                if(element + cur_total > target){
                    continue;
                }
                std::vector<unsigned long> remaining;
                std::copy_if(available.begin(), available.end(),
                             std::back_inserter(remaining), [element](unsigned long i){return i<=element;} );
                auto soma = std::accumulate(remaining.begin(), remaining.end(), 0);
                if( soma < target - cur_total) {
                    continue;
                }
                auto next = current;
                next.push_back(element);
                dfs(available, next, target, ans);
            }
        }
    }
}

bool confirm_answers(answer test, const vector<answer>& ans, const vector<unsigned long>& pres){
    set<int> presents(pres.begin(), pres.end());

    set<int> sol(test.weights.begin(), test.weights.end());
    std::vector<int> diff;
    std::set_difference(presents.begin(), presents.end(), sol.begin(), sol.end(),
                        std::inserter(diff, diff.end()));
    std::sort(diff.begin(), diff.end());
    for (auto answer_inner : ans){
        std::vector<int> buff(100);
        auto ls = std::set_intersection(diff.begin(), diff.end(),
                                        answer_inner.weights.begin(), answer_inner.weights.end(),
                                        buff.begin());
        int a = ls - buff.begin();
        if (a == answer_inner.weights.size()){
            return true;
        }

    }
    return false;
}

unsigned long get_min_qe(const vector<answer> &ans, const vector<unsigned long> &presents){
    int min = INT32_MAX;
    for (const auto& hit : ans){
        if (hit.len < min){
            min = hit.len;
        }
    }
    unsigned long QE = UINT64_MAX;
    for (const auto& hit : ans){
        if (hit.len == min){
            if(!confirm_answers(hit, ans, presents)){
                continue;
            }
            if (hit.prod < QE)
            {
                QE = hit.prod;
            }
        }
    }
    return QE;
}

int main(){
    vector<unsigned long> presents = get_data("data.txt");
    std::sort (presents.begin(), presents.end());
    int total = std::accumulate(presents.begin(), presents.end(), 0);
    int target = total/3;
    vector<answer> ans;
    dfs(presents, vector<unsigned long>(), target, ans);
    unsigned long qe = get_min_qe(ans, presents);
    cout << "Task 01: " << qe << std::endl;
    ans.clear();
    target = total/4;
    dfs(presents, vector<unsigned long>(), target, ans);
    qe = get_min_qe(ans, presents);
    cout << "Task 02: " << qe << std::endl;
}