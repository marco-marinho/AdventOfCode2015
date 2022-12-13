//
// Created by marco on 4/21/22.
//

#ifndef ADVENTOFCODE2015_MAIN_H
#define ADVENTOFCODE2015_MAIN_H

#include <unordered_map>
#include <vector>

using std::unordered_map;
using std::vector;

typedef unordered_map<int, int> status_t;

struct player_status{
    int health;
    int mana;
    int armor;
    status_t status;
    int mana_spent;
};

struct boss_status{
    int health;
    int damage;
};

enum effects{
    poison,
    shield,
    recharge,
};

void do_effects(player_status &p_stat, boss_status &b_stat);

void simulate(player_status p_stat, boss_status b_stat, vector<int> &wins, bool hard);

#endif //ADVENTOFCODE2015_MAIN_H
