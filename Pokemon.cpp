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
    level = (rand()%30) +70;
}

void Pokemon ::printDetails() {
    cout<<"Level " << level<< " " << name<<endl;
    this->printMoves();
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
    else if(type == Ghost)
        cout<<"Ghost";
    else if(type == Fighting)
        cout<<"Fighting";
    else if(type == Dragon)
        cout<<"Dragon";
    else if(type == Ground)
        cout<<"Ground";
    else if(type == Physic)
        cout<<"Psychic";
    else if(type == Rock)
        cout<<"Rock";

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
        else if(type2 == Ghost)
            cout<<"Ghost";
        else if(type2 == Fighting)
            cout<<"Fighting";
        else if(type2 == Dragon)
            cout<<"Dragon";
        else if(type2 == Ground)
            cout<<"Ground";
        else if(type2 == Physic)
            cout<<"Psychic";
        else if(type2 == Rock)
            cout<<"Rock";
    }
    cout<<endl;
    cout<<"Health: "<<health<<"/"<<Base_health<<endl;
    cout<<"Stats:"<<"\nAttack:"<<Base_attack<<"\nDefence:" << Base_defence<< "\nSpecial Attack:"<<Base_SPattack<< "\nSpecial Defence:" <<Base_SPdefence<<"\nSpeed:"<<Base_Speed<<endl;
}

void Pokemon :: printSimple() {
    cout<<"Level " << level<< " " << name<<endl;
    this->printMoves();
    cout<<"Health: "<<health<<"/"<<Base_health<<endl;
}

void Pokemon ::printMoves() {
    for(int i = 0;i<4;i++){
        moves[i].print();
    }
}
bool choose_pokemon(Pokemon& mypkmn){
    cout<<"Choose your Pokemon: \n";
    cout<<"1. Venusaur"<<
          " 2. Charizard" <<
          " 3. Blastoise" <<
          " 4. Pikachu" <<
          " 5. Pidgeot" << endl<<
          "6. Nidoking" <<
          " 7. Nidoqueen" <<
          " 8. Machamp" <<
          " 9. Golem" <<
          " 10. Muk" << endl<<
          "11. Gengar" <<
          " 12. Alakazam" <<
          " 13. Snorlax" <<
          " 14. Dragonite" <<
          " 15. Mewtwo" << endl;
    string name;
    cin>>name;
    for(int i = 0; i<name.length();i++){
        if(islower(name[i])){
            name[i] = toupper(name[i]);
        }
    }
    if(name == "CHARIZARD" || name == "2"){
        cout<<"You Chose Charizard" << endl;
        vector<pkmn_move> possibleMoves{pkmn_move(Fire,40,"Ember",100,40,true),
                                        pkmn_move(Fire,105,"Heat Wave",85,10,true),
                                        pkmn_move(Fire,90,"Flamethrower",100,20,true),
                                        pkmn_move(Fire,65,"Fire Spin",85,25,true),
                                        pkmn_move(Fire,75,"Fire Punch",85,20),
                                        pkmn_move(Flying,60,"Wing Attack",100,25),
                                        pkmn_move(Normal,40,"Tackle",100,35),
                                        pkmn_move(Normal,70,"Slash",100,25),
                                        pkmn_move(Dragon,60,"Dragon Tail",90,30)};
        vector<pkmn_move> moves_set;
        for(int i = 0;i<4;i++){
            int r = rand() % possibleMoves.size();
            moves_set.push_back(possibleMoves [r]);
            possibleMoves.erase(possibleMoves.begin()+r);
        }
        Pokemon Charizard("Charizard",moves_set,Fire,Flying,rand()%94+266,rand()%138+155,rand()%136+144,rand()%148+200,rand()%138+157,rand()%144+184);
        mypkmn = Charizard;
        return true;
    }
    else if(name == "BLASTOISE" || name == "3"){
        cout<<"You Choose Blastoise" << endl;
        vector<pkmn_move> possibleMoves{pkmn_move(Water,45,"Bubble Gun",100,45,true),
                                        pkmn_move(Water,50,"Water Gun",100,45,true),
                                        pkmn_move(Water,80,"Surf",90,25),
                                        pkmn_move(Water,120,"Hydro Pump",70,10,true),
                                        pkmn_move(Water,80,"Scald",100,15,true),
                                        pkmn_move(Normal,85,"Skull Bash",90,20),
                                        pkmn_move(Normal,40,"Tackle",100,35),
                                        pkmn_move(Dragon,120,"Outrage",60,10,true)
                                        };

        vector<pkmn_move> moves_set;
        for(int i = 0;i<4;i++){
            int r = rand() % possibleMoves.size();
            moves_set.push_back(possibleMoves[r]);
            possibleMoves.erase(possibleMoves.begin()+r);
        }
        Pokemon Blastoise("Blastoise",moves_set,Water,-1,rand()%94+268,rand()%138+153,rand()%144+184,rand()%138+157,rand()%146+193,rand()%136+144);
        mypkmn = Blastoise;
        return true;
    }
    else if(name == "VENUSAUR" || name == "1"){
        cout<<"You Choose Venusaur" << endl;
        vector<pkmn_move> possibleMoves{pkmn_move(Grass,45,"Vine Whip",100,30),
                                        pkmn_move(Grass,55,"Razor Leaf",100,20),
                                        pkmn_move(Grass,120,"Solar Beam",50,10),
                                        pkmn_move(Grass,95,"Power Whip",85,15),
                                        pkmn_move(Grass,100,"Petal Dance",100,5),
                                        pkmn_move(Poison,90,"Sludge Bomb",100,25),
                                        pkmn_move(Dragon,120,"Outrage",60,10),
                                        pkmn_move(Ground,100,"Earthquake",85,10),
                                        pkmn_move(Poison,30,"Poison Sting",100,35)};

        vector<pkmn_move> moves_set;
        for(int i = 0;i<4;i++){
            int r = rand() % possibleMoves.size();
            moves_set.push_back(possibleMoves[r]);
            possibleMoves.erase(possibleMoves.begin()+r);
        }
        Pokemon Venusaur("Venusaur",moves_set,Grass,Poison,rand()%94+270,rand()%137+152,rand()%138+153,rand()%144+184,rand()%144+184,rand()%136+148);
        mypkmn = Venusaur;
        return true;
    }
    else if(name == "PIKACHU" || name =="4"){
        cout<<"You Choose Pikachu" << endl;
        vector<pkmn_move> possibleMoves{pkmn_move(Electric,75,"Thunder Punch",85,20),
                                        pkmn_move(Electric,40,"Thunder Shock",100,30),
                                        pkmn_move(Electric,90,"Thunderbolt",100,20),
                                        pkmn_move(Electric,120,"Thunder",70,10),
                                        pkmn_move(Normal,70,"Headbutt",100,20),
                                        pkmn_move(Fighting,75,"Brick Break",100,15),
                                        pkmn_move(Fighting,85,"Seismic Toss",100,10),
                                        pkmn_move(Ghost,80,"Shadow Ball",100,20)};
        vector<pkmn_move> moves_set;
        for(int i = 0;i<4;i++){
            int r = rand() % possibleMoves.size();
            moves_set.push_back(possibleMoves[r]);
            possibleMoves.erase(possibleMoves.begin()+r);
        }
        Pokemon Pikachu("Pikachu",moves_set,Electric,-1,rand()%84+205,rand()%100+290,rand()%144+90,rand()%94+290,rand()%144+80,rand()%144+250);
        mypkmn = Pikachu;
        return true;
    }
    else if(name == "PIGEOT" || name == "5"){
        cout<<"You Choose Pigeot" << endl;
        vector<pkmn_move> possibleMoves{pkmn_move(Flying,60,"Wing Attack",100,25),
                                        pkmn_move(Flying,75,"Air Slash",95,20),
                                        pkmn_move(Flying,40,"Gust",100,30),
                                        pkmn_move(Flying,140,"Sky Attack",70,5),
                                        pkmn_move(Fire,105,"Heat Wave",85,10),
                                        pkmn_move(Normal,70,"Headbutt",100,20),
                                        pkmn_move(Normal,150,"Hyper Beam",50,5)};
        vector<pkmn_move> moves_set;
        for(int i = 0;i<4;i++){
            int r = rand() % possibleMoves.size();
            moves_set.push_back(possibleMoves[r]);
            possibleMoves.erase(possibleMoves.begin()+r);
        }
        Pokemon Pigeot("Pigeot",moves_set,Flying,Normal,rand()%94+276,rand()%136+148,rand()%134+139,rand()%132+130,rand()%132+130,rand()%145+186);
        mypkmn = Pigeot;
        return true;
    }
    else if(name == "NIDOKING"){

    }
    else if(name == "NIDOQUEEN"){

    }
    else if(name == "MACHAMP"){

    }
    else if(name == "GOLEM"){

    }
    else if(name == "MUK"){

    }
    else if(name == "GENGAR"){

    }
    else if(name == "ALAKAZAM"){

    }
    else if(name == "SNORLAX"){

    }
    else if(name == "DRAGONITE"){

    }
    else if(name == "MEWTWO"){

    }
    else{
        cout<<"Sorry that is not a valid input try again" << endl;
        return false;
    }
}