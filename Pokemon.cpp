//
// Created by Viraj P on 5/18/2019.
//

#include "Pokemon.h"


Pokemon :: Pokemon(string& pkmn, pkmn_move& move1, pkmn_move& move2, pkmn_move& move3, pkmn_move& move4, int _type, int _type2) {
    moves.push_back(move1);
    moves.push_back(move2);
    moves.push_back(move3);
    moves.push_back(move4);
    name = pkmn;
    type = _type;
    type2 = _type2;
}
