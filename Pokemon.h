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

    int health;
    int attack;
    int defence;

public:
    Pokemon(string& pkmn,pkmn_move& move1,pkmn_move& move2,pkmn_move& move3,pkmn_move& move4,int _type,int _type2);

};




#endif //UNTITLED_POKEMON_H