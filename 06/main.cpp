#include <fstream>
#include <array>
#include <regex>
#include <iostream>

struct coordinates{
    int x_start;
    int x_stop;
    int y_start;
    int y_stop;
};

std::array<std::array<int, 1000>, 1000> lights = {0};

const std::regex sep{"( )"};
const std::regex sep_coord{"(,)"};

void toogle(coordinates coord){
    for(int x = coord.x_start; x<= coord.x_stop; x++)
    {
        for(int y = coord.y_start; y<= coord.y_stop; y++){
            lights[x][y] += 2;
        }
    }
}

void set(coordinates coord, int status){
    for(int x = coord.x_start; x<= coord.x_stop; x++)
    {
        for(int y = coord.y_start; y<= coord.y_stop; y++){
            lights[x][y] += status;
            if(lights[x][y] < 0){
                lights[x][y] = 0;
            }
        }
    }
}

void parseInstructions(std::string &input){

    coordinates coord;
    int offset = 0;
    const std::vector<std::string> instructions{
            std::sregex_token_iterator(input.begin(), input.end(), sep, -1),
            std::sregex_token_iterator()
    };

    if(instructions.size() == 4){
        offset--;
    }

    const std::vector<std::string> start{
            std::sregex_token_iterator(instructions[2 + offset].begin(), instructions[2 + offset].end(), sep_coord, -1),
            std::sregex_token_iterator()
    };
    coord.x_start = std::stoi(start[0]);
    coord.y_start = std::stoi(start[1]);

    const std::vector<std::string> stop{
            std::sregex_token_iterator(instructions[4 + offset].begin(), instructions[4 + offset].end(), sep_coord, -1),
            std::sregex_token_iterator()
    };
    coord.x_stop = std::stoi(stop[0]);
    coord.y_stop = std::stoi(stop[1]);

    if(instructions.size() == 4){
        toogle(coord);
    }
    else{
        if(instructions[1] == "on"){
            set(coord, 1);
        }
        if(instructions[1] == "off"){
            set(coord, -1);
        }
    }
}

long long countOn(){
    long long out = 0;
    for(int x = 0; x < lights[0].size(); x++){
        for(int y = 0; y < lights[1].size(); y++){
                out+= lights[x][y];
        }
    }
    return out;
}


int main() {


    std::string line;
    std::ifstream data("../06/data.txt");

    if (data.is_open())
    {
        while(getline(data, line))
        {
            parseInstructions(line);
        }
        data.close();
    }
    long long out = countOn();
    std::cout << out;
    return 0;
}
