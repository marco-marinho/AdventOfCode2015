#include <iostream>
#include <fstream>
#include <string>
#include <tuple>
#include <vector>
#include <regex>
#include <array>
#include <algorithm>
#include <numeric>

using std::regex_match;

const std::regex vowels{ "([aeiou])" };
const std::regex repeat{"(.)\\1"};
const std::regex forbidden{"(ab)|(cd)|(pq)|(xy)"};
const std::regex pair{"(\\w\\w)\\w*\\1"};
const std::regex two_sep{"(\\w)\\w\\1"};


bool isGood(std::string &input){
    auto vowel_match = std::sregex_iterator(input.begin(), input.end(), vowels);
    int num_vowels = std::distance(vowel_match, std::sregex_iterator());

    auto repeat_match = std::sregex_iterator(input.begin(), input.end(), repeat);
    int num_repeat = std::distance(repeat_match, std::sregex_iterator());

    auto forbiden_match = std::sregex_iterator(input.begin(), input.end(), forbidden);
    int num_forbiden = std::distance(forbiden_match, std::sregex_iterator());

    if(num_vowels > 2 and num_repeat > 0 and num_forbiden == 0){
        return true;
    }
    else {
        return false;
    }
}

bool isGood2(std::string &input){
    auto pair_match = std::sregex_iterator(input.begin(), input.end(), pair);
    int num_pair = std::distance(pair_match, std::sregex_iterator());

    auto sep_match = std::sregex_iterator(input.begin(), input.end(), two_sep);
    int num_sep = std::distance(sep_match, std::sregex_iterator());

    if(num_sep > 0 and num_pair > 0){
        return true;
    }
    else{
        return false;
    }

}


int main() {

    std::string line;
    std::ifstream data("../05/data.txt");
    int good_ones = 0;

    if (data.is_open())
    {
        while(getline(data, line))
        {
            if(isGood2(line)){
                good_ones++;
            }
        }
        data.close();
    }
    return good_ones;
}

