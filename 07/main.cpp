#include <fstream>
#include <array>
#include <regex>
#include <iostream>
#include <algorithm>
#include <cstdint>
#include <unordered_map>

std::unordered_map<std::string, uint16_t> values;
std::regex filter{"AND|OR|NOT |RSHIFT|LSHIFT|->|\\r"};
std::regex sep{"[ ]+"};

using std::cout;

const std::string OR{ "OR" };
const std::string AND{"AND"};
const std::string NOT{"NOT"};
const std::string LSHIFT{"LSHIFT"};
const std::string RSHIFT{"RSHIFT"};

bool isNumber(const std::string& str)
{
    for (char const &c : str) {
        if (std::isdigit(c) == 0) return false;
    }
    return true;
}

bool contains(std::unordered_map<std::string, uint16_t> &map, std::string &key){
    auto got = map.find(key);
    if (got == map.end())
        return false;
    else
        return true;
}

std::vector<std::string> parseArguments(std::string &input){

    std::vector<std::string> out;
    auto arguments = std::regex_replace(input, filter, "");

    std::sregex_token_iterator iter(arguments.begin(),
                                    arguments.end(),
                                    sep,
                                    -1);

    std::sregex_token_iterator end;
    for ( ; iter != end; ++iter){
        out.push_back(*iter);
    }


    return out;

}

bool put(std::vector<std::string> arguments){
    if(isNumber(arguments[0])){
        values[arguments[1]] = stoi(arguments[0]);
        return true;
    }
    else{
        if(contains(values, arguments[0])){
            values[arguments[1]] = values[arguments[0]];
            return true;
        }
        else{
            return false;
        }
    }
}

bool put_not(std::vector<std::string> arguments){
    if(isNumber(arguments[0])){
        values[arguments[1]] = ~stoi(arguments[0]);
        return true;
    }
    else{
        if(contains(values, arguments[0])){
            values[arguments[1]] = ~values[arguments[0]];
            return true;
        }
        else{
            return false;
        }
    }
}

bool put_or(std::vector<std::string> arguments){
    int arg0, arg1;

    if(isNumber(arguments[0])){
        arg0 = stoi(arguments[0]);
    }
    else{
        if(contains(values, arguments[0])){
            arg0 = values[arguments[0]];
        }
        else{
            return false;
        }
    }

    if(isNumber(arguments[1])){
        arg1 = stoi(arguments[1]);
    }
    else{
        if(contains(values, arguments[1])){
            arg1 = values[arguments[1]];
        }
        else{
            return false;
        }
    }

    values[arguments[2]] = arg0 | arg1;
    return true;
}

bool put_and(std::vector<std::string> arguments){
    int arg0, arg1;

    if(isNumber(arguments[0])){
        arg0 = stoi(arguments[0]);
    }
    else{
        if(contains(values, arguments[0])){
            arg0 = values[arguments[0]];
        }
        else{
            return false;
        }
    }

    if(isNumber(arguments[1])){
        arg1 = stoi(arguments[1]);
    }
    else{
        if(contains(values, arguments[1])){
            arg1 = values[arguments[1]];
        }
        else{
            return false;
        }
    }
    values[arguments[2]] = arg0 & arg1;
    return true;
}

bool put_rshift(std::vector<std::string> arguments) {
    int arg0, arg1;

    if (isNumber(arguments[0])) {
        arg0 = stoi(arguments[0]);
    } else {
        if (contains(values, arguments[0])) {
            arg0 = values[arguments[0]];
        } else {
            return false;
        }
    }

    if (isNumber(arguments[1])) {
        arg1 = stoi(arguments[1]);
    } else {
        if (contains(values, arguments[1])) {
            arg1 = values[arguments[1]];
        } else {
            return false;
        }
    }
    values[arguments[2]] = arg0 >> arg1;
    return true;
}

bool put_lshift(std::vector<std::string> arguments) {
    int arg0, arg1;

    if (isNumber(arguments[0])) {
        arg0 = stoi(arguments[0]);
    } else {
        if (contains(values, arguments[0])) {
            arg0 = values[arguments[0]];
        } else {
            return false;
        }
    }

    if (isNumber(arguments[1])) {
        arg1 = stoi(arguments[1]);
    } else {
        if (contains(values, arguments[1])) {
            arg1 = values[arguments[1]];
        } else {
            return false;
        }
    }
    values[arguments[2]] = arg0 << arg1;
    return true;
}

bool parseInstructions(std::string input){
    if (input.find(OR) != std::string::npos) {
        return put_or(parseArguments(input));
    }
    else if (input.find(AND) != std::string::npos) {
        return put_and(parseArguments(input));
    }
    else if (input.find(NOT) != std::string::npos) {
        return put_not(parseArguments(input));
    }
    else if (input.find(LSHIFT) != std::string::npos) {
        return put_lshift(parseArguments(input));
    }
    else if (input.find(RSHIFT) != std::string::npos) {
        return put_rshift(parseArguments(input));
    }
    else{
        return put(parseArguments(input));
    }
}

std::vector<std::string> difference(std::vector<std::string> &v1,
                                      std::vector<std::string> &v2){
    std::vector<std::string> v3;

    std::sort(v1.begin(), v1.end());
    std::sort(v2.begin(), v2.end());

    std::set_difference(v1.begin(),v1.end(),
                          v2.begin(),v2.end(),
                          back_inserter(v3));
    return v3;
}


int main() {

    std::string line;
    std::ifstream data("../07/data.txt");
    std::vector<std::string> inputs;

    if (data.is_open())
    {
        while(getline(data, line))
        {
            inputs.push_back(line);
        }
        data.close();
    }

    while(!inputs.empty()){
        std::cout << inputs.size() << std::endl;
        std::vector<std::string> to_remove;
        for(auto const &input: inputs){
            if(parseInstructions(input)){
                to_remove.push_back(input);
            }
        }
        inputs = difference(inputs, to_remove);
        to_remove.clear();
    }
    cout << values["a"];
    return 0;
}
