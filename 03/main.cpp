#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>
#include <algorithm>

struct record{
    int x;
    int y;
    int visits;
    bool operator==(const record& rhs) const
    {
        return x==rhs.x && y==rhs.y;
    }
};


void add_visit(int x, int y, std::vector<record> &records){
    record temp {x, y, 1};
    auto it = std::find(records.begin(), records.end(), temp);
    if (it != records.end()){
        it->visits++;
    }
    else{
        records.push_back(temp);
    }
}


int main() {

    std::vector<record> records_santa;
    std::vector<record> robo_santa;
    std::string line;
    std::ifstream data("../03/data.txt");
    std::array<int, 2> position_santa = {0, 0};
    std::array<int, 2> position_robo = {0, 0};
    add_visit(position_santa[0], position_santa[1], records_santa);
    add_visit(position_robo[0], position_robo[1], robo_santa);
    std::array<int, 2> *position;
    int idx = 0;
    if (data.is_open())
    {
        while(getline(data, line)) {
            for (char const &c: line) {
                if(idx%2 == 0) {
                    position = &position_santa;
                }
                else{
                    position = &position_robo;
                }
                if (c == '<') {
                    (*position)[0]--;
                } else if (c == '>') {
                    (*position)[0]++;
                } else if (c == '^') {
                    (*position)[1]++;
                } else if (c == 'v') {
                    (*position)[1]--;
                }
                if(idx%2 == 0){
                    add_visit((*position)[0], (*position)[1], records_santa);
                }
                else{
                    add_visit((*position)[0], (*position)[1], robo_santa);
                }
                idx++;
            }
        }
        for(auto i : robo_santa){
            auto it = std::find(records_santa.begin(), records_santa.end(), i);
            if(it == records_santa.end()){
                records_santa.push_back(i);
            }
        }
        data.close();
    }
    return records_santa.size();
}