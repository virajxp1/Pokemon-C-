//
// Created by Viraj P on 5/18/2019.
//

#include "move.h"

pkmn_move:: pkmn_move(int t, int damage, string n,int acc, int num){
    type = t; power = damage; name = n; accuracy = acc; pp_MAX = num; pp = num;
    if(accuracy >100) {abort();}
    special = false;
}
pkmn_move:: pkmn_move(int t, int damage, string n,int acc, int num, bool sp){
    type = t; power = damage; name = n; accuracy = acc; pp = num; pp_MAX = num;
    if(accuracy >100) {abort();}
    special = sp;
}

void pkmn_move::print() {
    if(type == Fire)
        cout<<"(Fire) "<<name<<" Base Damage: " << power<<" Accuracy: " << accuracy << " PP: "<< pp<<"/"<<pp_MAX<< endl;
    else if(type == Water)
        cout<<"(Water) "<<name<<" Base Damage: " << power<<" Accuracy: " << accuracy << " PP: "<< pp<<"/"<<pp_MAX<< endl;
    else if(type == Flying)
        cout<<"(Flying) "<<name<<" Base Damage: " << power<<" Accuracy: " << accuracy << " PP: "<< pp<<"/"<<pp_MAX<< endl;
    else if(type == Grass)
        cout<<"(Grass) "<<name<<" Base Damage: " << power<<" Accuracy: " << accuracy << " PP: "<< pp<<"/"<<pp_MAX<< endl;
    else if(type == Poison)
        cout<<"(Poison) "<<name<<" Base Damage: " << power<<" Accuracy: " << accuracy << " PP: "<< pp<<"/"<<pp_MAX<< endl;
    else if(type == Electric)
        cout<<"(Electric) "<<name<<" Base Damage: " << power<<" Accuracy: " << accuracy << " PP: "<< pp<<"/"<<pp_MAX<< endl;
    else if(type == Normal)
        cout<<"(Normal) "<<name<<" Base Damage: " << power<<" Accuracy: " << accuracy << " PP: "<< pp<<"/"<<pp_MAX<< endl;
    else if(type == Dragon)
        cout<<"(Dragon) "<<name<<" Base Damage: " << power<<" Accuracy: " << accuracy << " PP: "<< pp<<"/"<<pp_MAX<< endl;
    else if(type == Ghost)
        cout<<"(Ghost) "<<name<<" Base Damage: " << power<<" Accuracy: " << accuracy << " PP: "<< pp<<"/"<<pp_MAX<< endl;
    else if(type == Rock)
        cout<<"(Rock) "<<name<<" Base Damage: " << power<<" Accuracy: " << accuracy << " PP: "<< pp<<"/"<<pp_MAX<< endl;
    else if(type == Fighting)
        cout<<"(Fighting) "<<name<<" Base Damage: " << power<<" Accuracy: " << accuracy << " PP: "<< pp<<"/"<<pp_MAX<< endl;
    else if(type == Ground)
        cout<<"(Ground) "<<name<<" Base Damage: " << power<<" Accuracy: " << accuracy << " PP: "<< pp<<"/"<<pp_MAX<< endl;
    else if(type == Physic)
        cout<<"(Psychic) "<<name<<" Base Damage: " << power<<" Accuracy: " << accuracy << " PP: "<< pp<<"/"<<pp_MAX<< endl;
}

vector<vector<pkmn_move>> create_moves(){
    vector<pkmn_move> grass;
    vector<pkmn_move> fire;
    vector<pkmn_move> water;
    vector<pkmn_move> electric;
    vector<pkmn_move> poison;
    vector<pkmn_move> normal;
    vector<pkmn_move> flying;
    vector<pkmn_move> rock;//
    vector<pkmn_move> ground;//
    vector<pkmn_move> ghost;//
    vector<pkmn_move> physic;//
    vector<pkmn_move> fighting;//
    vector<pkmn_move> dragon;//

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
    water.push_back(pkmn_move(Water,45,"Bubble Gun",100,45));
    water.push_back(pkmn_move(Water,50,"Water Gun",100,45));
    water.push_back(pkmn_move(Water,80,"Surf",90,25));
    water.push_back(pkmn_move(Water,120,"Hydro Pump",70,10));
    water.push_back(pkmn_move(Water,80,"Scald",100,15));

    //Electric type moves
    electric.push_back(pkmn_move(Electric,75,"Thunder Punch",85,20));
    electric.push_back(pkmn_move(Electric,40,"Thunder Shock",100,30));
    electric.push_back(pkmn_move(Electric,90,"Thunderbolt",100,20));
    electric.push_back(pkmn_move(Electric,120,"Thunder",70,10));

    //Flying type moves
    flying.push_back(pkmn_move(Flying,60,"Wing Attack",100,25));
    flying.push_back(pkmn_move(Flying,75,"Air Slash",95,20));
    flying.push_back(pkmn_move(Flying,40,"Gust",100,30));
    flying.push_back(pkmn_move(Flying,140,"Sky Attack",70,5));

    //Normal type moves
    normal.push_back(pkmn_move(Normal,40,"Scratch",100,35));
    normal.push_back(pkmn_move(Normal,40,"Tackle",100,35));
    normal.push_back(pkmn_move(Normal,70,"Slash",100,25));
    normal.push_back(pkmn_move(Normal,70,"Headbutt",100,20));
    normal.push_back(pkmn_move(Normal,85,"Skull Bash",90,20));
    normal.push_back(pkmn_move(Normal,150,"Hyper Beam",50,5));
    normal.push_back(pkmn_move(Normal,120,"Thrash",60,5));

    //Poison type moves
    poison.push_back(pkmn_move(Poison,90,"Sludge Bomb",100,25));
    poison.push_back(pkmn_move(Poison,30,"Poison Sting",100,35));
    poison.push_back(pkmn_move(Poison,80,"Poison Jab",100,25));

    //Fighting type moves
    fighting.push_back(pkmn_move(Fighting,85,"Seismic Toss",100,10));
    fighting.push_back(pkmn_move(Fighting,75,"Brick Break",100,15));
    fighting.push_back(pkmn_move(Fighting,120,"Superpower",80,5));
    fighting.push_back(pkmn_move(Fighting,30,"Low Kick",95,35));
    fighting.push_back(pkmn_move(Fighting,50,"Karate Chop",100,30));

    //Ghost type moves
    ghost.push_back(pkmn_move(Ghost,30,"Lick",100,30));
    ghost.push_back(pkmn_move(Ghost,70,"Night Shade",95,25));
    ghost.push_back(pkmn_move(Ghost,80,"Shadow Ball",100,20));

    //Rock type moves
    rock.push_back(pkmn_move(Rock,75,"Rock Slide",90,15));
    rock.push_back(pkmn_move(Rock,50,"Rock Throw",90,25));

    //Dragon type moves
    dragon.push_back(pkmn_move(Dragon,60,"Dragon Tail",90,30));
    dragon.push_back(pkmn_move(Dragon,120,"Outrage",60,10));
    dragon.push_back(pkmn_move(Dragon,85,"Dragon Pulse",90,15));
    dragon.push_back(pkmn_move(Dragon,45,"Dragon Rage",90,15));


    //Ground type moves
    ground.push_back(pkmn_move(Ground,100,"Earthquake",85,10));
    ground.push_back(pkmn_move(Ground,80,"Drill Run",80,10));

    //Physic type moves
    physic.push_back(pkmn_move(Physic,50,"Confusion",100,35));
    physic.push_back(pkmn_move(Physic,65,"Psybeam",100,30));
    physic.push_back(pkmn_move(Physic,70,"Psyshock",100,25));
    physic.push_back(pkmn_move(Physic,70,"Psychic",100,25));




    vector<vector<pkmn_move>> move_table;
    move_table[Grass] = grass;
    move_table[Fire] = fire;
    move_table[Water] = water;
    move_table[Electric] = electric;
    move_table[Normal] = normal;
    move_table[Flying] = flying;
    move_table[Poison] = poison;
    return move_table;
}

void delay(int p){
    int i = p;
    while (i!=0){
        i--;
    }
}

/*
 * Create a table of all the moves sorted by type
 * when creating a pokemon with select moves that i want
 */