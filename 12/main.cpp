#include <fstream>
#include <regex>
#include <iostream>
#include <algorithm>
#include "json.h"

using nlohmann::json;
using std::cout;

template<class T>
int recursive_sum(T iterable){
    int sum = 0;
    for(auto &it : iterable) {
        if(it.is_object()){
            sum += recursive_sum(it);
        }
        if(it.is_array()){
            sum += recursive_sum(it);
        }
        if(it.is_number()){
            sum += (int)it;
        }
    }
    return sum;
}

template<class T>
int recursive_sum_no_red(T iterable){
    int sum = 0;
    for(auto &it : iterable) {
        if(it.is_object()){
            bool skip = false;
            for (auto element = it.begin(); element != it.end(); ++element)
            {
                if(element.value().is_string()) {
                    if(element.value() == "red"){
                        skip = true;
                    }
                }
            }
            if(!skip){
                sum += recursive_sum_no_red(it);
            }
        }
        if(it.is_array()){
            sum += recursive_sum_no_red(it);
        }
        if(it.is_number()){
            sum += (int)it;
        }
    }
    return sum;
}

int main(){

    std::ifstream input("../12/data.json");
    json input_json;
    input >> input_json;

    cout << recursive_sum(input_json) << "\n";
    cout << recursive_sum_no_red(input_json) << "\n";

}



