//
// Created by Viraj P on 5/18/2019.
//

#include "move.h"

pkmn_move:: pkmn_move(int t, int damage, string n,int acc, int num){
    type = t; power = damage; name = n; accuracy = acc; pp = num;
    if(accuracy >100) {abort();}
}

vector<vector<pkmn_move>> create_moves(){
    vector<pkmn_move> grass;
    vector<pkmn_move> fire;
    vector<pkmn_move> water;
    vector<pkmn_move> electric;
    vector<pkmn_move> poison;
    vector<pkmn_move> normal;
    vector<pkmn_move> flying;


    //Grass type moves
    grass.push_back(pkmn_move(Grass,45,"Vine Whip",100,30));
    grass.push_back(pkmn_move(Grass,55,"Razor Leaf",100,20));
    grass.push_back(pkmn_move(Grass,120,"Solar Beam",50,10));
    grass.push_back(pkmn_move(Grass,95,"Power Whip",85,15));
    grass.push_back(pkmn_move(Grass,100,"Petal Dance",100,5));

    //Fire type moves
    fire.push_back(pkmn_move(Fire,40,"Ember",100,40));
    fire.push_back(pkmn_move(Fire,105,"Heat Wave",85,10));
    fire.push_back(pkmn_move(Fire,90,"Flamethrower",100,20));
    fire.push_back(pkmn_move(Fire,65,"Fire Spin",85,25));
    fire.push_back(pkmn_move(Fire,75,"Fire Punch",85,20));


    //Water type moves

    //Electric type moves
    electric.push_back(pkmn_move(Electric,75,"Thunder Punch",85,20));


    //Flying type moves
    flying.push_back(pkmn_move(Flying,60,"Wing Attack",100,25));
    flying.push_back(pkmn_move(Flying,60,"Wing Attack",100,25));

    //Normal type moves
    normal.push_back(pkmn_move(Normal,40,"Scratch",100,35));
    normal.push_back(pkmn_move(Normal,40,"Tackle",100,35));
    normal.push_back(pkmn_move(Normal,70,"Slash",100,25));
    normal.push_back(pkmn_move(Normal,70,"Headbutt",100,20));







    vector<vector<pkmn_move>> move_table;
    move_table[Grass] = grass;
    move_table[Fire] = fire;
    move_table[Water] = water;
    move_table[Electric] = electric;
    move_table[Normal] = normal;
    move_table[Flying] = flying;
    move_table[Poison] = poison;

}


/*
 * Create a table of all the moves sorted by type
 * when creating a pokemon with select moves that i want
 *
 */