#include <tuple>
#include <vector>
#include <iostream>
#include <algorithm>

using std::tuple;
using std::vector;
using std::cout;
using std::max;

typedef vector<vector<int>> combination;

int boss_health = 104;
int boss_armor = 1;
int boss_damage = 8;
int player_health = 100;

bool simulate(int p_dmg, int p_arm, int p_hth, int b_dmg, int b_arm, int b_hth){
    while(p_hth > 0 && b_hth >0){
        b_hth -= max(1, p_dmg - b_arm);
        if(b_hth<=0){
            return true;
        }
        p_hth -= max(1, b_dmg - p_arm);
        if(p_hth<=0){
            return false;
        }
    }
    return false;
}

int main() {
    combination weapons = {{4, 8},
                           {5, 10},
                           {6, 25},
                           {7, 40},
                           {8, 74}};
    combination rings = {{1, 0, 25},
                         {2, 0, 50},
                         {3, 0, 100},
                         {0, 1, 20},
                         {0, 2, 40},
                         {0, 3, 80}};
    combination armors = {{0, 0},
                          {1, 13},
                          {2, 31},
                          {3, 53},
                          {4, 75},
                          {5, 102}};

    combination wins;
    combination loses;
    for (auto weapon: weapons) {
        for (auto armor: armors) {
            int dmg = weapon[0];
            int def = armor[0];
            int cost = weapon[1] + armor[1];
            if (simulate(dmg, def, player_health, boss_damage, boss_armor, boss_health)) {
                wins.push_back({dmg, def, cost});
            }
            else{
                loses.push_back({dmg, def, cost});
            }
            for (auto ring: rings) {
                int dmg_1r = dmg + ring[0];
                int def_1r = def + ring[1];
                int cost_1r = cost + ring[2];
                if (simulate(dmg_1r, def_1r, player_health, boss_damage, boss_armor, boss_health)) {
                    wins.push_back({dmg_1r, def_1r, cost_1r});
                }
                else{
                    loses.push_back({dmg_1r, def_1r, cost_1r});
                }
            }
            for (int idx = 0; idx < rings.size() - 2; idx++) {
                for (int idx2 = idx + 1; idx2 < rings.size() - 1; idx2++) {
                    int dmg_2r = dmg + rings[idx][0] + rings[idx2][0];
                    int def_2r = def + rings[idx][1] + rings[idx2][1];
                    int cost_2r = cost + rings[idx][2] + rings[idx2][2];
                    if (simulate(dmg_2r, def_2r, player_health, boss_damage, boss_armor, boss_health)) {
                        wins.push_back({dmg_2r, def_2r, cost_2r});
                    }
                    else{
                        loses.push_back({dmg_2r, def_2r, cost_2r});
                    }
                }
            }
        }
    }
    int min_cost = INT32_MAX;
    int max_cost = 0;
    for (auto win: wins) {
        if (win[2] < min_cost) {
            min_cost = win[2];
        }
    }
    for (auto loss: loses){
        if (loss[2] > max_cost){
            max_cost = loss[2];
        }
    }
    cout << "Task 01: " << min_cost << std::endl;
    cout << "Task 02: " << max_cost << std::endl;
}
