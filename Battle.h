//
// Created by Viraj P on 5/20/2019.
//

#ifndef UNTITLED_BATTLE_H
#define UNTITLED_BATTLE_H

#include "Pokemon.h"
#include "move.h"

void Battle(Pokemon myPkmn, Pokemon cpuPkmn);
void BattleLoop(Pokemon& my, Pokemon& cpu);
void printMovenum(int n);
void print_pokemon(int n_pokemon);

#endif //UNTITLED_BATTLE_H
