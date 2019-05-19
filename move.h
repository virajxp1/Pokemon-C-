//
// Created by Viraj P on 5/18/2019.
//

#ifndef UNTITLED_MOVE_H
#define UNTITLED_MOVE_H
#include <iostream>
#include <vector>
using namespace std;

typedef enum {Grass,Fire,Water,Electric,Poison,Normal,Flying};

class pkmn_move {
    int type;
    int power;
    int accuracy;
    int pp;
    string name;
public:
    pkmn_move(int t,int damage,string n,int acc, int num);
};

vector<vector<pkmn_move>> create_moves();

#endif //UNTITLED_MOVE_H
