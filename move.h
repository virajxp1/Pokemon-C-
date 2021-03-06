//
// Created by Viraj P on 5/18/2019.
//

#ifndef UNTITLED_MOVE_H
#define UNTITLED_MOVE_H
#include <iostream>
#include <vector>
using namespace std;

typedef enum type {Grass,Fire,Water,Electric,Poison,Normal,Flying,Ground,Fighting,Rock,Ghost,Dragon,Physic} Type;

class pkmn_move {
    int type;
    int power;
    int accuracy;
    int pp_MAX;
    int pp;
    string name;
    bool special;
public:
    pkmn_move(int t,int damage,string n,int acc, int num, bool sp);
    pkmn_move(int t,int damage,string n,int acc, int num);
    void print();
    void printSimple();

    int move_type(){return type;}
    int move_power(){return power;}
    int move_accuracy(){return accuracy;}
    int move_pp(){return pp;}
    void move_use() {pp--;}
    bool specialS(){return special;}

    string move_name(){return name;}
};

vector<vector<pkmn_move>> create_moves();
void delay(int p);

#endif //UNTITLED_MOVE_H
