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

bool choose_pokemon(Pokemon& mypkmn){
    cout<<"Choose your Pokemon: \n";
    cout<<"1. Venusaur"<< endl <<
          "2. Charizard" << endl<<
          "3. Blastoise" << endl<<
          "4. Pikachu" << endl;
    string name;
    cin>>name;
    for(int i = 0; i<name.length();i++){
        if(islower(name[i])){
            name[i] = toupper(name[i]);
        }
    }
    if(name == "CHARIZARD"){
        cout<<"You Chose Charizard";
        return true;
    }
    else{
        cout<<"Sorry that is not a valid input try again" << endl;
        return false;
    }
}