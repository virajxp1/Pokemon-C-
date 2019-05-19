//
// Created by Viraj P on 5/18/2019.
//

#include "Pokemon.h"

Pokemon :: Pokemon(string pkmn, vector<pkmn_move>& move_set, int _type, int _type2,int HP,int Atk, int Def, int SPa, int SPdf, int Spd) {
    moves = move_set;
    name = pkmn;
    type = _type;
    type2 = _type2;
    Base_health = HP;
    health = HP;
    Base_attack = Atk;
    Base_defence = Def;
    Base_SPattack = SPa;
    Base_SPdefence = SPdf;
    Base_Speed = Spd;
}

void Pokemon ::printDetails() {
    cout<<name<<endl;
    for(int i = 0;i<4;i++){
        moves[i].print();
    }
    cout<<"Type: ";
    if(type == Fire)
        cout<<"Fire";
    else if(type == Water)
        cout<<"Water";
    else if(type == Flying)
        cout<<"Flying";
    else if(type == Grass)
        cout<<"Grass";
    else if(type == Poison)
        cout<<"Poison";
    else if(type == Electric)
        cout<<"Electric";
    else if(type == Normal)
        cout<<"Normal";
    if(type2 != -1){
        cout<<", ";
        if(type2 == Fire)
            cout<<"Fire";
        else if(type2 == Water)
            cout<<"Water";
        else if(type2 == Flying)
            cout<<"Flying";
        else if(type2 == Grass)
            cout<<"Grass";
        else if(type2 == Poison)
            cout<<"Poison";
        else if(type2 == Electric)
            cout<<"Electric";
        else if(type2 == Normal)
            cout<<"Normal";
    }
    cout<<endl;
    cout<<"Health: "<<health<<"/"<<Base_health<<endl;
    cout<<"Stats:"<<"\nAttack:"<<Base_attack<<"\nDefence:" << Base_defence<< "\nSpecial Attack:"<<Base_SPattack<< "\nSpecial Defence:" <<Base_SPdefence<<"\nSpeed:"<<Base_Speed<<endl;
}

bool choose_pokemon(Pokemon& mypkmn){
    cout<<"Choose your Pokemon: \n";
    cout<<"1. Venusaur"<< endl <<
          "2. Charizard" << endl<<
          "3. Blastoise" << endl<<
          "4. Pikachu" << endl;
    string name;
    //cin>>name;
    name = "CHARIZARD";
    for(int i = 0; i<name.length();i++){
        if(islower(name[i])){
            name[i] = toupper(name[i]);
        }
    }
    if(name == "CHARIZARD"){
        cout<<"You Chose Charizard" << endl;
        vector<pkmn_move> possibleMoves{pkmn_move(Fire,40,"Ember",100,40,true),
                                        pkmn_move(Fire,105,"Heat Wave",85,10,true),
                                        pkmn_move(Fire,90,"Flamethrower",100,20,true),
                                        pkmn_move(Fire,65,"Fire Spin",85,25,true),
                                        pkmn_move(Fire,75,"Fire Punch",85,20),
                                        pkmn_move(Flying,60,"Wing Attack",100,25),
                                        pkmn_move(Normal,40,"Tackle",100,35),
                                        pkmn_move(Normal,70,"Slash",100,25)};
        vector<pkmn_move> moves_set;
        //moves_set.push_back(possibleMoves[0]);
        for(int i = 0;i<4;i++){
            int r = rand() % possibleMoves.size();
            moves_set.push_back(possibleMoves [r]);
            possibleMoves.erase(possibleMoves.begin()+r);
        }
        Pokemon Charizard("Charizard",moves_set,Fire,Flying,rand()%94+266,rand()%138+155,rand()%136+144,rand()%148+200,rand()%138+157,rand()%144+184);
        Charizard.printDetails();
        mypkmn = Charizard;
        return true;
    }
    else{
        cout<<"Sorry that is not a valid input try again" << endl;
        return false;
    }
}