//
// Created by Viraj P on 5/18/2019.
//

#ifndef UNTITLED_POKEMON_H
#define UNTITLED_POKEMON_H

#include <vector>
#include "move.h"

class Pokemon {
    string name;
    int type;
    int type2;
    int level;
    int Base_health;
    int Base_attack;
    int Base_defence;
    int Base_SPattack;
    int Base_SPdefence;
    int Base_Speed;
    int health;
    int pokedex;

public:
    vector <pkmn_move> moves;
    Pokemon(){}
    Pokemon(string pkmn, vector<pkmn_move>& move_set, int _type, int _type2,int HP,int Atk, int Def, int SPa, int SPdf, int Spd,int pkdx);
    void printDetails();
    void printSimple();
    void printSimple_();
    void printCPU();
    void printMoves();
    void printMovesSimple();
    void damage(int d){health -= d;}
    string pkmn_name() {return name;}
    int pkmn_type(){return type;}
    int pkmn_type2() {return type2;}
    int pkmn_level(){return level;}
    int pkmn_attack(){return Base_attack;}
    int pkmn_spattack(){return Base_SPattack;}
    int pkmn_defence(){return Base_defence;}
    int pkmn_spdefence(){return Base_SPdefence;}
    int speed(){return Base_Speed;}
    int pkdx(){return pokedex;}
    int health_() {return health;}
};

bool choose_pokemon(Pokemon& mypkmn);
bool CPU_choosePkmn(Pokemon& CpuPkmn, int mytype);
Pokemon pkmn_generate(string name);

bool type_advantage(int type1,int type2);
bool type_disadvantage(int type1,int type2);
bool type_noeffect(int type1,int type2);


#endif //UNTITLED_POKEMON_H
