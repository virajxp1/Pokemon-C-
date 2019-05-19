//
// Created by Viraj P on 5/18/2019.
//

#include "move.h"

pkmn_move:: pkmn_move(int t, int damage, string n,int acc){
    type = t; base_damage = damage; name = n; accuracy = acc;
}

vector<vector<pkmn_move>> create_moves(){
    vector<pkmn_move> grass;
    vector<pkmn_move> fire;
    vector<pkmn_move> water;
    vector<pkmn_move> electric;

    grass.push_back(pkmn_move(Grass,45,"Vine Whip",100));
    grass.push_back(pkmn_move(Grass,55,"Razor Leaf",100));
    grass.push_back(pkmn_move(Grass,120,"Solar Beam",50));
    grass.push_back(pkmn_move(Grass,95,"Power Whip",85));


    vector<vector<pkmn_move>> move_table;
    move_table[Grass] = grass;
    move_table[Fire] = fire;
    move_table[Water] = water;
    move_table[Electric] = electric;
}


/*
 * Create a table of all the moves sorted by type
 * when creating a pokemon with select moves that i want
 *
 */