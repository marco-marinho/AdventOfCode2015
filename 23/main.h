//
// Created by marco on 4/22/22.
//

#ifndef ADVENTOFCODE2015_MAIN_H
#define ADVENTOFCODE2015_MAIN_H

#include <vector>
#include <unordered_map>

using std::vector;
using std::unordered_map;

constexpr int ra_n = (int)(unsigned char)'a';
constexpr int rb_n = (int)(unsigned char)'b';

const unordered_map<char, int> reg_addr = {{'a', ra_n}, {'b', rb_n}};

struct cpu_state{
    unordered_map<int, long long> regs = {{ra_n, 0}, {rb_n, 0}};
    int ip = 0;
};

enum assembly{
    hlf,
    tpl,
    inc,
    jmp,
    jie,
    jio,
};

struct instruction{
    assembly ic;
    vector<int> args;
};


#endif //ADVENTOFCODE2015_MAIN_H
