#include <string>
#include <fstream>
#include <regex>
#include <iostream>
#include "main.h"


using std::string;
using std::cout;

vector<instruction> load_instructions(const string &path) {
    std::ifstream data(path);
    string line;
    vector<instruction> output;
    if (data.is_open()) {
        while (getline(data, line)) {
            string inst_str = line.substr(0, line.find(' '));
            line.erase(0, line.find(' ') + 1);
            if (inst_str == "hlf") {
                output.push_back({hlf, {reg_addr.at(line.at(0))}});
            }
            if (inst_str == "tpl") {
                output.push_back({tpl, {reg_addr.at(line.at(0))}});
            }
            if (inst_str == "inc") {
                output.push_back({inc, {reg_addr.at(line.at(0))}});
            }
            if (inst_str == "jmp") {
                output.push_back({jmp, {std::stoi(line)}});
            }
            if (inst_str == "jie") {
                string arg_str = line.substr(0, line.find(", "));
                int arg = reg_addr.at(arg_str.at(0));
                line.erase(0, line.find(", ") + 2);
                int arg_2 = std::stoi(line);
                output.push_back({jie, {arg, arg_2}});
            }
            if (inst_str == "jio") {
                string arg_str = line.substr(0, line.find(", "));
                int arg = reg_addr.at(arg_str.at(0));
                line.erase(0, line.find(", ") + 2);
                int arg_2 = std::stoi(line);
                output.push_back({jio, {arg, arg_2}});
            }
        }
    }
    return output;
}

void execute(cpu_state &state, instruction inst) {
    switch (inst.ic) {
        case hlf: {
            state.regs[inst.args[0]] /= 2;
            state.ip += 1;
            break;
        }
        case tpl: {
            state.regs[inst.args[0]] *= 3;
            state.ip += 1;
            break;
        }
        case inc: {
            state.regs[inst.args[0]] += 1;
            state.ip += 1;
            break;
        }
        case jmp: {
            state.ip += inst.args[0];
            break;
        }
        case jie: {

            state.ip += (state.regs[inst.args[0]] % 2) == 0 ? inst.args[1] : 1;
            break;
        }
        case jio: {
            state.ip += state.regs[inst.args[0]] == 1 ? inst.args[1] : 1;
            break;
        }
    }
}

int main() {
    vector<instruction> rom = load_instructions("data.txt");
    cpu_state state;
    while (state.ip < rom.size()) {
        execute(state, rom[state.ip]);
    }
    cout << "Tast 01: " << state.regs[rb_n] << std::endl;
    state.regs[ra_n] = 1;
    state.regs[rb_n] = 0;
    state.ip = 0;
    while (state.ip < rom.size()) {
        execute(state, rom[state.ip]);
    }
    cout << "Tast 02: " << state.regs[rb_n] << std::endl;
}
