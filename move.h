//
// Created by Viraj P on 5/18/2019.
//

#ifndef UNTITLED_MOVE_H
#define UNTITLED_MOVE_H
#include <iostream>
#include <vector>
using namespace std;

typedef enum {Grass,Fire,Water,Electric};

class pkmn_move {
    int type;
    int base_damage;
    int accuracy;
    string name;
public:
    pkmn_move(int t,int damage,string n,int acc);
};

vector<vector<pkmn_move>> create_moves();

#endif //UNTITLED_MOVE_H
