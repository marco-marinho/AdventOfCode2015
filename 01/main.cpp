#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::string line;
    std::ifstream instruction("../01/data.txt");
    int up = 0;
    int down = 0;
    int floor;
    int position = 1;
    if (instruction.is_open())
    {
        while(getline(instruction, line))
        {
            for (char const &c: line) {
                if(c=='('){
                    up++;
                }
                else if (c==')'){
                    down++;
                }
                else{
                }
                floor = up-down;
                if(floor < 0){
                    return position;
                }
                else{
                    position++;
                }
            }
        }
        instruction.close();
    }
    return up-down;
}
