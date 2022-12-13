#include <fstream>
#include <regex>
#include <iostream>
#include <algorithm>
#include <utility>

using std::cout;
using std::string;
using std::vector;

std::regex filter{" can fly| km/s for| seconds, but then must rest for| seconds.|\\r"};
std::regex sep{" "};

class Raindear{
public:
    Raindear(string name, int speed, int time_active, int time_rest);
    void tick();
    string name;
    int speed;
    int time_active;
    int time_rest;
    bool state;
    int time_left_in_state;
    long long distance;
    int points;
};

Raindear::Raindear(string name, int speed, int time_active, int time_rest):
name(std::move(name)),
speed(speed),
time_active(time_active),
time_rest(time_rest),
state(true),
time_left_in_state(time_active),
distance(0),
points(0){}

void Raindear::tick(){
    if(state){
        distance += speed;
    }
    time_left_in_state -= 1;
    if(time_left_in_state==0){
        state = !state;
        if(state){
            time_left_in_state = time_active;
        }
        if(!state){
            time_left_in_state = time_rest;
        }
    }
}

void score(vector<Raindear> &raindears){
    long long max_distance = -1;
    for(auto &raindear: raindears){
        if(raindear.distance > max_distance){
            max_distance = raindear.distance;
        }
    }
    for(auto &raindear: raindears){
        if(raindear.distance == max_distance){
            raindear.points += 1;
        }
    }
}

string filter_string(const string &input){
    string output = std::regex_replace(input, filter, "");
    return output;
}

vector<Raindear> get_raindears(const string &path){
    vector<Raindear> output;
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
            int speed = stoi(*(++iter));
            int time_active = stoi(*(++iter));
            int time_rest = stoi(*(++iter));
            output.emplace_back(Raindear(name, speed, time_active, time_rest));
        }
        data.close();
    }
    return output;
}

int main(){
    int simulation_time = 2503;
    vector<Raindear> raindears = get_raindears("data.txt");

    for(int current_time = 0; current_time < simulation_time; current_time++){
        for(auto &raindear: raindears){
            raindear.tick();
        }
        score(raindears);
    }
}



