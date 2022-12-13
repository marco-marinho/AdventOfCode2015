#include <fstream>
#include <regex>
#include <iostream>
#include <algorithm>

using std::cout;
using std::endl;
using std::string;
using std::to_string;

string lookAndSay(string input){
    auto current = input.at(0);
    int count = 1;
    input.erase(0,1);
    string output;
    for (auto &digit: input) {
        if(digit == current){
            count++;
        }
        else{
            output += to_string(count);
            output += current;
            current = digit;
            count = 1;
        }
    }
    output += to_string(count);
    output += current;
    return output;
}

int main() {
    string input = "1113222113";
    for(int iter = 0; iter < 50; iter ++){
        input = lookAndSay(input);
    }
    cout << input.length();
    return 0;
}
