#include <fstream>
#include <regex>
#include <iostream>
#include <algorithm>

using std::cout;
using std::endl;
using std::string;
using std::to_string;
using std::regex;

bool check_valid(string input){
    regex double_letter{"([a-z])\\1"};
    regex forbidden_chars{"i|o|l"};

    auto double_letter_match = std::sregex_iterator(input.begin(), input.end(), double_letter);
    int num_double_letter = std::distance(double_letter_match, std::sregex_iterator());

    auto forbidden_chars_match = std::sregex_iterator(input.begin(), input.end(), forbidden_chars);
    int num_forbidden_chars = std::distance(forbidden_chars_match, std::sregex_iterator());

    char last = input.at(0);
    int count = 0;
    bool pass_increase = false;
    for (auto it = input.cbegin() + 1 ; it != input.cend() - 1; ++it) {
        if(*it - last == 1){
            count++;
        }
        else{
            count = 0;
        }
        if(count == 2){
            pass_increase = true;
            break;
        }
        last = *it;
    }
    if(pass_increase and num_double_letter >= 2 and num_forbidden_chars == 0){
        return true;
    }
    return false;
}

int main() {
    string input = "hepxxzaa";
    auto incr_idx = input.length() - 1;
    while(!check_valid(input)){
        while(input.at(incr_idx) == 'z'){
            input[incr_idx] = 'a';
            incr_idx--;
        }
        if(input.at(incr_idx) == 'h' or input.at(incr_idx) == 'k' or input.at(incr_idx) == 'n'){
            input[incr_idx] = input.at(incr_idx) + 2;
        }
        else {
            input[incr_idx] = input.at(incr_idx) + 1;
        }
        incr_idx = input.length() - 1;
    }
    cout << input;
    return check_valid(input);
}
