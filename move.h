//
// Created by Viraj P on 5/18/2019.
//

#ifndef UNTITLED_MOVE_H
#define UNTITLED_MOVE_H
#include <iostream>
#include <vector>
using namespace std;

typedef enum type {Grass,Fire,Water,Electric,Poison,Normal,Flying} Type;

class pkmn_move {
    int type;
    int power;
    int accuracy;
    int pp;
    string name;
public:
    pkmn_move(int t,int damage,string n,int acc, int num);
    int move_type(){return type;}
    int move_power(){return power;}
    int move_accuracy(){return accuracy;}
    int move_pp(){return pp;}
    void move_use() {pp--;}
    string move_name(){return name;}
};

vector<vector<pkmn_move>> create_moves();

#endif //UNTITLED_MOVE_H
