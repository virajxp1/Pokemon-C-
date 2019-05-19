//
// Created by Viraj P on 5/18/2019.
//

#ifndef UNTITLED_POKEMON_H
#define UNTITLED_POKEMON_H

#include <vector>
#include "move.h"

class Pokemon {
    string name;
    vector <pkmn_move> moves;
    int type;
    int type2;
    int Base_health;
    int Base_attack;
    int Base_defence;
    int Base_SPattack;
    int Base_SPdefence;
    int Base_Speed;
    int health;

public:
    Pokemon(){}
    Pokemon(string pkmn, vector<pkmn_move>& move_set, int _type, int _type2,int HP,int Atk, int Def, int SPa, int SPdf, int Spd);
    void printDetails();
    void damage(int d){health -= d;}
};

bool choose_pokemon(Pokemon& mypkmn);




#endif //UNTITLED_POKEMON_H
