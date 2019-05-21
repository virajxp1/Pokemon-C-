//
// Created by Viraj P on 5/18/2019.
//

#include "Pokemon.h"

Pokemon :: Pokemon(string pkmn, vector<pkmn_move>& move_set, int _type, int _type2,int HP,int Atk, int Def, int SPa, int SPdf, int Spd,int pkdx) {
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
    pokedex = pkdx;
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
    int spaceTotal = 59;
    cout<<"---------------------------------------------------------------------------------"<<endl;
    cout<<"           Level " << level<< " " << name;
    for(int i = 0;i<spaceTotal-name.length();i++){
        cout<<" ";
    }
    cout<<endl;
    cout<<"           Health: "<<health<<"/"<<Base_health;
    for(int i = 0;i<spaceTotal-6;i++){
        cout<<" ";
    }
    cout<<endl;
    this->printMoves();
    cout<<"---------------------------------------------------------------------------------"<<endl;

}
void Pokemon ::printSimple_() {
    int spaceTotal = 59;
    cout<<"---------------------------------------------------------------------------------"<<endl;
    cout<<"           Level " << level<< " " << name;
    for(int i = 0;i<spaceTotal-name.length();i++){
        cout<<" ";
    }
    cout<<endl;
    cout<<"           Health: "<<health<<"/"<<Base_health;
    for(int i = 0;i<spaceTotal-6;i++){
        cout<<" ";
    }
    cout<<endl;
    this->printMovesSimple();
    cout<<"---------------------------------------------------------------------------------"<<endl;

}

void Pokemon ::printCPU() {
    int spaceTotal = 18;
    cout<<"----------------------------------------"<<endl;
    cout<<"|           Level " << level<< " " << name;
    for(int i = 0;i<spaceTotal-name.length();i++){
        cout<<" ";
    }
    cout<<"|"<<endl;
    cout<<"|           Health: "<<health<<"/"<<Base_health;
    for(int i = 0;i<spaceTotal-6;i++){
        cout<<" ";
    }
    cout<<"|"<<endl;
    cout<<"----------------------------------------"<<endl;
}

void Pokemon ::printMoves() {
    for(int i = 0;i<4;i++){
        cout<<"           ";
        moves[i].print();
        cout<<endl;
    }
}
void Pokemon ::printMovesSimple() {
    for(int i = 0;i<4;i++){
        cout<<"           ";
        moves[i].printSimple();
        cout<<endl;
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
          " 15. Mewtwo" << endl<<endl<<endl;
    string name;
    cin>>name;
    for(int i = 0; i<name.length();i++){
        if(islower(name[i])){
            name[i] = toupper(name[i]);
        }
    }
    mypkmn = pkmn_generate(name);
    if(mypkmn.pkmn_name() == "null") {
        return false;
    }
    else{
        cout<<"You Chose "<<mypkmn.pkmn_name()<<endl;
       return true;
    }
}

bool CPU_choosePkmn(Pokemon& CpuPkmn,int mytype){
    int generatorNum = rand()%100+1;
    string name = to_string(rand()%15 +1);
    CpuPkmn = pkmn_generate(name);
    //The cpu pokemon should only have a type disadvantage 10% of the time
    if(type_disadvantage(CpuPkmn.pkmn_type(),mytype)){
        return false;
    }
    else{
        cout<<"Your Opponent Chose "<<CpuPkmn.pkmn_name()<<endl;
        return true;
    }

}


Pokemon pkmn_generate(string name){
    if(name == "CHARIZARD" || name == "2"){
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
        Pokemon Charizard("Charizard",moves_set,Fire,Flying,rand()%94+266,rand()%138+155,rand()%136+144,rand()%148+200,rand()%138+157,rand()%144+184,6);
        return Charizard;
    }
    else if(name == "BLASTOISE" || name == "3"){
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
        Pokemon Blastoise("Blastoise",moves_set,Water,-1,rand()%94+268,rand()%138+153,rand()%144+184,rand()%138+157,rand()%146+193,rand()%136+144,9);
        return Blastoise;
    }
    else if(name == "VENUSAUR" || name == "1"){
        vector<pkmn_move> possibleMoves{pkmn_move(Grass,45,"Vine Whip",100,30),
                                        pkmn_move(Grass,55,"Razor Leaf",100,20,true),
                                        pkmn_move(Grass,120,"Solar Beam",70,10,true),
                                        pkmn_move(Grass,95,"Power Whip",85,15),
                                        pkmn_move(Grass,100,"Petal Dance",100,5,true),
                                        pkmn_move(Poison,90,"Sludge Bomb",100,25,true),
                                        pkmn_move(Dragon,120,"Outrage",60,10,true),
                                        pkmn_move(Ground,100,"Earthquake",85,10,true),
                                        pkmn_move(Poison,30,"Poison Sting",100,35,true)};

        vector<pkmn_move> moves_set;
        for(int i = 0;i<4;i++){
            int r = rand() % possibleMoves.size();
            moves_set.push_back(possibleMoves[r]);
            possibleMoves.erase(possibleMoves.begin()+r);
        }
        Pokemon Venusaur("Venusaur",moves_set,Grass,Poison,rand()%94+270,rand()%137+152,rand()%138+153,rand()%144+184,rand()%144+184,rand()%136+148,3);
        return Venusaur;
    }
    else if(name == "PIKACHU" || name =="4"){
        vector<pkmn_move> possibleMoves{pkmn_move(Electric,75,"Thunder Punch",85,20),
                                        pkmn_move(Electric,40,"Thunder Shock",100,30,true),
                                        pkmn_move(Electric,90,"Thunderbolt",100,20,true),
                                        pkmn_move(Electric,120,"Thunder",70,10,true),
                                        pkmn_move(Normal,70,"Headbutt",100,20),
                                        pkmn_move(Fighting,75,"Brick Break",100,15),
                                        pkmn_move(Fighting,85,"Seismic Toss",100,10),
                                        pkmn_move(Ghost,80,"Shadow Ball",100,20,true)};
        vector<pkmn_move> moves_set;
        for(int i = 0;i<4;i++){
            int r = rand() % possibleMoves.size();
            moves_set.push_back(possibleMoves[r]);
            possibleMoves.erase(possibleMoves.begin()+r);
        }
        Pokemon Pikachu("Pikachu",moves_set,Electric,-1,rand()%84+205,rand()%100+290,rand()%144+90,rand()%94+290,rand()%144+80,rand()%144+250,25);
        return Pikachu;
    }
    else if(name == "PIGEOT" || name == "5"){
        vector<pkmn_move> possibleMoves{pkmn_move(Flying,60,"Wing Attack",100,25,true),
                                        pkmn_move(Flying,75,"Air Slash",95,20),
                                        pkmn_move(Flying,40,"Gust",100,30,true),
                                        pkmn_move(Flying,140,"Sky Attack",70,5),
                                        pkmn_move(Fire,105,"Heat Wave",85,10,true),
                                        pkmn_move(Normal,70,"Headbutt",100,20),
                                        pkmn_move(Normal,150,"Hyper Beam",50,5,true)};
        vector<pkmn_move> moves_set;
        for(int i = 0;i<4;i++){
            int r = rand() % possibleMoves.size();
            moves_set.push_back(possibleMoves[r]);
            possibleMoves.erase(possibleMoves.begin()+r);
        }
        Pokemon Pigeot("Pigeot",moves_set,Flying,Normal,rand()%94+276,rand()%136+148,rand()%134+139,rand()%132+130,rand()%132+130,rand()%145+186,18);
        return Pigeot;
    }
    else if(name == "NIDOKING" || name == "6"){
        vector<pkmn_move> possibleMoves{pkmn_move(Normal,120,"Thrash",60,5),
                                        pkmn_move(Normal,150,"Hyper Beam",50,5,true),
                                        pkmn_move(Fighting,85,"Seismic Toss",100,10),
                                        pkmn_move(Ground,100,"Earthquake",85,10),
                                        pkmn_move(Ground,80,"Drill Run",80,10),
                                        pkmn_move(Poison,30,"Poison Sting",100,35,true),
                                        pkmn_move(Poison,80,"Poison Jab",100,25),
                                        pkmn_move(Poison,90,"Sludge Bomb",100,25,true),
                                        pkmn_move(Dragon,60,"Dragon Tail",90,30),
                                        pkmn_move(Fire,75,"Fire Punch",85,20),
                                        pkmn_move(Ghost,80,"Shadow Ball",100,20,true)};
        vector<pkmn_move> moves_set;
        for(int i = 0;i<4;i++){
            int r = rand() % possibleMoves.size();
            moves_set.push_back(possibleMoves[r]);
            possibleMoves.erase(possibleMoves.begin()+r);
        }
        Pokemon Nidoking("Nidoking",moves_set,Ground,Poison,rand()%94+272,rand()%155+188,rand()%125+143,rand()%138+157,rand()%134+139,rand()%138+157,34);
        return Nidoking;
    }
    else if(name == "NIDOQUEEN" || name == "7"){
        vector<pkmn_move> possibleMoves{pkmn_move(Normal,120,"Thrash",60,5),
                                        pkmn_move(Normal,150,"Hyper Beam",50,5,true),
                                        pkmn_move(Fighting,85,"Seismic Toss",100,10),
                                        pkmn_move(Ground,100,"Earthquake",85,10,true),
                                        pkmn_move(Ground,80,"Drill Run",80,10),
                                        pkmn_move(Poison,30,"Poison Sting",100,35,true),
                                        pkmn_move(Poison,80,"Poison Jab",100,25),
                                        pkmn_move(Poison,90,"Sludge Bomb",100,25,true),
                                        pkmn_move(Water,45,"Bubble Gun",100,45,true),
                                        pkmn_move(Fire,75,"Fire Punch",85,20),
                                        pkmn_move(Electric,120,"Thunder",70,10,true)};
        vector<pkmn_move> moves_set;
        for(int i = 0;i<4;i++){
            int r = rand() % possibleMoves.size();
            moves_set.push_back(possibleMoves[r]);
            possibleMoves.erase(possibleMoves.begin()+r);
        }
        Pokemon Nidoq("Nidoqueen",moves_set,Ground,Poison,rand()%94+272,rand()%138+157,rand()%134+139,rand()%155+188,rand()%125+143,rand()%138+157,31);
        return Nidoq;

    }
    else if(name == "MACHAMP" || name =="8"){
        vector<pkmn_move> possibleMoves{pkmn_move(Normal,150,"Hyper Beam",50,5,true),
                                        pkmn_move(Fighting,85,"Seismic Toss",100,10),
                                        pkmn_move(Fire,75,"Fire Punch",85,20),
                                        pkmn_move(Fighting,75,"Brick Break",100,15),
                                        pkmn_move(Fighting,120,"Superpower",80,5),
                                        pkmn_move(Fighting,30,"Low Kick",95,35),
                                        pkmn_move(Fighting,50,"Karate Chop",100,30),
                                        pkmn_move(Poison,80,"Poison Jab",100,25)};
        vector<pkmn_move> moves_set;
        for(int i = 0;i<4;i++){
            int r = rand() % possibleMoves.size();
            moves_set.push_back(possibleMoves[r]);
            possibleMoves.erase(possibleMoves.begin()+r);
        }
        Pokemon Machamp("Machamp",moves_set,Fighting,-1,rand()%94+220,rand()%148+238,rand()%134+148,rand()%135+121,rand()%135+157,rand()%118+103,68);
        return Machamp;

    }
    else if(name == "GOLEM" || name =="9"){
        vector<pkmn_move> possibleMoves{pkmn_move(Rock,75,"Rock Slide",90,15,true),
                                        pkmn_move(Rock,50,"Rock Throw",90,25,true),
                                        pkmn_move(Ground,100,"Earthquake",85,10,true),
                                        pkmn_move(Ground,80,"Drill Run",80,10),
                                        pkmn_move(Fighting,30,"Low Kick",95,35),
                                        pkmn_move(Normal,40,"Scratch",100,35),
                                        pkmn_move(Normal,70,"Headbutt",100,20)};
        vector<pkmn_move> moves_set;
        for(int i = 0;i<4;i++){
            int r = rand() % possibleMoves.size();
            moves_set.push_back(possibleMoves[r]);
            possibleMoves.erase(possibleMoves.begin()+r);
        }
        Pokemon Golem("Golem",moves_set,Rock,Ground,rand()%94+270,rand()%148+220,rand()%134+248,rand()%135+103,rand()%135+121,rand()%118+85,76);
        return Golem;

    }
    else if(name == "MUK" || name == "10"){
        vector<pkmn_move> possibleMoves{pkmn_move(Poison,90,"Sludge Bomb",100,25,true),
                                        pkmn_move(Poison,30,"Poison Sting",100,35),
                                        pkmn_move(Poison,80,"Poison Jab",100,25),
                                        pkmn_move(Electric,90,"Thunderbolt",100,20,true),
                                        pkmn_move(Fire,75,"Fire Punch",85,20),
                                        pkmn_move(Rock,75,"Rock Slide",90,15,true)};
        vector<pkmn_move> moves_set;
        for(int i = 0;i<4;i++){
            int r = rand() % possibleMoves.size();
            moves_set.push_back(possibleMoves[r]);
            possibleMoves.erase(possibleMoves.begin()+r);
        }
        Pokemon Muk("Muk",moves_set,Poison,-1,rand()%105+320,rand()%125+193,rand()%134+139,rand()%135+121,rand()%155+184,rand()%118+85,89);
        return Muk;

    }
    else if(name == "GENGAR" || name == "11"){
        vector<pkmn_move> possibleMoves{pkmn_move(Poison,90,"Sludge Bomb",100,25,true),
                                        pkmn_move(Poison,30,"Poison Sting",100,35),
                                        pkmn_move(Poison,80,"Poison Jab",100,25),
                                        pkmn_move(Physic,70,"Psychic",100,25,true),
                                        pkmn_move(Physic,50,"Confusion",100,35,true),
                                        pkmn_move(Ghost,80,"Shadow Ball",100,20,true),
                                        pkmn_move(Ghost,70,"Night Shade",95,25,true),
                                        pkmn_move(Ghost,30,"Lick",100,30),
                                        pkmn_move(Normal,150,"Hyper Beam",50,5,true),
                                        pkmn_move(Fighting,75,"Brick Break",100,15),
                                        pkmn_move(Fighting,85,"Seismic Toss",100,10),
                                        pkmn_move(Electric,75,"Thunder Punch",85,20)};
        vector<pkmn_move> moves_set;
        for(int i = 0;i<4;i++){
            int r = rand() % possibleMoves.size();
            moves_set.push_back(possibleMoves[r]);
            possibleMoves.erase(possibleMoves.begin()+r);
        }
        Pokemon Gengar("Gengar",moves_set,Ghost,Poison,rand()%96+230,rand()%130+121,rand()%138+112,rand()%156+238,rand()%144+139,rand()%148+202,94);
        return Gengar;

    }
    else if(name == "ALAKAZAM" || name == "12"){
        vector<pkmn_move> possibleMoves{pkmn_move(Physic,70,"Psychic",100,25,true),
                                        pkmn_move(Physic,50,"Confusion",100,35,true),
                                        pkmn_move(Ghost,70,"Night Shade",95,25,true),
                                        pkmn_move(Physic,70,"Psyshock",100,25,true),
                                        pkmn_move(Physic,65,"Psybeam",100,30,true),
                                        pkmn_move(Normal,70,"Headbutt",100,20)};
        vector<pkmn_move> moves_set;
        for(int i = 0;i<4;i++){
            int r = rand() % possibleMoves.size();
            moves_set.push_back(possibleMoves[r]);
            possibleMoves.erase(possibleMoves.begin()+r);
        }
        Pokemon Alakazam("Alakazam",moves_set,Physic,-1,rand()%96+220,rand()%124+94,rand()%120+85,rand()%165+247,rand()%140+175,rand()%152+220,65);
        return Alakazam;

    }
    else if(name == "SNORLAX" || name == "13"){
        vector<pkmn_move> possibleMoves{pkmn_move(Physic,70,"Psychic",100,25,true),
                                        pkmn_move(Normal,70,"Headbutt",100,20),
                                        pkmn_move(Fighting,120,"Superpower",80,5),
                                        pkmn_move(Ground,100,"Earthquake",85,10,true),
                                        pkmn_move(Dragon,120,"Outrage",60,10,true),
                                        pkmn_move(Normal,150,"Hyper Beam",50,5,true),
                                        pkmn_move(Normal,40,"Tackle",100,35),
                                        pkmn_move(Electric,120,"Thunder",70,10,true),
                                        pkmn_move(Water,80,"Surf",90,25),
                                        pkmn_move(Grass,120,"Solar Beam",50,10,true),
                                        pkmn_move(Fire,75,"Fire Punch",85,20),
                                        pkmn_move(Water,45,"Bubble Gun",100,45,true),
                                        pkmn_move(Normal,70,"Slash",100,25),
                                        pkmn_move(Dragon,85,"Dragon Pulse",90,15,true)};
        vector<pkmn_move> moves_set;
        for(int i = 0;i<4;i++){
            int r = rand() % possibleMoves.size();
            moves_set.push_back(possibleMoves[r]);
            possibleMoves.erase(possibleMoves.begin()+r);
        }
        Pokemon s("Snorlax",moves_set,Normal,-1,rand()%96+430,rand()%148+202,rand()%130+121,rand()%130+121,rand()%148+202,rand()%118+54,143);
        return s;
    }
    else if(name == "DRAGONITE" || name == "14"){
        vector<pkmn_move> possibleMoves{pkmn_move(Physic,70,"Psychic",100,25,true),
                                        pkmn_move(Dragon,120,"Outrage",60,10,true),
                                        pkmn_move(Normal,150,"Hyper Beam",80,5,true),
                                        pkmn_move(Electric,120,"Thunder",70,10,true),
                                        pkmn_move(Water,80,"Surf",90,25),
                                        pkmn_move(Grass,120,"Solar Beam",50,10,true),
                                        pkmn_move(Dragon,85,"Dragon Pulse",90,15,true),
                                        pkmn_move(Dragon,45,"Dragon Rage",90,15,true),
                                        pkmn_move(Dragon,60,"Dragon Tail",90,30),
                                        pkmn_move(Fire,105,"Heat Wave",85,10,true),
                                        pkmn_move(Flying,60,"Wing Attack",100,25),
                                        pkmn_move(Flying,75,"Air Slash",95,20),
                                        pkmn_move(Flying,40,"Gust",100,30,true),
                                        pkmn_move(Flying,140,"Sky Attack",70,5)};
        vector<pkmn_move> moves_set;
        for(int i = 0;i<4;i++){
            int r = rand() % possibleMoves.size();
            moves_set.push_back(possibleMoves[r]);
            possibleMoves.erase(possibleMoves.begin()+r);
        }
        Pokemon d("Dragonite",moves_set,Dragon,Flying,rand()%96+292,rand()%168+245,rand()%148+175,rand()%142+184,rand()%142+184,rand()%136+148,149);
        return d;

    }
    else if(name == "MEWTWO" || name == "15"){
        vector<pkmn_move> possibleMoves{pkmn_move(Physic,70,"Psychic",100,25,true),
                                        pkmn_move(Dragon,120,"Outrage",60,10,true),
                                        pkmn_move(Normal,150,"Hyper Beam",80,5,true),
                                        pkmn_move(Physic,70,"Psyshock",100,25,true),
                                        pkmn_move(Physic,65,"Psybeam",100,30,true),
                                        pkmn_move(Physic,50,"Confusion",100,35,true),
                                        pkmn_move(Electric,120,"Thunder",70,10,true)};
        vector<pkmn_move> moves_set;
        for(int i = 0;i<4;i++){
            int r = rand() % possibleMoves.size();
            moves_set.push_back(possibleMoves[r]);
            possibleMoves.erase(possibleMoves.begin()+r);
        }
        Pokemon m("Mewtwo",moves_set,Physic,-1,rand()%96+322,rand()%168+202,rand()%148+166,rand()%162+281,rand()%142+166,rand()%136+238,150);
        return m;

    }
    else{
        cout<<"Sorry that is not a valid input try again" << endl;
        vector<pkmn_move> nulll;
        Pokemon null("null",nulll,0,0,0,0,0,0,0,0,0);
        return null;
    }
}

bool type_advantage(int type1,int type2){
    if(type1 == Grass){
        if(type2 == Ground || type2 == Rock || type2 == Water){
            return true;
        }
        return false;
    }
    if(type1 == Dragon){
        return false;
    }
    if(type1 == Electric){
        if(type2 == Flying || type2 == Water){
            return true;
        }
        return false;
    }
    if(type1 == Fighting){
        if(type2 == Normal || type2 == Rock) {
            return true;
        }
        return false;
    }
    if(type1 ==Ghost){
        return false;
    }
    if(type1 == Ground){
        if(type2 == Electric || type2 == Fire || type2 == Poison || type2 == Rock){
            return true;
        }
        return false;
    }
    if(type1 ==  Normal){
        return false;
    }
    if(type1 == Poison){
        if(type2 == Grass){
            return true;
        }
        return false;
    }
    if(type1 == Physic){
        if(type2 == Fighting || type2 == Poison){
            return true;
        }
        return false;
    }
    if(type1 == Rock){
        if(type2 ==Fire ||type2 ==Flying)
            return true;
        return false;
    }
    if(type1 == Water){
        if(type2 == Fire || type2 == Ground || type2 == Rock)
            return true;
        return false;
    }
}
bool type_disadvantage(int type1,int type2){
    if(type1 == Electric){
        if(type2 == Electric || type2 == Grass)
            return true;
        return false;
    }
    if(type1 == Dragon)
        return false;
    if(type1 == Fighting){
        if(type2 == Flying || type2 == Physic)
            return true;
        return false;
    }
    if(type1 == Fire){
        if(type2 == Rock || type2 == Water)
            return true;
        return false;
    }
    if(type1 == Flying) {
        if(type2 == Electric || type2 == Rock)
            return true;
        return false;
    }
    if(type1 == Grass){
        if(type2 == Fire || type2 == Flying || type2 == Grass || type2 == Poison)
            return true;
        return false;
    }
    if(type1 == Ground){
        if(type2 == Grass)
            return true;
        return false;
    }
    if(type1 == Normal){
        return false;
    }
    if(type1 == Poison){
        if(type2 == Ground || type2 == Poison || type2 == Rock)
            return true;
        return false;
    }
    if(type1 == Physic){
        if(type2 == Physic)
            return true;
        return false;
    }
    if(type1 ==  Rock){
        if(type2 ==Fighting || type2 == Rock)
            return true;
        return false;
    }
    if(type1 == Water){
        if(type2 == Grass)
            return true;
        return false;
    }
}
bool type_noeffect(int type1,int type2){
    if(type1 == Electric){
        if(type2 == Ground)
            return true;
    }
    if(type1 == Fighting){
        if(type2 == Ghost)
            return true;
    }
    if(type1 == Ghost){
        if(type2 == Normal || type2 == Physic)
            return true;
    }
    if(type1 == Ground){
        if(type2 == Flying)
            return true;
    }
    if(type1 == Normal){
        if(type2 == Ghost)
            return true;
    }
    return false;
}