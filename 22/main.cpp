#include <tuple>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include "main.h"

using std::tuple;
using std::vector;
using std::cout;
using std::max;
using std::unordered_map;

void do_effects(player_status &p_stat, boss_status &b_stat){
    if (p_stat.status.find(poison) != p_stat.status.end()){
        b_stat.health -= 3;
        p_stat.status[poison] -= 1;
        if (p_stat.status[poison] <= 0){
            p_stat.status.erase(poison);
        }
    }
    if (p_stat.status.find(recharge) != p_stat.status.end()){
        p_stat.mana += 101;
        p_stat.status[recharge] -= 1;
        if (p_stat.status[recharge] <= 0){
            p_stat.status.erase(recharge);
        }
    }
    if (p_stat.status.find(shield) != p_stat.status.end()){
        p_stat.armor = 7;
        p_stat.status[shield] -= 1;
        if (p_stat.status[shield] <= 0){
            p_stat.status.erase(shield);
        }
    }
    else{
        p_stat.armor = 0;
    }
}

void cast_magic_missile(player_status p_stat, boss_status b_stat, vector<int> &wins, bool hard){
    if (hard){
        p_stat.health -= 1;
        if(p_stat.health <= 0){
            return;
        }
    }
    if (p_stat.mana >= 53){
        p_stat.mana_spent += 53;
        p_stat.mana -= 53;
        b_stat.health -= 4;
        do_effects(p_stat, b_stat);
        if(b_stat.health <= 0){
            wins.push_back(p_stat.mana_spent);
            return;
        }
        p_stat.health -= max(1, b_stat.damage - p_stat.armor);
        if(p_stat.health <= 0){
            return;
        }
        do_effects(p_stat, b_stat);
        if(b_stat.health <= 0){
            wins.push_back(p_stat.mana_spent);
            return;
        }
        simulate(p_stat, b_stat, wins, hard);
    }
}

void cast_drain(player_status p_stat, boss_status b_stat, vector<int> &wins, bool hard) {
    if (hard){
        p_stat.health -= 1;
        if(p_stat.health <= 0){
            return;
        }
    }
    if (p_stat.mana >= 73){
        p_stat.mana_spent += 73;
        p_stat.mana -= 73;
        b_stat.health -= 2;
        p_stat.health += 2;
        do_effects(p_stat, b_stat);
        if(b_stat.health <= 0){
            wins.push_back(p_stat.mana_spent);
            return;
        }
        p_stat.health -= max(1, b_stat.damage - p_stat.armor);
        if(p_stat.health <= 0){
            return;
        }
        do_effects(p_stat, b_stat);
        if(b_stat.health <= 0){
            wins.push_back(p_stat.mana_spent);
            return;
        }
        simulate(p_stat, b_stat, wins, hard);
    }
}

void cast_shield(player_status p_stat, boss_status b_stat, vector<int> &wins, bool hard) {
    if (hard){
        p_stat.health -= 1;
        if(p_stat.health <= 0){
            return;
        }
    }
    if (p_stat.status.find(shield) != p_stat.status.end()){
        return;
    }
    if (p_stat.mana >= 113){
        p_stat.mana_spent += 113;
        p_stat.mana -= 113;
        p_stat.status[shield] = 6;
        do_effects(p_stat, b_stat);
        if(b_stat.health <= 0){
            wins.push_back(p_stat.mana_spent);
            return;
        }
        p_stat.health -= max(1, b_stat.damage - p_stat.armor);
        if(p_stat.health <= 0){
            return;
        }
        do_effects(p_stat, b_stat);
        if(b_stat.health <= 0){
            wins.push_back(p_stat.mana_spent);
            return;
        }
        simulate(p_stat, b_stat, wins, hard);
    }
}

void cast_poison(player_status p_stat, boss_status b_stat, vector<int> &wins, bool hard) {
    if (hard){
        p_stat.health -= 1;
        if(p_stat.health <= 0){
            return;
        }
    }
    if (p_stat.status.find(poison) != p_stat.status.end()){
        return;
    }
    if (p_stat.mana >= 173){
        p_stat.mana_spent += 173;
        p_stat.mana -= 173;
        p_stat.status[poison] = 6;
        do_effects(p_stat, b_stat);
        if(b_stat.health <= 0){
            wins.push_back(p_stat.mana_spent);
            return;
        }
        p_stat.health -= max(1, b_stat.damage - p_stat.armor);
        if(p_stat.health <= 0){
            return;
        }
        do_effects(p_stat, b_stat);
        if(b_stat.health <= 0){
            wins.push_back(p_stat.mana_spent);
            return;
        }
        simulate(p_stat, b_stat, wins, hard);
    }
}

void cast_recharge(player_status p_stat, boss_status b_stat, vector<int> &wins, bool hard) {
    if (hard){
        p_stat.health -= 1;
        if(p_stat.health <= 0){
            return;
        }
    }
    if (p_stat.status.find(recharge) != p_stat.status.end()){
        return;
    }
    if (p_stat.mana >= 229){
        p_stat.mana_spent += 229;
        p_stat.mana -= 229;
        p_stat.status[recharge] = 5;
        do_effects(p_stat, b_stat);
        if(b_stat.health <= 0){
            wins.push_back(p_stat.mana_spent);
            return;
        }
        p_stat.health -= max(1, b_stat.damage - p_stat.armor);
        if(p_stat.health <= 0){
            return;
        }
        do_effects(p_stat, b_stat);
        if(b_stat.health <= 0){
            wins.push_back(p_stat.mana_spent);
            return;
        }
        simulate(p_stat, b_stat, wins, hard);
    }
}

void simulate(player_status p_stat, boss_status b_stat, vector<int> &wins, bool hard){
    cast_magic_missile(p_stat, b_stat, wins, hard);
    cast_drain(p_stat, b_stat, wins, hard);
    cast_shield(p_stat, b_stat, wins, hard);
    cast_poison(p_stat, b_stat, wins, hard);
    cast_recharge(p_stat, b_stat, wins, hard);
}




int main() {
    int boss_health = 71;
    int boss_damage = 10;
    int player_health = 50;
    int player_mana = 500;

    player_status p_stat = {player_health, player_mana, 0, unordered_map<int,int>(),0};
    boss_status b_stat = {boss_health, boss_damage};
    vector<int> wins;
    simulate(p_stat, b_stat, wins, false);
    cout << "Task 01: " << *min_element(wins.begin(), wins.end()) << std::endl;

    wins.clear();
    simulate(p_stat, b_stat, wins, true);
    cout << "Task 02: " << *min_element(wins.begin(), wins.end()) << std::endl;
}