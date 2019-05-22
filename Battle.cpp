//
// Created by Viraj P on 5/20/2019.
//

#include "Battle.h"
#include <stdio.h>

void Battle(Pokemon myPkmn, Pokemon cpuPkmn){
    cout<<"Your Opponent sent out "<<cpuPkmn.pkmn_name()<<endl;
    print_pokemon(cpuPkmn.pkdx());
    cpuPkmn.printCPU();
    delay(INT32_MAX/2);
    cout<<"\n\nGo "<<myPkmn.pkmn_name()<<" I choose you!"<<endl;
    print_pokemon(myPkmn.pkdx());
    delay(INT32_MAX/4);
    myPkmn.printSimple_();
    delay(INT32_MAX/32);
    int moveNumber = 1;
    while(myPkmn.health_() > 0 && cpuPkmn.health_() > 0){
        printMovenum(moveNumber);
        if(myPkmn.speed()>cpuPkmn.speed()){
            BattleLoopMy(myPkmn,cpuPkmn);
            cpuPkmn.printCPU();
            if(cpuPkmn.health_()<=0)
                break;
            BattleLoopCpu(myPkmn,cpuPkmn);
            myPkmn.printCPU();
            moveNumber++;
        }
        else{
            BattleLoopCpu(myPkmn,cpuPkmn);
            myPkmn.printCPU();
            if(myPkmn.health_()<=0)
                break;
            BattleLoopMy(myPkmn,cpuPkmn);
            cpuPkmn.printCPU();
            moveNumber++;
        }
    }
    if(myPkmn.health_() >0 && cpuPkmn.health_()<=0){
        cout<<cpuPkmn.pkmn_name()<<" Fainted...Battle over you win!"<<endl;
    }
    else{
        cout<<myPkmn.pkmn_name()<<" Fainted...Battle over try again next time"<<endl;
    }
}

void BattleLoopMy(Pokemon& my, Pokemon& cpu) {
    // fix type effectiveness
    string input;
    cout << "1 -> " << my.moves[0].move_name() << endl;
    cout << "2 -> " << my.moves[1].move_name() << endl;
    cout << "3 -> " << my.moves[2].move_name() << endl;
    cout << "4 -> " << my.moves[3].move_name() << endl;
    cout << "5 -> Detailed Move Information" << endl;
    cout << "6 -> Detailed Pokemon Stats" << endl;
    cin >> input;
    Battleloop(my,cpu,input);
}


void BattleLoopCpu(Pokemon& my, Pokemon& cpu){
    int num = 1;
    bool flag = false;
    auto current = cpu.moves[num-1];
    // pick a move with type advantage if possible
    if(type_advantage(cpu.moves[0].move_type(),my.pkmn_type())|| type_advantage(cpu.moves[0].move_type(),my.pkmn_type())){
        if(cpu.moves[0].move_power()*2 >= current.move_power()){
            num = 1;
            current =cpu.moves[num-1];
            flag = true;
        }
    }
    if(type_advantage(cpu.moves[1].move_type(),my.pkmn_type())|| type_advantage(cpu.moves[1].move_type(),my.pkmn_type())){
        if(cpu.moves[1].move_power()*2 >= current.move_power()){
            num = 2;
            current =cpu.moves[num-1];
            flag = true;
        }
    }
    if(type_advantage(cpu.moves[2].move_type(),my.pkmn_type())|| type_advantage(cpu.moves[2].move_type(),my.pkmn_type())){
        if(cpu.moves[2].move_power()*2 >= current.move_power()){
            num = 3;
            current =cpu.moves[num-1];
            flag = true;
        }
    }
    if(type_advantage(cpu.moves[3].move_type(),my.pkmn_type())|| type_advantage(cpu.moves[3].move_type(),my.pkmn_type())){
        if(cpu.moves[3].move_power()*2 >= current.move_power()){
            num = 4;
            current =cpu.moves[num-1];
            flag = true;
        }
    }

    //else pick a move with no type disadvantage
    if(!flag){
        if(!(type_disadvantage(cpu.moves[0].move_type(),my.pkmn_type())|| type_disadvantage(cpu.moves[0].move_type(),my.pkmn_type()))){
            if(cpu.moves[0].move_power()*.25 >= current.move_power()){
                num = 1;
                current =cpu.moves[num-1];
                flag = true;
            }
        }
        if(!(type_disadvantage(cpu.moves[1].move_type(),my.pkmn_type())|| type_disadvantage(cpu.moves[1].move_type(),my.pkmn_type()))){
            if(cpu.moves[1].move_power()*2 >= current.move_power()){
                num = 2;
                current =cpu.moves[num-1];
                flag = true;
            }
        }
        if(!(type_disadvantage(cpu.moves[2].move_type(),my.pkmn_type())|| type_disadvantage(cpu.moves[2].move_type(),my.pkmn_type()))){
            if(cpu.moves[2].move_power()*2 >= current.move_power()){
                num = 3;
                current =cpu.moves[num-1];
                flag = true;
            }
        }
        if(!(type_disadvantage(cpu.moves[3].move_type(),my.pkmn_type())|| type_disadvantage(cpu.moves[3].move_type(),my.pkmn_type()))){
            if(cpu.moves[3].move_power()*2 >= current.move_power()){
                num = 4;
                current =cpu.moves[num-1];
                flag = true;
            }
        }
    }

    //else pick move with most power

    if(!flag){
        if(cpu.moves[0].move_power() >= current.move_power()){
            num = 1;
            current =cpu.moves[num-1];
            flag = true;
        }
        if(cpu.moves[1].move_power() >= current.move_power()){
            num = 2;
            current =cpu.moves[num-1];
            flag = true;
        }
        if(cpu.moves[2].move_power() >= current.move_power()){
            num = 3;
            current =cpu.moves[num-1];
            flag = true;
        }
        if(cpu.moves[3].move_power() >= current.move_power()){
            num = 4;
            current =cpu.moves[num-1];
            flag = true;
        }
    }
    //else pick move with most power else pick random move

    int random = rand()%2;
    if(!flag ||random || (type_noeffect(current.move_type(),my.pkmn_type()) || type_noeffect(current.move_type(),my.pkmn_type2()))){
        num = rand()%4+1;
    }
    string input = to_string(num);
    Battleloop(cpu,my,input);
}


void Battleloop(Pokemon& my, Pokemon& cpu,string input){
    if(my.moves[0].move_pp() == 0 && my.moves[1].move_pp() ==0 && my.moves[2].move_pp() ==0 && my.moves[3].move_pp() ==0){
        if(input != "5" && input != "6"){
            cout<<my.pkmn_name()<<" is out of moves with PP ... "<<my.pkmn_name() <<"used struggle";
            cpu.damage(5);
            return;
        }
    }
    if(input == "1"){
        auto current = my.moves[0];
        if(current.move_pp() <= 0){
            cout<<"This move has no PP left select a different move";
            BattleLoopMy(my,cpu);
            return;
        }
        double modifiers = 1;
        int accuracy = rand()%100+1;
        cout<<my.pkmn_name()<<" used "<<current.move_name()<<endl;
        int type1 = current.move_type();
        int type2 = cpu.pkmn_type();
        int type3 = cpu.pkmn_type2();
        if(type3 == -1){type3 = type2;}
        if(accuracy>current.move_accuracy()){
            cout<<"The attack missed"<<endl;
            return;
        }
        if((type_advantage(type1,type2) && type_disadvantage(type1,type3)) || (type_advantage(type1,type3) && type_disadvantage(type1,type2))){
            modifiers = 1;
        }
        else if(type_advantage(type1,type2) || type_advantage(type1,type3)){
            modifiers = 2;
            cout<<"It was super effective" << endl;
        }
        else if(type_disadvantage(type1,type2) || type_disadvantage(type1,type3)){
            modifiers = .25;
            cout<<"It was not very effective" << endl;
        }
        else if(type_noeffect(type1,type2) || type_noeffect(type1,type3)){
            modifiers = 0;
            cout<<cpu.pkmn_name()<<" is not effected by this move"<<endl;
        }
        if(current.specialS()){
            double pwr = (double)current.move_power()*1.0;
            double ratio = (double)my.pkmn_spattack()/(double)cpu.pkmn_spdefence()*1.0;
            double lvl = (double)my.pkmn_level()/70*1.0;
            double dmg = pwr*ratio*lvl*modifiers*.85;
            my.moves[0].move_use();
            cpu.damage(dmg);
        }
        else{
            double pwr = (double)current.move_power()*1.0;
            double ratio = (double)my.pkmn_attack()/(double)cpu.pkmn_defence()*1.0;
            double lvl = (double)my.pkmn_level()/70*1.0;
            double dmg = pwr*ratio*lvl*modifiers*.85;
            my.moves[0].move_use();
            cpu.damage(dmg);
        }
    }
    else if(input == "2"){
        auto current = my.moves[1];
        if(current.move_pp() <= 0){
            cout<<"This move has no PP left select a different move";
            BattleLoopMy(my,cpu);
            return;
        }
        double modifiers = 1;
        int accuracy = rand()%100+1;
        cout<<my.pkmn_name()<<" used "<<current.move_name()<<endl;
        int type1 = current.move_type();
        int type2 = cpu.pkmn_type();
        int type3 = cpu.pkmn_type2();
        if(type3 == -1){type3 = type2;}
        if(accuracy>current.move_accuracy()){
            cout<<"The attack missed"<<endl;
            return;
        }
        if((type_advantage(type1,type2) && type_disadvantage(type1,type3)) || (type_advantage(type1,type3) && type_disadvantage(type1,type2))){
            modifiers = 1;
        }
        else if(type_advantage(type1,type2) || type_advantage(type1,type3)){
            modifiers = 2;
            cout<<"It was super effective" << endl;
        }
        else if(type_disadvantage(type1,type2) || type_disadvantage(type1,type3)){
            modifiers = .25;
            cout<<"It was not very effective" << endl;
        }
        else if(type_noeffect(type1,type2) || type_noeffect(type1,type3)){
            modifiers = 0;
            cout<<cpu.pkmn_name()<<" is not effected by this move"<<endl;
        }
        if(current.specialS()){
            double pwr = (double)current.move_power()*1.0;
            double ratio = (double)my.pkmn_spattack()/(double)cpu.pkmn_spdefence()*1.0;
            double lvl = (double)my.pkmn_level()/70*1.0;
            double dmg = pwr*ratio*lvl*modifiers*.85;
            my.moves[1].move_use();
            cpu.damage(dmg);
        }
        else{
            double pwr = (double)current.move_power()*1.0;
            double ratio = (double)my.pkmn_attack()/(double)cpu.pkmn_defence()*1.0;
            double lvl = (double)my.pkmn_level()/70*1.0;
            double dmg = pwr*ratio*lvl*modifiers*.85;
            my.moves[1].move_use();
            cpu.damage(dmg);
        }

    }
    else if(input == "3"){
        auto current = my.moves[2];
        if(current.move_pp() <= 0){
            cout<<"This move has no PP left select a different move";
            BattleLoopMy(my,cpu);
            return;
        }
        double modifiers = 1;
        int accuracy = rand()%100+1;
        cout<<my.pkmn_name()<<" used "<<current.move_name()<<endl;
        int type1 = current.move_type();
        int type2 = cpu.pkmn_type();
        int type3 = cpu.pkmn_type2();
        if(type3 == -1){type3 = type2;}
        if(accuracy>current.move_accuracy()){
            cout<<"The attack missed"<<endl;
            return;
        }
        if((type_advantage(type1,type2) && type_disadvantage(type1,type3)) || (type_advantage(type1,type3) && type_disadvantage(type1,type2))){
            modifiers = 1;
        }
        else if(type_advantage(type1,type2) || type_advantage(type1,type3)){
            modifiers = 2;
            cout<<"It was super effective" << endl;
        }
        else if(type_disadvantage(type1,type2) || type_disadvantage(type1,type3)){
            modifiers = .25;
            cout<<"It was not very effective" << endl;
        }
        else if(type_noeffect(type1,type2) || type_noeffect(type1,type3)){
            modifiers = 0;
            cout<<cpu.pkmn_name()<<" is not effected by this move"<<endl;
        }
        if(current.specialS()){
            double pwr = (double)current.move_power()*1.0;
            double ratio = (double)my.pkmn_spattack()/(double)cpu.pkmn_spdefence()*1.0;
            double lvl = (double)my.pkmn_level()/70*1.0;
            double dmg = pwr*ratio*lvl*modifiers*.85;
            my.moves[2].move_use();
            cpu.damage(dmg);
        }
        else{
            double pwr = (double)current.move_power()*1.0;
            double ratio = (double)my.pkmn_attack()/(double)cpu.pkmn_defence()*1.0;
            double lvl = (double)my.pkmn_level()/70*1.0;
            double dmg = pwr*ratio*lvl*modifiers*.85;
            my.moves[2].move_use();
            cpu.damage(dmg);
        }
    }
    else if(input == "4") {
        auto current = my.moves[3];
        if (current.move_pp() <= 0) {
            cout << "This move has no PP left select a different move";
            BattleLoopMy(my, cpu);
            return;
        }
        double modifiers = 1;
        int accuracy = rand() % 100 + 1;
        cout << my.pkmn_name() << " used " << current.move_name() << endl;
        int type1 = current.move_type();
        int type2 = cpu.pkmn_type();
        int type3 = cpu.pkmn_type2();
        if (type3 == -1) { type3 = type2; }
        if (accuracy > current.move_accuracy()) {
            cout << "The attack missed" << endl;
            return;
        }
        if ((type_advantage(type1, type2) && type_disadvantage(type1, type3)) ||
            (type_advantage(type1, type3) && type_disadvantage(type1, type2))) {
            modifiers = 1;
        } else if (type_advantage(type1, type2) || type_advantage(type1, type3)) {
            modifiers = 2;
            cout << "It was super effective" << endl;
        } else if (type_disadvantage(type1, type2) || type_disadvantage(type1, type3)) {
            modifiers = .25;
            cout << "It was not very effective" << endl;
        } else if (type_noeffect(type1, type2) || type_noeffect(type1, type3)) {
            modifiers = 0;
            cout << cpu.pkmn_name() << " is not effected by this move" << endl;
        }
        if (current.specialS()) {
            double pwr = (double) current.move_power() * 1.0;
            double ratio = (double) my.pkmn_spattack() / (double) cpu.pkmn_spdefence() * 1.0;
            double lvl = (double) my.pkmn_level() / 70 * 1.0;
            double dmg = pwr * ratio * lvl * modifiers * .85;
            my.moves[3].move_use();
            cpu.damage(dmg);
        } else {
            double pwr = (double) current.move_power() * 1.0;
            double ratio = (double) my.pkmn_attack() / (double) cpu.pkmn_defence() * 1.0;
            double lvl = (double) my.pkmn_level() / 70 * 1.0;
            double dmg = pwr * ratio * lvl * modifiers * .85;
            my.moves[3].move_use();
            cpu.damage(dmg);
        }
    }
    else if(input =="5"){
        my.printSimple();
        BattleLoopMy(my,cpu);
    }
    else if(input == "6"){
        my.printDetails();
        BattleLoopMy(my,cpu);
    }
    else{
        cout<<"Sorry not a valid input try again";
        BattleLoopMy(my,cpu);
    }
}

void printMovenum(int n){
    cout<<"\n\n";
    cout<<"--------------"<<endl;
    cout<<"Move number: "<<n<<endl;
    cout<<"--------------"<<endl;
    cout<<"\n\n";
}


void print_pokemon(int n_pokemon) {
    switch(n_pokemon) {
        case 1:
            printf("                                           /\n");
            printf("                        _,.------....___,.' ',.-.\n");
            printf("                     ,-'          _,.--\"        |\n");
            printf("                   ,'         _.-'              .\n");
            printf("                  /   ,     ,'                   `\n");
            printf("                 .   /     /                     ``.\n");
            printf("                 |  |     .                       \\.\\\n");
            printf("       ____      |___._.  |       __               \\ `.\n");
            printf("     .'    `---\"\"       ``\"-.--\"'`  \\               .  \\\n");
            printf("    .  ,            __               `              |   .\n");
            printf("    `,'         ,-\"'  .               \\             |    L\n");
            printf("   ,'          '    _.'                -._          /    |\n");
            printf("  ,`-.    ,\".   `--'                      >.      ,'     |\n");
            printf(" . .'\\'   `-'       __    ,  ,-.         /  `.__.-      ,'\n");
            printf(" ||:, .           ,'  ;  /  / \\ `        `.    .      .'/\n");
            printf(" j|:D  \\          `--'  ' ,'_  . .         `.__, \\   , /\n");
            printf("/ L:_  |                 .  \"' :_;                `.'.'\n");
            printf(".    \"\"'                  \"\"\"\"\"'                    V\n");
            printf(" `.                                 .    `.   _,..  `\n");
            printf("   `,_   .    .                _,-'/    .. `,'   __  `\n");
            printf("    ) \\`._        ___....----\"'  ,'   .'  \\ |   '  \\  .\n");
            printf("   /   `. \"`-.--\"'         _,' ,'     `---' |    `./  |\n");
            printf("  .   _  `\"\"'--.._____..--\"   ,             '         |\n");
            printf("  | .\" `. `-.                /-.           /          ,\n");
            printf("  | `._.'    `,_            ;  /         ,'          .\n");
            printf(" .'          /| `-.        . ,'         ,           ,\n");
            printf(" '-.__ __ _,','    '`-..___;-...__   ,.'\\ ____.___.'\n");
            printf(" `\"^--'..'   '-`-^-'\"--    `-^-'`.''\"\"\"\"\"`.,^.`.--'   \n");
            printf("\n");
            printf("\n");

            break;

        case 2:
            printf("                               ,'\"`.,./.\n");
            printf("                             ,'        Y',\"..\n");
            printf("                           ,'           \\  | \\\n");
            printf("                          /              . |  `\n");
            printf("                         /               | |   \\\n");
            printf("            __          .                | |    .\n");
            printf("       _   \\  `. ---.   |                | j    |\n");
            printf("      / `-._\\   `Y   \\  |                |.     |\n");
            printf("     _`.    ``    \\   \\ |..              '      |,-'\"\"7,....\n");
            printf("     l     '-.     . , `|  | , |`. , ,  /,     ,'    '/   ,'_,.-.\n");
            printf("     `-..     `-.  : :     |/ `   ' \"\\,' | _  /          '-'    /___\n");
            printf("      \\\"\"' __.,.-`.: :        /   /._    l'.,'\n");
            printf("       `--,   _.-' `\".           /__ `'-.' '         .\n");
            printf("       ,---..._,.--\"\"\"\"\"\"\"--.__..----,-.'   .  /    .'   ,.--\n");
            printf("       |                          ,':| /    | /     ;.,-'--      ,.-\n");
            printf("       |     .---.              .'  :|'     |/ ,.-='\"-.`\"`' _   -.'\n");
            printf("       /    \\    /               `. :|--.  _L,\"---.._        \"----'\n");
            printf("     ,' `.   \\ ,'           _,     `''   ``.-'       `-  -..___,'\n");
            printf("    . ,.  .   `   __     .-'  _.-           `.     .__    \\\n");
            printf("    |. |`        \"  ;   !   ,.  |             `.    `.`'---'\n");
            printf("    ,| |C\\       ` /    | ,' |(]|            -. |-..--`\n");
            printf("   /  \"'--'       '      /___|__]        `.  `- |`.\n");
            printf("  .       ,'                   ,   /       .    `. \\\n");
            printf("    \\                      .,-'  ,'         .     `-.\n");
            printf("     x---..`.  -'  __..--'\"/\"\"\"\"\"  ,-.      |   |   |\n");
            printf("    / \\--._'-.,.--'     _`-    _. ' /       |     -.|\n");
            printf("   ,   .   `-..__ ...--'  _,.-' | `   ,.-.  ;   /  '|\n");
            printf("  .  _,'         '\"-----\"\"      |    `   | /  ,'    ;\n");
            printf("  |-'  .-.    `._               |     `._// ,'     /\n");
            printf(" _|    `-'   _,' \"`--.._________|        `,'    _ /.\n");
            printf("//\\   ,-._.'\"/\\__,.   _,\"     /_\\__/`. /'.-.'.-/_,`-'   \n");
            printf("`-\"`\"' v'    `\"  `-`-\"              `-'`-`  `'\n");

            break;

        case 3:
            printf("                           _._       _,._\n");
            printf("                        _.'   `. ' .'   _`.\n");
            printf("                ,\"\"\"/`\"\"-.-.,/. ` V'\\-,`.,--/\"\"\".\"-..\n");
            printf("              ,'    `...,' . ,\\-----._|     `.   /   \\\n");
            printf("             `.            .`  -'`\"\" .._   :> `-'   `.\n");
            printf("            ,'  ,-.  _,.-'| `..___ ,'   |'-..__   .._ L\n");
            printf("           .    \\_ -'   `-'     ..      `.-' `.`-.'_ .|\n");
            printf("           |   ,',-,--..  ,--../  `.  .-.    , `-.  ``.\n");
            printf("           `.,' ,  |   |  `.  /'/,,.\\/  |    \\|   |\n");
            printf("                `  `---'    `j   .   \\  .     '   j\n");
            printf("              ,__`\"        ,'|`'\\_/`.'\\'        |\\-'-, _,.\n");
            printf("       .--...`-. `-`. /    '- ..      _,    /\\ ,' .--\"'  ,'\".\n");
            printf("     _'-\"\"-    --  _`'-.../ __ '.'`-^,_`-\"\"\"\"---....__  ' _,-`\n");
            printf("   _.----`  _..--.'        |  \"`-..-\" __|'\"'         .\"\"-. \"\"'--.._\n");
            printf("  /        '    /     ,  _.+-.'  ||._'   \"\"\"\". .          `     .__\\\n");
            printf(" `---    /        /  / j'       _/|..`  -. `-`\\ \\   \\  \\   `.  \\ `-..\n");
            printf(",\" _.-' /    /` ./  /`_|_,-\"   ','|       `. | -'`._,   L  \\ .  `.   |\n");
            printf("`\"' /  /  / ,__...-----| _.,  ,'            `|----.._`-.|' |. .` ..  .\n");
            printf("   /  '| /.,/   \\--.._ `-,' ,          .  '`.'  __,., '  ''``._ \\ \\`,'\n");
            printf("  /_,'---  ,     \\`._,-` \\ //  / . \\    `._,  -`,  / / _   |   `-L -\n");
            printf("   /       `.     ,  ..._ ' `_/ '| |\\ `._'       '-.'   `.,'     |\n");
            printf("  '         /    /  ..   `.  `./ | ; `.'    ,\"\" ,.  `.    \\      |\n");
            printf("   `.     ,'   ,'   | |\\  |       \"        |  ,'\\ |   \\    `    ,L\n");
            printf("   /|`.  /    '     | `-| '                  /`-' |    L    `._/  \\\n");
            printf("  / | .`|    |  .   `._.'                   `.__,'   .  |     |  (`\n");
            printf(" '-\"\"-'_|    `. `.__,._____     .    _,        ____ ,-  j     \".-'\"'\n");
            printf("        \\      `-.  \\/.    `\"--.._    _,.---'\"\"\\/  \"_,.'     /-'\n");
            printf("         )        `-._ '-.        `--\"      _.-'.-\"\"        `.\n");
            printf("        ./            `,. `\".._________...\"\"_.-\"`.          _j\n");
            printf("       /_\\.__,\"\".   ,.'  \"`-...________.---\"     .\".   ,.  / \\\n");
            printf("              \\_/\"\"\"-'                           `-'--(_,`\"`-`   \n");

            break;

        case 4:
            printf("              _.--\"\"`-..\n");
            printf("            ,'          `.\n");
            printf("          ,'          __  `.\n");
            printf("         /|          \" __   \\\n");
            printf("        , |           / |.   .\n");
            printf("        |,'          !_.'|   |\n");
            printf("      ,'             '   |   |\n");
            printf("     /              |`--'|   |\n");
            printf("    |                `---'   |\n");
            printf("     .   ,                   |                       ,\".\n");
            printf("      ._     '           _'  |                    , ' \\ `\n");
            printf("  `.. `.`-...___,...---\"\"    |       __,.        ,`\"   L,|\n");
            printf("  |, `- .`._        _,-,.'   .  __.-'-. /        .   ,    \\\n");
            printf("-:..     `. `-..--_.,.<       `\"      / `.        `-/ |   .\n");
            printf("  `,         \"\"\"\"'     `.              ,'         |   |  ',,\n");
            printf("    `.      '            '            /          '    |'. |/\n");
            printf("      `.   |              \\       _,-'           |       ''\n");
            printf("        `._'               \\   '\"\\                .      |\n");
            printf("           |                '     \\                `._  ,'\n");
            printf("           |                 '     \\                 .'|\n");
            printf("           |                 .      \\                | |\n");
            printf("           |                 |       L              ,' |\n");
            printf("           `                 |       |             /   '\n");
            printf("            \\                |       |           ,'   /\n");
            printf("          ,' \\               |  _.._ ,-..___,..-'    ,'\n");
            printf("         /     .             .      `!             ,j'\n");
            printf("        /       `.          /        .           .'/\n");
            printf("       .          `.       /         |        _.'.'\n");
            printf("        `.          7`'---'          |------\"'_.'\n");
            printf("       _,.`,_     _'                ,''-----\"'\n");
            printf("   _,-_    '       `.     .'      ,\\\n");
            printf("   -\" /`.         _,'     | _  _  _.|\n");
            printf("    \"\"--'---\"\"\"\"\"'        `' '! |! /\n");
            printf("                            `\" \" -'   \n");
            printf("\n");
            printf("\n");

            break;

        case 5:
            printf("                      ,-'`\\\n");
            printf("                  _,\"'    j\n");
            printf("           __....+       /               .\n");
            printf("       ,-'\"             /               ; `-._.'.\n");
            printf("      /                (              ,'       .'\n");
            printf("     |            _.    \\             \\   ---._ `-.\n");
            printf("     ,|    ,   _.'  Y    \\             `- ,'   \\   `.`.\n");
            printf("     l'    \\ ,'._,\\ `.    .              /       ,--. l\n");
            printf("  .,-        `._  |  |    |              \\       _   l .\n");
            printf(" /              `\"--'    /              .'       ``. |  )\n");
            printf(".\\    ,                 |                .        \\ `. '\n");
            printf("`.                .     |                '._  __   ;. \\'\n");
            printf("  `-..--------...'       \\                  `'  `-\"'.  \\\n");
            printf("      `......___          `._                        |  \\\n");
            printf("               /`            `..                     |   .\n");
            printf("              /|                `-.                  |    L\n");
            printf("             / |               \\   `._               .    |\n");
            printf("           ,'  |,-\"-.   .       .     `.            /     |\n");
            printf("         ,'    |     '   \\      |       `.         /      |\n");
            printf("       ,'     /|       \\  .     |         .       /       |\n");
            printf("     ,'      / |        \\  .    +          \\    ,'       .'\n");
            printf("    .       .  |         \\ |     \\          \\_,'        / j\n");
            printf("    |       |  L          `|      .          `        ,' '\n");
            printf("    |    _. |   \\          /      |           .     .' ,'\n");
            printf("    |   /  `|    \\        .       |  /        |   ,' .'\n");
            printf("    |   ,-..\\     -.     ,        | /         |,.' ,'\n");
            printf("    `. |___,`    /  `.   /`.       '          |  .'\n");
            printf("      '-`-'     j     ` /.\"7-..../|          ,`-'\n");
            printf("                |        .'  / _/_|          .\n");
            printf("                `,       `\"'/\"'    \\          `.\n");
            printf("                  `,       '.       `.         |\n");
            printf("             __,.-'         `.        \\'       |\n");
            printf("            /_,-'\\          ,'        |        _.\n");
            printf("             |___.---.   ,-'        .-':,-\"`\\,' .\n");
            printf("                  L,.--\"'           '-' |  ,' `-.\\\n");
            printf("                                        `.'   \n");

            break;

        case 6:
            printf("                 .\"-,.__\n");
            printf("                 `.     `.  ,\n");
            printf("              .--'  .._,'\"-' `.\n");
            printf("             .    .'         `'\n");
            printf("             `.   /          ,'\n");
            printf("               `  '--.   ,-\"'\n");
            printf("                `\"`   |  \\\n");
            printf("                   -. \\, |\n");
            printf("                    `--Y.'      ___.\n");
            printf("                         \\     L._, \\\n");
            printf("               _.,        `.   <  <\\                _\n");
            printf("             ,' '           `, `.   | \\            ( `\n");
            printf("          ../, `.            `  |    .\\`.           \\ \\_\n");
            printf("         ,' ,..  .           _.,'    ||\\l            )  '\".\n");
            printf("        , ,'   \\           ,'.-.`-._,'  |           .  _._`.\n");
            printf("      ,' /      \\ \\        `' ' `--/   | \\          / /   ..\\\n");
            printf("    .'  /        \\ .         |\\__ - _ ,'` `        / /     `.`.\n");
            printf("    |  '          ..         `-...-\"  |  `-'      / /        . `.\n");
            printf("    | /           |L__           |    |          / /          `. `.\n");
            printf("   , /            .   .          |    |         / /             ` `\n");
            printf("  / /          ,. ,`._ `-_       |    |  _   ,-' /               ` \\\n");
            printf(" / .           \\\"`_/. `-_ \\_,.  ,'    +-' `-'  _,        ..,-.    \\`.\n");
            printf(".  '         .-f    ,'   `    '.       \\__.---'     _   .'   '     \\ \\\n");
            printf("' /          `.'    l     .' /          \\..      ,_|/   `.  ,'`     L`\n");
            printf("|'      _.-\"\"` `.    \\ _,'  `            \\ `.___`.'\"`-.  , |   |    | \\\n");
            printf("||    ,'      `. `.   '       _,...._        `  |    `/ '  |   '     .|\n");
            printf("||  ,'          `. ;.,.---' ,'       `.   `.. `-'  .-' /_ .'    ;_   ||\n");
            printf("|| '              V      / /           `   | `   ,'   ,' '.    !  `. ||\n");
            printf("||/            _,-------7 '              . |  `-'    l         /    `||\n");
            printf(". |          ,' .-   ,' ||               | .-.        `.      .'     ||\n");
            printf(" `'        ,'    `\".'    |               |    `.        '. -.'       `'\n");
            printf("          /      ,'      |               |,'    \\-.._,.'/'\n");
            printf("          .     /        .               .       \\    .''\n");
            printf("        .`.    |         `.             /         :_,'.'\n");
            printf("          \\ `...\\   _     ,'-.        .'         /_.-'\n");
            printf("           `-.__ `,  `'   .  _.>----''.  _  __  /\n");
            printf("                .'        /\"'          |  \"'   '_\n");
            printf("               /_|.-'\\ ,\".             '.'`__'-( \\\n");
            printf("                 / ,\"'\"\\,'               `/  `-.|\"   \n");

            break;

        case 7:
            printf("               _,........__\n");
            printf("            ,-'            \"`-.\n");
            printf("          ,'                   `-.\n");
            printf("        ,'                        \\\n");
            printf("      ,'                           .\n");
            printf("      .'\\               ,\"\".       `\n");
            printf("     ._.'|             / |  `       \\\n");
            printf("     |   |            `-.'  ||       `.\n");
            printf("     |   |            '-._,'||       | \\\n");
            printf("     .`.,'             `..,'.'       , |`-.\n");
            printf("     l                       .'`.  _/  |   `.\n");
            printf("     `-.._'-   ,          _ _'   -\" \\  .     `\n");
            printf("`.\"\"\"\"\"'-.`-...,---------','         `. `....__.\n");
            printf(".'        `\"-..___      __,'\\          \\  \\     \\\n");
            printf("\\_ .          |   `\"\"\"\"'    `.           . \\     \\\n");
            printf("  `.          |              `.          |  .     L\n");
            printf("    `.        |`--...________.'.        j   |     |\n");
            printf("      `._    .'      |          `.     .|   ,     |\n");
            printf("         `--,\\       .            `7\"\"' |  ,      |\n");
            printf("            ` `      `            /     |  |      |    _,-'\"\"\"`-.\n");
            printf("             \\ `.     .          /      |  '      |  ,'          `.\n");
            printf("              \\  v.__  .        '       .   \\    /| /              \\\n");
            printf("               \\/    `\"\"\\\"\"\"\"\"\"\"`.       \\   \\  /.''                |\n");
            printf("                `        .        `._ ___,j.  `/ .-       ,---.     |\n");
            printf("                ,`-.      \\         .\"     `.  |/        j     `    |\n");
            printf("               /    `.     \\       /         \\ /         |     /    j\n");
            printf("              |       `-.   7-.._ .          |\"          '         /\n");
            printf("              |          `./_    `|          |            .     _,'\n");
            printf("              `.           / `----|          |-............`---'\n");
            printf("                \\          \\      |          |\n");
            printf("               ,'           )     `.         |\n");
            printf("                7____,,..--'      /          |\n");
            printf("                                  `---.__,--.'  \n");

            break;

        case 8:
            printf("     __                                _.--'\"7\n");
            printf("    `. `--._                        ,-'_,-  ,'\n");
            printf("     ,'  `-.`-.                   /' .'    ,|\n");
            printf("     `.     `. `-     __...___   /  /     - j\n");
            printf("       `.     `  `.-\"\"        \" .  /       /\n");
            printf("         \\     /                ` /       /\n");
            printf("          \\   /                         ,'\n");
            printf("          '._'_               ,-'       |\n");
            printf("             | \\            ,|  |   ...-'\n");
            printf("             || `         ,|_|  |   | `             _..__\n");
            printf("            /|| |          | |  |   |  \\  _,_    .-\"     `-.\n");
            printf("           | '.-'          |_|_,' __!  | /|  |  /           \\\n");
            printf("   ,-...___ .=                  ._..'  /`.| ,`,.      _,.._ |\n");
            printf("  |   |,.. \\     '  `'        ____,  ,' `--','  |    /      |\n");
            printf(" ,`-..'  _)  .`-..___,---'_...._/  .'      '-...'   |      /\n");
            printf("'.__' \"\"'      `.,------'\"'      ,/            ,     `.._.' `.\n");
            printf("  `.             | `--........,-'.            .         \\     \\\n");
            printf("    `-.          .   '.,--\"\"     |           ,'\\        |      .\n");
            printf("       `.       /     |          L          ,\\  .       |  .,---.\n");
            printf("         `._   '      |           \\        /  .  L      | /   __ `.\n");
            printf("            `-.       |            `._   ,    l   .    j |   '  `. .\n");
            printf("              |       |               `\"' |  .    |   /  '      .' |\n");
            printf("              |       |                   j  |    |  /  , `.__,'   |\n");
            printf("              `.      L                 _.   `    j ,'-'           |\n");
            printf("               |`\"---..\\._______,...,--' |   |   /|'      /        j\n");
            printf("               '       |                 |   .  / |      '        /\n");
            printf("                .      .              ____L   \\'  j    -',       /\n");
            printf("               / `.     .          _,\"     \\   | /  ,-','      ,'\n");
            printf("              /    `.  ,'`-._     /         \\  i'.,'_,'      .'\n");
            printf("             .       `.      `-..'             |_,-'      _.'\n");
            printf("             |         `._      |            ''/      _,-'\n");
            printf("             |            '-..._\\             `__,.--'\n");
            printf("            ,'           ,' `-.._`.            .\n");
            printf("           `.    __      |       \"'`.          |\n");
            printf("             `-\"'  `\"\"\"\"'            7         `.\n");
            printf("                                    `---'--.,'\"`'   \n");

            break;

        case 9:
            printf("                       _\n");
            printf("            _,..-\"\"\"--' `,.-\".\n");
            printf("          ,'      __.. --',  |\n");
            printf("        _/   _.-\"' |    .' | |       ____\n");
            printf("  ,.-\"\"'    `-\"+.._|     `.' | `-..,',--.`.\n");
            printf(" |   ,.                      '    j 7    l \\__\n");
            printf(" |.-'                            /| |    j||  .\n");
            printf(" `.                   |         / L`.`\"\"','|\\  \\\n");
            printf("   `.,----..._       ,'`\"'-.  ,'   \\ `\"\"'  | |  l\n");
            printf("     Y        `-----'       v'    ,'`,.__..' |   .\n");
            printf("      `.                   /     /   /     `.|   |\n");
            printf("        `.                /     l   j       ,^.  |L\n");
            printf("          `._            L       +. |._   .' \\|  | \\\n");
            printf("            .`--...__,..-'\"\"'-._  l L  \"\"\"    |  |  \\\n");
            printf("          .'  ,`-......L_       \\  \\ \\     _.'  ,'.  l\n");
            printf("       ,-\"`. / ,-.---.'  `.      \\  L..--\"'  _.-^.|   l\n");
            printf(" .-\"\".'\"`.  Y  `._'   '    `.     | | _,.--'\"     |   |\n");
            printf("  `._'   |  |,-'|      l     `.   | |\"..          |   l\n");
            printf("  ,'.    |  |`._'      |      `.  | |_,...---\"\"\"\"\"`    L\n");
            printf(" /   |   j _|-' `.     L       | j ,|              |   |\n");
            printf("`--,\"._,-+' /`---^..../._____,.L',' `.             |\\  |\n");
            printf("   |,'      L                   |     `-.          | \\j\n");
            printf("            .                    \\       `,        |  |\n");
            printf("             \\                __`.Y._      -.     j   |\n");
            printf("              \\           _.,'       `._     \\    |  j\n");
            printf("              ,-\"`-----\"\"\"\"'           |`.    \\  7   |\n");
            printf("             /  `.        '            |  \\    \\ /   |\n");
            printf("            |     `      /             |   \\    Y    |\n");
            printf("            |      \\    .             ,'    |   L_.-')\n");
            printf("             L      `.  |            /      ]     _.-^._\n");
            printf("              \\   ,'  `-7         ,-'      / |  ,'      `-._\n");
            printf("             _,`._       `.   _,-'        ,',^.-            `.\n");
            printf("          ,-'     v....  _.`\"',          _:'--....._______,.-'\n");
            printf("        ._______./     /',,-'\"'`'--.  ,-'  `.\n");
            printf("                 \"\"\"\"\"`.,'         _\\`----...'   \n");
            printf("                        --------\"\"'\n");
            printf("\n");
            printf("\n");

            break;

        case 10:
            printf("                   _,........_\n");
            printf("               _.-'    ___    `-._\n");
            printf("            ,-'      ,'   \\       `.\n");
            printf(" _,...    ,'      ,-'     |  ,\"\"\":`._.\n");
            printf("/     `--+.   _,.'      _.',',|\"|  ` \\`\n");
            printf("\\_         `\"'     _,-\"'  | / `-'   l L\\\n");
            printf("  `\"---.._      ,-\"       | l       | | |\n");
            printf("      /   `.   |          ' `.     ,' ; |\n");
            printf("     j     |   |           `._`\"\"\"' ,'  |__\n");
            printf("     |      `--'____          `----'    .' `.\n");
            printf("     |    _,-\"\"\"    `-.                 |    \\\n");
            printf("     l   /             `.               F     l\n");
            printf("      `./     __..._     `.           ,'      |\n");
            printf("        |  ,-\"      `.    | ._     _.'        |\n");
            printf("        . j           \\   j   /`\"\"\"      __   |          ,\"`.\n");
            printf("         `|           | _,.__ |        ,'  `. |          |   |\n");
            printf("          `-._       /-'     `L       .     , '          |   |\n");
            printf("              F-...-'          `      |    , /           |   |\n");
            printf("              |            ,----.     `...' /            |   |\n");
            printf("              .--.        j      l        ,'             |   j\n");
            printf("             j    L       |      |'-...--<               .  /\n");
            printf("             `     |       . __,,_    ..  |               \\/\n");
            printf("              `-..'.._  __,-'     \\  |  |/`._           ,'`\n");
            printf("                  |   \"\"       .--`. `--,  ,-`..____..,'   |\n");
            printf("                   L          /     \\ _.  |   | \\  .-.\\    j\n");
            printf("                  .'._        l     .\\    `---' |  |  || ,'\n");
            printf("                   .  `..____,-.._.'  `._       |  `--;\"I'\n");
            printf("                    `--\"' `.            ,`-..._/__,.-1,'\n");
            printf("                            `-.__  __,.'     ,' ,' _-'\n");
            printf("                                 `'...___..`'--^--'   \n");

            break;

        case 11:
            printf("                                   ,--..\n");
            printf("                                  /     `.\n");
            printf("                                 /|       `.\n");
            printf("                                / |        |\n");
            printf("                               /  j        |\n");
            printf("                              /  |         `\n");
            printf("                             '  ,'          \\\n");
            printf("                           ,'                L\n");
            printf("                          /                  +\n");
            printf("                        .:.                   .      `\n");
            printf("                     ,\"`.  `.       ,..-._    +\n");
            printf("                     |  |`.  L     '   _.'`.   .\n");
            printf("                     j  `.,\\ '    | ,.' |  +.  +\n");
            printf("                    '`.    |,'    |\" `\"\"   / `, .\n");
            printf("                   |   `\"\"'/      `-.____.'    \\|\n");
            printf("                 ,'|     ,'                     Y\n");
            printf("                /  |    /                      '|\n");
            printf("               /   |  ,'                     ,' +\n");
            printf("              /    \\-'                      /    `\n");
            printf("             /    /                       ,'      `\n");
            printf("            .     ,`'-.                 ,'         L\n");
            printf("             \\   /     \\               /            .\n");
            printf("                /      `               \\            |\n");
            printf("              `/          _,            `          ,'\n");
            printf("               |                         `       ,'\n");
            printf("               |           \"'             `.   ,'\n");
            printf("               j         -\"'               |`-'\n");
            printf("              /                           /'/\n");
            printf("             /           ,               / /\n");
            printf("            /            '              j /\n");
            printf("          .' ___                        '/\n");
            printf("          |-'   `\"`-.                  '/\n");
            printf("          '          \\                .'\n");
            printf("        ,\"            l          _,.-'\n");
            printf("       ,---..         |L     _.-'\n");
            printf("     ,'      `.      / |  ,-'\n");
            printf("    /          `  _,'  ;-'\n");
            printf("  ,'--.       ,-`|  ,-'\n");
            printf(" /     L   _,'  _|-'\n");
            printf("(       \\-' _,-'\n");
            printf(" `......^.-'   \n");
            printf("\n");
            printf("\n");

            break;

        case 12:
            printf("       ,-.                                            ___.._\n");
            printf(" _     `. `.                                    _,-\"\"\"      ',._\n");
            printf("`.`.      `.\\                                _,'         _..-'  `.\n");
            printf("  `._\\       `.                            ,'         _,'_,.-'-.  \\\n");
            printf("      `.       `.                        ,'        ,-',-\"       \\  .\n");
            printf("        `.       \\                      /  _,----\"',-'           L  L\n");
            printf("          `.      \\                   ,' _.--\"-.  [              |  |\n");
            printf("            `.     .                 / ,'       | |     _..---../   |\n");
            printf("              .     L               / /         | j ,.-'        `   |\n");
            printf("               \\    .              ' /          j ,'             |  |\n");
            printf("                \\    .            ' /          ' /               |  |\n");
            printf("                 \\   l           / /          /,'                j  '\n");
            printf("                  L__L._        / /          +'      __,........'  j\n");
            printf("                ,'   '  \"`.    / /         .' _,.--'\"           \\  |\n");
            printf("               /,\"\"-.      `. ' '        _/.-'                  | F\n");
            printf("              /|   / l       . /       ,'                       | |\n");
            printf("             | |  /  |       ]'      ,'                         | |\n");
            printf("            ,._\\\"'   |       |     ,'-'\"\"\"\"\"\"\"\"\"\"\"\"\"'----.._    / |\n");
            printf("            |  \\`.._,'       F  _,'                         `--'  |\n");
            printf("            `..'           _/ ,:_____                         L   |\n");
            printf("              `..          .-'       `'--.._                   | j\n");
            printf("            _,. /,---.       \\              `--..              | |\n");
            printf("           F  <j-.'   `       ._                 `\"-._        j  '\n");
            printf("           |  <|`,.    |       `L._                   `..   _, ,'\n");
            printf("           `..<|`.___,'        |.  `-.                   Y\"' _.\n");
            printf("              `L               | `.   `-.._____________,',.-'\n");
            printf("                `.            .Y   \\      `\"\".\"\"\"\"\".  .\"'\n");
            printf("                  `.        ,' |\\   `.        `+-._ \\  |\n");
            printf("                    `,--. -'   | .    `.       `   `.| |\n");
            printf("                    /    //    |  \\    ``-..___/     | |\n");
            printf("                   j    .l     |   .    F   \\   `   F  |\n");
            printf("                   |    ||     |    `   `    .   ` ,  /\n");
            printf("                   |    ||    F      `-.|     . _,' _'\n");
            printf("                   |   / |    |       `._`-----'  ,'\n");
            printf("                   |  /  |   /           `-------'\n");
            printf("                   l /   \\_,'\n");
            printf("                    \"   \n");

            break;

        case 13:
            printf("               ,`.\n");
            printf("               L  \\\n");
            printf("              ,    \\\n");
            printf("             j      \\\n");
            printf("             ,       \\\n");
            printf("            j         `\n");
            printf("            ,          .__\n");
            printf("         ,-'Y          `  `-.\n");
            printf("      .-'    `..___..-'      `-.\n");
            printf("     /__           ,-.          \\\n");
            printf("    /(__)         `   '          `.\n");
            printf("   |               `\"'             L\n");
            printf("   `.------._                      |\n");
            printf(" ,'          `                     |\n");
            printf("F             |                    |\n");
            printf("|             |                    |\n");
            printf("`._         ,'                     j\n");
            printf("   `+------'                      /\n");
            printf("     \\                           /                         |`._\n");
            printf("      `.                       ,'                          |   \\\n");
            printf("        `._                _,-'                            |    \\\n");
            printf("           `-,.________,.-'   `.                           |     L\n");
            printf("            /                   '                          |     |\n");
            printf("           /             _,._   |                          ,`---,'\n");
            printf("         ,'|            /    .  j                        .'      `.\n");
            printf("         . L            '    | ,                      ,-'\"'`-..   |\n");
            printf("          .,\\            `--' / `.               ___./       ,.' ,'\n");
            printf("             \\              ,'    \\__         ,-'     \"-.    | |'\n");
            printf("              `-._______,.-'  __   | `'-._.,- ._        _`   `\"Y\n");
            printf("                |           .\"  \\  |     \\      `.    ,'  \\   ,'\n");
            printf("                |           '    | ;      .       .   `._./.-'\n");
            printf("                7.           `'\"' / `.--. |   _.. |      j\n");
            printf("                `.__       `   _-'   |   |j  /   ||     .'\n");
            printf("                    `-...,_..-'      `--'/   `._, ^----'\n");
            printf("                         .\\            _'       ,'\n");
            printf("               `         `._-.______,.'`.___,.-'  \n");
            printf("\n");

            break;

        case 14:
            printf("           _,--'\"\"\"\"\"\"---.._\n");
            printf("         ,'                 `._\n");
            printf("       ,'                      `.\n");
            printf("     ,'                          \\\n");
            printf("    .                             \\\n");
            printf("  ,'.                  ,-`.        \\\n");
            printf(" /   \\               ,'    ,        \\\n");
            printf("|`.  |\\            ,`      |         |\n");
            printf("L  `.| |         .''     _,'        _'\n");
            printf(" \\    \"'        ,`'_..-''        _,'\n");
            printf("  `.            '\"\"          _,.' `.\n");
            printf("    /._                 _..-\"       \\\n");
            printf("   /   `.          _,.-'             \\\n");
            printf("  /      \\-.___.--'/                  \\\n");
            printf(" |      ,/.     .-^+.._               F\n");
            printf("  L..-''.' \\  .'   |   `'--.....___   .\n");
            printf("  /     /   `/     |               `\"-;\n");
            printf(" /     j    j      '                ,'\n");
            printf(" `.    |    |       L          _.-'Y\n");
            printf("  ,`._/     |        .    _,.-'     .\n");
            printf("  `.  '|    |         \\\"\"\"|         |\n");
            printf("   |   |    |         |   |         |\n");
            printf("   |   |    |        ,'   |         |\n");
            printf("   |   L    +      ,'     |         |\n");
            printf("   |    \\    L    ,\\      j         |\n");
            printf("   L     \\   |   /  `.   /          j\n");
            printf("    \\    j\\  |  /    `. /          .\n");
            printf("     L  .  ` | /       \\          /\n");
            printf("     +  |   `|/                  /\n");
            printf("      \\ | _,..._         \\      /\n");
            printf("       ./'      `-._      \\   ,'\n");
            printf("        l           `.     ^_/\n");
            printf("        +             `   /\n");
            printf("         L-\"\"--.       .,'\n");
            printf("         |      `.     ,\n");
            printf("         .        \\  ,'\n");
            printf("          `       _.'\n");
            printf("           `....-'   \n");

            break;

        case 15:
            printf("                     ,--\"\"+--.\n");
            printf("                    /     j   /`.\n");
            printf("                   |     /   |   `.\n");
            printf("                   |   ,'    '     \\\n");
            printf("                   j,-'     '`..    \\\n");
            printf("                  +      _ /    `._/ \\\n");
            printf("                  |     / '-.     |   .\n");
            printf("                  |    /     |   /    |\n");
            printf("                  |   /     j   j     |\n");
            printf("                  |  j      |   |     |._\n");
            printf("                  | .'     7    |     |  `.\n");
            printf("  ___      _.._   | j      |    +     '    `.\n");
            printf(" |.---=-.,'+-. `. |/       F     L  ,'    ,'`.\n");
            printf(" ||,==--'|_' |  j  \\      /      |,'   ,`'    L\n");
            printf(" 'Y'   | |  '/ ',.-.\\    j     ,,^  _,' \\     |\n");
            printf("`.||   |  `.'  '    `.   / _,-'   `'     L   F\n");
            printf("  ||   `     .  ,-.   `,--'              |   |\n");
            printf("  `'    `.  /_,' ,'     `--------------\"\"\"\"'Y\n");
            printf("         _:\"'_.-'       /_>:-.__           /\n");
            printf("      `-\".`\"'__,`-.,-._/      `.\"\"`------\"'\n");
            printf("      `.| `\"'      | | _.--'\"\"'--\\\n");
            printf("       || /        | '\"  ___,.._  \\\n");
            printf("      _|||__      / /,.-'       `- .\n");
            printf("    ,'   `. .    /,'/'  _.,-\"\"\"--._F\n");
            printf("    7     | |  .',L'|_-'           |\n");
            printf("    +     | | / / ',\"'  ,.-'\"\"'`-._|\n");
            printf("     L    ' |. /  .-.`\"'           |\n");
            printf("     |   j j   \\  `-.'\\           j\n");
            printf("     +   | | \\  `.   ` `.  _.... ,\n");
            printf("      L  | |  \\   .   `  \\\"     /\n");
            printf("      | ,' |   L  ,'    \\ `    .\n");
            printf("      | || |   '  |      L `   |\n");
            printf("      `./|j     `. .     `. \\ j\n");
            printf("       |  '       ` .     | '\\`\n");
            printf("                   \\ '.   | \\\n");
            printf("                    | |  /,-'\n");
            printf("                    j l  \"\n");
            printf("                  _/_,'\n");
            printf("                 ','   \n");

            break;

        case 16:
            printf("                   .,\n");
            printf("            , _.-','\n");
            printf("          \"\"|\"    `\"\"\"\".,\n");
            printf("         /'/       __.-'-\"/\n");
            printf("        ','  _,--\"\"      '-._\n");
            printf("    _...`...'.\"\"\"\"\"\".\\\"\"-----'\n");
            printf(" ,-'          `-.) /  `.  \\\n");
            printf("+---.\"-.    |     `.    .  \\\n");
            printf("     \\  `.  |       \\   |   L\n");
            printf("      `v  ,-j        , .'   |\n");
            printf("     .'\\,' /        /,'      -._\n");
            printf("    ,____.'        .            `-.\n");
            printf("        |         /                `-.\n");
            printf("       /          `.                  `-.\n");
            printf("      /             `. |                 `.                  _.\n");
            printf("     .                `|                 ,-.             _.-\" .\n");
            printf("    j                  |                 |  \\         _.'    /\n");
            printf("    .                  |               .'    \\     ,-'      /\n");
            printf("    |                  |            ,-.\\      \\  ,'      _.-\n");
            printf("    |                . '  `.       |   `      `v'  _,.-\"/\n");
            printf("    ||    \\          |  ` |(`'-`.,.j         \\ `.-'----+---.\n");
            printf("    |'|   |L    \\  | |   `|   \\'              L \\___      /\n");
            printf("    ' L   |`     L | |     `.                 | j   `\"\"\"-'\n");
            printf("       `-'||\\    | ||j       `.       ._    ` '.\n");
            printf("          `\\ '\"`^\"- '          `.       \\    |/|\n");
            printf("            `._                  `-.     \\   Y |\n");
            printf("    __,..-\"\"`..`._                  `-._  `\\ `.|\n");
            printf("   +.....>+----.' \"\"----.........,--\"\"\" `--.'.'\n");
            printf("       ,' _\\  ,..--.-\"' __>---'  |\n");
            printf("      --\"\"  \"'  _.\" }<\"\"          `---\"\"`._\n");
            printf("               /...\"  L__.+--   _,......'..'\n");
            printf("                 /.-\"\"'/   \\ ,-'\n");
            printf("                     .' ,-\"\"'\n");
            printf("                    /.-'   \n");

            break;

        case 17:
            printf("                        |\n");
            printf("                   ____ A,\n");
            printf("               _,-'\\  || /`'`.\n");
            printf("              /-.   '.'|    ,'-.\n");
            printf("            .'   `. |/j | ,'    ..\n");
            printf("           .\"\"|._  \\` | ,'  _.,\\--.\n");
            printf("           '/ |  |\"\\\\,| |,\"| |  |  \\\n");
            printf("           |.'_..|().\\../()|_/\\ |\\ |'\n");
            printf("           | |     ,'   `    L \\| Y\n");
            printf("           | '    /.-\"\"-.`    |||  \\\n");
            printf("           . |   |_,-----.|   j||  `\n");
            printf("           | .   . .     ,'  /,'/\n");
            printf("         __|  \\   \\ \\__,'/  // j\n");
            printf("     _,'\" ,'   `._ `.__.'  ,'  |---._\n");
            printf("   ,'    .        `\"----\"\"'    .     `.\n");
            printf("  ,     .                       `      `\n");
            printf(" /     /    ,-\"\"\"\"\"\"\"\"\"\"\"\"\"--._  \\      '\n");
            printf(" |    j   ,'                   `. `     |\n");
            printf("|'.'  |  /                       `.|    |\n");
            printf("| `.  /.'                          \\  | |\n");
            printf("L  `'v'/                            . |,|\n");
            printf(" \\   '|                             | 'j\n");
            printf("      |                             ./ /\n");
            printf("  `   '                             j /\n");
            printf("   `  `                            / /\n");
            printf("    `. .                          / /\n");
            printf("      `.`.                       /,'\n");
            printf("         \\`.                   ,',\n");
            printf("          . `                 .-\n");
            printf("           `.  +.       _,.- ,'\n");
            printf("            |`-| `\"--\"\"' `,'-|\n");
            printf("           ,'  | _      _ |  |\n");
            printf("   ,--...-'    `' |> <(\"     |-..__,..\n");
            printf(" ,'    _.+- ,  +..'    --.  .  `.___  '\n");
            printf("`-\"\"--:-' ,' |  `.       |   `..   .||_\\\n");
            printf("     /\"|_'   `.,-|       | _.|  `-.'_\\ `\n");
            printf("     .'        | |        ` ||\n");
            printf("                '          V'   \n");

            break;

        case 18:
            printf("                   ..-`\"-._\n");
            printf("                 ,'      ,'`.\n");
            printf("               ,f \\   . / ,-'-.\n");
            printf("              '  `. | |  , ,'`|\n");
            printf("             `.-.  \\| | ,.' ,-.\\\n");
            printf("              /| |. ` | /.'\"||Y .\n");
            printf("             . |_|U_\\.|//_U_||. |\n");
            printf("             | j    /   .    \\ |'\n");
            printf("              L    /     \\    .j`\n");
            printf("               .  `\"`._,--|  //  \\\n");
            printf("               j   `.   ,'  , \\   L\n");
            printf("          ____/      `\"'     \\ L  |\n");
            printf("       ,-'   ,'               \\|'-+.\n");
            printf("      /    ,'                  .    \\\n");
            printf("     /    /                     `    `.\n");
            printf("    . |  j                       \\     \\\n");
            printf("    |F   |                        '   \\ .\n");
            printf("    ||  F                         |   |\\|\n");
            printf("    ||  |                         |   | |\n");
            printf("    ||  |                         |   | |\n");
            printf("    `.._L                         |  ,' '\n");
            printf("     .   |                        |,| ,'\n");
            printf("      `  |                    '|||  j/\n");
            printf("       `.'    .             ,'   /  '\n");
            printf("         \\\\    `._        ,'    / ,'\n");
            printf("          .\\         ._ ,'     /,'\n");
            printf("            .  ,   .'| \\  (   //\n");
            printf("            j_|'_,'  |  ._'` / `.\n");
            printf("           ' |  |    |   |  Y    `.\n");
            printf("    ,.__  `; |  |-\"\"\"^\"\"\"'  |.--\"\"`\n");
            printf(" ,--\\   \"\"\" ,    \\  / \\ ,-     \"\"\"\"---.\n");
            printf("'.--`v.=:.-'  .  L.\"`\"'\"\\   ,  `.,.._ /`.\n");
            printf("     .L    j-\"`.   `\\    j  |`.  \"'--\"\"`-'\n");
            printf("     / |_,'    L ,-.|   (/`.)  `-\\.-'\\\n");
            printf("    `-\"\"        `. |     l /     `-\"`-'\n");
            printf("                  `      `-   \n");

            break;

        case 19:
            printf("                                      ,'\"\"`--.\n");
            printf("                                     |     __ `-.\n");
            printf("                                     |    /  `.  `.\n");
            printf("                                      \\        ,   `.\n");
            printf("                                       `.      \\_    `.\n");
            printf("                                         `.    | `.    \\\n");
            printf("                                           `--\"    `.   `\n");
            printf("                                                     `.  `\n");
            printf("                 ,.._                                  \\  `\n");
            printf("               /_,.  `.                                 \\  `\n");
            printf("              j/   .   \\                  ___            \\  \\\n");
            printf("              |    |   `____         _,--'   `.           .  L\n");
            printf("               L  /`--\"'    `'--._ ,'   ,-`'\\ |            . |\n");
            printf("                |-                /  ,''     ||            | |\n");
            printf("     -v._      /                   ,'        ||            | |\n");
            printf("       `.`-._,'               _     \\        |j    _,...   | |\n");
            printf("         `,.'             _,-. \\     |      /,---\"\"     `- | |\n");
            printf("        .'              ,\".   ||     `..___/,'            `' |\n");
            printf("        |   ,         _/`-'  /,'                            `|\n");
            printf("        |-.__.-'\"''\"\"' \"\"\"\"\"\"\"\"--`_,...-----''''--...--      `.\n");
            printf("         `.____,..              \"\"   __,..---\"\"\"              |\n");
            printf("          |       `              --\"'.                        `\n");
            printf("          |     ,' `._                \\'                       `\n");
            printf("          | |  .^.    `.             /                          `.\n");
            printf("         ,'_]__|  \\   / `.          /          /____._            `._\n");
            printf("       ,'          \\ j    '        /          /       `.             `.\n");
            printf(" ___,.' `._       __L/    |     __'          /     _, / \\             |\n");
            printf("`-._       L,.-\"\"\"  .    ,' _.-','          /-----'-./   `--.         |\n");
            printf("   '   / ,'         '..'\"_,'    /         F /  .\"'_,'        |.__     '\n");
            printf("  / ,.\\,'              \"\"      /         / (,'\\ .'        ,.-\"'  `.  j\n");
            printf("  -'   '                      /        ,'     `\"         / __/' .- ,'\n");
            printf("                           __.'\"`.    /                 `-' | _,L,'\n");
            printf("                         .',      `\"\"'                      '/,--\n");
            printf("                          / _..' _,,'\n");
            printf("                          ,' `-\"'   \n");

            break;

        case 20:
            printf("                        |.     .|\n");
            printf("                      `.  `._.' |,'Y'     _.......\n");
            printf("      +--------..  _\\\"'  \"\"\"\"\"\"'--.=-_ ,-'  ,.-- '     .\n");
            printf("       |  '\"\"`.  `.`-._           .-\" |   .'    (      |`\n");
            printf("       j       \\  |..'-- ,-----. ,.]..|  /       `.    L .\n");
            printf("  ____(___     |      _.' -  , `--..    | __.....-/-..__|L\n");
            printf(".'._______\"\"\"\"----  ,'   _____._    ` ,-':,...------\"\"\"\"i .\n");
            printf("         |\"\"\"\"-.  -'    '.     /`    ' -------.j__      | |\n");
            printf("     .,--------        / \\    j  L      `=..-\"\"----'    | |\n");
            printf("           ,-_,.-     j   L | |   .     `-..:-.__       | |\n");
            printf("        ,++-.  |      |   /-+-|   |       | `\"-._`._    | |\n");
            printf("      .+\"\" '- .'      L  j  | L   j       | L    `-.`.  F-|\n");
            printf("    ,'    .-) `,       \\_/     \\ /        j  \\       ` /-.|\n");
            printf("   '        |  .        `.......-        /   j_       j  j\n");
            printf("         .--|  ,\\_                      ,'\". / )     ,^-.|\n");
            printf("          `.`,-                        /  / / ,`._  ,.   F\n");
            printf("       \"\"\"| '  .'`.'                   `-'\\ \"'  \\ \\,  \\ /\n");
            printf("      | j`.    |     . ,. .,..  ,_  .     `...-.| |.  ,'\n");
            printf("      `-'  /\"\"/    ,' .' \\ '  `/. `-       Y   |`\"  `/\n");
            printf("          j  /'                             .  | \\ ,'\n");
            printf("           \\ \\                              |  | ,'\n");
            printf("           ' '                              j j-'\n");
            printf("            `.\\                            ,.'\n");
            printf("            _+.`.                       _.,---.._    _\n");
            printf("   ,-\"\"--.,'   `--.._              ,::`\"-        '\"\"' -.\n");
            printf(" .'  _..--          ,`\"`--------\"\"'  `._    ....<\"\"`-\",.'\n");
            printf(" `-\"'   _,-\"\"'  _,-'                    `-..__   v._  `.\n");
            printf("   / ,-'/  _,-`'                              `-. \\ `-.|\n");
            printf("   -'  |_,'                                      \"'   \n");

            break;

        case 21:
            printf("               _,\n");
            printf("             .'.'  _.\n");
            printf("           ,' ._,-'_\"'\n");
            printf("        _,'   '  ------\"\"'`._\n");
            printf("      ,'                 _,.--\"'              ___        __,..\n");
            printf("      |    _,..       ,-'             _,.--\"\"'   7_,.--\"'    ,'\n");
            printf("      j. .'D  |       |            ,'\"       _.-'       _.-\"\"'.  _,..-\"'\n");
            printf(" ,---'  `+----'       |`._      _.'         '                '.-'      /\n");
            printf("j         `.       ,-'    `'--,\"                           ,'       ,-'\n");
            printf("|    __    |      '-.._,    .'                           ,'     ,.-'\n");
            printf("`. ,' ('T--'        .\"     /                          _.'  _,--\"\n");
            printf("  `   `,  /         _`.   j                         _', ,-\"__,..,-.\n");
            printf("      `-\"`.        \\   `-.|                        _,'\"\"\"\"'       l\n");
            printf("           `.,      \\     L                     _.'      __,...--'\n");
            printf("            ` '-    .`     `._             _,.-' ,--'\"\"\"\"\n");
            printf("             '  \\`.,\\         `+------,--\"'     /\n");
            printf("                 \\ )`'      ,-'      /         /\n");
            printf("                  `     _,-'       ,'         /\n");
            printf("                   `+\"\"'         ,'     ,.  ,'\n");
            printf("                     `.        ,'     ,'   .\n");
            printf("                       `-._.,-'      /. _.,j\n");
            printf("                           \"\"`-----.'  '  /\n");
            printf("                                / /   /  /\n");
            printf("                    _.......__,' /__,' ,'\n");
            printf("                  ,\\  ,--..--------\"_  ...._\n");
            printf("                 '--\"(_,`|  ,..-' _,....__  |.\n");
            printf("                        '-./...-'\"        `\"\"\"-   \n");

            break;

        case 22:
            printf("    ,---...__     ,.._\n");
            printf("  .\"\"\"_...   \"\"---\\.,_`\"-._                    __,..._\n");
            printf(" ,--   \"\"\"\"\"\":--..    \"-   `-._ _,.        ,-\"\" ..----'\"\"\",\n");
            printf("`---........_____ ._     `-._  `. |       / /'      '\"\"\"\"-----.\n");
            printf("\\\"'\"\"\"\"\"\"''\"\"\"'\"-`           `-. `.      / j     .\\ |\\   -.,:,- .\n");
            printf(" `-.......___     `._           \\  \\    ]\\ |   . |L ||/\\   `. ` .`.\n");
            printf("         __,..==--'/ '           \\  L  A|,'|    \\| |||||  ` .`.. -._\n");
            printf("    .--\"\"          `.             L | j  /'\"-.__\\V '/|||   | `. `._ `.\n");
            printf("      `....----_..-`\"`/.          | | | j   __ `._   | |'_`.\\  `.  `. |\n");
            printf("            -\"'       \\           | `_|.   l  `.  `.   |||   ` | `   \\'\n");
            printf("            `-._,...-\"\"\\-         |        |    .   /`.  \\  ..Y   `.  \\\n");
            printf("               `-..,'  .`         '         L \\  .  `--\"`.`.`|  .   \\  |\n");
            printf("                  \\  ,'  `|     ,'          .\\ +-'-...-^._`. | |..  ,\\ '\n");
            printf("                   `\\     `.._ j             /\"       \\  |\\ `..- `.'- `\n");
            printf("                    `. ,' | .  |           .'          \\ | `._`.\n");
            printf("                      +   | | j           /             `'    `.`.\n");
            printf("                       `.+._j_'      __..)                      `..\n");
            printf("                        _,-'   .,   j ` .'\"\"`--.                  `\n");
            printf("                     _.' .-'  /,'`\"-.  ,` .\\ \\` `\n");
            printf("                   ,'  .' / /`,'    ||'` ,'`T|.`-|\n");
            printf("                 ___,'/_,._/        L|   . |'-'\\\"\n");
            printf("                                    `-   ||    '   \n");

            break;

        case 23:
            printf("        _,--\"\"'\"\"\"-.\n");
            printf("      ,'   .,-.     `.\n");
            printf("     '`...( |  |      \\\n");
            printf("    |      `--'        .\n");
            printf("    '_,...__,'          `\n");
            printf("     `._                 `\n");
            printf("        `..______         |\n");
            printf("             |.          ,|\n");
            printf("             | `-.....,-\" |\n");
            printf("             |            j\n");
            printf("             ^.         _F\n");
            printf("            /  `-.....-'/\n");
            printf("           /          ,'\n");
            printf("          /          /\n");
            printf("         /          /\n");
            printf("        j       _.-- .\n");
            printf("        |      /     ,+---....___\n");
            printf("        L     /     /            \"\"`-.._\n");
            printf("         \\   j     j                    `-.\n");
            printf("          `. |     |            .'         `\n");
            printf("            `+...__|__       .,+-..         |\n");
            printf("                      \"\"`._.l      `.       j\n");
            printf("                      ,.-\"   \"-.     L    ,'\n");
            printf("                    ,'          L    : _.'\n");
            printf("                   /            |   _:'\n");
            printf("                  .            .|,-'\n");
            printf("                   .            `.._\n");
            printf("   '\\               `-.             `\"-.\n");
            printf(" ,`.'                  `-.              L\n");
            printf(" |  )                     `-. _...__     |\n");
            printf(".'-'                         )      `.   j\n");
            printf("|  |_                      _,'\"\"`.    \\ /\n");
            printf(" .-' `+._               _,\"       `.  |/\n");
            printf("  \\   |  \"`,,,,,....---'           | .'\n");
            printf("   `-.'   /                        |+\n");
            printf("      `--+                     _.-'\n");
            printf("          `--.___       __.---'\n");
            printf("                 `\"\"\"\"\"\"   \n");

            break;

        case 24:
            printf("                   _,.----'\"\"\"'---..._\n");
            printf("              _,-'\"                   `-..\n");
            printf("           _,'                            `-.\n");
            printf("         ,'                                  `-.\n");
            printf("       ,'                                _,..._ `.\n");
            printf("      /                               ,.\"     `:- L\n");
            printf("    ,'                             |.'         / ||\n");
            printf("   /            _,.-._             L        .-' -,'\n");
            printf("  /        _,.-\"      `.            `     __   .'\n");
            printf(" j      _,\"           ||\\|           `. ,-  _.'\n");
            printf(".     ,' `-..________.-' |            |' ,-'\n");
            printf("|   .' `--,.___       _,'| /`.        ` '\n");
            printf("|   |     `._  '\"\"\"\"\"'   . `_Y.        Y_\n");
            printf("`._          `-...__      `.`-'        | `-,...___\n");
            printf("   ``-,.._          `\"\"--.._`.         |  /     _,+`-._\n");
            printf("    .'    '--._             `-+      _ |./    ,\"       \\\n");
            printf("   ,  _,...._  `..             `-.:L_,v-'\"`-./_____     L\n");
            printf("  .,-\"       `-.| `,                )/       \\     \"`   |\n");
            printf("  j             |  \\`\\       _,......|       |       `  |\n");
            printf("  |       _,.---^.v[\\_   _,-'        |       |        \\ '\n");
            printf("  |     ,\"       _>.. \"\"\"            |       |        _V\n");
            printf("  '    .        /  |'`\\              |.._   ,'     _,'\n");
            printf("   .  j       ,'    |  `._           |   `\"\"-----\"'\n");
            printf("    \\ |      j      '     `--..,,,..j\n");
            printf("     Y       |       \\             /\n");
            printf("      `.     |        \\           /\n");
            printf("        `.   `         `.      _,'\n");
            printf("          `._ `.         `--..'\n");
            printf("             `---...,,,...-\"'   \n");
            printf("\n");

            break;

        case 25:
            printf("                                             ,-.\n");
            printf("                                          _.|  '\n");
            printf("                                        .'  | /\n");
            printf("                                      ,'    |'\n");
            printf("                                     /      /\n");
            printf("                       _..----\"\"---.'      /\n");
            printf(" _.....---------...,-\"\"                  ,'\n");
            printf(" `-._  \\                                /\n");
            printf("     `-.+_            __           ,--. .\n");
            printf("          `-.._     .:  ).        (`--\"| \\\n");
            printf("               7    | `\" |         `...'  \\\n");
            printf("               |     `--'     '+\"        ,\". ,\"\"-\n");
            printf("               |   _...        .____     | |/    '\n");
            printf("          _.   |  .    `.  '--\"   /      `./     j\n");
            printf("         \\' `-.|  '     |   `.   /        /     /\n");
            printf("         '     `-. `---\"      `-\"        /     /\n");
            printf("          \\       `.                  _,'     /\n");
            printf("           \\        `                        .\n");
            printf("            \\                                j\n");
            printf("             \\                              /\n");
            printf("              `.                           .\n");
            printf("                +                          \\\n");
            printf("                |                           L\n");
            printf("                |                           |\n");
            printf("                |  _ /,                     |\n");
            printf("                | | L)'..                   |\n");
            printf("                | .    | `                  |\n");
            printf("                '  \\'   L                   '\n");
            printf("                 \\  \\   |                  j\n");
            printf("                  `. `__'                 /\n");
            printf("                _,.--.---........__      /\n");
            printf("               ---.,'---`         |   -j\"\n");
            printf("                .-'  '....__      L    |\n");
            printf("              \"\"--..    _,-'       \\ l||\n");
            printf("                  ,-'  .....------. `||'\n");
            printf("               _,'                /\n");
            printf("             ,'                  /\n");
            printf("            '---------+-        /\n");
            printf("                     /         /\n");
            printf("                   .'         /\n");
            printf("                 .'          /\n");
            printf("               ,'           /\n");
            printf("             _'....----\"\"\"\"\"   \n");

            break;

        case 26:
            printf("                                        _,--\"\"`---...__\n");
            printf("                            _.---\"\"\"\"`-'.   .-\"\"\"'`-.._`-._\n");
            printf("                _,.-----.,-\"         .\". `-.           \"---`.\n");
            printf("             _,' _,.-..,'__          `.'  ,-`...._      ,\"\"''`-.\n");
            printf("           ,' ,-'     / (  .   ,-.       |    `.  `-._  .       `.\n");
            printf("         ,',-\"       /   `\"    `\"'       '      .    _`. \\\n");
            printf("       ,','       ,-'7--.                 `.__.\"|   ( ` `j\n");
            printf("      '.:--.    ,'   |   .       |\\             '    `--'\n");
            printf("     /.     | ,'     |   |       `'            .\n");
            printf("    '       |',\".    |._,'                     `      _.--\"\"\"\"\"-._\n");
            printf("'.          `-..'    `.                      ,  \\  ,-' _.-\"\"\"\"\"-. `.\n");
            printf("` `                   F  -.                 /    ,' .-'          `  `\n");
            printf(" \\ `                 j     `.              ,-.   . /               . `\n");
            printf("    `.               |     .-`.           .  '-.  V                 . `\n");
            printf("  `   `.      .      | .    \\  \\         j      \\/|                  ' .\n");
            printf("   .    `.    |`.    |-.`._/`   .        |    ,'  A                  | |\n");
            printf("    \\     `. F   \\   |--`  \"._  |        `-.-\"   / .                 | |\n");
            printf("     \\      -'    `. |        `\"'                  |                 F '\n");
            printf("      \\             `+`.                           |                / .\n");
            printf("       \\              .-`                     .    j               / ,\n");
            printf("        \\              \\   `.               .'    /               ' .\n");
            printf("         \\       |`._   \\    `-.._        ,'    ,'              ,'.'\n");
            printf("          '      |   `.  `.       `<`\"\"\"\"'    .'             _,'.'\n");
            printf("           `     |     `-. `._      )   `.     .          _.'_.'\n");
            printf("            `    |        `--/     /`-._  .     `.___..--'_.\"\n");
            printf("             `   |          /     /._   `\"\"`.     `. _,.-\"\n");
            printf("              `  |         /     /   `--.....`.     `._\n");
            printf("               ` |       ,'     /              .\"\"\"\"'  `.\n");
            printf("                `'      , `-..,7                `    . `.`.\n");
            printf("                       .       '                 `.   \\  `v\n");
            printf("                      j.  ,   /                    `.._L_.'\n");
            printf("                      || .   /\n");
            printf("                      `\"-'__/   \n");
            printf("\n");
            printf("\n");

            break;

        case 27:
            printf("          _...-----'`._\n");
            printf("      _,-'   _`. .\"\". \\`._\n");
            printf("    ,'    ,-'   ` ` |  \\/--.\n");
            printf("  ,:_  ,-'       ` `|  |`.  `.\n");
            printf(" /   `'-..        `  .-'  `   \\\n");
            printf("j         `.--,    \\       `   :\n");
            printf("|         '--' |    \\       `._'-.\n");
            printf("|___     |     |     L      .'    `.\n");
            printf("|   `-. /|___.' `.   |    .'.       .\n");
            printf("|     ,'          .  j.  /   `.      \\\n");
            printf(".  _,'            |,'  `.      \\   ,<`.\n");
            printf(" .'             _.-      `      j.'  \\ \\                          ,.\n");
            printf("  `       ,v-\"\"'   \\      )__,+'      . \\                       ,' |\n");
            printf("   `.    / |  /  _,'`.  ,'  \\  \\       /`.                   _.:   |\n");
            printf("     `,-'-`  / ,'     \\'    j,  \\   ,.'   L               ,-'   . F\n");
            printf("     / ,. | / .        \\  .'     \\.-\\     |         _,.-\"`.     `,'\n");
            printf("     (_\\/|'|   \\        .'   _,-\"    `    +....---+'       `     '\n");
            printf("     . \\ |.     \\    ,.^---`<_        | ,'||       \\        \\   /\n");
            printf("      `.'| \\_    :v-'         `.      |-  | \\ __..--\\     _,'\\,'\n");
            printf("        `'/`----'/              '.  ,'    |  Y       L_,-'  ,'\n");
            printf("          \\     /            ___,.'\\     j   |       |    .'\n");
            printf("           \\   .\"`\",\"\"'\"\"\"'\"`     | .   .'   |       |  ,'\n");
            printf("            \\  |   |         |    | | .' j,.-|       j-'\n");
            printf("             `. ___|________/.....|_Y'  /    |   _.-'\n");
            printf("          __,-' \\                 |    /    _j,-'\n");
            printf("         '--.    .                `...+---\"\"\n");
            printf("        `_____\\  _`..__    __,..-\"'\n");
            printf("              .-'_|._  `\"\"\"       \\\n");
            printf("             , -'    .          __/\n");
            printf("             \"------------\"\"\"\"\"\"   \n");
            printf("\n");

            break;

        case 28:
            printf("                    ,\\\n");
            printf("                _,-'.+..----\"/_____\n");
            printf("             _,'---,        /      `\"\",\n");
            printf("           .'    ,'  __..../_     _,-'\n");
            printf("          /    ,' ,-\"       ,'---+--...__\n");
            printf("        ,'   ----'        ,'             `\"\n");
            printf("       '                ,'     ______  ,-\"`-._\n");
            printf("      /  ,+\"\"\",   ....-^--..<\"\"      ``-._    `-.\n");
            printf("    ,' .'-'  /      |        `._          `-.   _`-\n");
            printf("   /    `\"\"\"'       `           `.           `,\"\n");
            printf("  |                  `.           `.      ,-'\"--.\n");
            printf("  '               ,-   `._ ,-\"\"\"`.__:---\"\"'-._   `._\n");
            printf("   `-----..__  _,'     .-\".       `._         `.    `.\n");
            printf("   /________.'\"/      /  j         | `-._       `.    `.\n");
            printf("\\`-.`.__    )_/__    ._,-|         |     `.       `.\"\"\"'\n");
            printf(" .      `\"\"\"\"j   `\"\"`'   |         |       `.       `.\n");
            printf(" \\`._       /            L         '         `.....---\n");
            printf("  `  `..___'              \\      ,\"            .   `.\n");
            printf("   `.     `              _.\\ _.-\" `-._          `.   `.\n");
            printf("     `-._  \\         _,-\"-. '|        .`-.-\"\"\"\"``\\     `.\n");
            printf("         `\"-^'   _.-'        |         \\  `.      `---...-\n");
            printf("              \\.\"            |          L   `.     `.\n");
            printf("              /              `          |     \\      `.\n");
            printf("             j                `.        |      `,....__`\n");
            printf("             |                  \\       |       `   \\\n");
            printf("              .                  .      F        \\   `.\n");
            printf("      _,...,---`.                 `.   j `.       L--..`\n");
            printf("    ,\",.--\"'-.   -.                _`. |   `._    .\n");
            printf("    ,'        \\_.--`._     ,----.-<.  V       `-._ ._\n");
            printf("   /.---\"\".-\"\"\" )     `\"\"\"'      `. `-.._         `' `._\n");
            printf("        ,' _.-\"\"\"\"`.               |     `\"-..__        `-.\n");
            printf("        '\"\"         \\         _,..-'            `\"\"----...-'\n");
            printf("         '-----------+---\"\"\"\"\"   \n");
            printf("\n");
            printf("\n");

            break;

        case 29:
            printf("        .'-.                            ,.. _,._\n");
            printf("  ,--\"\".`.  `.                        ,'  /'    `-.._\n");
            printf("  \\__   `-`   \\                     ,'  ,' _____     `-.\n");
            printf("     | ,-.._   \\                  ,'    _,'     \\   ___.'\n");
            printf("     j |    `   L               .'    ,'        |  |\n");
            printf("    . j      \\  |              /    ,'  ___     |  |\n");
            printf("    | |  .\"\"\"|  `    _,.--....'|   /-'\"\"   `.   |  '\n");
            printf("    |j  j    `   `-\"\"          '  '         |   | F\n");
            printf("    ||  |    ,'                   `         |   | |\n");
            printf("    |`. |   /      ,\"\".       .    \\        |   ' |\n");
            printf("    `  `.  /,\\     |   \\     / `    \\       |,-' F\n");
            printf("     `.  `/ | \\    '    .   /.  |    \\   _,-   ,-'\n");
            printf("       `-. j  |\\       \"   /.|  |     `\"\"__..-'\n");
            printf("        .' |_ |(`        ,' )|__'      `._____\n");
            printf(".-------'.   `-'-`       `--\"\"      \"\"\"\"\"__..-'\n");
            printf(" \"\"\"\"\"\"--.                           \"\"\"(\n");
            printf("     ___.'        .                 -----..._\n");
            printf("   .\"____..       '   -'              \"\"`----`_\n");
            printf("          `.     . _._   _,             ,. `./ |\n");
            printf("            >     `.  .\"\".              \\ |  \\ j\n");
            printf("           j       `.,'  /               \"'   Y\n");
            printf("          /          `..'                     |\n");
            printf("                                              |\n");
            printf("         .                             ,\"-.   |\n");
            printf("         |                             |   \\  |\n");
            printf("         |                             .   /  |\n");
            printf("         |                              `-'   |\n");
            printf("         |   `.                           ,   '\n");
            printf("         L     \\                      _  /   /.\n");
            printf("          \\     \\             |      ( `/  .'  `.\n");
            printf("           L     `.           |       \"/ _/    _|\n");
            printf("         _,|       -,_        |       j-'_._  ,  `.\n");
            printf("        '..|       (_.'--.._  L       |-+_  ..`.,.`\n");
            printf("           |      j         \"\" .    __|   `\"'\n");
            printf("           |,..__<             |\"`,\"  \\\n");
            printf("           | _,x..)            '-' --.'\n");
            printf("            \"   \n");

            break;

        case 30:
            printf("                           _            _\n");
            printf("                          / )  _  _,.-\"\" )\n");
            printf("                        ,' /..' /\"   _,+'--\"`.\n");
            printf("                       /     / j_.-\"'     ,-\"\n");
            printf("                     ,'    ,'       _____  `\n");
            printf("                   _+__   .     _.-'     \\  `...._\n");
            printf("              ,'\"\"\"    \"\"/  _.-'          .       \\\n");
            printf("            ,'          '  ',--'\"\"`-.      L   ,-\"\n");
            printf("          .\"              .'         \\     |  /\n");
            printf("        ,' _                          \\    | j      _\n");
            printf("       / ,'   _,+-'                 _,'   ,' /_,.-\"\" |\n");
            printf("    _.' '  .+'.  \\               ,-\"___..\"  -'      ,'\n");
            printf(" ,-\"     ,'-' |  |           .,-\"\"''___,..-'       /\n");
            printf("j        `\"\"\"\"---'             '\"'\"\"       ._    , _.--\".\n");
            printf("\\   ,                                        `- ' `._  ,'\n");
            printf(" \\                            _.-'            .\"`.   `-. ____...----\"\"`\n");
            printf("  `.-\"-._,..---+ +          ,'       `         `.'      `.             |\n");
            printf("      `.        \\/        ,'          |            ,.---. \\           .\n");
            printf("        `._               +__,...__   |     ,     |     |  L        .'\n");
            printf("           `--...-\"\"`-._   /       `,\"    ,'      `     |  |      ,'\n");
            printf("                     /  `./        /    ,'         \\    j  '    .'\n");
            printf("                    /    j        /    .       _    `._'     ,-'\n");
            printf("                   j     '       /     |     .\" `         ,-'\n");
            printf("                   |, .<(       '      `      \\_/       ,'\n");
            printf("                   |-...+.___,./`.______\\             ,'\n");
            printf("                   `.'`.' \\/  V /_/.___  `.  _     _,'\n");
            printf("                                `....\\_`,-\",' |,-./\n");
            printf("                                        `\"\"..-'---`   \n");

            break;

        case 31:
            printf("                                          .\"\n");
            printf("                                        ,'  |\n");
            printf("                                      _,... '.___\n");
            printf("                             +--._  ,'.-\"+.      \"`-.\n");
            printf("                         _,---\\   `\" / |p|.'     \"'   \\\n");
            printf("                       ,- _.---\".   |_,'      ,-\"\"\"\"-._|\n");
            printf("                     ,' ,.'    .'          ,-'        ,'\n");
            printf("                   ,' ,' |    .          .^---._      |\n");
            printf("            |. _  `. /   .    |   ,---.+'       `.    |\n");
            printf("           ,| | `/\\|.    `    |  .      `-.       .  /\n");
            printf("       .---. \"`-`.,\\ \\    `-.,'  |         `-._   | '\n");
            printf("        `.-'        , \"\"\"\"--'..-  \\            `--'.L\n");
            printf("          .          |`.     `     `._             _,'   .\n");
            printf("           `.        |  `.    |_,..   `-..______.-'  _,-| |. ,\"\\\n");
            printf("             -.     /     +--'/    `.            -,\"'   `\"  \".-'\n");
            printf("               `-+-'      |  /       `.        '\\ |           .L_\n");
            printf("           -\"--.,-`._..._,' j          `.     / | '           (_,'\n");
            printf("          `.    j.-'     `- |            \\   j  |  `.  _...___'\n");
            printf("            `. /__ ,...._  \\|             |  |  |...-`\"\n");
            printf("              j|  `      ,-/`.           /   `  ;.._\n");
            printf("          ,-. ||   |\"\"-.'  |  `..__,...-'     \\'    `.\n");
            printf("          `   |/`--    .  /|                  /----.__\\\n");
            printf("           \\  .         `' /                 /         \\\n");
            printf("            . |           ,`.              ,'     ___..+--.\n");
            printf("            +-|          /   `-..______..-\"     ,\"  `.   /___\n");
            printf("          ,'  |         j               .'    ,'      `\"|    /\n");
            printf("       ,-+    .         |`._          ,+_    /          `-..'\n");
            printf("   _.-'  |     `.      /    ``-----:='   `.,'         _,..'\n");
            printf(",-'      L       `-.--'         ,,'        |       ,-'\n");
            printf("\\_        \\         `._    _,.-'           `.___..'\n");
            printf("  `.._     `._      __.+'\"'\n");
            printf("      `---... +---\"\"   \n");

            break;

        case 32:
            printf("                  .\"\\                            _\n");
            printf("                  | |  ,.                    _,-\" /\n");
            printf("                  j `-' /                 _.'   /..\n");
            printf("                ,'     |                ,'   _..  |\n");
            printf("               /       `.          .\"','  ,-'   \\ `...\n");
            printf("             .'          \\       ,' ,' ,-'      |   _/\n");
            printf("            /             \\     /    ,'         |  |\n");
            printf("           /               `.  /    /           |  '\n");
            printf("          |                  `/    /            | `.\n");
            printf("       .-.`                  /   ,'            j   |        _\n");
            printf("       \\                   /V   /              |  ,'     ,-' |\n");
            printf("        .                _/    /               | /    ,-'   /\n");
            printf("        |               |    ,'               j / _.-'    ,'\n");
            printf("        |               |   /                 ' \"\"       /\n");
            printf("     `\"--               |  /                  |        ,'  _,..-.\n");
            printf("      \\                 | j                  .'       ---\"'     /\n");
            printf("       \\               j  |                  /                ,'\n");
            printf("        \\       __...--.  |                 /_..-----.       /\n");
            printf("         \\   ,\"\"       |  |   _.           /        /      ,'\n");
            printf("          . /          |  |  /  |        ,'        /      /\n");
            printf("           Y           |  |.'   F    _,-'         /__,._ `.......\n");
            printf("        _,'               '    / _.+'   ,-\"\"-.        .'       ,'\n");
            printf("    _.-'                      `-'| |   ,      .       -._   ,-'\n");
            printf("_.-'                  .\"\\        | |    ._   ,'         / .'\n");
            printf(" `\"\"\"---...._        /D  |       | |      \"\"' .     __  `--.\n");
            printf("       / |  ,      ,`  `-|       ` |  /`    ,'    /\"  \\     `.\n");
            printf("      .  `_/      /  `-..|         |  .'   /      `.  |       \\\n");
            printf("      `          '-......'         |      .         `-'        L\n");
            printf("       \\                          ,'     j                     |\n");
            printf("        `                      _.'       |                    .-.\n");
            printf("        /    ,            _,.-'          |                    '  \\\n");
            printf("       j._            ,-+'             __|                  ,^.   \\\n");
            printf("      | | `+\"\"-.....,' .'           ,-'   `._           _.-'\"\"\"`\"\"\n");
            printf("      |,|  _`. |     ,+          _,'         `\"-------\"'\n");
            printf("      '  \"\"   \"     | ,\"\"-.   _,'\n");
            printf("                    |,` _.+--'\n");
            printf("                    ' \"'   \n");

            break;

        case 33:
            printf("    `._\n");
            printf("     \\ `.\n");
            printf("      \\  `.\n");
            printf("       .   `.\n");
            printf("       j     :-----+...-.\n");
            printf("       /  _,'   /\"\"_     `.     _,..._\n");
            printf("     ,'  '      .-\"c|\"`+- -+--\"'      `-.._\n");
            printf("   ,'            \"\"\"+_ |       _,--\"\"--.._ `---..\n");
            printf("  '     _             \"'      '\\          `--._  `.\n");
            printf(" |    -'                      _.'              `-. `.\n");
            printf(" (     __   ,.----.._        \\``-.                |  `._\n");
            printf("  `.  /_ \"\"\"   ___.| ,.      j  `.`.   ,          `.    `.\n");
            printf("    `'| |    ,'    '.'/'\"\"'\"'   j`. \\,'|  _________||\"\"`-'`.\n");
            printf("      `_.\\   j       j      __-'|_/'\"._:.\"  __       .    \"\n");
            printf("          | /        /      \\ `/        |`.   .   ..._`.\n");
            printf("          ||        /       | /         | |    :.'    -/\n");
            printf("          |'    _,-'        |.`.       ,' |   | |\\_\n");
            printf("    _     | `--'     _,-    . `.`--- ,'   /   |  .\\`-..\n");
            printf("    |`v,-'\"\"\"'`-.,.-'        `._``--'  _,'    |  | \\  ,'\n");
            printf(",--'`- _       \\ \\              '\"\"''`'       `_,'  +-\n");
            printf(" -.'    \\       . |                        /`     ,---.\n");
            printf(" -`\\    |       | L                        `-'     '\"\"'`\\\n");
            printf(" '---...:_      / \\                          |   ,.-\"\"\".|\n");
            printf("          '---+'   \\                         ' ,'       `\n");
            printf("               '`''\".                       / /          `.\n");
            printf("                     \\                     j |            '.\n");
            printf("                      `.                   | |              \\\n");
            printf("                        \\ _                |/             /\\|\n");
            printf("                         / \"-   --\"\"----+--'             / ||\n");
            printf("                        `v'\"\"\"\"\"-..     |      `..__.,.-'-.,,\n");
            printf("                         |         `-.,'           .`.J     /\n");
            printf("                         |            |             '---...'\n");
            printf("                         |     .     /\n");
            printf("                         |    | `,  j\n");
            printf("                        ..--+'\"--_  /\n");
            printf("                         `-.|     \\'\n");
            printf("                             `----'   \n");

            break;

        case 34:
            printf("                  _.___.._              ,'            ,. ____\n");
            printf("                   \\      '-.._      |: | '       __,- _ ... )\n");
            printf("                   j-\"\"\"|\"`-._ `.'.  | \\| |    ,\"'_,--.     `.\n");
            printf("                  |     |     `. `.\\-' j   .-.'  '     `.    |\n");
            printf("     _.           `     |       \\  \"  /    \\   .'       |    |\n");
            printf("    /  |           \\    L       j           )   \\       j   j\n");
            printf("   /   |            \\    `.   ,'_ ..   .__,. ,   `     /   ,'\n");
            printf("  /   j              `-._  `./  /`. \\       / /\"| \\ .-'  ,'\n");
            printf(" .  ,.|                _`+..    |.)`       ' (| |  ``._.'\n");
            printf(" |-'  |              ,'    /,     \"`'       '--\"   |   '`.\n");
            printf("j     |             '        \\ './.             |\\-'      `\n");
            printf("|     |            |          \\  `/, . . . _-|./ |        _\\\n");
            printf("| ,-\"\".            `-\"\"-.     |`-._`| \\--|'/|, ,,'    _.-' /\n");
            printf("|/     \\        __(      \\   ,+..._`---...-'_.--\"\". .'     \\\n");
            printf("|       `   ,-\"'   `._   | _.      `\"-....-'       `.    ,.---.\n");
            printf("|    ,-'\"  '\"'\\       L,-|'            `v           |  ,'      `\n");
            printf("L   /    .\"`--'       |  |              |           |||         `'\n");
            printf(" | /     `..        ,.|  |.             |          ,' '|       .\"\".\\\n");
            printf(" `'      | /        . `. | `.       _,--+--._    ,',-''|        `-'|\n");
            printf("  `     .,\"`. ,..  / `  `|   `-...-'         `\"-' / ,.-\\         /\"\".\n");
            printf("   \\   j    |`. |.-   `/. `.     __.-----...__   ,`/    `.___    \\  |\n");
            printf("    .  |    |  \\|      | \\\\ `- -'             `.. |       |  `,\"\" `.'\n");
            printf("     ` |   j .         | | \\                   |  |       |,-| \\\n");
            printf("      `'   | \".      ,-' `. L                  .-' `        ,'  |\n");
            printf("        `. |   \\    /     .'`.               ,'     `      /    |\n");
            printf("          `.    `\"\"'      /   `-._       __.' .'\\    `....'    /\n");
            printf("           ,'             \\ _____ `\"\"\"\"\"\"  _.'  /             '\n");
            printf("           ' ,--'\"\"`--.___,'     \"\"------''    '_    _,...__ /`.\n");
            printf("            `-........'                          `-.'       `,\"\n");
            printf("                                                     `\"\"\"---'   \n");

            break;

        case 35:
            printf("                    __.._\n");
            printf("                ,--'     \"`-._    _,.-,--------.\n");
            printf("    ________ ,-'              `-\"'   /     _.-'|\n");
            printf(" ,-'  '     :                       .    ,'    '\n");
            printf("|    '     j      _.._              |  ,'     j\n");
            printf("L   /      |    .'    `.            |.'      /\n");
            printf(" \\ j       |    `.,'   |           ,'       /    _\n");
            printf("  .|      ,'\\         /           '.___    / _.-\" |\n");
            printf("   `    .'   `-.....-'                 `- +-'    /\n");
            printf("    `. ,'                                `.     <__\n");
            printf("      `.             .\\ \\                 |   ___ ,'\n");
            printf("      |     | #      || |                  ,\"\"   \"`.\n");
            printf("      |     | #      `'_/                   .       `.\n");
            printf("     ,'     `.         ,-\"\".                L         `.\n");
            printf("    /     (__)       _  \"\"\"                  :\"\"-.      .\n");
            printf("   /             \\\"'u|         |/            |    \\     |\n");
            printf("  .               \\  |         |           | |     |    |\n");
            printf("  |     _          `-'        j           /  |     '    |\n");
            printf("  L      `.                   |          /   |   ,'     '\n");
            printf("   \\       `.                ,'         /    |_,'      /\n");
            printf("    `.   ,.<'                `+--.    ,'     /       ,'\n");
            printf("      `./`._'                 '_.`._,'      j      _,\n");
            printf("        /\"'                      \"          |   _,'\n");
            printf("       /   `._              .              '..-'\n");
            printf("      j       `-._           `            /\n");
            printf("      |        _,'`\"--........+.         /\n");
            printf("      ,\"-.._,-'                 `.  .-._/\n");
            printf("      '---'                       `+__,'   \n");

            break;

        case 36:
            printf("                                       __,......._\n");
            printf("    _............___          ____....<__         `\"._\n");
            printf("   '._      `\",     `'--._,.-'   ___     `\"-.    ___..>---,---------..\n");
            printf(" ____ -.,..--\"            `-  ,-'   `       .`-\"'       .'_         ,-'\n");
            printf("'._  \"\"'-.                  .'     _.._                    `-._ ,.-'\n");
            printf("   `-._   `._              .     ,'    `.                    ,-'----.._\n");
            printf("       _>.   -.            `     |      |                _,-'          )\n");
            printf(",..--\"\"`--\"\"\"\"\"`-.          \\    `-.    |             ,.+.__   _,;---\"\"\n");
            printf("\\_ |              `.         `.       _.'         _,-`      `\"\"   `.\n");
            printf("  \"\\                `       / _`\"----'           '                 /-.\n");
            printf("   `.____                  |  #      #' \\                         `,..'\n");
            printf("       ,-\"--...__          `--        --'                   ___,..'\n");
            printf("      '-.---\"'  |           -.,........,            ,.---\"\"\" .\n");
            printf("                |            |        \\'             \\\"\"--..._`\n");
            printf("                |             \\       /              |\n");
            printf("                .              `.    /               |\n");
            printf("                 ,               `--'                j\n");
            printf("                j \\                                 /\n");
            printf("                |  .                               '`.\n");
            printf("                 L._`.                           .' ,|\n");
            printf("                 |  `.:-._                    _,' ,' |\n");
            printf("                 `.,'| \"\"\"`.__            _,< _..-   '\n");
            printf("                     `...-'   `----------'   `-.__|`'   \n");

            break;

        case 37:
            printf("               _,.+-----__,._\n");
            printf("              /  /    ,'     `.\n");
            printf("     ,+._   ./...\\_  /   ,..   \\\n");
            printf("     | `.`+'       `-' .' ,.|  |\n");
            printf("     |  |( ,    ,.`,   |  `-',,........_       __......_\n");
            printf("      \\ |..`/,-'  '\"\"\"' `\"\"'\"  _,.---\"-,  .-+-'      _.-\"\"`--._\n");
            printf("       .\"|       /\"\\`.      ,-'       / .','      ,-'          \\\n");
            printf("      .'-'      |`-'  |    `./       / / /       /   ,.-'       |\n");
            printf("     j`v+\"      `----\"       ,'    ,'./ .'      /   |        ___|\n");
            printf("     |                      |   _,','j  |      /    L   _.-\"'    `--.\n");
            printf("      \\                     `.-'  j  |  L     F      \\-'             \\\n");
            printf("       \\ .-.               ,'     |  L   .    /    ,'       __..      `\n");
            printf("        \\ `.|            _/_      '   \\  |   /   ,'       ,\"    `.     '\n");
            printf("         `.             '   `-.    `.__| |  /  ,'         |            |\n");
            printf("           `\"-,.               `----'   `-.' .'   _,.--\"\"\"'\" --.      ,'\n");
            printf("              |          ,.                `.  ,-'              `.  _'\n");
            printf("             /|         /                    \\'          __.._    \\'\n");
            printf("   _...--...' +,..-----'                      \\-----._,-'     \\    |\n");
            printf(" ,'    |     /        \\                        \\      |       j    |\n");
            printf("/| /   |    j  ,      |                         ,._   `.    -'    /\n");
            printf("\\\\'   _`.__ | |      _L      |-----\\            `. \\    `._    _,'\n");
            printf(" \"\"`\"'     \"`\"---'\"\"`._`-._,-'      `.              `.     `--'\n");
            printf("                       \"`--.......____:.         _  / \\\n");
            printf("                               `-----.. `>-.....`,-'   \\\n");
            printf("                                      `|\"    `.  ` . \\ |\n");
            printf("                                        `._`..'    `-\"'\n");
            printf("                                           \"'   \n");

            break;

        case 38:
            printf("        ,-\"\"'-.._\n");
            printf("   .---'\"\" \">` - `--\n");
            printf("   `.      `-._  .`-.\n");
            printf("     `-.       \\ .` : -.\n");
            printf("      _.>._     / ` `:..,\n");
            printf(" ,.../...._`\"-./    '.|, `\n");
            printf("`---.._\"'-.`-._    |    \"'--.\n");
            printf("       `--.\\`. `._,'         `.---------------.._\n");
            printf("            \"-'--.___          \\`'\"-..__         `-._\n");
            printf("                     `.\"`-\\     ` `\"--..\"`-.-..__    `\".\n");
            printf("                       `.  `.     |``._ `--. `-..`\"-._`.\\-.\n");
            printf("                         \\   -....' `-.`-.  `-._ `-.  `-.\\ `.\n");
            printf("                          `-.__  `.`-. `. `._   `._ `-.  `.  `.\n");
            printf("                               `-..`` `. `.  `.    `.  `-.     \\\n");
            printf("                                   \\`.` `  `.  `.    `.   `-.   `.\n");
            printf("                                    `.`-'`.  \\   .     `.    `.   \\\n");
            printf("                                      `..  \\  \\   \\      `.    `.,_`.\n");
            printf("                                         \\` \\  .   `.     '\\     `.`.`._\n");
            printf("                                          \\``.  \\    \\     \\`.    |\n");
            printf("                                           ' '.  \\    \\     \\ \\   L\n");
            printf("                                             \\ \\  '    `    '. `.  \\\n");
            printf("                                              ` `. \\    `    '.  `. `.\n");
            printf("                                               `. `,`.   `.   `.   `._.\n");
            printf("                                                 `-  \\._   `.  `.     \"`\n");
            printf("                                                      ` `.   `.  .\n");
            printf("                                                          `-. ``-.:-.\n");
            printf("                                                              -.`. '\"-'\n");
            printf("                                                                 `\"-.   \n");

            break;

        case 39:
            printf("   ,..__\n");
            printf("  |  _  `--._                                  _.--\"\"\"`.\n");
            printf("  |   |._    `-.        __________         _.-'    ,|' |\n");
            printf("  |   |  `.     `-..--\"\"_.        `\"\"-..,-'      ,' |  |\n");
            printf("  L   |    `.        ,-'                      _,'   |  |\n");
            printf("   .  |     ,'     ,'            .           '.     |  |\n");
            printf("   |  |   ,'      /               \\            `.   |  |\n");
            printf("   |  . ,'      ,'                |              \\ /  j\n");
            printf("   `   \"       ,                  '               `   /\n");
            printf("    `,         |                ,'                  '+\n");
            printf("    /          |             _,'                     `\n");
            printf("   /     .-\"\"\"'L          ,-' \\  ,-'\"\"\"\"`-.           `\n");
            printf("  j    ,' ,.+--.\\        '    ',' ,.,-\"--._`.          \\\n");
            printf("  |   / .'  L    `.        _.'/ .'  |      \\ \\          .\n");
            printf(" j   | | `--'     |`+-----'  . j`._,'       L |         |\n");
            printf(" |   L .          | |        | |            | |         |\n");
            printf(" |   `\\ \\        / j         | |            | |         |\n");
            printf(" |     \\ `-.._,.- /           . `         .'  '         |\n");
            printf(" l      `-..__,.-'             `.`-.....-' _.'          '\n");
            printf(" '                               `-.....--'            j\n");
            printf("  .                  -.....                            |\n");
            printf("   L                  `---'                            '\n");
            printf("    \\                                                 /\n");
            printf("     ` \\                                        ,   ,'\n");
            printf("      `.`.    |                        /      ,'   .\n");
            printf("        . `._,                        |     ,'   .'\n");
            printf("         `.                           `._.-'  ,-'\n");
            printf("    _,-\"\"\"\"`-,                             _,'\"-.._\n");
            printf("  ,'          `-.._                     ,-'        `.\n");
            printf(" /             _,' `\"-..___     _,..--\"`.            `.\n");
            printf("|         _,.-'            `\"\"\"'         `-._          \\\n");
            printf("`-....---'                                   `-.._      |\n");
            printf("                                                  `--...'   \n");

            break;

        case 40:
            printf(",-.                                                 .\n");
            printf(".` `.                                             .'|\n");
            printf("` `. `-._                     _,.--._            /  |\n");
            printf(" `  ..   `.                  /       `.        ,' , '\n");
            printf("  `  ` `.  `-._              | '\".     \\      /  / .\n");
            printf("   `. `   `.   `.          ,\"'---'      .   ,' ,'' |\n");
            printf("     ` `.    `.  `.       .             |  /  / /  F\n");
            printf("      `. .     `.  \\ ,..--|             |,'  / /  /\n");
            printf("        \\ `.     .  |      \\           ,.   / /  /\n");
            printf("         `._`._   j   .----.`._     _,` | ,\" / ,'\n");
            printf("            `._`\"`  ,',\"\"\"\"-.`.\"\"--' ,-\":+.-'.'\n");
            printf("            ,'     . |`._)   . L     ||_7\\+-'\n");
            printf("           /       | |       | |     .\\   \\.\n");
            printf("          /        |  .      | |      \\\\_,'j\n");
            printf("         .          ._ `----' /        `--\" '\n");
            printf("        j             \"--..--'              |\n");
            printf("       ,|                        ,-\".       |\n");
            printf("     ,' |                       /   |       '\n");
            printf("    /   '                       `..'    ,'   \\\n");
            printf("   /   j                               /      L\n");
            printf("  j    |                              .       |\n");
            printf("  |  _.'                              |     , |\n");
            printf("  `-' .                               |   ,'  '\n");
            printf("      |                               `.-'     .\n");
            printf("      |                                        |\n");
            printf("      |                                        j\n");
            printf("      '                                       .\n");
            printf("       `                                     /\n");
            printf("        `.                                  /\n");
            printf("     ______.                              ,'\n");
            printf("   ,'       `-._                     _,.'\"\"`--..\n");
            printf("  .         ___,+ -...._________,...<_          \\\n");
            printf("   .___,.-\"'                          `-._      |\n");
            printf("                                          `-....'   \n");

            break;

        case 41:
            printf("                                        `\"--.._\n");
            printf("                                         '  ,__`-._\n");
            printf("                                          ` |   `-.`._\n");
            printf("                                           |`       `._`.\n");
            printf("                                    ./\"\\   | `.        `.`.\n");
            printf("                                  .'/   .  | _ `.        `.`.\n");
            printf("     /|                          / /    |  || `-.`.         `..\n");
            printf("    / |                         . /     |  ||    `.`.         `.`\n");
            printf("   /  '        _.,.____      _,.'._     '  j       `.`          `..\n");
            printf("  j ,-.`       . \"\"--._`-. ,',.-++.`. ,'  //         `..          `..\n");
            printf("  / '  \\`       \\      `. '.'|  ''  \\`   //            ``.          `.\n");
            printf(" j /    \\`.      \\       || `'       |\\ //              `..    __,....`.\n");
            printf(" |.      `.`.     `.     ||         [|'//                 \\\\_,\"        `\n");
            printf(" ||       |,.`._    `----.`_\"\\   _.-\"  .        ___........\\|\n");
            printf("jj        || `-.`-.______ `/`--'\"       \\   _.-'\n");
            printf("|.        ||     `--..___\"\"              .,'\n");
            printf("||        ||             \"\"|             Y\n");
            printf("||        ||               \\            /\n");
            printf("||        ||           _....\\.         ,\\\n");
            printf("||        '|        ,-'       `,.___,.-. .\n");
            printf("||         L      ,'           `  /     ` .\n");
            printf("||         '`    /              ||       ` .\n");
            printf("||          \\| ,'               ||        `.`\n");
            printf("||        ___|/                 '|          .`.\n");
            printf("||    _,-'    |                  L           ` .\n");
            printf("||  ,'                           ||           ` .\n");
            printf("` ./                             ||            ` .\n");
            printf(" `V                              ||             ` .\n");
            printf("                                 ||              ``\n");
            printf("                                 ||               ``\n");
            printf("                                 ||                `\\\n");
            printf("                                 ||                 `'\n");
            printf("                                 ||\n");
            printf("                                 ||\n");
            printf("                                 !|\n");
            printf("                                 _/   \n");

            break;

        case 42:
            printf("                           ---..__\n");
            printf("_____                          `._\"`._\n");
            printf("  `._`\"--_._                      `.  `._._\n");
            printf("     `._   `-._._                   `.   `.`._\n");
            printf("        `.     `-._.                  `.    `.`._\n");
            printf("          `.       `-`._                `.    `-.`.\n");
            printf("            `.        `-`._               \\      `.`.\n");
            printf("              \\          `.`.              \\       `-.`.\n");
            printf("               \\            `..             \\         `.`.\n");
            printf("                \\             `..            \\          `.`\n");
            printf("                 \\             _:`.           |           `..\n");
            printf("                  L       _,-\"\" jj            |     ___......:\n");
            printf("                  |     ,'      ||            |  ,.\"        .'\n");
            printf("                  |   ,'        ||            |\"'           / \\\n");
            printf("                  |  /         /|L       ,\".   ]`.         /   L\n");
            printf("                  |,'         . ` \\      /  \"\"\"  \"`.      j    |\n");
            printf("                  /_          |  `.\\    (\\  <.)|    \\     |    |\n");
            printf("                    `-.       |    \\`.  |_____..     \\   j     |\n");
            printf("                       `,     |     `.`.\\|    V \\   .'\\  |     |\n");
            printf("                         \\    |       `._|       | <  ` j     j\n");
            printf("                          `.  |          `.      |  \\  |      |\n");
            printf("                            \\ |           |L      L  L |__    |\n");
            printf("                             \\|           ||      |  |  __`. j\n");
            printf("                              Y           ||.-.   |  | |   \\ |\n");
            printf("                               \\,--\"\"\"\"\"`-.|`. \\  |  |/|    `\n");
            printf("                                '          |  \\ `.'    j\n");
            printf("                                          (|  | ,.`.  /\n");
            printf("                                      _.-\"_`._| | `' /\n");
            printf("                              ,....../ ,'\" `.__.'_,-'\n");
            printf("                              `-----._`..      \"\"\n");
            printf("                                      `.J   \n");

            break;

        case 43:
            printf("                           .-\"--.__\n");
            printf("          _                / '+.--'\n");
            printf("           \\.-._          j / |\n");
            printf("            \\`-.`._      . j  |\n");
            printf("             \\  `. `.    | |  L                        _,,--+='\n");
            printf("              L   `. `-. | |   \\                  _.-+'    /\n");
            printf("              |     \\   j  |    \\            _,-'\" .'    ,'\n");
            printf("              .      \\  |  |     \\         ,'   _,'    ,'\n");
            printf("               \\      `j   |      \\      .'   ,'      /\n");
            printf("                `.     |   |       \\   ,'   ,'       /\n");
            printf("                  \\    |   |        \\ /    /        /\n");
            printf("  _,-''\"\"\"\"'\"\"'\"\"`--. j    |         V    /      _,+............._\n");
            printf("-=`...-----...__     `|    |         .   /   _.-'        _,.--\"\",..=.\n");
            printf("      `-.       `._   |    |          L,'  ,'       _,.-'    ,-'\n");
            printf("         `.        `. |    |          |  .'     _.-'       ,'\n");
            printf("            .        \\|    '          L/    _,-'          /\n");
            printf("             `._      `.    L        /   _,'            ,'\n");
            printf("                `-._    \\   `       ,' ,'             ,'\n");
            printf("                    `-.. `   \\     /,-'           _.-'\n");
            printf("                      ,'\"-..  .   /_,..---\"`+'\"\"\"\"\n");
            printf("                     /           '           `.\n");
            printf("                    j                          .\n");
            printf("                   .                           |\n");
            printf("                   |   .-.       ,.            |\n");
            printf("                   |    -'       `.'           |\n");
            printf("                   `                           '\n");
            printf("                    `.      .--.             ,'\n");
            printf("                      `.    `._|          ,-'\n");
            printf("                    _.-`   ,..______.. .  `-.\n");
            printf("                  ,'       |          |      `.\n");
            printf("                ,'         '          |        `.\n");
            printf("               /         ,'            .         .\n");
            printf("               \\     _,-'               `._      |\n");
            printf("                `---'                      `-....'   \n");

            break;

        case 44:
            printf("                            ,.--\"\"+`-,\n");
            printf("                    ___,..-'  C'  `.' `-.\n");
            printf("                 .\"|      `-,...._   ___:.\n");
            printf("                /'\"|   _,..^..__ _'\"'     `-.\n");
            printf("               ' `\" ,-`c.   ..  `.     ,\"\".  `.\n");
            printf("              /,  ,'       `._'   `.|)  \"'    /\\           .\n");
            printf("          _,.|'- /  .-.             \\         `\".          |\\\n");
            printf("      _.-'   |  |   '-        _     |           |          | \\\n");
            printf("    ,'       |  |            \\.'    |           |          |  .\n");
            printf("   ,          . |                   |           j          j  |\n");
            printf("  /_.-'\"\"\"'\"':.+|                   |          /         ,'   |\n");
            printf(" /'       ,-'    \\                 /        _,'-..___,..'     j\n");
            printf("j|       /        `.             ,^.......-+                 /\n");
            printf("||      /     _,-.\"\"'-..____,..-'-._        \\               /\n");
            printf("| \\   ,|    ,' .'   ,'    .         `.       \\__         ,-'\n");
            printf(" . `-'.|   /  /  _.'       `.         \\       . `---+.-'|\n");
            printf("  `._, ' j   j '\"            `--..     `.     |.     `. |\n");
            printf("        .|   |                           .    ||       `|\n");
            printf("        `'   |,----......__...._         '    ||        |\n");
            printf("             |`._=-=====___''-. `-.      |   / |        '\n");
            printf("          _,.L   `\"\"\"------|  .---'      |  /`-+_\n");
            printf("     ,'\"`/    \\            |  |          |.'.    `\"\"'-.\n");
            printf("     |   \\__,.'`           | j              _+-._     |\n");
            printf("     |    `     `._        | |             ,     `---\"\n");
            printf("      .    `...,-' +._      `|            /\n");
            printf("       `.       -'\"   `-...________,..--.  `.,..\n");
            printf("         \\     |                         `.     |\n");
            printf("          `._  |                          '    /\n");
            printf("             `'                      _,.-'    /\n");
            printf("                                  ,-'        /\n");
            printf("                                 `.       _,'\n");
            printf("                                   `'----'   \n");

            break;

        case 45:
            printf("                        _..--------..__\n");
            printf("                    ,-\"'    __         `-.\n");
            printf("                 ,-'    .-\"'  |   .--.    `. ____\n");
            printf("               ,'  _..   `\"\"\"'    `-'  _.-'\"'    `\"--._\n");
            printf("             .'   `..'  _           _,' ,\"\"`,        __`._\n");
            printf("      _.--\"\"\"`\"---.._  '.\"   ___..,'__   `\"'        `. `. `.\n");
            printf("    .'__       .-,   `'-+.--\"-------..`-.   `=`       `\"'   \\\n");
            printf("  ,'(__,'   _   \"       |( ,-'\"\"'\"\"'`-.`,|  _.----\"\"'\"`--.../\n");
            printf(" /         |_)          | `-...______,.' |-'        `-'      `-.\n");
            printf("j                      .'_,..........__,'     c.          .-.   `.\n");
            printf("|        _,..  `+' _,.-'\"        .,    `-._               \\__'    `\n");
            printf("|       `___,'   ,'   .:\"',     '\"    .-,  `-.     ,--.      _     |\n");
            printf(" \\             ,'       \"\"             `      `.   `--'    ,' |    |\n");
            printf("  `.         ,'  .'\"\"`.          :\",       __   \\          `..'    '\n");
            printf("    `._     .    `---'            \"       |  `.  \\               ,'\n");
            printf("       `\"--+                   __          `\"'    .           _,'\n");
            printf("           |                 ('  )                |...,,...-'\"\n");
            printf("            `.                 \"'                ,'\n");
            printf("              `-..__                          _,'\n");
            printf("                    `+---.=,---------+.----+\"'\n");
            printf("                ,'\"`/     \"          \"   ,-.\\\n");
            printf("                \\    \\         _        /  | +.\n");
            printf("               .`.            '/       /   | | \\\n");
            printf("             ,'   A   '               /    j |  `.\n");
            printf("            '    / \\   \\             j    / /`.   \\\n");
            printf("             `--'   \\   \\            |   j,'   `.,'\n");
            printf("                      . |-.........,.|   .\n");
            printf("                       `'            `,.'   \n");

            break;

        case 46:
            printf("           ____                               ____\n");
            printf("      ,-\"|\"    \"\",._                    _,--\"' |  ``-.\n");
            printf("     /   \\.   _,'   `-.               ,'  \\   ,'    ,-\".\n");
            printf("    /      `\"'        |              /     \\.'      |   L\n");
            printf("   /_     .-..    ,'\"\"|             |   _,.    ,--. `.__|\n");
            printf("  j  \\   /    |  /    |     _____   `  j   \\  |    \\     L\n");
            printf("  |  |   `    L  \\   / _.\"\"|    .\"'--._|    |  `.__/     |\n");
            printf("  |  '    `-./    `.+-'    `..-'       |-.  |        ,\"`.|\n");
            printf("  `-'            ,'  )   __,...__       ` `-._      /   ||\n");
            printf("   `,---.      ,'  .'_,-'        ``-._   `-.__|-.../_...'\n");
            printf("    `-..,\\.--'/..-`.'  ..-------..._ ,-.\"'`-.    `.\n");
            printf("            ,\"`.__  `.'    `'  `-' .(   ).   \\     . ,--._\n");
            printf("         ,\"|`._)  `. |  _      ,.  |`-,'  `. |     |'     `.\n");
            printf("        / _|  .    | | `-'     -'  |  .   ,' |,-\"\"-`.,--.   `.\n");
            printf("       /\"\" `.  `\"-'  '    ___       `. `\"'  .'       .   I-.  `.\n");
            printf("     ,'      `-..,.-' ,-'\"   `-.      `\"--'\"/         \\   \\ `.  `\n");
            printf("    /         |      /         |\"-.        /           `.  `. `. \\\n");
            printf("   /          |.    | `. ___ ,.'  |       j            \\ `   `. \\ .\n");
            printf("  j           | `. (`._ \\  .\"   _,{      ,'             L `.   . \\|\n");
            printf("  |           |,' `-.  `\\   \",-'  |_,..-'|              |   L  |  '\n");
            printf("  |           |      `-..'  '__,.-'      |              |    . |\n");
            printf(" /|            L        `\"\"\"'           j               |    | |\n");
            printf("j |            |                        |              j     | |\n");
            printf("| |             L                       |              .     ' j\n");
            printf("| [             |                       |             /       '\n");
            printf(" - `.           |                       |            /\n");
            printf("    `.   ,'\"\"`-,                        |.--..__    /\n");
            printf("      `.'      \\                        '       `.,'\n");
            printf("        `.      \\                     ,'      _,-'\n");
            printf("          `.     `.                 ,'    _,-'\n");
            printf("            `-..__ \\              <___..-\"   \n");

            break;

        case 47:
            printf("                                       _______\n");
            printf("                                   _,\"\"|      `-._\n");
            printf("                                 ,\"  _.'          `.\n");
            printf("                                ,'\"\"'               `.\n");
            printf("                              ,'       ,.----._  .--. \\\n");
            printf("                             /        `____    \\  \\_ ) \\\n");
            printf("                           ,'              \"\"`-'    \"   L\n");
            printf("                         ,'                             |\n");
            printf("                       ,'.'                              L\n");
            printf("                     ,'-'    _,...._             .\"\"`.   |\n");
            printf("                  _,'     ,-'       `.       ,.   `.  `. '\n");
            printf("              _.-'      .'     ______/       `_)    `._;  \\\n");
            printf("           ,-'           `-\"'\"\"                            \\\n");
            printf("         ,'   ,.---,                                        \\\n");
            printf("        /   .'   _,                    ,\"\"\"`-._         .\"`-.'\n");
            printf("        7-\"'-+--'     ___               `-.__  `.       `.   `\n");
            printf("      ,'      \\_____.'   `.--.'\"\"`.          `-.'         `-..\\\n");
            printf("     /         `.`._|     | |      |`--...,.---.               `.\n");
            printf("   ,'      . `  |    \\    ,-|     ,'..,-'       `.,_             \\\n");
            printf("  /     \"       |.,.._\"'\"'   `-..'  .'            \\ `\"-.._      __\\\n");
            printf(" /              | '-..\"\"..________./              |..-\"\". `+.  (  ,\n");
            printf("j               | L\"`--._....___  /               |_...  `/  \\  -.'\n");
            printf("|             | | |      `--._  \"/                j__..`  `.  `.-'\n");
            printf("|          /  j ' |           \"./       ,.'    \" /_..-\"'\\   \\.  `.\n");
            printf("|         /' / /| |            /         ' \"    /'       \\   \\`.  `.\n");
            printf(" L       / |V j | |           /               ,'          \\   \\ \\   `.\n");
            printf(" |      j  |  | |  L         j              ,'            /    | \\   |\n");
            printf("  L     |  |  | `.  \\        |            ,'             j    /   \\  |\n");
            printf("  .    j   `. L   `._`.     j          _,'               '   '     . |\n");
            printf("   \\   |     `.\\     `\"`    |       _.'                 /   /      | |\n");
            printf("    \\  |       `           /   _,.-'                   /   /       j .\n");
            printf("     \\ |                  /.-\"'                    _,-'  ,'       /,'\n");
            printf("      '                                           '----\"'   \n");

            break;

        case 48:
            printf("                                           _.----.\n");
            printf("                                       __,'   _,-'\n");
            printf("                                  _..\"_..---\"'\n");
            printf("                               _.'_,-'_____________,......\n");
            printf("                    `. .   ._,_.-',--',.-...........    __;\n");
            printf("                 __  `/ ),`','_.'..,--'_,.---;      `\"\"\"\n");
            printf("              `.,..`\"'  ,.'.-_.-',..-'\"   ,-'\n");
            printf("            _,..        ___-'           ,'\n");
            printf("         ,-'    |     ,'   `-.         '----..\n");
            printf("       ,'       |   ,'        \\             \\.\n");
            printf("      /         '  /           L            `-\n");
            printf("     |        ,'  j            |        ,     `.\n");
            printf("     |    _,+----.|            |       . `.    .-.\n");
            printf("     |   /\\    ,..\\L           '       |   .   |`---\n");
            printf("     |`-| ,\\___|  | \\.        /        |   |  .--            .,|\n");
            printf("     |   V     / ,   '-.....'\"         |   |   `.           ,.-'`'\n");
            printf("     |\\       `-'                      `._,     _\\\n");
            printf("     '|                                         ` _   .-.--\".-\n");
            printf("  _,.. |                                       ,./`.,/   ,.-'\n");
            printf(".' .   |,                            ,---,     \"._      /\n");
            printf("|  `     `.                         /   `.     ,--     /.----...,\n");
            printf(" \\         \\                        \\   .\"    '.._             |\n");
            printf("  `.        L                        `...'  `..--. -\"\"_..    _.'\n");
            printf("    `.      '.,`.                          ..'-.`,_      `-\"'\n");
            printf("      \\       \\` ',-                     .'     \\\n");
            printf("       `.      L  `.  .             ,.-'\"\\       \\\n");
            printf("         \\     |    '`.`. .-. .-..,..'.   \\       \\\n");
            printf("          `-._,'         `\". `-..          \\       `.\n");
            printf("                                            `. -.   |\n");
            printf("                                              '-.+--'   \n");

            break;

        case 49:
            printf("                      ,-\"\"-.                _ _,....._\n");
            printf("                    ,'     |            _,-\"_..----\"\"-\"\\\n");
            printf("              .   ,      ,'|         _,\"_.-'            |\n");
            printf("            ,'/  /|    ,'  |      ,-'_,'                |\n");
            printf("           / /  /j    /    |   ,-'_,'            __,..--'\n");
            printf("          / /  / '   /    j  ,' ,'          _.--'      /\n");
            printf("         / /  / /   /     |,' .'         ,-'          /\n");
            printf("        / /  j /   /     /' .'        ,-'            /\n");
            printf("       / /   |j   /  __.' ,'       _,'             ,'\n");
            printf("      / /  ,\",|  /,-\".' ,'       ,:_______________/\n");
            printf("     / , ,','j  /\", /,\"/|      ,'                /\n");
            printf("    /  |' /  |_/ / / .' |    ,'                 /\n");
            printf("   /   |,'  ,' .' / /  j   ,'                _,`\n");
            printf("  j   '/ ,-' .'  / /   | ,'              _.-\" |\n");
            printf(" .'   j.'  ,'|  / /    ,'          _,.--'     j\n");
            printf(" | _.-_,../| | / /    |      _,,-'\"        _./\n");
            printf(" j  ,( )__ `.// /   ,'|  _.-'          _.-'  |\n");
            printf(".   | `(  ) |/ /   /  ,`+        _,..-'      '\n");
            printf("|   |   \"'  | /  ,'_,'   `.  _,-'           .\n");
            printf("|   .`.___,'--. /,'       ,+\"               |\n");
            printf("|  | `/         \\     ,-'\"\"'\"\"-.._         .'\n");
            printf(" .,j /           \\ ,-'         \\  `-.      /\n");
            printf("  `|'      /`.    Y-\"'\"\"\"---.._|     `.   /\n");
            printf("   |     ,' / 7   |            |`-.    \\ /\n");
            printf("   |___,'  / /`.  |_           |   `.  ,'\n");
            printf("   `.___..' / /  /  .,.__      |     `.\n");
            printf("     `.____/,' _'   /`.  '`-.._|      Y\n");
            printf("       `-+----'   ,'   7-..   j -.     .\n");
            printf("         |  __.,-'    -|   `-.+   `-.  |\n");
            printf("         |\"'      ,.'` ',   /  `._   `.|\n");
            printf("         |_  _,,.'      |`..      `.   |\n");
            printf("          .'\"          ,'  \\.       `. \"-.\n");
            printf("          `        ,./\"|\\   \\|        `.  |\n");
            printf("           `v.^.,`.    | \\   )     ,    `.|\n");
            printf("             `._     .'   `./_\\.--' .     `.\n");
            printf("                `---'               '      /\n");
            printf("                                     `. _,'\n");
            printf("                                       \"   \n");

            break;

        case 50:
            printf("                     _,.---'\"\"'\"--.._\n");
            printf("                   ,\"                `-.\n");
            printf("                 ,'                     `.\n");
            printf("                /     _       ,.          `.\n");
            printf("               /     ||      |\"|            \\\n");
            printf("              /      ||      | |             \\\n");
            printf("             /       .'      `_'              L\n");
            printf("            j                                 |\n");
            printf("            |        __,...._                 |\n");
            printf("            |      .\"        `.               |\n");
            printf("            |      '           )              |\n");
            printf("            |       `-...__,.-'               |\n");
            printf("            |                                 |\n");
            printf("            |                                 |\n");
            printf("         ...|                                 |\n");
            printf("      _,'   |                                 |\n");
            printf("  _,-'  ___ |                                 |.-----_\n");
            printf("-' ,.--`.  \\|                                 |     . \\\n");
            printf(",-'     ,  |--,                               |  _,'   `- -----._\n");
            printf("      ,' ,'    - ----.            _,..       _|.',               \\\n");
            printf(" ,-\"\"' .-             \\  ____   `'  _-'`  ,-'     `.              `-\n");
            printf(" .--'\"`   ,--:`.       --    ,\"'. ,'  ,'`,_\n");
            printf("        _'__,' |  _,..'_    ,:______,-     --.         _.\n");
            printf("        -__..--' '      ` ..`L________,___ _,     _,.-'\n");
            printf("                                              '\" '   \n");

            break;

        case 51:
            printf("                                        _..-----._\n");
            printf("                                     ,-'__      __`-.\n");
            printf("                                   ,'  '  `    /  |  \\\n");
            printf("                   _____          /   ,...            \\\n");
            printf("              _.-\"\"     `-.      |   /    `. ,-\"\"`.    \\\n");
            printf("             /             `.    |  |   `  || .    |    .\n");
            printf("            j             _. \\   |  `..__.' '      |    |\n");
            printf("           .     __     ,'--. \\ j       ,....`....-'    |\n");
            printf("           |     .---. .     | \\|      (__    )         |\n");
            printf("           |   .'   . || '   |  Y         \"\"\"'          |\n");
            printf("           |   |      | `-..-'  |                       |\n");
            printf("           |    `-...',.--.     |      ,--,.--\"\"'\"-.._ j\n");
            printf("           |        .\"    _|    |      .-\" |    ,\"\"\"`.`|\n");
            printf("           |        `---\"'      `.    /    '   /     |  `\n");
            printf("           |                     L   /,-\"\"-.   _,...     \\\n");
            printf("       _._  L                    |  j|    _ | /     `.    L\n");
            printf("     ,'   `-|                     L ||      | |  '   |    |\n");
            printf(" ,--\"     _||                     |j  `----'  `      |    |\n");
            printf("\"       ,',:|                     .     ,-\"\"--.`-- -'     | _\n");
            printf("     ,-._'  '.                    |     `-...__)         j'\" `-.\n");
            printf("    :,.._:.   `.               ,-'|                      |_,.._ ---.\n");
            printf("               _:......--.,..-'   |                      |     `.  ,`.\n");
            printf("          `\"\"\"' ..../__,  \"----.\"'-\\  _,-'\"`._           | .   __\n");
            printf("                                '-..- .....- .`-...,-\"\"`-,|___.\n");
            printf("                                                '\"-----\"'.   \n");

            break;

        case 52:
            printf("                                        .\n");
            printf("                         |              |\n");
            printf("                         |             ,|\n");
            printf("                ,_       |\\            F'   ,.-\"\"`.\n");
            printf("               /  `-._   |`           // ,-\"_,..  |\n");
            printf("              |   ___ `. | \\ ,\"\"\"`-. /.-' ,'    ' |_....._\n");
            printf("              |  /   `-.`.  L......|j j_.'      ` |       `._\n");
            printf("              | |      _,'| |______|' | '-._     ||  ,.-.    `.\n");
            printf("               L|    ,'   | |      | j      `-.  || '    `.    \\\n");
            printf("___            | \\_,'     | |`\"----| |         `.||       |\\    \\\n");
            printf(" \"\"=+...__     `,'   ,.-.   |....._|   _....     Y \\      j_),..+=--\n");
            printf("     `\"-._\"._  .   ,' |  `   \\    /  ,' |   \\     \\ j,..-\"_..+-\"  L\n");
            printf("          `-._-+. j   !   \\   `--'  .   !    \\  ,.-\" _..<._  |    |\n");
            printf("              |-. |   |    L        |   !     |  .-/'      `.|-.,-|\n");
            printf("              |__ '   '    |        '   |    /    /|   `, -. |   j\n");
            printf("        _..--'\"__  `-.___,'          `.___,.'  __/_|_  /   / '   |\n");
            printf("   _.-_..---\"\"_.-\\                            .,...__\"\"--./L/_   |\n");
            printf(" -'\"\"'     ,\"\"  ,-`-.    .___.,...___,    _,.+\"      \"\"\"\"`-+-==++-\n");
            printf("          / /  `.   )\"-.._`v \\|    V/  /-'    \\._,._.'\"-. /    /\n");
            printf("          ` `.  )---.     `\"\"\\\\__  / .'        /    \\    Y\"._.'\n");
            printf("           `\"'`\"     `-.     /|._\"\"_/         |  ,..   _ |  |\n");
            printf("                        `\"\"\"' |  \"'           `. `-'  (_|,-.'\n");
            printf("                               \\               |`       .`-\n");
            printf("                                `.           . j`._    /\n");
            printf("                                 |`.._     _.'|    `\"\"/\n");
            printf("                                 |    /\"\"'\"   |  .\". j\n");
            printf("                                .`.__j         \\ `.' |\n");
            printf("                                j    |          `._.'\n");
            printf("                               /     |\n");
            printf("                              /,  ,  \\\n");
            printf("                              \\|  |   L\n");
            printf("                               `..|_..'   \n");

            break;

        case 53:
            printf("\n");
            printf("         ,-\"\"--.\n");
            printf("        /       \\\n");
            printf("        | ,\"`.   L\n");
            printf("        |     |  |\n");
            printf("        \\_   /   |\n");
            printf("          `-' |  |\n");
            printf("              |  |\n");
            printf("              |  |\n");
            printf("              j  j\n");
            printf("             .  .\n");
            printf("             j  j\n");
            printf("            .  .\n");
            printf("            |  |\n");
            printf("            |  |\n");
            printf("            |  |\n");
            printf("            L  |\n");
            printf("             \\_|._\n");
            printf("       _.-,-\"     `\".\n");
            printf("     ,' .'           \\\n");
            printf("    /  /              \\\n");
            printf(" _,'  /  /             \\\n");
            printf("<    /  /              |\\\n");
            printf("<+-'|  j               |/\n");
            printf(" `--+  |    ___        `    ..-.\n");
            printf("     \\ |  ,\"--.`.       \\__/,\"\".|\n");
            printf("      `-\\||    `.\\--\"\"\"\"' //    |\n");
            printf("         |`    / `          \\  ,'\n");
            printf("          \\|. / ,.  ,-.  _.. \\'___..\n");
            printf("      _____| Y |  `.`./ /  | ;.=\"\n");
            printf("         \"-+=+.|  ! \\  /_! / |_____\n");
            printf("          _|_L, `\"\"\" ._. \"\"  .---------\n");
            printf("       _+==+-`\\. .__,.|...,-=+\\._\n");
            printf("     ,\"\"   | .+-+ \\     )/.'   \\\"-+\n");
            printf("           ,+'  |` \\    // \\    \\\n");
            printf("          '|    | `.\\..'/   \\    \\\n");
            printf("           |    |   `\"\"'     \\    L\n");
            printf("           |    |             \\   |,._\n");
            printf("           |    `             _j .'  '>\n");
            printf("           |  ,..\\           /        /-.\n");
            printf("          ,^.' _  |          `.  .--.'  j\n");
            printf("        ,'  | |/  |-\"`.       |'-'\"\"``-|/\n");
            printf("        |_   .,---.  |\\\n");
            printf("        |/_,`-...-^..`'   \n");

            break;

        case 54:
            printf("                              ,-'   ,\"\",\n");
            printf("                             / / ,-'.-'\n");
            printf("                   _,..-----+-\".\".-'_,..\n");
            printf("           ,...,.\"'             `--.---'\n");
            printf("         /,..,'                     `.\n");
            printf("       ,'  .'                         `.\n");
            printf("      j   /                             `.\n");
            printf("      |  /,----._           ,.----.       .\n");
            printf("     ,  j    _   \\        .'  .,   `.     |\n");
            printf("   ,'   |        |  ____  |         | .\"--+,^.\n");
            printf("  /     |`-....-',-'    `._`--....-' _/      |\n");
            printf(" /      |     _,'          `--..__  `        '\n");
            printf("j       | ,-\"'    `    .'         `. `        `.\n");
            printf("|        .\\                        /  |         \\\n");
            printf("|         `\\                     ,'   |          \\\n");
            printf("|          |                    |   ,-|           `.\n");
            printf(".         ,'                    |-\"'  |             \\\n");
            printf(" \\       /                      `.    |              .\n");
            printf("  ` /  ,'                        |    `              |\n");
            printf("   /  /                          |     \\             |\n");
            printf("  /  |                           |      \\           /\n");
            printf(" /   |                           |       `.       _,\n");
            printf(".     .                         .'         `.__,.',.----,\n");
            printf("|      `.                     ,'             .-\"\"      /\n");
            printf("|        `._               _.'               |        /\n");
            printf("|           `---.......,--\"                  |      ,'\n");
            printf("'                                            '    ,'\n");
            printf(" \\                                          /   ,'\n");
            printf("  \\                                        /  ,'\n");
            printf("   \\                                      / ,'\n");
            printf("    `.                                   ,+'\n");
            printf("      >.                               ,'\n");
            printf("  _.-'  `-.._                      _,-'-._\n");
            printf(",__          `\",-............,.---\"       `.\n");
            printf("   \\..---. _,-'            ,'               `.\n");
            printf("          \"                '..,--.___,-\"\"\"---'   \n");

            break;

        case 55:
            printf("                ,|\n");
            printf("              ,' |         .',\n");
            printf("             /   |    /\\_,' j\n");
            printf("            /    |  ,' |    |\n");
            printf("          ,'     |,'   |   .\n");
            printf("         /       '    j   j    _,.-/\n");
            printf("        /      ,'     |   |..-\"  ,'\n");
            printf("       /              |         /                      `\n");
            printf("      /               |       ,'\n");
            printf("    ('  (                 ,\"\"`-.                        /|\n");
            printf("     | | .              ,'      \\                      / |\n");
            printf("     | |p'             /        |                     /  |\n");
            printf("     |.`              '       ,'|-.                 ,'   '\n");
            printf("     /`\"`\"\"\"'\"`-.    /       .  |. `.___           /    /\n");
            printf("    /      ,-\"'_|._,'        |  | `.    `\"--..    /    j\n");
            printf("  ,'     ,',-\"',-'           |,'    `-.       | ,'     |\n");
            printf(" /     .'.'   /  ,-'|       \\'         `.    ,'/      j\n");
            printf("|    .','    /  /   |   ,-.  \\           `+-','       '\n");
            printf("|  .''      .._/   /   /   \\  \\           `.'        /\n");
            printf(" \\/         | /`\"-.'  /_,..\"\\,\\                     /\n");
            printf("            '/    |\"|(       \\ .                  ,'\n");
            printf("                   .| \\       `'                 /\n");
            printf("                    ' _\\       ,.----\"\"-\\      ,'\n");
            printf("                 ,-'\"\"  \\    ,'          `   ,'\n");
            printf("                |        `-.'              ,'\n");
            printf("                .           \\           _.'\n");
            printf("                 \\        ___\\         `.\n");
            printf("                  `.    \"\" `. \\          \\\n");
            printf("            ,-/\"\"\"\"'._       \\_`.         `.\n");
            printf("`         _.`-'\"\"            /_`.\\          \\\n");
            printf("         /.-n+==`       _,,-'\"    \\          \\\n");
            printf("           ,\\ __.-\"\"\"\"'\"           )          `..__\n");
            printf("          (,.'                   _/         .._   _\\_\n");
            printf("          '                    ,\"  _,.-._   -. `_/__ \\\n");
            printf("                              / ),+....._\\ ,--.\"    `'\n");
            printf("                             `\"'          `.._ \\\n");
            printf("                                              `'   \n");

            break;

        case 56:
            printf("                                ,.-\"\".\n");
            printf("                               ,| .   `.\n");
            printf("   ,-\"\"\"\"'\"`.                 '/ |   /  \\\n");
            printf("  ,'     _.  \\           ,.  (/ ,'  `    .               ,-\"\"--.\n");
            printf(".'j ,  ,\"\"`.  \\         /  \\  -.\\   |\\   L             ,'  ,..  `.\n");
            printf("|( |   |    \\  \\|`-.  ,//\"  \\   `\"--' \\   \\           j   /---.   .\n");
            printf("`-\\|_..'     \\  ||. `/`/  \\  \\---,    `.   \\          |  '.    |  |\n");
            printf("              \\ || \\    `-.|  ` '`\"-,  |    .         '   |    |__|\n");
            printf("               `||/        `       `.. |    |          `--'    |  |\n");
            printf("               ,'                 __.-\"     |                  |  |\n");
            printf("              /                ,'\"       ,-\"'                  '  |\n");
            printf("             /   ,'           '        ,'L                    /   '\n");
            printf("            /. .'.                   .'   |                  /   /\n");
            printf("           |/ /|||               __,'     L                 /   /\n");
            printf("          .-.'|L|'__            --         \\               '   /\n");
            printf("         | . \\                             `.           _,'   /\n");
            printf("         ` ' ,                              .`       _,'    ,'\n");
            printf("          `-+                              /--------'    _,'\n");
            printf("            \\             .               {         _,.-\"\n");
            printf("           ,\"\\            \\       .     ,-\"-----\"\"\"'\n");
            printf("       _,.'   `.           )      |  __,.\n");
            printf("      /        __.        /       |-'\n");
            printf("      .   ..--+.  `/`v  ./     ,-\"\"\"-.\n");
            printf("       `-\"`.    \\     `/ \\           '\n");
            printf("            `-.  \\        `\"\"\"\"--.._  `.\n");
            printf("               )  \\___              `._ `.\n");
            printf("             _/       `-.               _ `._\n");
            printf("     .'\"\"\"--' ,  ,-\"\"`..'           ,\"\"``    `.\n");
            printf("     \\ _.,--.' ,'                   ( ,-.    __'\"\"\"`.\n");
            printf("      \" '.___./                      '  |  '\"  `-.   '.\n");
            printf("                                        |   -.    `-._/\n");
            printf("                                        |   /\n");
            printf("                                        '--.'   \n");
            printf("\n");

            break;

        case 57:
            printf("                                       _.-\"\"'-.\n");
            printf("     _______                        ,-'        `.\n");
            printf("   ,\" .  ,  `.                  ,. .             \\\n");
            printf("  / ,.-\"\"     \\      ,v\\       / '\\|              `'.\n");
            printf(" /  |     _    |__  j   \\  /| / .  |               |.\\\n");
            printf("j   `._,.+.. ,-'  \\ |.\\ ,`,`'/ /|   \\         ,\"\"- '/ |\n");
            printf("'        |  / _.,_/ || \\,'  / / `    \\_    _.:-...+'  |\n");
            printf(" `-._    `-| /.\"  \\ |''      `. _\\   '.`---..|`-\"'  _/\n");
            printf("     `---' `.L\\    /'   | \\_.  ' `           '--.--'  \\\n");
            printf("               \\ ,-    .'  ,                    |      \\\n");
            printf("                V ,-   -. l            __       |       .\n");
            printf("              ,','    , '              ..+.....'        |\n");
            printf("             /.'    .|                 `,              /\n");
            printf("            | '   .' |                 .'           _.'\n");
            printf("            | . ,'!  |                 `--....,...-'--.. _\n");
            printf("           _|_`-..--\"                   -'             <__\n");
            printf("          /,  `.                                       ,.'\n");
            printf("          \\'   |                                    _,'\n");
            printf("           ._ ,'                                   <\n");
            printf("             \\                                    ,-`\n");
            printf("              \\                                  <\"`\n");
            printf("              .\\                                  \\\n");
            printf("           _,'  \\                     _     ___ ,--\"\n");
            printf("         .'      \\              ,.'--`|:._.._`. `\n");
            printf("         |       _\\'.,_        '| `\"- | `--. `\"`\n");
            printf("          \\         ) `...|`-`,-|      `.._\n");
            printf("           `\"-.     \\-.   `.    '          `,\n");
            printf("               j__._,-'|         `---.       \\ _\n");
            printf("              |-.-'   _'              ` _      )|.\n");
            printf("              `.__..-' `-.               +.__.,'  |\n");
            printf("               ,'         /              \\..-'   ,`.\n");
            printf("       ,-\"----'      ,.--'                \\___,-'   `.\n");
            printf("       /  .-\"'    ,-'                        `.       `.._\n");
            printf("       `-..L____,'                            j __        |\n");
            printf("                                             |    `.      |\n");
            printf("                                              `___,'--....'   \n");

            break;

        case 58:
            printf("\n");
            printf("\n");
            printf("\n");
            printf("                   _,\n");
            printf("                 .',_..,\n");
            printf("               ,'     /,--\n");
            printf("             .'       ,./.__\n");
            printf("             |_,.----/,,'`.  _\n");
            printf("            .'__     //    `...>\n");
            printf("       ____//|) |    `      /.'\n");
            printf("      (/    `-.-'.._     _,|                 ,.-------.._\n");
            printf("      .             `.  '   \\               /            `-._\n");
            printf("      `..---._       |       `.            j                 `.\n");
            printf("        >-,-\"`\"\"'    |        |`\"+-..__    |              -. `-.\n");
            printf("       ( /|         /____     |  |  |  \\\"\"|+-.._     ___    `.  `.\n");
            printf("        \" `-..._     \"--,_    |  |  `   | |   | `.-.\"   \"-._  |  -`\n");
            printf("             ,'        '_>_   j ,'  '. ,` |,  |   `. `.-v.' `-+..._`.\n");
            printf("            '.         >       '     | |  ' \\ L     ..`.  '        `._\n");
            printf("             '.       /              '|`     \\|      '^,         ..,{ `.\n");
            printf("            / /      /                '       v          |__    ___,'\"\"\n");
            printf("          ,'  >---+-+.        |   __,..--\"`-._          /.-'`\"----'\n");
            printf("         /`.       `. '.      |-\"'            `\"--....-'._\n");
            printf("       .'___'        `._`,    j             ___,-','      `-..._\n");
            printf("  _ _.'    '/.-          '  ,'       __..<\"\"__,.-'              `.\n");
            printf(" `.)         |'---\"\"`.+-.--'-------\"\"-...__  ,-'/ .\"\\          _  |\n");
            printf(",\"\\ ,--.  _,-          ` `'                `'\"\"\"'`\"'\"\"\"`--._  . `/\n");
            printf(" `-`.___.'                                                  `\"-\"'\n");
            printf("\n");
            printf("\n");
            printf("\n");
            printf("\n");

            break;

        case 59:
            printf("            /  ,'(\n");
            printf("           /`-'   \\__.,\n");
            printf("         ,'     .-\"\\ `---/                     /\n");
            printf("      |`'      /,'||    '.               ,`. ,(,_. _,\n");
            printf("  __  |  ,--+--.  ||     `'/  .     _.-\"'   `    \"\"`.\n");
            printf(".\" ,'-'.\"d__|  `.'_'    _,-    ,.  /        ._      `\\_\n");
            printf("|,'     `-..-----\"._     `.     ` |           `.     \\.\n");
            printf(" `\"V\"--._           `.   `._    ' |             \\     \\,\n");
            printf("  \\      `----      '. _,-'    ,' |              \\     .\n");
            printf("   `._             .--`       `.  |               .    |\n");
            printf("      `-.          `,.       ,--  |               L    '\n");
            printf("        /   [-,=.---' `.__`,`     `.              |     \\\n");
            printf("    _.-'    `.._'--.._   - `--+\"\"\"\" '._           |      `._,\n");
            printf("    \\        _  ---..__`--._'-.`,  ,' ,`._       j         -,'\n");
            printf("   .'        ,-..     ,'    `. `  . ,'  / `._   /`._    ___,-'_\n");
            printf("   l        .|_  `,  -' . .-\"      v   /   _.`.'`   7\",',-,.-\" --,\n");
            printf("    \\      `.  .,  -..',')'\"\",   .    /  .'    |  ,'.',/| ,.     >\n");
            printf("     V-.    '    -._,-\"    _,  .,'   j ,^    ,'/`--' `    -..,   `...\n");
            printf("     '  \\/\\|.     :/       './`'|    |/    ,' /            `___    ,'\n");
            printf("           | `. ,'`-.        /  |    ' _.-'  |               ,'  .\"\n");
            printf("           L._`.'   |       Y,.'|    ,-    ,-'          __.,'  .'\n");
            printf("            \\ \\  /`.|     _,.',''.  .`-,../         ,.-/,...-`'\n");
            printf("             \\ ,|| |/_.-\\\" .+'    \\._  _,'       _.'\"  |\n");
            printf("              '  ' L| | `,' |      `.\"\"          ,.    |\n");
            printf("              )    `|\"      |        `>.. _,..--\" j    |\n");
            printf("           ,-'      |____,..'       ,',-\"'       /   _,'\n");
            printf("          /\"'    _,.'               |(      _..-' `\"\"\n");
            printf("          `----\"'                    `'\"\"'\"\"   \n");
            printf("\n");
            printf("\n");

            break;

        case 60:
            printf("  _..__                                    ___\n");
            printf(" /     `._                          ,--\"\"\"\"   `\"-.\n");
            printf("|         `.                    _.'\"\"/`.        |/`-.\n");
            printf("|           `.                ,+ `..' | |       |'...+.\n");
            printf("|     \\       \\              / /\\____,' '    __ `.`._,\".\n");
            printf("|      ..      \\           ,'  \\      .' ,-\"'  `. `.._,'`.\n");
            printf("|       .`.     \\         /     `-..-'  .  _.... |._      \\\n");
            printf("'        ' `     \\       /          ,-\"\"`.____...'  `.     \\\n");
            printf(" `        `.`.    \\     '         ,'   _,--------.`.  `.    L\n");
            printf("  `         ` `.   \\   j         /  .,' ,\"_.....`.`.`   \\   |\n");
            printf("   `.        `. `.  \\  |        / ,'/ .','..... `.\\ \\|   .  |\n");
            printf("     `.        `. .  \\ |       j . / ..'.,-\"\". \\ || ||   |  |\n");
            printf("       `.        `.`. \\'.      | | | |||.   .,.','/ /'   |  |\n");
            printf("         `-.       `. .:\\      | | | ||'`..___.'.','/   j   |\n");
            printf("            `-._     `-._\\      \\'.`.`..`..__....','   ,   /\n");
            printf("                `--......-\\      \\ `.`.`.......-\"'   ,'   /\n");
            printf("                           `.     `. `-..____,.-\" _.'   ,'\n");
            printf("                             >.     '--...___,..-'   _.\"\n");
            printf("                           ,'  `--,__            _,-\"  `-.\n");
            printf("                       _.-'      '   `'--------\"' `.      `-.\n");
            printf("                     .'        ,'                   \\        `.\n");
            printf("                    .        .'                      `.        .\n");
            printf("                    |      ,'                          `._     |\n");
            printf("                     `----'                               `\"--\"   \n");
            printf("\n");
            printf("\n");

            break;

        case 61:
            printf("             ___   _,-'\"\"-.\n");
            printf("           /`.  `./,\\`.    `.\n");
            printf("          /'. |  / || |      .\n");
            printf("         . `|,+-'| `| |       `._\n");
            printf("         `,-'    `. | '          `.\n");
            printf("        ,' -'      `\"'             `.\n");
            printf("       /\"`-.                         `.\n");
            printf("      :`.   \\                          .\n");
            printf("     ' `.\\   \\                          `\n");
            printf("    .`.  .`   `           `.             .\n");
            printf("   / `.'  .`   .      .     \\             \\\n");
            printf("  /``  .`  `\\   .      \\     .             .\n");
            printf(" j  .\\  .:  .'  :       .    '             |\n");
            printf(" |`. .. ||  :|  |        ,..--`._          |\n");
            printf(" |:| |: :|  |:  |      ,'        |         |\n");
            printf(" ||| :: |:  |:  |      |         |         |\n");
            printf(" :'j '| :|  :|  |      |         |         |\n");
            printf(" `/ .j  ,:  :|  |     ,'         `         |\n");
            printf("  \\/ / . '  ',  |   .'            \\        '\n");
            printf("  ` , /,'  /.  j   |               .      /\n");
            printf("   `.'/   /'   '   |  .             .   ,'\n");
            printf("     .  .'/   /    `._/             '  /\n");
            printf("      `.,'   /       |          __,' .'\n");
            printf("        `-._,         `.   _,.-\" _,-'\n");
            printf("            `+..____    `\"'    .'\n");
            printf("           _/    |  `\"\"\"''\\    '\n");
            printf("     _,.-\"'      \\        |     \\\n");
            printf(" _.-'             .       |      `\n");
            printf(",                 |       |       `.\n");
            printf("`_          __,,-'        '         `.\n");
            printf("  `'\"\"'\"'\"''             .            .\n");
            printf("                         |            |\n");
            printf("                         '            /\n");
            printf("                          `.        ,'\n");
            printf("                            `-..,.-'   \n");

            break;

        case 62:
            printf("                               __,.-\"\"\"'\"--..._.,---.\n");
            printf("                           _,-'               /      `.\n");
            printf("                        _.'                 ,'   ,-\"\"`.|\n");
            printf("                      ,'                        / ,+\"`.;\n");
            printf("                    ,'   ____                  . |_/  /\n");
            printf("                   /  .\"'    `-.               ` `..-/`.  _\n");
            printf("                  '  /                     .    `---'   `: `.\n");
            printf("                 /  .    ,-\"\"`.           .'             \\`-.`+\"\"`\"`.\n");
            printf("                /   |  .' ,\"\".|               _,...,._    L |  `     `.\n");
            printf("               /    |  | ._)  /     \\    _.-\"'        \"`. | j          .\n");
            printf("              j     `  ' |  ,'        ,-'   ___......_   .|\"           |\n");
            printf("              |         `-+'        ,'  _,\"__.---\"\"\"`-.`.||            |\n");
            printf("              '                   ,'  ,'.-'    _______ `.`|\\           |\n");
            printf("            .\"                   /  ,\",'   _,\"+.------+`.`:|           |\n");
            printf("          ,'     .             ,' .,-'   .\".-'  _..._  ` \\''    .      ;\n");
            printf("       _,+      /             ,  ,/    ,'.' .-\",.----.+ `7  `.   `._,.'\n");
            printf("      /  '    ,'             .  '.   ,\".\" .:,-'__     :|j     `-.-'\n");
            printf("     j    \\  /|`            ,  //   .,' ,'.' .\"__`.   ||'\n");
            printf("   ,-+     `\" | \\             /.   //  /,\" ,'.'  \\ \\  |'\n");
            printf("  /           '  \\         : j '  //  //  .,'     || ,\"\n");
            printf(" /           /    \\        | :|  j.' j/   ||_.\") , ;<_\n");
            printf(".            `-.   `.      : ||  || |.    `..-'.'.'   `'-._\n");
            printf("|              |     `.    | |:  :| |'        _,'          `.\n");
            printf("|              |      /`-._`.`:. \\' `.`..__.-'+              `\n");
            printf("`          .   F     ,     /\"`+-+.^+--`\"\"\"     `._            |\n");
            printf(" `.       |   /     /     .                       `._         /\n");
            printf("   `._   _,..'    ,'      '                          `\"-....-'\n");
            printf("      `\"\"        /       j\n");
            printf("               ,'        |\n");
            printf("              /          |\n");
            printf("             j           '\n");
            printf("             |          /\n");
            printf("             |         /\n");
            printf("             '        /\n");
            printf("              `.___,.'   \n");

            break;

        case 63:
            printf("                                                        _\n");
            printf("                                                   _, -\"'|\n");
            printf("                                               _.-'   ,'j\n");
            printf("                       ____           _,.....-'      /  |\n");
            printf("                      `.   `'--..,--\"'              .   |\n");
            printf("                       `.                           |   |\n");
            printf("                        .`.                         \\  j\n");
            printf("                _.,     '  .                         ` |\n");
            printf("              .','       . |                            \\\n");
            printf("            ,\" /         `./                             \\\n");
            printf("           /  /           /                    ,-'        \\\n");
            printf("         ,'  j           j  .._              ,'            L._\n");
            printf("        /    |           |     `.          ,'             ,'  `-.\n");
            printf("       .     |           |       `.       .            _,'       `.\n");
            printf("       |     |           `.        `               _,-'            \\\n");
            printf("       |     `           / `-.                  ,\"/                `.\n");
            printf("       |    _.\\         j     `-.._       ,   .' |                  ;\n");
            printf("       '  ,'   \\        |        _,'.    '  ,'    `.              .'\n");
            printf("        +'   ,.-^.      `-..,..-'/ _,^-----+.       `._       _,-'\n");
            printf("        .+--`._   `-._     L_   j-\"          `-.  _,-\\ `..,--'\n");
            printf("          \\    `      `\"-+'  `-.'               \"\" ,.'/ ` |      ,\n");
            printf("_____      L    `       /       `.._.----.._   _.-'  /   F     ,'|\n");
            printf("`.   `.    |     \\     '.           `\"\"\"-+.-`\"'     '    |`. ,'  |\n");
            printf("  `.   `.  |      L   _,+\\__              `          \\   |/ /    |\n");
            printf("    \\    +,'      |  '     `.`._           `.         |  |.,     |\n");
            printf("    `.  '         |,\"        \\  `.          |.      _,|         /\n");
            printf("      `           |           |   +.       / | _,-+'  |        /\n");
            printf("       \\          |          '    |\\.     /-',\"  /    |       j\n");
            printf("        \\         |         /_    | \\`..,-\".\"   |     j       |\n");
            printf("         \\         \\ _   _,'  `-.  `-,|/___.\\,-.|    /        '\n");
            printf("         `         `' \"\"\"        `\"\"'            \\  |        .\n");
            printf("          `. ,\"\"'   |                             `-+`./     |\n");
            printf("            `.     '                                  |      F\n");
            printf("              )   |                                    \\    /\n");
            printf("             /__,.'                                     \\,.'   \n");

            break;

        case 64:
            printf("                       .-\n");
            printf("                       | \\               _,\n");
            printf("                      j   \\           ,-' |\n");
            printf("                      |    \\       ,''   .'\n");
            printf("                      |     \\    ,'   .  |\n");
            printf("         .-`.        .|    __\\_,'    ,  ,\n");
            printf("       ,'   |        ||  \"\"        .'  /\n");
            printf("      .     +.      ,\"'           .   /   ___\n");
            printf("    ,-.\\ _,`.'     ,  __._        `. ,  ,'   |\n");
            printf("    .  `'   /     /  <   ,'    _    \\`.'     `-,._\n");
            printf(" ,\\_|`.,-`.'     /`. `-^-'  _.|    .-\"||     .'   `-.\n");
            printf("` `. //`.`      j \\`.     ,'|)|   ,\\  |`.    |  ,.--'\n");
            printf(" `. `'`//       |  `|   .:,-'     |`.'   `.___`\" '\n");
            printf("  `.|>,'\\       |`..|  /     ____.' |    `-. >    \\,_..._\n");
            printf("  // `   \\     ,',-'| /  \"'-\".  ` `.`.    ,-\"\"\\  ,'      `\".\n");
            printf(" (/   :  `-._,/ /,'`./  '\"-._ `. `. ``--..\\_,-' ,'          \\\n");
            printf("      '.    .',' /'|     /|  `. `. ._.__ _,'.\"|'             \\\n");
            printf("        .   `,' /  |  ` /-'    \\  `. ` -..-'  |\"`.            '\n");
            printf("         `--'/ /    `+-'        \\  ``.       .    `.          `\n");
            printf("            ' .       `-.  ,-\"--.+  \\ .    .' `.    `    .   | \\\n");
            printf("           '| |          `.\\,\" ,. ` ' '_.-'     \\    \\   |   ' |\n");
            printf("           |' |    __,.-\"' .| '|`. . \\`.   \\     \\    .  | ,'  |\n");
            printf("           || |  ,'\\        .`. V  | |     |      .   |  '   /.'\n");
            printf("           `| | /   `._     `. _|  | ||    |      |   | /..-' /   .\n");
            printf("            ' . '      /`---'.`.`._| '|,--.|      |   |'     /    '|\n");
            printf("             . . \\    ,'      ` \\/ '/ `    `._    '  ,'     |   ,' |\n");
            printf("              `.\\ `.  \\        `. .'   |      `.,' ,'|      '+-'   '\n");
            printf("            _.--`.-j   `-.-..    `-.   `-.     | ,/  `.       `  .'\n");
            printf("          .'_.'+\"\"' _   _,.'-`      `-..._,\\   |-'     `-...__..'\n");
            printf("          ' /_..|/-' `\"'                ,_.`'   `..__\n");
            printf("                                          `.  `-._  ,-'\n");
            printf("                                           `,..`. `/  |\n");
            printf("                                            :  /    `.'\n");
            printf("                                             `.'   \n");

            break;

        case 65:
            printf("                                               _,'|\n");
            printf("                                             .'  /\n");
            printf("                    __                     ,'   '\n");
            printf("                   `  `.                 .'    '\n");
            printf("                    \\   `.             ,'     '\n");
            printf("                     \\    `.          ,      /\n");
            printf("                      .     `.       /      ,\n");
            printf("                      '       ..__../'     /\n");
            printf("                       \\     ,\"'   '      . _.._\n");
            printf("                        \\  ,'             |'    `\"._\n");
            printf("                         |/               ,---.._   `.\n");
            printf("                       ,-|           .   '       `-.  \\\n");
            printf("                     ,'  |     ,   ,'   :           '__\\_\n");
            printf("                     |  /,_   /  ,U|    '            |   .__\n");
            printf("                     `,' `.\\ `./..-'  __ \\           |   `. `.\n");
            printf("                       `\",_|  /     ,\"  `.`._       .|     \\ |\n");
            printf("                      / /_.| j  ---'.     `._`-----`.`     | |\n");
            printf("                     / // ,|`'  `-/' `.      `\"/-+--'    ,'  `.\n");
            printf("                 _,.`,'| / |.'  -,' \\  \\       \\ '._    /     |\n");
            printf(" .--.      _,.-\"'   `| L \\ \\__ ,^.__.\\  `.  _,--`._,>+-'  __,-'\n");
            printf(":    \\   ,'          |  | \\          /.   `'      '.  `--'| \\\n");
            printf("'    | ,-.. `'   _,--' ,'  \\        `.\\            7      |,.\\\n");
            printf(" `._ '.  .`.    .>  `-.-    |-.\"\"---..-\\        _>`       `.-'\n");
            printf("    `.,' | l  ,' ,>         | `.___,....\\._    ,--``-.\n");
            printf("   j | .'|_|.'  /_         /   _|         \\`\"--+--.   ` ,..._\n");
            printf("   |_`-'/  |     ,' ,.._,.'\"\"\"'\\           `--'    `-..'     `\".\n");
            printf("     \"-'_,+'\\    '^-     |      \\                    /         |\n");
            printf("          |_/         __ \\       .                   `.`.._  ,'`.\n");
            printf("                  _.:'__`'        `,.                  |   `'   |\n");
            printf("                 `--`-..`\"        /--`               ,-`        |\n");
            printf("                   `---'---------'                   \"\"| `#     '.\n");
            printf("                                                       `._,       `:._\n");
            printf("                                                         `|   ,..  |  '.\n");
            printf("                                                         j   '.  `-+---'\n");
            printf("                                                         |,.. |\n");
            printf("                                                          `. `;\n");
            printf("                                                            `'   \n");

            break;

        case 66:
            printf("                        ,.\"--.\n");
            printf("                   _.../     _\\\"\"-.\n");
            printf("                 //  ,'    ,\"      :\n");
            printf("                .'  /   .:'      __|\n");
            printf("                || ||  /,    _.\"   '.\n");
            printf("                || ||  ||  ,'        `.\n");
            printf("               /|| ||  ||,'            .\n");
            printf("              /.`| /` /`,'  __          '\n");
            printf("             j /. \" `\"  ' ,' /`.        |\n");
            printf("             ||.|        .  | . .      _|,--._\n");
            printf("             ||#|        |  | #'|   ,-\"       `-.\n");
            printf("            /'.||        |  \\.\" |  /             `\n");
            printf("           /    '        `.----\"   |`.|           |\n");
            printf("           \\  `.    ,'             `  \\           |\n");
            printf("            `._____           _,-'  `._,..        |\n");
            printf("              `\".  `'-..__..-'   _,.--'.  .       |\n");
            printf("               ,-^-._      _,..-'       `.|       '\n");
            printf("           _,-'     |'\"\"'\"\"              `|  `\\    \\\n");
            printf("       _.-'         |            `.,--    |    \\    \\\n");
            printf("  _,.\"\"'\"\"'-._      '      `.     .      j      '    \\\n");
            printf(" /            `.___/.-\"    ._`-._  \\.    |      |     L\n");
            printf("/  ____           /,.-'    . `._ '\"\"|`.  `      |     |\n");
            printf(" `.    `\"-.      / _,-\"     `._ `\"'\".  `. \\     '     '\n");
            printf("   \\       `-   .\"'            \"`---'\\   ` `-._/     /\n");
            printf("    `-------.   |                     \\   `-._      /\n");
            printf("             \\ j                      .       `...,'\n");
            printf("              `|                       \\\n");
            printf("               '                        \\\n");
            printf("                .                      / \\\n");
            printf("                |`.                   /   `._\n");
            printf("                |    `.._____        /|      `-._\n");
            printf("                |        |   Y.       |.         `.\n");
            printf("                |       j     \\       '.`\"--....-'\n");
            printf("             _,-'       |      |        \\\n");
            printf("          .-'           |     ,'         `.\n");
            printf("         '              |     |            `.\n");
            printf("         `.        __,..'     '.             \\\n");
            printf("           `-.---\"'             `-..__      _/\n");
            printf("                                      `'\"\"\"'   \n");

            break;

        case 67:
            printf("           ,-\"\"\",.--\n");
            printf("         ,:-'_.--\"\"\"\\\n");
            printf("       ,\"/,-'  _,..--+-.\n");
            printf("      .,'/ _.-'         \\\n");
            printf("      |||,'_.-.          \\ ____\n");
            printf("      |.','U| |         .-'    `-.\n");
            printf("    ,\"   |_L:/        ,'          `.\n");
            printf("   j                 /              .\n");
            printf("   \\_______...-7    j           ___ |\n");
            printf("    V V/     _.'    |    _,.---- ,_`\"-.\n");
            printf("     ,/_...-\"   __.-|  -\"    `,.   ``.'`.\n");
            printf("     `..,......\"    `.  | \\    `+`. `  \\ .\n");
            printf("       j /            `./ \\\\    ` .  \\\\ . .\n");
            printf("       | |               ` `\\     \\'  \\' \\|\n");
            printf("       | |              | `.`+. /         \\\n");
            printf("       ` '              |   `\".',  `\\  `|  )\n");
            printf("        \\ \\           .'     . ||   || ||.'\n");
            printf("         `>`.,.....-----\"'\"\"\"\"\\`|   |' |||\n");
            printf("         / .||D.\\\\|.'\\ () (_) (\\|  j|  j/|\n");
            printf("        / +,|| ||||_____........|  || / .'\n");
            printf("     _,'.\"'_|\\.'/|   _,---._    |  .' ,'\n");
            printf("  .\"' .   '\"j-...' ,' ,     `. .'  '  |\n");
            printf(" /  ,/  ,'.'`     /  /       ,'       `.\n");
            printf(" | /| ,`./   \\   / .'        |         |.\n");
            printf(" | ||_|./ .   `.j /          `.        | )\n");
            printf(" `-'`.+' /      | `          ,'`.__     Y\n");
            printf("     .' /       | `.       .'   /  `\"\"'\"\n");
            printf("     |  '      /|    .___.'   ,'\n");
            printf("      `.   / -' `.        ,   `.\n");
            printf("       |  /       `+.     |     `.\n");
            printf("       |  \\        | `    `       \\\n");
            printf("        \\  `.      |`.`.   `.      |\n");
            printf("         \\   `.    |  `..    `.    '\n");
            printf("         /     `-. |    `.     `  /\n");
            printf("  ____.-'          `.  _,'      --\\\n");
            printf(",' .'_.,_.         __:\"            `.\n");
            printf("| ( | (         ,-\" ,-'.\" ,'_.      |\n");
            printf("`-`-^--`--------'__|__(  | /   _,--\"\n");
            printf("                       \"\"--'..'   \n");

            break;

        case 68:
            printf("                 __.\"`. .-.                    ,-..__\n");
            printf("              ,-.  \\  |-| |               ,-\"+' ,\"'  `.\n");
            printf("              \\  \\  \\_' `.'             .'  .|_.|_.,--'.\n");
            printf("               \\.'`\"     `.              `-' `.   .  _,'.\n");
            printf("                \\_     `\"\"\"-.             .\"--+\\   '\"   |\n");
            printf("                | `\"\"+..`..,'             `-._ |        |\n");
            printf("               j     |                       '.       _/.\n");
            printf("              /   ,' `.      _.----._          `\"-.  '   \\\n");
            printf("             |   |     |   ,'  ,.-\"\"\"`.           |  .    \\\n");
            printf("    __       |   '    /-._.  ,'        `.         |   \\    \\\n");
            printf("   (  `.     `.     .'    | /  _,.-----. \\       j     .    \\\n");
            printf("    `. |.  __  `,         |j ,'\\        `|\"+---._|          ,\n");
            printf(" .-\"-|\"' \\\"  |   \". '.    ||/d |_-\"\"`.    /     ,'.          )\n");
            printf(" `._. |  '.,.'     '  `  ,||_.-\"      |  j     '   `        .\n");
            printf(".\"'--:' .  )        `.  (     _.-+    |  |                  |\n");
            printf("`-,..'  ` <_          `-.`..+\"   '   ./,  ._         |      |\n");
            printf(" `.__|   |  `-._     _.-\"`. |   /  ,'j      `. `....' ____..'\n");
            printf("   `-.,.'    \\  `. ,'     ,-|_,'  /  |        `.___,-'   )\n");
            printf("      `.      `.  Y       `-..__.',-'    __,.'           '\n");
            printf("        `         '   ,--.    |  /            `+\"\"       `.\n");
            printf("         `.       ,--+   '  .-+-\"  _,'   ,--  /     '.    |\n");
            printf("           `-..   \\     __,'           .'    /        `.  |\n");
            printf("               `---)   |  ____,'      ,....-'           `,'\n");
            printf("                  '                 ,' _,-----.         /\n");
            printf("                   `.____,.....___.\\ _...______________/\n");
            printf("                                  __\\:+.`'O O  O O  O |\n");
            printf("                              ,-\"'  _,|:;|\"\"\"\"\"\"\"\"\"\"\"\"|\n");
            printf("                            ,'   ,-'  `._/    _.\"  .`-|\n");
            printf("                         .-\"    '      \\    .'      `.`.\n");
            printf("                        :      .        \\   |        / |\n");
            printf("                         .      \\.__   _,`-.|       /  |\n");
            printf("                         `.      \\  \"\"'     `.         `....\n");
            printf("                           .     |            \\             `.\n");
            printf("                          .'   ,'              \\              |\n");
            printf("                  ,------'     `.               `-...._  '\"-. '.\n");
            printf("                 / ,'\"'\"`        |                  `--`._      `.\n");
            printf("                 `\"......---\"\"--'                         \\       .\n");
            printf("                                                          |        `.\n");
            printf("                                                         (   -..     .\n");
            printf("                                                          `\"\"\"' `....'   \n");

            break;

        case 69:
            printf("                _.--\"'\"\"\"--._\n");
            printf("              .\"             `.\n");
            printf("             /                 .\n");
            printf("            j                   .\n");
            printf("            |                   |\n");
            printf("            |                   |\n");
            printf("            | (')              j\n");
            printf("            `                 ,`.\n");
            printf("             \\               ,^. `.\n");
            printf("              .             /   \\  .\n");
            printf("              |            /     . |\n");
            printf("              |          ,'      | |\n");
            printf("             ,'---..___ /        | |\n");
            printf("            ' `--..___ \"`.      .  |\n");
            printf("             `\"--....___.'     /  j__.....__\n");
            printf("                              /   |         `.\n");
            printf("                             / _,------._     `.\n");
            printf("                            /,+_         `.     `.\n");
            printf("                          ,'    `-.        \\      .\n");
            printf("                         .         `.       \\      \\\n");
            printf("                         |           `.     |       \\\n");
            printf("                         |             `.   |_,..__  .\n");
            printf("                         |\\              \\  |      `.|\n");
            printf("                         | `.,--------._  \\ |        `\n");
            printf("                         |  |           `. \\|\n");
            printf("                         |  |             `.|\n");
            printf("                         |  |\n");
            printf("                         |  |\n");
            printf("                         |. '\n");
            printf("                        .' \\ `.\n");
            printf("                     _,' ,' `. ._\n");
            printf("   ---====+,______,.\"_.-'     .  `.\n");
            printf("   _,..==`'_.+'-\"\"\"\"'         / ^.\\`:._\n");
            printf(" ,=\"/    ,\"            ....==+ /  `\\  `:.\n");
            printf("'  /    / |               _+:-'    .|   ``.\n");
            printf("       '  `.           --\"\"        |'     `\\\n");
            printf("                                   '   \n");

            break;

        case 70:
            printf("                                    _...._\n");
            printf("                                  ,'   __ `.\n");
            printf("                                .'   ,'  `. |\n");
            printf("                               .   .'      .|\n");
            printf("                              /   .        ||\n");
            printf("                          .-\"'\"\"\"-'        ,'\n");
            printf("                      _,'\"\"\"'\"--._ `.\n");
            printf("                    .'            `.:\n");
            printf("                  ,'                `.\n");
            printf("                 /     _              \\\n");
            printf("   ..--._       /     ._;              \\\n");
            printf(" ,'      `.    j                        .\n");
            printf(".          `.  |                        |\n");
            printf("|           ,+-' ,-\"\"-.       _.-\"'\"\"\"`\"`._\n");
            printf("|          : |/ /`.    |    ,'             `.\n");
            printf("|          |// :  |    |   ,                 '.\n");
            printf("'    .     |/  '-\"     |  /                    `.\n");
            printf(" `    \\   ,'    `-...,'  j                       `\n");
            printf("  '._/_\\.'               |                        `\n");
            printf("  .'   `\"-._             |                         \\\n");
            printf("  |         `.           |                          \\\n");
            printf("  | --+.      `.          .                 ___      .\n");
            printf("  '   | `.      `.         .           _.-\"\"   `\"._  |\n");
            printf("   .  '    .      `.        `-.____,.-' /          `.|\n");
            printf("    .  `    `.      .                  /             `\n");
            printf("     `. `.    `.     \\                ,\n");
            printf("       .  .     .     .             ,'\n");
            printf("        `  `.    `.    .           .\n");
            printf("         `.  `.    .   |        _,'\n");
            printf("           `    `. |   |      ,'\n");
            printf("            `.    `'   |  _.-'\n");
            printf("              `-.      ;-'\n");
            printf("                 `--..\"   \n");

            break;

        case 71:
            printf("                                       ___\n");
            printf("                                    ,\"\" __\"`.\n");
            printf("                                   / .'\"   `-`.\n");
            printf("                                  / /        ` .\n");
            printf("                            _,.__. /_,...._   \\ \\\n");
            printf("                         ,-'     |j        `-._\\ \\\n");
            printf("                      _,'        ||            `._\\\n");
            printf("                    ,'_,..,.      |        .----._`.\n");
            printf("                  _,\"'   / /     `'         `.   :`-'\n");
            printf("                        / j               ,_  \\   `|\n");
            printf("                       j ,'-._      _..-\"\"' | `.  ||\n");
            printf("                       | |    `'-.,'        |  |  ||\n");
            printf("                       | |  _.              ' j   ||\n");
            printf("                       ' '.'.'         \\\"-./ ,    |'\n");
            printf("                        ` `/_           \\_/ /     | L\n");
            printf("                         `._ `-..___,.-'\"_,:      | |\n");
            printf("                          | `._      _,-' ||      | |\n");
            printf("                          |`..,+----`.__,\" |      | |\n");
            printf("                          |                |      | |\n");
            printf("         _.--\"\"\"\"--._     |               _'    _.+-'\"\"\"'`-._\n");
            printf("       ,'            `-.  |.-.           , `\\ ,'             `.\n");
            printf("     ,'                 \\j |  |          `./ /                 `.\n");
            printf("    / _.--\"\"\"--._        | `-\"               |    _,.-------.._  \\\n");
            printf("   /.'           `-.    j                    | ,-'             `-.\\\n");
            printf("  ,'                `-. |                    |'                   '.\n");
            printf(" /   __                \\|                    /                      `\n");
            printf("j .'\"  \"-..             |  _         ,\"`.    |           _,.--'\"\"'-. .\n");
            printf("|/:        `._          / | \\        |  |    |        _,:           \\|\n");
            printf("` '           `-._    ,'| `.,'       '.-'    `..__,..' '`.   __\n");
            printf(" '                `\"\"'  '                    ;          `.`.'  \"'--...,'\n");
            printf("                         .  Y.          /\"','             '-..____,.-'\n");
            printf("                          `-._         _`-'\n");
            printf("                              `\"------\"   \n");

            break;

        case 72:
            printf("                             _,--'\"\"\"`\"--._\n");
            printf("                           ,'            _.-+._\n");
            printf("                       ,-.'            ,'      `.\n");
            printf("                     .'  |            .          `.\n");
            printf("                    /    '            |            \\\n");
            printf("                   /    /             |             L\n");
            printf("                  /    /            . |             |\n");
            printf("                 j    /             | '             |\n");
            printf("                 |   /              '  .            |\n");
            printf("                 |  j  .             \\  .           |\n");
            printf("                 '  | /               `  `.       .''\n");
            printf("                  \\ |j                 `.  `-....\" j\n");
            printf("                  |`'|   ,',..           `.._      |\n");
            printf("                  `. `   |/   \\              `     |\n");
            printf("                    `.   `.   |                    |\n");
            printf("                     |     `__'                    |_,..---..\n");
            printf("                   __|                            ,'         |\n");
            printf("                .\"\"  '     .    '               ,'           |\n");
            printf("                |     .    |     \\   ____     ,'             |\n");
            printf("                .      `-..L      `,'u   `:-./              j\n");
            printf("                '        |u \\     /    _,-'  |             /\n");
            printf("                 `.   ,./`\"\"`\\_ ,'`\"--'      |            /\n");
            printf("                   `./  \\..._  |    _,..._   |.---+.    ,'\n");
            printf("                    / ,'     `.|  ,'      `--'-.   \\`--'\n");
            printf("                   j .         `.'              `.  .\n");
            printf("                   | |                           |  |\n");
            printf("                   | |                           |  |\n");
            printf("                  j j                            |  |\n");
            printf("                 ,' |                            |  |\n");
            printf("           ___.-'  ,'                            |  |          _,-..\n");
            printf("    _,.-'\"\"   __,.-'                             |  |       ,-' ,--\"'\n");
            printf(" ,-',.-' _,.-'                                   |  '     ,'  .'   /\n");
            printf(". ,' _,-'                                         .  `---'  ,'  _,'\n");
            printf("|/ .'                                              `.    _,' _,'\n");
            printf("`-'                                                  `\"-`.,-'   \n");

            break;

        case 73:
            printf("                                      _.._,-\"\"-.._     \n");
            printf("                             _....\"\".'_,./        `.\n");
            printf("                           .'  ,|   ,'   |          `.\n");
            printf("                          ' _,'\"'\"\"'      `.          |\n");
            printf("                         .,' ___            `--....__ |\n");
            printf("                        ,|.\"\"   `-.____,.--'\"\"\"\"`-._ `'.\n");
            printf("                      ,','            _,.--         `.._`.._\n");
            printf("                    ,.,'          _.-\"   /'\"\"-._        `\"'-`.\n");
            printf("                   /      ,-\"\"\"-,'-.._,.'       `.           |\n");
            printf("                  (      |`.__,' `.      ,-.      |         (\n");
            printf("                   `._   |_.'     |  /|  ` |,\" .  |          |\n");
            printf("                     /`  |       .'  |`   `.'.`\\`/          ,'\n");
            printf("                    '._ j       /   .` .    .``.`.`-._ _,.-'\n");
            printf("                       `/      /    ||`.`    `..``.`-.`.._\n");
            printf("       _              ,'      /,.___'|  ``.,..-\\`-\\`/ `._.+,------._\n");
            printf("      \\ `\"-.__      ,+      .'|| | j |+-+-`._`+.\\+--\"\"\"\"            `-.\n");
            printf("       `._    \"'\"'\"'/|     j| |' . | |\\`.`.  |+---+--+-+--.....__      \\\n");
            printf("     __..-`--------+-|     || | \\ / / \\\\ \\ \\ | `.\\ \\. \\ \\   `. `.`-.___/\n");
            printf("   .'       _,.-',','`     || |  /,\\  ` \\ ' \\|   `\\ \\`.\\ '    \\  \\\n");
            printf(" ,'     _,-'    / . .'\\    || |,'/\\ \\  \\ \\ \\ |    | |-. L`+._  \\  |\n");
            printf("/    ,/'       . j  | |\\   '.-'.'  \\ `. \\ \\ .|    / `  `| |  `-.`-'\n");
            printf("|   ,'        j  | j  | `.  `.\"\\    `  \\ . .|'   /|  \\  | |`.   .\n");
            printf("`..'          .  | |  `.  /. `. `    `. `| |/   / |  |  |  . `-.'\n");
            printf("              |  | `.  | /  +. \\ `.    \\ |,'  ,'\\ |  |  |  |\n");
            printf("              |. |  `..' | .' `\".  .   _\\+  _.| | |  '  '  '\n");
            printf("              .`.'       `-'    `--'  '--+\"'| `.' `-'  `..'\n");
            printf("                                         `--'   \n");

            break;

        case 74:
            printf("                                            _,.---.\n");
            printf("                                        _,-'       `.\n");
            printf("                                     _,'  ,          \\\n");
            printf("                                   ,'  _,'   .        `.\n");
            printf("                                  /  ,'     ,'          `.\n");
            printf("         __                       .,'    _,'              `.\n");
            printf("    _,..'  `-....___              :    ,'     '             \\\n");
            printf("  ,'   /            :             /`.,'      /               `\n");
            printf(" /    /  ._         |         __..|  `.    .'       ,         `.\n");
            printf(" |   |   ,'\"--._    |      ,-'    `-._`.,-'       ,:            .\n");
            printf(".'\\   \\     _,'.    `'___.'           `\"`.     _,' /            |\n");
            printf("|  \\   \\---'       ,\"'  .-\"\"'\"----.       `.  '  ,'             |\n");
            printf(" `. `-.'          /    /                    `-..^._             '\n");
            printf("   |._|    _.    /    /                            `._           .\n");
            printf("   `...:--'--+..'   ,'                              /            |\n");
            printf("       '._  `|   ,-'       _..._                   j     \\       |\n");
            printf("         |` |   /       ,-'     `-.__              |      L      |\n");
            printf("         |  |  /      ,'                           |      |      |\n");
            printf("         |_,'        /         _,-                  .     |      |\n");
            printf("        ,'  ,   |  ,'        ,|            ,..._     \\    |      '\n");
            printf("       ,     \\ j  '       _.\" |           /     `-.__'    '    ,'\n");
            printf("        +._   '|       ,'|    |          /        ,'    .'    /\n");
            printf("        |  `._  `-' .:|  |    '.       -'        '           j\n");
            printf("        '    |`    ' |'  |     |                             |\n");
            printf("         `.  |       |--'     _|        .                    |\n");
            printf("           \\ |       '----'\"\"\"           \\      __,....-+----'\n");
            printf("           | '                            `---\"\"      .'\n");
            printf("           `. `.                                     ,\n");
            printf("             `\" \\_...-\"\"\"'--..         _+          ,'\n");
            printf("                  '            -.'  `-'  `.  .\"-..'\n");
            printf("                   `-..._            _____,.'\n");
            printf("                         `--.....,-\"'   \n");

            break;

        case 75:
            printf("               __..  ,..--+'\"\"--.._\n");
            printf("            ,-'    \\_|_...'        |\n");
            printf("     ,'\\  ,'`.,----\"    '          |.._\n");
            printf("    /  _\\_'   `.                _,.+.  `-.___\n");
            printf("    |          |           ,.--'     \\       `.\n");
            printf("  /'|          |\\,-.       |          `\"--.    `.\n");
            printf(" |  |          |/   \\                      :     |\n");
            printf(" |  '          /    '                      |     |\n");
            printf(" `.|         ,'    /                       '     `\n");
            printf("|\"j               _,\\                             \\\n");
            printf("| /  ,          -'   \\                             \\\n");
            printf(" |  '/     _.-       |            _,.               `..\n");
            printf(".'| /   ,-'/     --- `         -\"'   `.                |\n");
            printf(" `| `--d  |         __        __       |        __     |\n");
            printf(" /    /...'   .  ,\"'  .         `.    .'          \\    |\n");
            printf("'..-----.._ ,'   |    '           \\    `           |   |\n");
            printf("   |/  _,.-'     '                      \\          /  ,'\n");
            printf("  /'\"\"'                      .\"\\         \\       ,'   |\n");
            printf("   -...--.__                 `  \\        _\\..     \\   `.\n");
            printf("    `.                        \\\"        :   |     |   /\n");
            printf("     |    _..-.    ,..-.       `.    ..\"    `     /  .'\n");
            printf("   ,-|   |     `---;             |           `.  '   |\n");
            printf("   \\  `. `---._ '\"\"`---.         |             | __.-'\n");
            printf("   |..\"|+.\"`-'        /         j.            /  |\n");
            printf("    `. | \\          \"'      _.' '|           /  /\n");
            printf("     |\"\"`.`\"'          __,\"\"  __.-          j ,'\n");
            printf("     .--- \\ `--------\"'      ,              +'\n");
            printf("     |__,' `+.          .    |.            |\n");
            printf("   ,'  |     \\`-.___,-' `.__.' `.          |\n");
            printf("   |._,'   | |   |         |   ,'\\    '.   '\n");
            printf("   |\"`.--|-+.' _.'         |`..  /`--/ :.-.|\n");
            printf("   '  |  \\  |,'.. _     .-' _ .-'   /.-'  /\n");
            printf("    `-'   `.|_(._|______|_ /  '.__,' \\,...'\n");
            printf("                          `\"-------'\"   \n");

            break;

        case 76:
            printf("                            _____   ____\n");
            printf("                       _,.,|     `\"`-.._`--._\n");
            printf("                    _,\" ,j |            `\"-. `-,\n");
            printf("                 _,\"_,-' ' |._              `.  \\`.\n");
            printf("               ,' ,',.....L   `-._            \\  . `.\n");
            printf("             .' ,\"'\"`.__  |       `-.._        | |   \\\n");
            printf("   ,.._     ,'-/     '  `.|..'\"\"|`._   `-.___.-','-._ `.\n");
            printf(" ,' . _>-.._/ /     /    /   `-.' \\ `-._  |   ,'     `-..\n");
            printf("/,..|`._'  / /     /   ,'   _ _\\   `.   `-:..'          `\\\n");
            printf("''  | .--./ /     /   / ,'\"\"|/ .'\"\"'\\`.._ |  \\            |\n");
            printf("  /'`.   / |`...+.   /.' _.`+._ `._/ \\'| `|\\  `.____      |\n");
            printf(" /,..:.-+ _|.-\"'\"\"`./__.\"      `.|    j   `.\\  /---._\"---.|`.\n");
            printf(" '     _:\"    ____  | |          `+---'     `\\/       \"-._| |\n");
            printf("     ,'    ,+\"  |   ' '.           \\`.       |            `.|\n");
            printf("    .     d |  /     \\  \\          |  \\      |             ||\n");
            printf("    |   _/..+.'       \\  \\      __,^.  '._   |            j |\n");
            printf("   ,'_,'        ___    \\  `----\" ,.--`+..,.-'+`-.._       | |\n");
            printf("  ',\"     ____,'/     / +...--'_,.--\"'||       '._ `-..__/ /\n");
            printf("   `...--\"'|  .'   _,'| / ..-'\"       ||          `.    / |\n");
            printf("          ,'./ ,.-'   |j |          __||          .'`,\"__.'\n");
            printf("          \\__.'\\     j | |        ,'    `-.     ,\" ,'.\" .'\n");
            printf("              \\|     | 'j       ,'         `. ,' .',' .'\n");
            printf("             . `.____|/ |__    :            |`,-'.'_.\"\n");
            printf("             '.  `._ _.\"-._`-._|            +----'\"\n");
            printf("               `.   `\"\"-.._`-._|            |\n");
            printf("                |          `<\" `.           |\n");
            printf("                /            `.  `.         '\n");
            printf("           ,.\":\"_,-           |,..'          `._\n");
            printf("          '.__|' ,--.    __,.\"'> .             /`.\n");
            printf("              '\"\"`---`'\"\"  \\_.' _|-\":__,....--'\"''\n");
            printf("                             `-',..-'   \n");

            break;

        case 77:
            printf("                    .' .\n");
            printf("                   .| '\\\n");
            printf("           _...___/`'   .\n");
            printf("         ,'             |\n");
            printf("     ,|,\"             )/|                             , .\n");
            printf("    / |              / , .                            \\` \\\n");
            printf("   /            ...-'  ',                              .  \\\n");
            printf("  .           ,>      .                                |   |\n");
            printf("  |          .'   ___`,                  .'  ,--.._,.-'/  ,'\n");
            printf("..|          |.-\"', /                  ,' | /       .\"'   '.\n");
            printf("\\ '          |  ,'//                   .'  \"    __,._'    |\n");
            printf(" \\ `         /.\"_/'_,                 '.       /         _'\n");
            printf("  `.\\     _,'   \\.`  ) ,^.              `     '       ,-\"\n");
            printf("    |.  .'  _   | `. '-  `,            , \\     `.    ,-\n");
            printf("    | `w  ,\" |  |   \\   .'   _,_ :\"'. / 7 . ,`..'   .'\n");
            printf("    '|    `.'  /     \\   `-'\"   `   _:_,.}|  :  _. ,'\n");
            printf("     \\       .'       `-.      _,.-\"       `-+-`  '\n");
            printf("     |       |           ``--\"'               `.\n");
            printf("     \\   .- .                                   \\\n");
            printf("      `.._,\":                                    \\\n");
            printf("            '                                    `.  '-7\n");
            printf("             \\                                  .'`-\"  :\n");
            printf("              \\                        .        `      `-'\n");
            printf("             j \\                       `.        `.     |\n");
            printf("             |  `.  |      .^,'.       ,.+        :    _'\n");
            printf("             |   |`.|      |    \\,  ,-'  :`.       \\  /_.,\n");
            printf("            /    |  |     /     .,-'.     `.`.      \\   /\n");
            printf("           /    .' j     / _._,\"     `      ':`.     . (\n");
            printf("          /    /,-\"|    j  `.         `-.    |  .    |/\n");
            printf("          .   `'   |    |    7           |   |   |   |\n");
            printf("           `.   .  |    |  v'            |  .'   |   |\n");
            printf("             `.  `.|   j'.'              |  |    |  j\n");
            printf("               \\   |   |                j   |   j   |\n");
            printf("                `.j   /\\                |_,j    |  j\n");
            printf("                  /  /`\"              ,\"   |    '  |\n");
            printf("                 /  j                 '_,.-'   /.-'|\n");
            printf("                |   |                         /__.-'\n");
            printf("               .'`-.'\n");
            printf("              /    |\n");
            printf("              `----'   \n");

            break;

        case 78:
            printf("                     :`./\n");
            printf("                    _|  ,-\n");
            printf("               ,'\"\"'    ,`\n");
            printf("             ,'.\\       `.    __  ,.-.\n");
            printf("          . ./ `'    __  '. ,'  \\ `.|\n");
            printf("          \\\\  \\   .\"'  L   \"     `\" `\\                          _,-.\n");
            printf("           \\` |\\.`      7     .,   :._|   --'`.                 ` |\n");
            printf("          ` \\`+ `'\\      \\^--\"  `. |    ,'     `.            ,..' |\n");
            printf("           | ,.    |              ` `.  |    ..  '.          |    /\n");
            printf("           ':P'     '.    ,..      \\  `-+`\"-'  `._ \\     -`,- ..,'\n");
            printf("          /        / `-,-'  ,'`.    `.   ; .--'   `+    '.   | ,\n");
            printf("         /     _..     .   `-.  \\,.   `-'  '.  `.^  `\".__|   ' |\n");
            printf("        '   , / |       `.   \\    |        ,'     \\           /\n");
            printf("         `\"' \" .         \\   |  __ \\    ,-'       `----.   _,'\n");
            printf("              /           |  `\"' _} `\"\"'                `-'\n");
            printf("             /.'         /     .-.         ,\".\n");
            printf("     .._,.  /           /     '-.,'    ,'-. .'.\n");
            printf("    /  `. \\/             `-.      `.   /`.  :\n");
            printf("   /  __ `.'                '-.     `-+_.'  .'          ,__\n");
            printf("  / .'  `.___                  `,..__      <__          \\ (\n");
            printf(" / /       \"..   /                   `-.     .' .-'\"`--.'  \\\n");
            printf("/  |       /-'  /                       \\ ,._|  |          /'\n");
            printf("\\.'|+.+.  (`..,'                         \\`._ _,'           \\__\n");
            printf(" \\ |||| \\ _`.^ `.            .            |  \"    .'`\"-.       `.\n");
            printf("  `+'|/ `( \\'    `-....__    |            |._,\".,'     `,        |\n");
            printf("                         `:-.|            `           ..'   ,'`.,-\n");
            printf("                          |  |            |`.        '-..    . /\n");
            printf("                          '  |           /  /           `.   |\n");
            printf("                           ` '          /  ',.         ,     `._\n");
            printf("                            \\|        ,'   \\'|         :  __    '\n");
            printf("                             `,     ,`     .._`..       `'  `-,.`.\n");
            printf("                       _`'`\".  `.   ``-._ /   F   )        ,._\\ `\n");
            printf("                      '-\"'`, \\   \\ ,. ).-'-.^,|_,'         `  '.\n");
            printf("                          '.. \\___j  `\"'               ,..  | .'\n");
            printf("                             \\            ___       ,. `\\ \\,+-'\n");
            printf("                              7.._   .--+`.  |_    |  `,'\n");
            printf("                           _,'  .'`--'  '    7 ` v.-\n");
            printf("                         .\"._  /-.  -.   \\.^-`\n");
            printf("                       .'  __+'...`'  `--'\n");
            printf("                        `\"\"   \n");

            break;

        case 79:
            printf("                                  _.---\"'\"\"\"\"\"'`--.._\n");
            printf("                             _,.-'                   `-._\n");
            printf("                         _,.\"                            -.\n");
            printf("                     .-\"\"   ___...---------.._             `.\n");
            printf("                     `---'\"\"                  `-.            `.\n");
            printf("                                                 `.            \\\n");
            printf("                                                   `.           \\\n");
            printf("                                                     \\           \\\n");
            printf("                                                      .           \\\n");
            printf("                                                      |            .\n");
            printf("                                                      |            |\n");
            printf("                                _________             |            |\n");
            printf("                          _,.-'\"         `\"'-.._      :            |\n");
            printf("                      _,-'                      `-._.'             |\n");
            printf("                   _.'                              `.             '\n");
            printf("        _.-.    _,+......__                           `.          .\n");
            printf("      .'    `-\"'           `\"-.,-\"\"--._                 \\        /\n");
            printf("     /    ,'                  |    __  \\                 \\      /\n");
            printf("    `   ..                       +\"  )  \\                 \\    /\n");
            printf("     `.'  \\          ,-\"`-..    |       |                  \\  /\n");
            printf("      / \" |        .'       \\   '.    _.'                   .'\n");
            printf("     |,..\"--\"\"\"--..|    \"    |    `\"\"`.                     |\n");
            printf("   ,\"               `-._     |        |                     |\n");
            printf(" .'                     `-._+         |                     |\n");
            printf("/                           `.                        /     |\n");
            printf("|    `     '                  |                      /      |\n");
            printf("`-.....--.__                  |              |      /       |\n");
            printf("   `./ \"| / `-.........--.-   '              |    ,'        '\n");
            printf("     /| ||        `.'  ,'   .'               |_,-+         /\n");
            printf("    / ' '.`.        _,'   ,'     `.          |   '   _,.. /\n");
            printf("   /   `.  `\"'\"'\"\"'\"   _,^--------\"`.        |    `.'_  _/\n");
            printf("  /... _.`:.________,.'              `._,.-..|        \"'\n");
            printf(" `.__.'                                 `._  /\n");
            printf("                                           \"'   \n");

            break;

        case 80:
            printf("                   ,-'\"-.\n");
            printf("             __...| .\".  |\n");
            printf("        ,--+\"     ' |   ,'\n");
            printf("       | .'   ..--,  `-' `.\n");
            printf("       |/    |  ,' |       :\n");
            printf("       |\\...-+-\".._|       |\n");
            printf("     ,\"            `--.     `.     _..-'+\"/__\n");
            printf("    /   .              |      :,-\"'     `\" |_'\n");
            printf(" ..| .    _,....___,'  |    ,'            /\\\n");
            printf("..\\'.__.-'  /V     |   '                ,'\"\"\n");
            printf("`. |  `:  \\.       |  .               ,'         ,.-.\n");
            printf("  `:       |       |  '             .^.        ,' ,\"`.\n");
            printf("    `.     |       | /               _.\\.---..'  /   |     ,-,.\n");
            printf("      `._  A      / j              .\"       /   /    |   .',' |\n");
            printf("         `. `...-' ,'             /        /._ /     | ,' /   |\n");
            printf("           |\"-----'             ,'        /   /-.__  |'  /    |\n");
            printf("           | _.--'\"'\"\"`.       .         /   /     `\"^-.,     |\n");
            printf("           |\"       ____\\     j             j            `\"--.|\n");
            printf("           |  _.-\"\"'     \\    |             |                j\n");
            printf("         _,+.\"_           \\   |             |                |\n");
            printf("        '    . `.     _.-\"'.     ,          |                '\n");
            printf("       |_    | `.`. ,'      `.   |          |               .\n");
            printf("       | `-. |  ,'.\\         .\\   \\         |              /\n");
            printf("       |\\   ;+-'   \"\\      ,'  `.  \\        |             /\n");
            printf("       '\\\\.\"         \\ _.-'     ,`. \\       '            /\n");
            printf("        \\\\\\           :       .'   `.`._     \\          / `-..-.\n");
            printf("         ``.          |    _.\" _...,:.._`.    `._     ,'   -. \\'\n");
            printf("          `.`.        |`\".'__.'           `,...__\"--`/  |   / |\n");
            printf("            `.`.     _'    \\|             ,'       ,'_  `..'  |..__,.\n");
            printf("              `._`--\".'     \\`._      _,-'       ,' `-'  /    | .  ,'\n");
            printf("                 `\"\"'        `. `\"'\"\"'   ,-\" _,-'    _ .'     '  `' `.\n");
            printf("                               `-.._____:  |\"       _,\" .\"  ,'__,..\"'\n");
            printf("                                         `.|-...,.<'    `,_\"\"'`./\n");
            printf("                                             `.'   `\"--'\"   \n");

            break;

        case 81:
            printf("                                  _,._,._\n");
            printf("                                 '-\"._,\"--,\n");
            printf("                                  `\"..-+-'\n");
            printf("                                  :'==-:\n");
            printf("                                  :`=-\":\n");
            printf("                                 _.\"-..|\n");
            printf("     _____                  _.-'\"  `\"\"' `-._\n");
            printf("    |  |  `\"\"'----._      ,'                `.\n");
            printf("    |__|            `.  ,'                    '.\n");
            printf("    '..|\"\"'---._     | /                        \\    _.......______\n");
            printf("          `\"\"\"--:    |/         ,.---._          \\ .'.------.....__`-...\n");
            printf("                |    j        ,'       `.         . '              |\"--|\n");
            printf(".'\"\"|\"---......-'   .|       /           \\        |'     ______    |   |\n");
            printf("|   |              / |      .      .      .       |    .'      `\"\"`--..'\n");
            printf(":\"\"'|---.....___.-'.'|      |             |       |    :\n");
            printf(" `\"`+---....____,.'  `      `.           /       /|    '_\n");
            printf("                      \\ _,..  `.       ,'       / `      `\"\"'--....,._\n");
            printf("                      .'::__:   `-...-'        ,   `._            '   |\n");
            printf("                      |-..--|          ,-\"-. ,'       \"--.....___:   j\n");
            printf("                      `.::_,          |.-''-:                     `\"'\n");
            printf("                            `\"-...____' \" :.'\n");
            printf("                                       `\"\"'   \n");
            printf("\n");
            printf("\n");
            printf("\n");
            printf("\n");
            printf("\n");
            printf("\n");

            break;

        case 82:
            printf("                                 _\n");
            printf("                              ,\"'_\\\n");
            printf("                         ,\"\\  `.\"  \\       ,..._\n");
            printf("                        '.' \\   \\   .     ('\"\"`.\\     _\n");
            printf("                         \\   \\  `.  |      /=.:.'  ,:`.`.\n");
            printf("                          \\   \\.';  |\"\"\"\"\"`-./   .'   .`\n");
            printf("                           \\   `\"   '         `.'   ,' ,\"`.\n");
            printf("                            `.___..'            `. `..:'`./\n");
            printf("                            /             _,.._   \\    _.'\n");
            printf("                 _....__   /            ,\"     `.  ._,'\n");
            printf("             ,-\"'       `\"+.           :         . |\n");
            printf("+'\"|\"\"'-.  ,'               `.         |      \"  | |\n");
            printf("\\\\_|__   `:                   \\         \\       /  |          _,-.\n");
            printf("      :)  |        ,.-----.    \\         ._   .'   '._    _,-'`\\  j\n");
            printf("  ...,'   |       /        \\    . __ _ _,\".`\"'   ,'   `.,\"    _.`\"\n");
            printf("  \\\\ |  _,'      .          .   || |I ' -'|    _, _     `   ,\"'  _.\".\n");
            printf("  `\"\"'':         '     \"    |   |`\"'^\"`\"| /  ,`:://\\     \\  `..-' \\  '\n");
            printf("       '          \\        /   ,\"\"`--..`\"\"-\"`\"\"':{.|      .      _,+\"\n");
            printf("        .          `-....-'   :`:'-|            |l,'      |.__.-\"\n");
            printf("         \\,.                  '. :/                       |\n");
            printf("     .-.\":`.`.              ,'  \"'     ,\"-.   _       _,._|\n");
            printf("     \\`. \\`,\"`._        __,:      .    `.'/`,'.`.   .'    '\n");
            printf("      '.`.;     \"--+--'\"_  `       `     `.` \"' ; ,'  .  /\n");
            printf("        `\"         ||  :|.  :       `.     \\_:.' :    _.'\n");
            printf("                   ||  |||__|         `._        `...\"\n");
            printf("                   ||__||| _|            `\"-....-\"\\\\,\\\n");
            printf("                   || _| `\"                  \\\\  \\ \\\\'\n");
            printf("                   `\"'                        \\`.-\\\n");
            printf("                                               \\\\.'   \n");

            break;

        case 83:
            printf("        .\n");
            printf("      ,' \\\\\n");
            printf("     /   ' \\\n");
            printf("  _  \\    \\ \\\n");
            printf(" / \". \\    ` \\                                        ,.\n");
            printf("j    \\ \\    ` \\                \"\"\"'-. ..          .. :| \\\n");
            printf("|     `.\\    ` `              __ `.  \\: \\         \\ `||  .    ___\n");
            printf(" `.     `\\    `.`.            \\ `\"-`. \\ |          \\ `|  |   //  |\n");
            printf(" _ '.     `     . `.           `-.,    `'-.._       \\    |  //   |\n");
            printf("| `._`.          `. `         .-'   --._  || `.      \\   | //   j\n");
            printf("|    `.`           . `.      /     .\"\"-.`._|.\".\\      \\,-|'/    |\n");
            printf("'       `.          `. `.   /      | '::|  '|:| .      : |,     '\n");
            printf(" `._                  .  \\ :       |  ::|.-\"\"\"'.|___...+-+-..  /\n");
            printf("    `-.                \\  `:       '__.,'               _,..-)/\n");
            printf("   .\"`-`.               \\   .       .'_....__    __..-\"' _.-'/\n");
            printf("    \\                    \\   \\      :\"       `'\"\"  __.-\": |,\":\"`.\n");
            printf("     \\                    \\   \\ .,\"--`.       _..-\",'   | |.\"   |\n");
            printf("      `._                  \\    j      `\"'\"\":'  ,'      |,'     |\n");
            printf("         `.                 .   /           |_,'      ,-'       |\n");
            printf("      \\`._ `.                `\"'            '       ,'          |\n");
            printf("       .  `-.:._                           j       /          _.'\n");
            printf("        `.     .`.._                       |      :.......--\"\" '\n");
            printf("          `. '`   `.`-._                  .      .'           /\n");
            printf("            `:      `                    ,       \"-..._____..'\n");
            printf("        `\"\"\"-.--.....__                .'         _.' /  /\n");
            printf("        _.`--         .`,           _,'----....--'   /  /\n");
            printf("       \"---..,.  __,--`-........,.-\"                /  /\n");
            printf("            /..-\"_..---\"'   _.-'                   /  j\n");
            printf("               --.,..    _,'                      /   |\n");
            printf("                 .','_,-'                         '--\"\n");
            printf("                 `\"-'   \n");

            break;

        case 84:
            printf("                                  _.---.._\n");
            printf("                                ,'       ,.\n");
            printf("                               :    _    '_|\n");
            printf("             _,-\"'--._         :  :'|\\      :\n");
            printf("           .'         `.       |  `--'  .\"\".;\n");
            printf("           |     __     .      `.       `. '.\n");
            printf("           |    :_'|    :        `.    _.'`. `.\n");
            printf("           ,\"'. `--'    .          |\"''     `. '.\n");
            printf("          '  ,'        /           | |        `. `._\n");
            printf("        .' ,'`.   __,-\"            | |          `.  `.\n");
            printf("      .' .'    `|\" |              j .             `.  \\\n");
            printf("    ,' .'       |  | _   ._      .  '               `.'\n");
            printf("  ,' ,'         '  |' `-'  `..\"',  j\n");
            printf(".' .'         .\"'  '          ,'  .'\n");
            printf("`-'         .'   `  `.      .\"  ,'  \\\n");
            printf("           <      `   \\      `-'     .\n");
            printf("            :      `  .'             ,\n");
            printf("           j        `\"         .-   :\n");
            printf("           :                  .  \"   `\n");
            printf("           |               .  `       '\n");
            printf("          `.                         7\n");
            printf("           ,                        '\n");
            printf("            '.                    .'\n");
            printf("              ,-.               ,'\n");
            printf("                 '..        _.-:\n");
            printf("                    `|\".-.-' | |\n");
            printf("                     | |     | |\n");
            printf("                     | |     | |\n");
            printf("                     ' .     ' '\n");
            printf("                    . .       , .\n");
            printf("                      |       | |\n");
            printf("                   :  '       | |\n");
            printf("          ,-\"`----\"'  .___    | |\n");
            printf("         '-'..--\",    ___:_`.\"'  -..____\n");
            printf("             _.-'_,.  ._\\_,.      _____:_\\\n");
            printf("           ,\"  ,'   : `    / ,-.  \\\n");
            printf("          ,'.,'     |  : ,' /   '  \\\n");
            printf("         '.-\"       `.\"\": ,'     `  `.\n");
            printf("                      '/`.        `.\"|\n");
            printf("                       .'           \\'   \n");

            break;

        case 85:
            printf("                            .\n");
            printf("                          .'/   .\n");
            printf("                        .\" / ,\".'    _.--:'`-......___\n");
            printf("                     , / ,-\"_,' ___.\"   ,.`-.....-\"\"\n");
            printf("                   // //_.-'   /.._\"\"\". |_'  : `-...\n");
            printf("                 ,/.-'`'  `.  '  '._..-.     '\n");
            printf("               ..','   _,   :      `.,'    .'\n");
            printf("             .'/-.: |,'|_   :       /\\__ ,'\n");
            printf("           ,'_,   _'_ \"     ;       j,| |\"`--,\\_\n");
            printf("          :_`.'_,\"_,+\\   ,^.`.     '/ | |      '.\n");
            printf(" ,.------\"...,\".-\" '/`\"'`   `.`.  ,'  ` l       `.    _.---._,.-..\n");
            printf("'-...-\"' .\",.____./`.\"-._     `.`...   `_\\       '_.-'_,.-'       \\\n");
            printf("       .','      :/  `-._`\"---..`.._|            : ,-\" __..--\"\"'`.-'\n");
            printf("      +\"'        /       `\"'\"\"----.              ;,.-\"'          _|\n");
            printf("                /                 :_     '.   _;\"'+.,--\"'\"''\"'\"\"\"\n");
            printf("                                  ' `-:.,' `'\"     /-..\n");
            printf("                                      |     .-----'--..`.\n");
            printf("                                      ;___,'           `.`.\n");
            printf("                  _.,....---------...' ,'                `.`.\n");
            printf("            _.--\"',     ____,.....----\"                    `.`-._     ,\n");
            printf("           :-'.,-' .-._'.                                    `._ `----')\n");
            printf("          '._\".  .'    \"'                                       `. `.__\n");
            printf("         `' ',.-'                                                `.-...'   \n");

            break;

        case 86:
            printf("                            _,.--\"\"\"'--._\n");
            printf("                          ,\"             `.         _,.--'\"\"\"\"--.._\n");
            printf("                         /                 `.     ,\"               `.\n");
            printf("                        |  ,                 \\   '                   `.\n");
            printf("                        '.'                   \\ /                -..   .\n");
            printf("                         j                     '                    \\  |\n");
            printf("                         |                                    .._    . |\n");
            printf("                         .    .       _...         _,..._        `.  :'\n");
            printf("                          `-./      ,'    `.      /      \"`.      |  ;\n");
            printf("                             '.   ,'       |     (          \\     .-'\n");
            printf("                               `\"'         |      \\          `-..'\n");
            printf("                                          /        \\\n");
            printf("                                        ,'          \\\n");
            printf("                                     _,'             `.\n");
            printf("                                 _,-'                  \\\n");
            printf("                               ,'                       \\\n");
            printf("                              /  /\\                      \\\n");
            printf("                             /  /  \\                      \\\n");
            printf("                            /  /    \\                      l\n");
            printf("                         _,.-\"/      '--._                 |\n");
            printf("                       ,'      `.  '      `.               |\n");
            printf("                     ,' _..          _      `.             |\n");
            printf("                    ,   _  `       ,' `.      \\            |\n");
            printf("                   .  .\".`          ...        \\           '\n");
            printf("  _.--\"\"`--....--\"'|  |`' |       .(_) |        .         /\n");
            printf(",'  _              |  `../        `.__.'        |        /\n");
            printf("| ,'              ,'-\"'--._,...  ______         |    _  /\n");
            printf("|/  _.           .  .      \\_,'\"'      `-.      '     `'..__,...----._\n");
            printf("' ,'             | | \\               ,'|  \\    /                      `\n");
            printf(" `|          _,-\"'.|  \\ .---,-._    /  |   | .' __                \"\"`-.\\\n");
            printf("  `.     _.-'      |  .:   j    `-.j   |  /.'--'  `.           .       |\n");
            printf("    `'\"\"'           `-''   '     ,'|   | ,'         `.          \\      |\n");
            printf("                        `-......'--...`-'             \\          .    ,'\n");
            printf("                                                       `-._      |_,.'\n");
            printf("                                                           `\"---\"'   \n");

            break;

        case 87:
            printf("             /\\\n");
            printf("        _.--'  `\"-.\n");
            printf("       ' ,.        `\n");
            printf("     ,' '_.'        \\\n");
            printf("    |                .\n");
            printf("    \"..+--.,-        :\n");
            printf("       ||'           '\n");
            printf("       `._            `.\n");
            printf("          |             `._\n");
            printf("          |                `.._\n");
            printf("          |  .                 `\"--.._\n");
            printf("          | /   . .                   `-._\n");
            printf("          `/    |  .                      `.\n");
            printf("          /    j   |                        `.\n");
            printf("        ,'    '|   |                          \\\n");
            printf("      ,' .\"  / |   |                           \\\n");
            printf("    .' ,'  ,'  '   |                            \\\n");
            printf("   /          '    ._                            .\n");
            printf("   `\"\"-.          /  `-._                         .\n");
            printf("        `\"'-....-'       `\"--...__                |\n");
            printf("                                  `\"-.._          |\n");
            printf("                                        `.        |\n");
            printf("                                          `.      '\n");
            printf("     ,-._                                   .    .\n");
            printf("    /    `-._                               |    '\n");
            printf("   j         `-._                           |   /\n");
            printf("   |    ___      `-.                       ,'  /\n");
            printf(" ,'        `\"--..__ `-._                _,'  ,'\n");
            printf("|                  `\"--.``---........--'    /\n");
            printf("`                               _..-      ,'\n");
            printf(" `.                    __...--\"' _,'    .'\n");
            printf("  |     '\"\"'\"-----\"'`\"\"      _.-'    _,'\n");
            printf(" /                    __,.-\"'  _. _,'\n");
            printf(" `.    _______....--\"'      _,'_.'\n");
            printf("   `.                   _,.'_.'\n");
            printf("    |           ___,..-'_,-'\n");
            printf("    `._          __..-\"'\n");
            printf("       \"'`._...-\"   \n");

            break;

        case 88:
            printf("                                        _.---.\n");
            printf("              __             _____  _.-'      |\n");
            printf("    .\"\"\"--._,'  \\          .\"     \"\"          |\n");
            printf("    '.    `.`._ /          |                 / `.\n");
            printf(" .---'      `._|  _,....._  `.___          .`   /\n");
            printf("|     ...._   .`\"'    __  `\"-. ` `.     _.'___,'\n");
            printf("`._      `.`.'\\     ,\"  `.    `.)`.`-\"\"'_.\" .'\n");
            printf("   |.____.,'. |   _/ .    ;__  ,   ``\"\"\"     `.\n");
            printf("   |,-.  /    ' .\" |     ,__ `.'           . ,'\n");
            printf("   '   `j`---'.',-\"`----'   `\"| \\ __       | |\n");
            printf("    `.  |   `'\"'            .  \\ `._\"..__.'  .\n");
            printf("     |  '                  /:  |\"`--',..\"     |\n");
            printf("     |`. `.___...----.....' '  `    |  |     .'\n");
            printf("     |-.`.__,--|          |\"   :    |  |    /(\n");
            printf("    .   `-.___.|   ,--.,-\"|    ``.  |  |   . .'\n");
            printf("    `          |  /       |   . `.`.`--' ,'.'  `-\n");
            printf("     '.        | /        |   |   `.`...-,'      |\n");
            printf("      '`-._  _/|j        /  ,.'     '---\"   _..-\"|\n");
            printf("       `._.`\" |||       / .','            .' _..'|\n");
            printf("        |  `..||\\     ,'.\".-     ``.    .' .'    `.\n");
            printf("        |     \\`\"-..-'  :|         \\`\"\"' .'     .'.`.\n");
            printf("       ,'      `-----.-\".'   '`._   `\"--'     .','   \\\n");
            printf("      .               `\"      `..-'     .\"\"`-','.'   |\n");
            printf("      |.__..        ___       .        /.'\"\"\" .'     '.\n");
            printf("      '___.--..__.-\"_..`.    ,..___  ,'  `\"'\"'       _.'.\n");
            printf("        '---. `.__,\"`._`-._,' `----`'              .'  ,-'\\\n");
            printf("     _,'  ___`--\"                      ,-'\"`..___.' .-'   |\n");
            printf("   ,\"   ,..-.`\"._  ___..._    .\"\"..__,'.'\"\"`-......'       `._\n");
            printf("  /    _____ `.__`\" _.-\"'       `-..--\"       _...._  _....__ `.\n");
            printf("  | .\"'----.`._  `\"\"       ,.\"\"--._         _.....,_`\"_.----...'\n");
            printf("  `------'\"\"`._`.      _,.--\"''\"\"--......-\"'        \"\"\n");
            printf("               `\"-----\"   \n");

            break;

        case 89:
            printf("                             _,..-------.._\n");
            printf("                         _,-'              `-._\n");
            printf("                       ,\"               .---.._`.\n");
            printf("                      /----.       _._,.._\"\"\":\"`\"`.\n");
            printf("                     /`--\"\"     _.'.'  / .`-.'-\"'\"`\\_\n");
            printf("                    /\"\"-._`----\" .'  .' '   _.`     \\\"-._\n");
            printf("                   .      `.___.'   / ,' . |   |  ._  . .``-._\n");
            printf("                 _,' _.            .,' ,\"| |   |   .`.|'.' ,--\".\n");
            printf("               ,'    ||`._..____..\"' ,'--'.|   |    `.|'  .'\"-._|\n");
            printf("              /___...'|   :._     _,'      `'-. |     |  _,.._  |.\n");
            printf("             |,--.._|j  ,'   `'\"\"'         ||  `|     '.'_..._` | )\n");
            printf("            ,'      /  /                   ||   |    /',\"     ` '/|\n");
            printf("         ,-'   .,-./  /      _,..----..___,':`_'    /.'        `.' ._\n");
            printf("        /  __.._ `-\\.'-----\"'  _,...__      '\"     /.\"\"-..-\"\"\"-. |_  `._\n");
            printf("   __..:--\"_.--.`.  `---....-`\"..__.\" `-...      _.\"'\"''`---..__`._`\"\"__\\\n");
            printf(".-'  `\"\"''\"       `..--\"\"-.   _.--.._   _.-\"\"-_,'              _.._`-._  '_\n");
            printf("|\"\"-.    __.-----._ '....`._-\" _,-\"'`-..._,..`__...\"\"\"-.__  _.'_.._`-..:'\"-)\n");
            printf(" `\"\"`..-\"_...----..___)     `\"\"              `....------._\"\",-'    `..-'`\"\"\n");
            printf("      `\"                                                  `\"   \n");

            break;

        case 90:
            printf("               _,.-'\"\"\"''--..._\n");
            printf("           _,-'               `.\"-.._\n");
            printf("         .\"     _..-'\"'\"\"--._   `.   `-._\n");
            printf("       ,'   _.-'             `._  `.     `-._\n");
            printf("      /   .`                    `.  \\        `.\n");
            printf("     /  .'                        `. `.        `.       _,..\n");
            printf("   .'  /                            `. `.        `...-\"'    \\\n");
            printf("  /   /                               _. `.               ,-'\n");
            printf(" j   /                   ,-\"\"'`.   ,\"'  `. `.           .'\n");
            printf(" |  .     _..------...__'  \"   |  |   \"   |  `.       ,'\n");
            printf(" `._...-'\"_,.-\"'        `..__,\"    `._ _,.'`.  `    .'\\\n");
            printf("   ,\"  _,'             __..-\"\"'`\"'.  ,'    `..  `.     .\n");
            printf(" ,'  .\"        _..-''\"\"            \\/        `.   \\    '\n");
            printf(":         _..+'----\"'               `.         `.  \\    \\\n");
            printf(":      _,'    `-._                               \\  \\    \\\n");
            printf(" `...-'           `.                              \\  \\\n");
            printf("                    \\                              \\  \\   .\n");
            printf("                     \\                              .     '\n");
            printf("                    / \\                    .        '  `  :\n");
            printf("                  ,'   \\               .    \\        \\  \\  `-,._\n");
            printf("                ,'    __\\               \\    \\        \\  \\  /._ `.\n");
            printf("               .  _.\"'   \\               \\    \\        `._'/._ \"-.\\\n");
            printf("                `\"        `.              `._.'        ,'.-.. `-._ `\n");
            printf("                            `-._                    _.'.  `,\"`-._ `.`\n");
            printf("                                `--...__     ___..-\"  \\ `. '     `._`|\n");
            printf("                                        `\"'\"\" \\   :    \\  `.`.      \"\n");
            printf("                                               \\  :     `   `.`.\n");
            printf("                                                '\":      `.__,.'\n");
            printf("                                                  `-.....'   \n");

            break;

        case 91:
            printf("                                                          _\n");
            printf("                                                       ,\"  '\n");
            printf("                                                     ,'   /\n");
            printf("                                                    /    /\n");
            printf("                                                  ,'    /\n");
            printf("                                                ,'     .\n");
            printf("                                     _...      /       '\n");
            printf("                                  ,'\"'\"\".`.   |_..    /\n");
            printf("                        ,-\"'\".   /       \\\\  ,'   `.\"'\n");
            printf("                       .\"\"\"'. |,'         .`\".    /.\n");
            printf("                      /     | |           `...`\".',___\n");
            printf("                     /      | `.            _.-' /.___`\".\n");
            printf("                   .'       `-._`-.._____,-'    /     \\ |\n");
            printf("             ,..    \\           `. . ,'.'      /       .|\n");
            printf("           .'   `.   \\   /        .||.'       '.`.._   ||--.\n");
            printf("           \\      `...`-'         ||||      .'  `-.._`.||_ |\n");
            printf("       _,.--`\"'-..\"'              ||``. ,-\"\"\"\"`'\"--._`\"-._`-.\n");
            printf("  _,-\"'           `.              ' .\\`'             `.   `. \\......\n");
            printf(",'                 '               || .|              |`.   \\ \\   .'\n");
            printf("`.._____________ ,'\"`+-\"\"'''       || ||              |  \\  `. .-'\n");
            printf("               |    .    _..-'    j | ||              |  |    ||\n");
            printf("               |    |   .         |. j |              |_'|.   ||\n");
            printf("               |    '    `-.._    || | |  .........      | |  ||\n");
            printf("               |     `._          || ' '   \\  __.-\"  _,' '.. , '\n");
            printf("               `._      `..       ' . `..   \"\"_,..-\"'  .'  \\/.'\n");
            printf("                  ``.    /         \\`.  ``-._`-....\"_,'   .,'|`._\n");
            printf("                     `..'           `.`._  `.`--\"'      .,'\\ :   `.\n");
            printf("                      /     _.-   .    `-.:-._ ` '._    :   . `--..'\n");
            printf("                    ,'  _,-' `.   :    __  `-.` `.._`. /,  ,','\n");
            printf("                  .'  .'       `-. `-'\"       \\`.   ` ',  ','\n");
            printf("                  `--' `--..     | `-._____   `._:---.| .'/\n");
            printf("                            \\    |     .'  \"-.____`\". |-\"'\n");
            printf("                             `.__|    /           `\"'\"\n");
            printf("                                 |   /\n");
            printf("                                 '._'   \n");

            break;

        case 92:
            printf("                             _\n");
            printf("                          .\"' `..._\n");
            printf("                         '         `.\n");
            printf("                       .'      ___..'\n");
            printf("                 _   .\"       '   .__,-.,\"\", ,----.\n");
            printf("      ,.-\"\"''-..\" :  :        `--'        ' :      :\n");
            printf("    .'            :_,'                    `._`\"--. ;\n");
            printf("    :              _,.--'\"'\"\"`--._           `.  `\"\n");
            printf("   j             ,'               `-.      ,._.'  ,\"\".\n");
            printf("   :           ,'                   ,-.   .   __  `..'\n");
            printf("   `--.    .'.'                   ,'   `. :_,\"  `.\n");
            printf(" ,.   ;   .   \\                 ,'      |         `.\n");
            printf("' :  :    |    `.             ,'        |\\         `.  _\n");
            printf(" `.   ._  |      \\         _.'          | .      ___ `\" :\n");
            printf("        : '     . \\      ,'  .          ' |     :   `...'\n");
            printf("       ,'  \\       `.   .             ,'  |     '  __\n");
            printf("      .    `.       |    \\          .'    '    .  (  `.\n");
            printf("    .'      \\`.___,'      `-.____.-'     '     :   `-.'\n");
            printf("     .   ,\". \\ ..___              _     /      :    .\n");
            printf("     :   . :  \\|/\\  `\"'--------+\"|,'  ,'       `-..' :\n");
            printf("      `-\" .'   `: `\"-.._______,.\\|  .'               '\n");
            printf("          `--. _ `._             _,'        ,\"\"-.__,'\n");
            printf("              \" :   `\"--.....--\"'     __   .\n");
            printf("              ,-'                 ,.-\"  `-'\n");
            printf("             :   ,..             .    ,\"\".\n");
            printf("            .'   .  :   __..._   `\"-. :   :\n");
            printf("            `.._  : ' ,'      `\"--..' `--\"\n");
            printf("                `-' `\"   \n");

            break;

        case 93:
            printf("               -._                                   _.\n");
            printf("                \\ `-.._                           _,' |\n");
            printf("                 \\     `-._    _,.--------.._  _.\"    '\n");
            printf("                  \\        `--'              ``.     /\n");
            printf("                   \\                                j    __\n");
            printf("__         __       \\                               |.-\"' /\n");
            printf(" `.`-.`-.__`.`'\"----\"\\                              |    /\n");
            printf("    `.       `.       '        ._                       /\n");
            printf("    `..        \\               | `.               /|   /\n");
            printf("      `.        `.             |   `._          .' |  /\n");
            printf("        `.  .-----`            |      `.       /   ' '\"\"''\n");
            printf("          `. `.            .    ._      `_    /  ,'    .'\n");
            printf("            `. `.           `._   `'\"\"'\"'     \"\"' ,  ,'\n");
            printf("              `. `.          `.`.              ,-/ ,'       _..\n");
            printf("                `. `.          \\|,---..  ,--\"./ / ,--------\".  \\\n");
            printf("                  `._           `.     `/ , .`.',:           \\  \\\n");
            printf("                     `._          `..\".,./ ' _.' :            \\  `.\n");
            printf("                   ,-'\" `-._              _.\"     .   |.-\"`.   \\  |\n");
            printf("                  .         `-..........-'        |   `..   \\   |_'\n");
            printf("                  |           `\".                 `.._   .  '  ,'\n");
            printf("                  |         |   |                     `\"'    .'\n");
            printf("                  |   /\\    |'  '\n");
            printf("                  '  /  \\   ||   .\n");
            printf("                 '   \\  '   |'   ;\n");
            printf("                  \\  '  \\   `...'\n");
            printf("                   `\"\"   `,'   \n");

            break;

        case 94:
            printf("                 |`._         |\\\n");
            printf("                 `   `.  .    | `.    |`.\n");
            printf("                  .    `.|`-. |   `-..'  \\           _,.-'\n");
            printf("                  '      `-. `.           \\ /|   _,-'   /\n");
            printf("              .--..'        `._`           ` |.-'      /\n");
            printf("               \\   |                                  /\n");
            printf("            ,..'   '                                 /\n");
            printf("            `.                                      /\n");
            printf("            _`.---                                 /\n");
            printf("        _,-'               `.                 ,-  /\"-._\n");
            printf("      ,\"                   | `.             ,'|   `    `.\n");
            printf("    .'                     |   `.         .'  |    .     `.\n");
            printf("  ,'                       '   ()`.     ,'()  '    |       `.\n");
            printf("'-.                    |`.  `.....-'    -----' _   |         .\n");
            printf(" / ,   ________..'     '  `-._              _.'/   |         :\n");
            printf(" ` '-\"\" _,.--\"'         \\   | `\"+--......-+' //   j `\"--.. , '\n");
            printf("    `.'\"    .'           `. |   |     |   / //    .       ` '\n");
            printf("      `.   /               `'   |    j   /,.'     '\n");
            printf("        \\ /                  `-.|_   |_.-'       /\\\n");
            printf("         /                        `\"\"          .'  \\\n");
            printf("        j                                           .\n");
            printf("        |                                 _,        |\n");
            printf("        |             ,^._            _.-\"          '\n");
            printf("        |          _.'    `'\"\"`----`\"'   `._       '\n");
            printf("        j__     _,'                         `-.'-.\"`\n");
            printf("          ',-.,'   \n");

            break;

        case 95:
            printf("                                                       _\n");
            printf("                                       ___            | |\n");
            printf("                                   .-\"'   `...._      | |\n");
            printf("                      _,--\"'-.   ,' .           `.    | |\n");
            printf("                    .'       ,`,'    \\            `.  | |\n");
            printf("                  ,'.      .','       \\            | j  |\n");
            printf("           __,..,'   `----\"  `         \\       _..-+.`  |..\n");
            printf("        ,'\"     .             '._  ___...-._ ,'     |   |  `--.\n");
            printf("       /       _|              | `\"        .'       |   |      `.\n");
            printf("      /`  _.-`'  ._..----\"\"`._ |         ,'         |   |        .\n");
            printf("     | .-\"         `-._    _,.' `.     .'          j    |         `.\n");
            printf("  ,-\"\"\"--..._       |  '`\"\"       `-../\\     _,\"''\"|    |.._       ,|\n");
            printf(" /    '.     `\"----,'                 ` '._,'      |   j    `.   .' |\n");
            printf("/_.-'\"  `-.___..-.\"                    \\ ,'   \\    |   '    | `.'   '\n");
            printf("`                |                    _.'          |  |,_   '   `. /\n");
            printf(" .        _______|                 .-'    |.       `. '           |\n");
            printf("  `...---\"     .-'               .'       | `.                 ,  '\n");
            printf("  ,'._     _,-\"                  `        |  ,`.  ,  .    _.-'|    `.\n");
            printf(" .    `\"\"-'    `.                 \\       `.....`.     .-',   |      .\n");
            printf(" |             _,|                 ._ --.        |     '\"--...       '\n");
            printf("  `.--\"`.....-\" ,                    /\".`        |   |        _____,'\n");
            printf("    .       | .'_                   /   \\        |  j       \"'_,..'\n");
            printf("     /`-...-+\"   `.                 '   .'.__ -..'  |_,..   ,'  |\n");
            printf("    '          ____.                 \\  |    \"`-..___,....-.    '\n");
            printf("     .     _.\"\"'   |                  `. .                 / .-'\n");
            printf("      `. .'       .._                   \\ \\               / /\n");
            printf("        `-._   _.'   `.                  \\.--......____ .' /\n");
            printf("          .'`\"\"    .'  .                  .            '_.'\n");
            printf("          |       /    |____               `\"._     _,-\"      ,-'\"'\n");
            printf("           `. _.,'     |    `.                 `--\"'       _.--,.'\n");
            printf("             `'--.__,.\"       |                          ,' .' |\n");
            printf("                   |   ,.._   |\"--._                  ,-+-.'  /\n");
            printf("                   `..'    ``.'   ,.`.     _..__.-\"\"\"-.__.'\\\"'\n");
            printf("                     `----.,\"    '   .--..'   _..`-../:  _,'\n");
            printf("                           .    /  .'  _.'\\.-\"  |     '-\"\n");
            printf("                            \"--+--\"`..'   |.   ,^.__,'\n");
            printf("                                     `---\"  `-\"   \n");

            break;

        case 96:
            printf("                        .\"'`-._,........_.------..\n");
            printf("                       / _.-'          ,' ,---\"\"/\n");
            printf("                      /.'                /   ,.'\n");
            printf("                    .'                      `-.\n");
            printf("                  ,'                           `.\n");
            printf("                 /          _..                  \\\n");
            printf("        ______,..         .',\"\"\"\"\\)               `.\n");
            printf("   .\"\"\"\"        |.-----           -                 \\\n");
            printf("  /.' .   _     |______                              \\\n");
            printf(".'/   | ,'      '        _.....-         _,---.       \\\n");
            printf(" \\  ,\"'/-._      \\----  /-..____.   _,.-\"              .\n");
            printf("  `.|      `\"-.._ \\____/        ,---..._               '\n");
            printf("                 `            .' .      `.              \\\n");
            printf("                  |           |  |  |  |/       ,        .\n");
            printf("                  |           './|  |`.'.._   .'         |\n");
            printf("                  |               `.'      `\"\"           |\n");
            printf("                  |--.      ___       _,...    _.'\"`-...'|\n");
            printf("                ,/    `---\"'   `-....'     `--\"          |\n");
            printf("              .'.                         _...           |\n");
            printf("             /  |                      ,-'               |\n");
            printf("            /   |                    ,'                 j\n");
            printf("           .     \\                  /                   |\n");
            printf("           |      \\                .                    |\n");
            printf("           '       `               |                    |\n");
            printf("            `.      `._            '                    '\n");
            printf("              `.       `._          \\                  /\n");
            printf("            ,.\".          `.-........'.               /\n");
            printf("          ,.-'  `.____....-'           `.            '\n");
            printf("          '...--\"'                       )           `.\n");
            printf("                                       .',.-,----.    |\n");
            printf("                                       `.  |      \\_.'\n");
            printf("                                         `-+----\"\"'   \n");

            break;

        case 97:
            printf("                  .\\\n");
            printf("                 .  \\\n");
            printf("                     \\              _,|\n");
            printf("                j    _\\____      _.\" ||\n");
            printf("                |  -'      `\"-.-',---.|_\n");
            printf("               /                /j      `.\n");
            printf("              /                . |    |   `.\n");
            printf("             ,                 | |    |     \\\n");
            printf("            /|.                ' `    |  / ,'|\n");
            printf("          ,' |\\`.               `.`.__|_/.',`\n");
            printf("         :   | `|      ,.--..     ||\\   '\"   `.\n");
            printf("        .'   | /      |`'-\"\"'     '| \\         `.\n");
            printf("        )    `j       `.         / |  \\          .\n");
            printf("       ,`-'   |       .'        /  | `.\\         |\n");
            printf("      / |   _ |     ,'       _,'  _|_ | \\        '\n");
            printf("  _,-'  `. /  \\   ,'......--'   .\" _ `.  `      /\n");
            printf(".\" ---._ ,'|   --`              | . `. |------\"'\n");
            printf("|       |  '    .       .       `.`-' .'\n");
            printf("|       |   `.  |        |      _/:--'\n");
            printf("|       |    \\`-|        | _..-'  |\n");
            printf("|       |  _,.\\  `\"--..-\"'`      ,^.\n");
            printf("|       `.'    `                    `-.\n");
            printf("`         `\"-.                         `.\n");
            printf(" \\       .---'                           \\\n");
            printf("  \\\\\\  . `.         __....._              \\\n");
            printf("   \\\\\\__\\__'    _,-'        `-.            .\n");
            printf("   |          ,+             .'`.         .'\n");
            printf("   '.     _.-'  \\            '            \\\n");
            printf("  ,-\"`-...     ,'             \\     _ '\"-. `.\n");
            printf(" / ,'   .-    /                `.    `.   \\.'\n");
            printf(" \\_|  .'    ,'                   `-...'--\"\n");
            printf("   `--'---'\"   \n");

            break;

        case 98:
            printf("            ,-\"'\"'\"--.                       ,-\"\"\"\"'`-.\n");
            printf("           '          `.                   /           \\\n");
            printf("          '             \\                 ' __          \\\n");
            printf("         /       .+\"\"`'`-                `-'  `\",        \\\n");
            printf("        /       , |                             |\\        .\n");
            printf("       .       .  |          ,.    ,-.       .  | .       |\n");
            printf("       '       |  |.\".       | .   | |      ' `.| |       |\n");
            printf("        \\      |_.'  '      .' .  .  |       `  `.|       '\n");
            printf("        .    _,'    /    ,\"\"-. `-.' ,-\"\"-.    |    `.    .\n");
            printf("        j-..'      / ,-.'  .  \\    |  .   .--.'      `...'.\n");
            printf("        | `-`._.--'.'  `._     |   |   __.'   \\`--...'-'  |\n");
            printf("        `....'     | /\\___`'--'     `\"\"_....\"\\ \\     `...'\n");
            printf("         | |-\"-._,`.'     `\"-._     _.\"       \\|\". ,^.|  |\n");
            printf("         | `..,\"_,'            `---'           \\  `-..'  |\n");
            printf("         `._|_.\\ `._____                 _...__.`._,_' _.|\n");
            printf("         /  '`-.`-._|.  `-._           ,\"     .','_,\"'`\\ \\\n");
            printf("        ' .'    `-._`.`.    `.       ,'     ,' _.'      . `\n");
            printf("  ____.'  |         `\"  `\"---+------'-----\" `\"'         |  `.____\n");
            printf(",'_,.-`._,'                                             '.--...._`\n");
            printf("`\".--..__'                                               `._.---`\"`   \n");

            break;

        case 99:
            printf("                                 _,.._\n");
            printf("                            _,-'\"     `.\n");
            printf("                       _,.-'            `._\n");
            printf("                     .'                    `-._\n");
            printf("                    .       /                  `-.\n");
            printf("                    |      /                      |\n");
            printf("                    |   _,'                       |\n");
            printf("  ,'\"\"'\"`-._        |`\"\"                          |\n");
            printf(" /          `-.     |       _,....._              |\n");
            printf("/...._         .    '    ,-'| | |`-.`.            '\n");
            printf("     ``.       '  _  `./\\`\\ | | | | `.`.   _,.---- `.\n");
            printf("  ,.  | .       \\ ``.    ._\\|_| | | / \\ \\._          `.\n");
            printf("  | `.| |        . `.`.  |\\   `-'.|/_,.-\"  `          |\n");
            printf("  \\    `._       |   `.`-' `.              |         ,'\n");
            printf("   \\      `.   ,'     _\\,.'\"\"`.            |        .\\\n");
            printf("    `.     |  /   ||.'./ /.   |`.          |       / |\n");
            printf("      `-._.'_.    |||,' ._...-' .`-.._____.'    _,' .'\n");
            printf("          \\\" |   ,'|'   _ _   ,'   | .-\". `-..-'  ,|\n");
            printf("           . |   \\  `..' \" `-'     '/|   `._`\".    |.\n");
            printf("           | `:\"-'`.                `+.._   `\"|    .'\n");
            printf("           `._|_,\".\"`.   ........_   ,\"  `-._ '.    )|\n");
            printf("                  ' /.`-._        `\"'...-\"_.'`._\\_,' '\n");
            printf("              __.' j  /`..`..__      _.:-'    | |  \\  \\\n");
            printf("            ,__/   |-`.,'      `\"`'\"\"         | |   \\  \\\n");
            printf("               `--\"'-.'                       |  \\   .  `___\n");
            printf("                                              `./\"\"\"-`./\"'__`\n");
            printf("                                                `..--.|`-'  `'   \n");

            break;

        case 100:
            printf("                         __...--------...__\n");
            printf("                    _.--'                  `\"-..\n");
            printf("                _.-'                  ,.        `-._\n");
            printf("             _,'                    .'  \\           `._\n");
            printf("           ,\"                     ,'     .             `.\n");
            printf("         ,'                      /        `.             `.\n");
            printf("        /                       .           \\              `.\n");
            printf("      ,'                         `.._        .               .\n");
            printf("     /                               `-._    /`               \\\n");
            printf("    /                                    `-._  \\               \\\n");
            printf("   /    __,........----...__                 `\"-'               \\\n");
            printf("  /.--\"\"                    `'--.._                 ...........\n");
            printf(" j                                 `\"-._            `. /      |  `\n");
            printf(" '                                      `._           `.      .   .\n");
            printf(".                                          `._          `.    '   |\n");
            printf("|                                             `.          \\  /    |\n");
            printf("|                                               `.         `'     |\n");
            printf("|                                                 `.              |\n");
            printf("|                                                   `.            |\n");
            printf("'                                                     `.          |\n");
            printf(" .                                                      .         |\n");
            printf("                                                         \\        '\n");
            printf("  '                                                       \\      '\n");
            printf("   .                                                       \\    /\n");
            printf("    \\       ____                                            .  /\n");
            printf("     \\    .\"    `\"\"-._                                       '/\n");
            printf("      `   '           `-.                                   ,'\n");
            printf("       `.  `.            `.                               ,'\n");
            printf("         `.  .             `.                           .'\n");
            printf("           `._`-.            \\                        .'\n");
            printf("              `._`._          '                    _,'\n");
            printf("                 `._`\"-._     |                 _.\"\n");
            printf("                     \"-.._`--'           __,.-\"'\n");
            printf("                          `\"\"----------\"'   \n");

            break;

        case 101:
            printf("\n");
            printf("                         _,.--\"'\"\"\"''\"\"\"''--..__\n");
            printf("                    _.-\"'                       `-._\n");
            printf("                 _.'                                `-._\n");
            printf("              _,'                     ._                `.\n");
            printf("            ,'                          `._               `.\n");
            printf("          .'                               `._              `.\n");
            printf("         /                                    `.              \\\n");
            printf("       ,'                             .         `.    |        `.\n");
            printf("      /                               |           `.  |   |      .\n");
            printf("     /                                |             \\ |   |       \\\n");
            printf("    /                                                `    | ,.-\"'  \\\n");
            printf("   /                                                                \\\n");
            printf("  j                                                        |         .\n");
            printf("  |                  __...--'\"''\"\"'\"'\"\"\"'`--..__           |         '\n");
            printf(" j             _.--\"'                           `-.._                 .\n");
            printf(" |         _,-'                      .\"\"'`--..__     `\"-._            |\n");
            printf(" |     _.-'                          |          `\"-._     `._         |\n");
            printf(" |  _.'                              |               `-._    `._      |\n");
            printf(" |,'                                 |    |              `-._   `.    |\n");
            printf(" |                                   |    |                  `-.  `._ |\n");
            printf(" |                                   '    |     |               `.   `'\n");
            printf(" |                                    `\"--'.....+................'   j\n");
            printf(" '                                                                   |\n");
            printf("  .                                                                  '\n");
            printf("   .                                                                /\n");
            printf("    `                                                              /\n");
            printf("     '                                                           ,'\n");
            printf("      `.                                                        .\n");
            printf("        .                                                      /\n");
            printf("         `.                                                  ,'\n");
            printf("           `.                                              .'\n");
            printf("             `._                                        _.'\n");
            printf("                `._                                 _.-'\n");
            printf("                   `-._                         _,-\"\n");
            printf("                       `\"--..__           __..-'\n");
            printf("                               `\"\"\"''\"'\"\"\"   \n");

            break;

        case 102:
            printf("                       __.__._\n");
            printf("                     .\"   ) `.`\".\n");
            printf("                    /     `.../  \\\n");
            printf("                   |   _.'   \\    .\n");
            printf("                   |  '       `.  |\n");
            printf("                   '            `.'\n");
            printf("                    \\          _,..---..._\n");
            printf("         _,.._       `._     ,'           |.\n");
            printf("      ,\"\\  `. `\".       `\"\".'             | `.\n");
            printf("     /   \\ _|_  _\\       .'               |   `.\n");
            printf("   ,'     `...' `.\\    ,'                 |     \\         _......_\n");
            printf("  .        ,' ___. .  /                  j    _,'\\      .'   |    `.\n");
            printf("  |       .        | /                   |.--\"    \\    /     |      /.\n");
            printf("  |       |        |.                    |            /      |     /  \\\n");
            printf("  '       |        '                     '         ' j       |`  .'    .\n");
            printf("   `.  ,`.|       /|     `.                         .|`-._   .--,      |\n");
            printf("     `/   |    _.' |      |`._             _,       || `--` '--'       '\n");
            printf("       `\"-+---\"    |      `   `-._     _.-'  |      | .   ----        /\n");
            printf("      _.......__   |       `.....'   -.______'      |  \\            ,'\n");
            printf("    ,'         `\"--|_            ____               '   `-._    __.'\n");
            printf("   /                 |.         -....-\"            /        `\"\"\"\n");
            printf("  /         '   -._  | `.                         /\n");
            printf(" /         / \\     `.|   \\                      .'\n");
            printf(".         / .'       '._  \\                   ,'\n");
            printf("|        /.\"            '--._                .__..._\n");
            printf("'  .....,               |  | `-.._     __..-\"\"      `\".\n");
            printf(" . |  .'  _.-           |  |      `'\"\"'.\"              `.\n");
            printf(" `. `\" .-'              |  '          /                  \\\n");
            printf("   .                    ' .          /                    .\n");
            printf("    `.                .' /          |                     |\n");
            printf("      `.              |.'           |                     |\n");
            printf("        `-._       _,-'             `.     '-.        _,- '\n");
            printf("            \"'---\"'                   \\     `..`.  ....' /\n");
            printf("                                       \\                /\n");
            printf("                                        `._   --==-. _,'\n");
            printf("                                           `---...--'   \n");

            break;

        case 103:
            printf("\n");
            printf("                              .'\n");
            printf("                              | \\\n");
            printf("                              |  .\n");
            printf("              '._             |   .\n");
            printf("              `. `._          |   |        .             __...\n");
            printf("                `.  `.        |   '      .'        _,.-\"'_.'\n");
            printf("                  .   `.      |    .    / '    _,-'   _,'\n");
            printf("                   `.   `.    |        / /  _,\"    _,\"\n");
            printf("           `+.._     `    `.  '     . / / .\"     ,\"\n");
            printf("              `._`-._ `.    `. .    |/ /,'     .'\n");
            printf("    _,..---\"\"\"\"--`.  `-.`.    \\|    | ./     ,'  _,.---,________\n");
            printf(" -`=..__                `-.    |    |.'    .'_..+---\"\"\"         `\"-..\n");
            printf("        `\"\"---..___        `.  |    |'   .'-\"          ___,.....---\"\"`'\n");
            printf("               _,.-\"\"__,.._  `   ___'  .'  ____..---\"\"'\n");
            printf("         _,.-\"\"    .'  ,.  \\ .-\"'   `-.  \"\"-------...__\n");
            printf("      .-\"    __.-.'   '-\"'  / -='   `\"'\\......__       `\"-..._\n");
            printf("    .\" _,.--\"\"  / .\"\"\"|    /            \\  _  ..`.-.....______`_\n");
            printf("   '.-' .'_.-\"\".  | _.|   .   `.-----\"'  .'\"  __  `             '\n");
            printf("       -\"'     '  |'  |   |              | '\"\"     .\n");
            printf("                \\  ...'   |              '         |`-.\n");
            printf("                 `._      ,.            /          '\"--'\n");
            printf("                    `\"\"\".'  `._     _,\"`.       _,'\n");
            printf("                       /.....__`\"\"\"'     \\--..-\"\n");
            printf("                      /        `'\"\"'----...\n");
            printf("                .    /____                |\n");
            printf("               | |  j----.`\"\"---..__      |\n");
            printf("         '`-.,-`.'--|`-.  `.        `'\"--.|\n");
            printf("          `./   ___ `.  .  |              '\n");
            printf("           ' ,\"'   `. . |  |             /\n");
            printf("           . |      | | | .'          .'j\n");
            printf("            \\`.     | '-'`..._____..-'  |\n");
            printf("             `.`.__.'/     ,'`._       ,'\n");
            printf("               `\"--`'     . \\   `-.__ /\n");
            printf("                          |  `...___.'\n");
            printf("                          /\"`__.._'\".\n");
            printf("                          `\"'     `\"   \n");

            break;

        case 104:
            printf("                                             ..\n");
            printf("                                           .'  |\n");
            printf("                                           |   '\n");
            printf("                                           '    \\\n");
            printf("                                          /      `-._\n");
            printf("                                  _...--\"'           `\"-._\n");
            printf("                                ,'                        `-.______\n");
            printf("                               j                                   |\n");
            printf("                               |                                  ,'\n");
            printf("                               |           _                    ,'\n");
            printf("                              /          ,':\"\"\"\"\"-.           .'\n");
            printf("                             .___..  __,'\"       `.`.         |\n");
            printf("                               |       ||        `.\\ .        |\n");
            printf("                             ,'|      _||  `-._   | ||        |\n");
            printf("                  .\"`-------'  `-..,-\" ||...._()`-  '|        '\n");
            printf("                  `.               \\.-\"       `.__,','       /\n");
            printf("                    \\            .\"            |_.-'        .\n");
            printf("                     /                    _...-'            |\n");
            printf("                    /                   .'.                 |\n");
            printf("                  ,'                  .'   |        __      '\n");
            printf("                 ,                  ,'     |      .'  `      `.\n");
            printf("                /                  '       |___   |   /    .--'\n");
            printf("               .        ____                 | `. `..'   ,'\n");
            printf("               |            `\"-.             |   \\     .'\n");
            printf("            _,\"j'               `.           |    `--+\"-._\n");
            printf("          ,\"  /                   \\          |       |    `.\n");
            printf("       _,'   .                     .         |       '.     `.  _,.\n");
            printf("     ,\"      |                     |         '      /  |    ,\"._  '\n");
            printf("  _,'        |_,...._              |       ,'      /__.'  ,'    `/\n");
            printf(",'           |   _.' `\".          .     _,'\"--.._,'     .'      /\n");
            printf("`._          `--'       \\        /_,.-\"'  __,.-'       '      ,'\n");
            printf("   `\"'\"\"------`.        .\"`----\"\"     _.-\"..__________      ,'\n");
            printf("                `._     |          ,-'                `\"--'\"\n");
            printf("                   `-..-`._       /\n");
            printf("                           `.   ,'\n");
            printf("                             `\"'   \n");

            break;

        case 105:
            printf("      ,.                           __     ,\"`.\n");
            printf("     / |                      _.-\"'  `\"--'   |\n");
            printf("    /  |              .\"--..,'               |\n");
            printf("   j   |              `                      |\n");
            printf("   '    `-.            `.                    |\n");
            printf("  .       .'            '                    |\n");
            printf("  |    ,-\"               .                   '\n");
            printf("  |     \\                |                    ,\"\"`.\n");
            printf("  |      \\               |                   ||    `\n");
            printf("  |       \\             j     `-.           .||     `.\n");
            printf("  |        \\            |       |`.         |||      |\n");
            printf("  |         \\         __|       |  |`.      |'|\\   .'\n");
            printf("  |          `.  _.-\"'   `-.._  `._'  `.    | | `-\"\n");
            printf("  |          _,+\"             `.   `\"\"--\\     |\n");
            printf("  '        .'                   `.            |\n");
            printf("  '      ,'                      |`.       .  '\n");
            printf("   \\   .'                        `. `.     , /\n");
            printf("    \\,'             _,.-+\"\"'.      `  `.   .'\n");
            printf("    /            .-'     `-. '      `.  `\"'\n");
            printf("  ,'           ,'\\          `.`.      `\n");
            printf(" '            /.  `.         ,\\ \\      `._\n");
            printf(".            /  \\   `._    .'  \\ .        `\".\n");
            printf("|           /._  `-._  `,-'    ,' `.         \\\n");
            printf("|          /   `\"-+---\"'      |    |         ,-.._\n");
            printf("|..____,.-'       |`.         '   ,'         |    `\"-._        __\n");
            printf("`---'\"            |  \\         `.'  `-.._   ,|      `._`\"-._.\"'  `.\n");
            printf("                  |`._`.        |        `.  `-._      \"-          .\n");
            printf("                   `.,' `.___..'           `\"    `._                |\n");
            printf("                                                    `.              |\n");
            printf("                                                      `._         .'\n");
            printf("                                                         `        |\n");
            printf("                                                          .       |\n");
            printf("                                                           \\      |\n");
            printf("                                                            `..,.'   \n");

            break;

        case 106:
            printf("                                                   __           ,-\"\".\n");
            printf("                                                 .'  `.       ,'     .\n");
            printf("                                            _____|     \\    ,'       |\n");
            printf("                                      _,-'\"\"     |      `..'     _,-'\n");
            printf("                                    ,\"           `.            ,'\n");
            printf("                                   /       /|   ,\"'`,        ,'\n");
            printf("               _,..__             /      ,'.|  .  .',`.     `.\n");
            printf("            .\"'      `'--\"\"-._  .'     .' ,'/  |  | |' |      `.\n");
            printf("        __.'             `.   `.       |`'.'      ` '.`|        `\n");
            printf("   .-\"\"'   |               `\"-.' ,\"`.  '-'         `---'.        \\\n");
            printf("  `-.      '             ____   '.`\"\"/               .'  `\"-.     .\n");
            printf("     `-.__/            ,'    `\".  `./._              |       '    |\n");
            printf("       _,.            j        |   |  |`\"-._         '      .     '\n");
            printf(" _,.-\"'   \\           |        |   |  |   | `+-.\"\"-.  .     |    .\n");
            printf("'._       |           |        |   '  |   '  |  |.    |     `..-'\n");
            printf("   `\"-....'           `.      ,'  '  ,'  ,   |  ' .   '\n");
            printf("         .._            `-...'  ,'--+---+--.'_.'  |  .\n");
            printf("       .'   `                _.'      `.     `-..'  /\n");
            printf("     ,'     _\\         __..-\",'         `     \\    /\n");
            printf("     \"'`\"'\"'  `\"----'\"\"/.-+\"             `     `  /\n");
            printf("                    ,-'---|               \\      .\n");
            printf("                   /      |                `.__..'\n");
            printf("                 .'    .' `.                \\    /.\n");
            printf("               ,'  ,..\" ..  `.               \\-\"'  \\\n");
            printf("               '._'  |  | `-.'                \\  _,`.\n");
            printf("                     |  '                      \\'   /.\n");
            printf("                     `.  )                      . ,'  '+-._\n");
            printf("                       `'                        `. .' ||.\"`.\n");
            printf("                                                   `._,'||   |\n");
            printf("                                                    |._,' `-.|\n");
            printf("                                                    `.       |\n");
            printf("                                                     '       |\n");
            printf("                                                      .__ _ .|\n");
            printf("                                                       | | | |\n");
            printf("                                                       '.`.'.'   \n");

            break;

        case 107:
            printf("                                            __\n");
            printf("                                          ,'  `\".\n");
            printf("                                    _    /      '\n");
            printf("                                .-\"' | ,'      /\n");
            printf("                             ,.j     |/       /   _,\".\n");
            printf("                           ,' ||     |       j _,\"    `.\n");
            printf("                          |   ||             '\"      .'\n");
            printf("                          |    |                   ,\"\n");
            printf("                          |                      .' _..-.\n");
            printf("           _______        |   \\                  `'\"     \\\n");
            printf("      _,-\"'       `-._    |  | \\                      _.\"\n");
            printf("    .'                `.  |  | b`       _..+-      _,'  ___......\n");
            printf("   ,                    \\ `. `-     -'\"d   |   _,.---'\"\"         |\n");
            printf(" ,.                      \\  `.----.._  ---'_.-'                  |\n");
            printf("| |                       ',-\"`._    `-.,-'                    .'\n");
            printf("`.|                       |      `\"---.'  _..,.-\"\"\"\".      _.-'\n");
            printf("  `.                      |\\        ,'. .\"    |    __...-\"'\n");
            printf("    `.                   ,'/`\"-.__,'  ,'    __|.-'\"    /\n");
            printf("      `-._            _,\\.'         `.  _,-\"\\`-._____,'._\n");
            printf("          `\"-...----'\"   \\---...____.'\"\"_.'  `-..,'   `  `-.\n");
            printf("                          `\"'\"`\\   `._.'     .' /      '    \\\n");
            printf("                                `._,'      ,'  /       |     \\\n");
            printf("                                    `\"-.  .   /        |      \\\n");
            printf("                                  ,'   ,'\"'`-+...-'\"\"'/__..--\"'\n");
            printf("                              _,.'   .'        |     /\n");
            printf("                            ,\"     ,'          |    .\n");
            printf("                          ,'      .            |    '.__\n");
            printf("                        .'      .'             `.       `.\n");
            printf("                     _.'|    _,'                 `.       `.\n");
            printf("                   .\"   `-..'7                     `.       `.\n");
            printf("                 .'         /                        \\        \\\n");
            printf("                 |        .'                          \\        ,\".\n");
            printf("                 `--....-\"                          ..-`'\"\"`--'   \\\n");
            printf("                                                   /              '\n");
            printf("                                                   `._      _...-'\n");
            printf("                                                      `\"--\"'   \n");

            break;

        case 108:
            printf("             _____                       ,\".\n");
            printf("        _.-\"'     ``.                  .'   `\n");
            printf("      ,'             .               ,'      |\n");
            printf("    .'               |            _,'        |\n");
            printf("  ,'                 '          ,'           |\n");
            printf(" ,               / ,'         .'             '---.._\n");
            printf(" '              /.'         ,'              /       `-.\n");
            printf(".              ,\"          /               '           `.\n");
            printf("|      |      .           .                              \\\n");
            printf("|      |      |           |                               \\\n");
            printf("|      |      |           |                                .\n");
            printf("|      |      |           `\n");
            printf("'      |      |            `.             _,.._             .\n");
            printf(" \\     |      '    __...._   `.__     _,-'     \"-.          |\n");
            printf("  \\    '      ' ,\"'       ``./   `'\"\"'            `.        |\n");
            printf("   \\    .      '.       ___  `.                     \\       '\n");
            printf("    \\    \\      \\       ,..`                         \\     /\n");
            printf("     `.   \\      \\     ( \" )          ,......--'\"\"`.  \\   /\n");
            printf("       .   \\      \\     `\"'                   ,\".   |  `.'\n");
            printf("    ,..|`.  \\      `.                         `\"'   |    \\\n");
            printf("   |    . `.-`\"''\"\"\"`--._                        _.'      \\\n");
            printf("   ,\".   `.|             `-..    /`. .._      _,\"          \\\n");
            printf("   `\"'._   '                   ,'  | |  `\"+\"\"' ,-'\"\"''-.    .\n");
            printf("        `\"--`._             _.\"    | |   |    .  ,...   .   |\n");
            printf("              |`+..____,..-'       ' |   |    | .    |  |   |\n");
            printf("              |/  ,..\\           ,'  '   |    | `.__,'  |  ,'\n");
            printf("              '  |   |`.___   _.'   /    `.   `._     _.' ,-.\n");
            printf("               \\ `--'   /._'\"\"   _,'     .'`._   `\"--\"  .'   `.\n");
            printf("                `-..,.-'   `---\"'     _,'_,.--`\".___,.-'      |\n");
            printf("                   /-----\"'   ,`\"\"''\"\"           |   _....._ .'\n");
            printf("                  ,-'\"\"--._,-'                   '.\"'      .\"\n");
            printf("                   -..---'                         `\"-----'   \n");

            break;

        case 109:
            printf("                               ,----.\n");
            printf("                              '      |\n");
            printf("                             /       '\n");
            printf("                       __,..'         \"-._        _\n");
            printf("                  _.-\"\"                   `-.   ,\" `\".\n");
            printf("         ,-._  _.'                           `\"'      '\n");
            printf("       ,'    `\"                                       |\n");
            printf("      .                                               .\n");
            printf("       `.          _.--..               ____          '\n");
            printf("       /         ,'    . `           ,\"' .  `.         `.\n");
            printf("      /         .         |         /         \\          \\\n");
            printf("     /          `------...'        ._____      .          \\\n");
            printf("    .                                    `'\"\"\"'            \\\n");
            printf("    '                    ________                           .\n");
            printf("   j           `.\"\"/'\"\"\"`        '\"\"\"'\"'--....,-            |\n");
            printf("   |             `/.                      ,\\ /              `.\n");
            printf("   |                `-._               _.'  '                 `-.\n");
            printf("   |                    `\"-----------\"'                         |\n");
            printf(" .\"                         ____                                |\n");
            printf("|                      ,-\"\"'    `\".                            ,'\n");
            printf("|                     .   .----.   `.                        .\"\n");
            printf("`.._                  |  '.____,'   |                        '\n");
            printf("    |             ,\". `.           ,' _                     /\n");
            printf("    '            '   `._`.'._\".__,' .' .                   /\n");
            printf("     .            `'-._ `._     _.-'  _.'                 /\n");
            printf("      `.               `.  `--'\" _,.-'                    `\n");
            printf("        .               ,'     .\"                          '\n");
            printf("         '        .-..-' _,.--._`\"-..,-.                 ,'\n");
            printf("        /         \\    ,'       `-.    |           .-'\"-\"\n");
            printf("        \\          `-.'            `..'         _,'\n");
            printf("         `.,.-\"`._                           ,-'\n");
            printf("                  `\"-.                       |\n");
            printf("                      \\       ,..----.     _.'\n");
            printf("                       `\"\"---\"        `..-\"   \n");

            break;

        case 110:
            printf("                  __....____,'  `-.\n");
            printf("         ,\"\"-..-'\"          \"-    |       ..      _.._\n");
            printf("         |        _, .,           '._    /  `'\"\"\"'    |\n");
            printf("        .'         _____             `.,'     ____     `.\n");
            printf("     _,\" _.'      \\  |  '\"--..        '       \\__ `\"-.   `.\n");
            printf("    | ,'\"|/        `-.______,'      `     ' |\\_  `'\"\"'  .  \\\n");
            printf("    .'---'      _____             . '   `   |,'\"\"\"-._  ' \\  .\n");
            printf("   /   __..--\"\"|___/ \"-.._/|         ,'       ___    `. \\ \\ '_\n");
            printf("  . .'...-----'\"\"----.._.' |-.      |        | ,.`\".   \\ `'   |\n");
            printf("  | `\"                  \"-.'-'      `.        \\`._`.\\   |.  .-'\n");
            printf(".\"        _..._                 .              `._  ,   `.' |\n");
            printf(" `.    ,\"'_....`\".               |                \"\"       .\n");
            printf("  |    | |     | |             -'   `,                    /\n");
            printf("  `,.  `._`---'_,'  ,-.    '        ' `-.             _   |\n");
            printf("  ,\\ `._  |___|  _,'  |  `    \\        . /-.__     _.' `-\"\n");
            printf("  \\ `.._`-._ _.-'_,.--'        |        `.    |  ,'\n");
            printf("   `-\"\\ `-. ' ,'_         `-..'       .-'    /  /\n");
            printf("       `._.---._ `\"----.        .   ,'.   _.'  /\n");
            printf("         `.     `'-.._/       -\" ,-\" `.`-'      `.\n");
            printf("           `.,       .-\"    _    |     | .     ) |\n");
            printf("             '._  ,\"`----\"\"`.    |     ' `'       .\n");
            printf("                \"\"           `--'       \\`      ,\"'\n");
            printf("                                         `-._,-'   \n");
            printf("\n");
            printf("\n");
            printf("\n");
            printf("\n");
            printf("\n");
            printf("\n");
            printf("\n");
            printf("\n");

            break;

        case 111:
            printf("\n");
            printf("                                        '\"-.\n");
            printf("                                       //   .\n");
            printf("                            .,.       '/    `\n");
            printf("                           |   \\     /.      \\        ,.\n");
            printf("                           |    `.  / '       \\     ,' |\n");
            printf("                          .|      `\"-'         \\  ,'   |\n");
            printf("                          ||                    \\'     '\n");
            printf("                   ,--.   ||             _,.     `\"-.   `.\n");
            printf("                __.  ,.`.j '    _.-'\"\"','  |__ ..    |    `.\n");
            printf("               .  |  |/  `.   ,'    .'     ' .'  `. ,_...   \\\n");
            printf("               '  '        \\-+.._,.'      .,'      `    .'   .\n");
            printf("              .  /      '  |     .-'      /           ./     |\n");
            printf("             /  /     .'   |             .'         ,'_|,..   .\n");
            printf("            /  '     /     '             |        _.-\"   .'   |\n");
            printf("           /  '    .' _.'   `.        __ |    _,-'      /      .\n");
            printf("          / ,'    / .'        `.    ,'. ||_,-'         /       |\n");
            printf("         /,'     /.'           `._,',\"  '|           ,'        '\n");
            printf("       ,+'      .'            .'\".'    / '          .           .\n");
            printf("      |         '           .','      |,`.         j            |\n");
            printf(".\"\"'--+--     .'           | /        '   .        |            |\n");
            printf(" \\          ,_|             \\'         `._|        |            '\n");
            printf("  `._     .'    ______      .+---.        `--..    |             .\n");
            printf("     `. ,'   _.\" |    `-. ,'      `.          |    |             |\n");
            printf("      |    .' /\\ |    ,' /         |        ,'     '.            |\n");
            printf("       `--'  /,'\"    /  /          |      ,'        /            |\n");
            printf("            /.     .' .'           |    ,:    ___  /             |\n");
            printf("           . |    /  /.  ,---.    j    /. `..'   \"           ,-. |\n");
            printf("           | |  .'  / |.'     `.  |   / ,\"-..__,...--._     /   \\|\n");
            printf("           |`-\"' _.' .'|      . .' `-'.'        /     |`..-'     |\n");
            printf("           `..-\"'--\"/  |    .'| |    '_.-. _.--'     .'.    /\\   |\n");
            printf("                    ..-'----' |,          '          |.`._ . | _,'\n");
            printf("                             `                       '    `| ,'\n");
            printf("                                                            \"   \n");

            break;

        case 112:
            printf("            ,\".\n");
            printf("            |--\\\n");
            printf("            | .'\\   |.\n");
            printf("            |'  _\\  |' ,.\n");
            printf("            |,.._ \\_| `.|    .-\"|\n");
            printf("          .'      .--   `. ,',\" '\n");
            printf("         '_..._   ..|`    \\ '  /\n");
            printf("         `     `.       .  /  /\n");
            printf("          .     ``.     ,' `./\n");
            printf("          |      `|`.   `-._ `\"\"\".\n");
            printf("          '       |.'`.     '   '\n");
            printf("           \\           \\  .'     `__,..\n");
            printf("            `.                ,.-'    '\n");
            printf("        _..-' `.     _.'   \"-.|      /\n");
            printf("    _.-'    |  ,`\"'\"\"   _       `.  .-..\n");
            printf("  ,\"   |    | .       .'  `     | `.  /  _,..\n");
            printf(" |     '    ' |      /     |    |   `.`'\"   '                _,..__\n");
            printf(".'.     `.__..| |\\  /      '    |     \\    /             _,'\\    _.'\n");
            printf("|,'     ,' _..|.-'\".            |      \\  .            .'.   \\,-'\n");
            printf(" \\\",  .'  ,`-.      `.          |       \\ `\".       _,'   \\ .'\n");
            printf("  `\"\"'    ` ._\\      |   _,.'   '        \\ /___,.--\"`.    .'\n");
            printf("          .`         |,-\"     .+       _  V    `.     \\  /\n");
            printf("           `-._    _,' `\"-...' ,\\ .\"    `.|      .     \\'\n");
            printf("              ,`.            .'  /        `.     |    /\n");
            printf("            ,'   \\\"--.....-\"'   .        .  \\    |  ,'\n");
            printf("           .    .\"\\           _,|        |   .   |.'\n");
            printf("           |  ,'   `-.____..-\"  |        '   |_..'\n");
            printf("           | |       /`._      _|         \\  |\n");
            printf("          ,. .       \\   `-.-'\"  .         \\ |\n");
            printf("        .' |,-`     _/       `'\"\"-`.        `.\n");
            printf("       -'\".'  \\_,-\"\"                |.     .. |\n");
            printf("         ''\"'\"\"                     ' |  ,'  \\|\n");
            printf("                                   | .'..|    |\n");
            printf("                                   '\"     `...   \n");

            break;

        case 113:
            printf("\n");
            printf("                    _,.-''\"\"\"`-._\n");
            printf("                  ,\"             `._\n");
            printf("                ,'   ..     .       `.\n");
            printf("              .'     ||     ||        `._\n");
            printf("   ,.....---'\"                         `._`-..._\n");
            printf("   `._  _,.-\"/        `\"--'         `  `. `._   `\"'-.\n");
            printf("  __..-'   ,' /                      \\   `.  `-.__.-'\n");
            printf("`._    __,'  ,                        `.   `.    \"--.\n");
            printf("   `\"'.'   .'       _,.+..              `.   `.-...-'\n");
            printf("    ,'  _,'     _.-\"   A  `-._            `._  `-.\n");
            printf("    `\"+'       '     ,' `     `-             \"''-'\n");
            printf("      '            ,' ___`.                   |\n");
            printf("     .            ' .`   `.`.                 |  _,.\n");
            printf("     |            ,'       `                  |,\" ,'\n");
            printf("     |           /          \\                 |  /\n");
            printf("     |          j            '                | /\n");
            printf("     '          |'`\"\"''\"`'\"\"\"|                |/\n");
            printf("      .         `            '               ,'\n");
            printf("       `.        \\          /              ,'\n");
            printf("         `._      `._     ,'             .'\n");
            printf("            `._      `\"\"\"'             .'\n");
            printf("          _,'  `-.....___________...-'`-.\n");
            printf("         `...---'               `--.....-'   \n");

            break;

        case 114:
            printf("                      _____         ____\n");
            printf("                   ,\"'     `.   ,-\"'    `\".     ,.\n");
            printf("                  .  ,---.   |,'   _...    .    | `.\n");
            printf("             _.---'`'\"-._ |  /   .'.---`.  '    '  |\n");
            printf("           ,'            `| /...-._____ |  |`\".'   |\n");
            printf("          /    _,---+-.   ,'       `-. ||  '   `..-.._\n");
            printf("         .   ,`._    `.`,'.   _...    \\` .  `.   `.   `-.\n");
            printf("         |_,.-...`---\"'|  ,`.|  .\"`    \\`.`.  `.   \\     \\\n");
            printf(" ,      ,'             |  |  |  |  \\    \\ `.`._ `.  \\`.   .\n");
            printf("| \\    '     __......-\"|  |  |  |`._\\    '. `\"-`. .  . \\,\"'-._\n");
            printf("|  `\"'|   .\"'   ___    |  |  '  `-...\\...|_`.._ | |..:-'      `.\n");
            printf(" `-..-|  .    .\"  _`+.,'  |   `._          `-.,'  |     ,+\"|`. |\n");
            printf(" ,'  ,|  |  ,' ,\"'     __,'      `'\"\"\"\"'`-.   .  ,'...-' | | | |\n");
            printf(".   / `  |  | .   ,-'\"'             ____   `. |-'-.| |   ',' `'\n");
            printf("|  |   \\ |  | | .'   ,-'\"\"'-.    ,'\"    `.  | |.   | |__     ,.\n");
            printf("'  `.   `|  ' | |  .'        \\  .         | | `.`. '  . `\"-.' |\n");
            printf(" \\ |\\`-..|   .`.|  |    ()    | |   ()    ' `._ ,.' \\  `---' ,\n");
            printf("  `| `--\"    | |   '          ' '        .    .' |   |.____,' \\\n");
            printf("   `.       ,' '    `.     _,'   `. ___.'_..,'   |   |  | `.   .\n");
            printf("     `-...-' .' _...  `---\" _....._  _.'\"    `..'|   |  |  |   |\n");
            printf("    ,'    _.\" ,'    |    .-' ___   `'   _..    `/|   |`.|  |   '\n");
            printf("   '    ,'/  /   _,.'  ,' .-'   `\".  \\,'   `.   | .  `  .  '  /\n");
            printf("  .   ,` ' .'   '    |/  /   ____/ \\  . ,-\"'|   '-.`.__,',' ,'\n");
            printf("  |   | |  ||  |`-..\"/  /`.'\"   /   . |'  _,'  /.  `. .\"' .'`..__,.\n");
            printf("  `   `.|_..'  `._  /  /   `._ /   /| | ,'/   /  \\   \\  ,\"._    _,'\n");
            printf("  ,`.        \\    `-._/ `.    `-.,' | |. /  ,'   /.   \\'  __`--\"\n");
            printf("  |  |-..,.\"| `-._    `.  `,      \",  '-j  .   ,',`.   `\"'  '\n");
            printf("  |  |   `. `-../ `-.   `.' `\"+-..' .'  |  |_,'.\"| |`.   _,'\n");
            printf("  '   `-._ `._.'   / `.  | _,'  |\"'|`-..|  |   | | |  `\"\"\n");
            printf("   `._    `\"'   _.|__.-| |\" `---|  '.   |  '.,'  `.'\n");
            printf("      `-.....-\"'  |___,  '       `. \\`+-`.   `.\n");
            printf("             .'   '  /  /          \"'/    `\"--'-._\n");
            printf("           _,:  ,'   `-\".           .             `._\n");
            printf("        ,-'   `\"         |          |                `.\n");
            printf("      ,'                 |          '                  `.\n");
            printf("     /                 _,'           `._                |\n");
            printf("    |               _,\"                 `-..__        _,'\n");
            printf("    `.        __..-'                          `\"\"\"`\"''\n");
            printf("      `-----\"'   \n");

            break;

        case 115:
            printf("                               |`.\n");
            printf("                               |  \\\n");
            printf("                          __   |   `.\n");
            printf("                        _|  \\  |     .\n");
            printf("                      .' \\`-.. `     | _____\n");
            printf("                      ,`-`  `.| \\   ,\"'     `-.     ______\n");
            printf("                     |        |  \\.'           `.,\"'      `\",'\n");
            printf("                     `.     __| ,'|             |        _.'\n");
            printf("                      '    .  :/  |             |......-'\n");
            printf("                     j      `./  .'\\            | |\n");
            printf("                    ||      ,/   ' \"'         ,'  |\n");
            printf("                    ||     . `.   `.|       .'|   |\n");
            printf("                    '+     `.  `.   '     ,|__'   '\n");
            printf("                     `    .'    \\`.  `\"-.'      .'_\n");
            printf("                      \\   `   ,  `.`.    _..-|     `---....-\"-._\n");
            printf("                       \\ . `.' _..---`.._..-\"|   |              `,\n");
            printf("                        /    .'          `.  |  ,` ._           /|\n");
            printf("                      .'    /              \\ `-|     |        ,'|'\n");
            printf("                     '/    /                .  '    .' ,-----'\"\"'\n");
            printf("                _ ,.-'    /       _.._      |   \\.-'--'\n");
            printf("              .\"         /   ,..\"'`\\/ `     |   |\n");
            printf("             /|         j  _,`/    _| \"`.   |   |\\\n");
            printf("            j `-.       |,' `.    |.|    .  |   .|\n");
            printf("            |    |    . |     `._.`-|`.  |  |    '\n");
            printf("            |    |  _ ` |       `..'\"`\"\"' \\ '     `.\n");
            printf("         _.-'\"\"\"\"' | `\"\\`                  .       |.\n");
            printf("      ,-'|   .\"`.  `.   \\`.                '      j  .\n");
            printf("    _'_..'   |   :-.--.' `.`._           ,'       |  |\n");
            printf("  .'          `+'_  `.|      _`.._____,-' ,\"`.    `._/\n");
            printf(" /         _____  `-.__..--\"\"         `-.'    \\     |\n");
            printf(".    _,.-\"'     ``\"\"'                    `-..-\"  ___/\\\n");
            printf("'.,-'                                      .',-.'   |'\n");
            printf("                                           ,'   `.  |\n");
            printf("                                                  `\"   \n");

            break;

        case 116:
            printf("                          _,..----.._\n");
            printf(" ,\"''-.               _.-'           `\"-._\n");
            printf(".,-.   `._          ,'    ,---.           `.             _,..\n");
            printf("||  \\     `._     ,'    .' |   .            `.     _,.-\"' _,'\n");
            printf("||   .       `-._.      |.'|   |            _...-\"'    _,'\n");
            printf("''   |           '      |  '   |         --'       _,-'\n");
            printf(" \\\\  |                  '.'    |                 ,'\n");
            printf("  .`.'                   `.    '                (\n");
            printf("   `.____                  `--'                  `--..__\n");
            printf("         ``\"-.._                                        ``--..__\n");
            printf("                |\"                                              ``.\n");
            printf("                `                             .--\"''\"\"\"'`--------'\n");
            printf("                 `.                           \\\n");
            printf("     ,-\"'`-._      `-._                 `._    `.\n");
            printf("    /        `.     ,._`-.._          _,'  `-.   .\n");
            printf("   .    _      `.   |  `\"-._`     .-\"'        `-. `.\n");
            printf("   |     `\"-._   `. |--.._  `._   \\              `. .\n");
            printf("   |          `-._ `|     `-._ `-. `.              `'\n");
            printf("   `        ._    `/'         `-. `. .\n");
            printf("    \\         `\"-.'  .-....__    `. `.`.\n");
            printf("     .          /    '       `\"-.._   | \\\n");
            printf("      `.       /------\\            `  |  \\\n");
            printf("        `.___./        `              '   .\n");
            printf("             ,          `._        ,-'    |\n");
            printf("             |.-\"''\"\"'--.._`\"---'\"/       |\n");
            printf("             |  ______      `\"-../        |\n");
            printf("             .\"'      `\".       /         '\n");
            printf("           ,'            .     /         .\n");
            printf("          .              |   .'         /\n");
            printf("          |       ,'     |.-'          /\n");
            printf("          |       |      '            '\n");
            printf("           .       `-..-\"          _,'\n");
            printf("            `.                  _,\"\n");
            printf("              `._          __.-'\n");
            printf("                 `'------\"'   \n");

            break;

        case 117:
            printf("                                .                ,'\n");
            printf("                               /|               /,\n");
            printf("                              'j               / |\n");
            printf("                             / |              / j\n");
            printf("                            .  |             /  |\n");
            printf("             .              |  |      _     /  j                _,..\n");
            printf("   ,         |\\            j   |   _,\",'   /   |           _.-\"',-'\n");
            printf("   '`        | `.      ,.  |   | ,'  '    /   j        _.-', _.'\n");
            printf("    \\`.      |   `...-\" '  |   \"'  ,'    /    |    _.-' _.','\n");
            printf("     \\ \\     |           \\ |      /     /     L_.-'  _,' .'\n");
            printf("      \\ `. ,\"`            v      `.__  /           ,' _.'\n");
            printf("       \\  \\   .           |        .' /         _,' ,'\n");
            printf("        \\  `  '           '      ,'  /        ,'  ,'\n");
            printf("      .--`.    \\   .     .     .'---/      ,-'   (\n");
            printf("       `.  \\| | .  |    |`.  .'    /    _,'       `-..__\n");
            printf("         `. | ' '  |    ' |  |        ,'                `\"---...__\n");
            printf("          .'`. ` \\ '   ..'|  |    `,              __________......\"\n");
            printf("          `\"--`.`.\\ ` `---' ,    -.    -'\"'\"\"`''\"\"\n");
            printf("                |\"\"`      .'     /  .._.'  .  `\"`.\n");
            printf("       __..--'\"\" `.       |`__|\\.     |  __`     |\n");
            printf(" _,.-\"'            \\      | |     .  .'    |  --.'\\\n");
            printf("`-----\"`'\"\"''+.  _,'|     |/|      `-'  .  |    |  \\\n");
            printf("           .' _,\"   |     ' `..'_......._`\"  .  '   .\n");
            printf("         .'_,\"   _. |    _.'  ,'         `.   `'    |\n");
            printf("        /.\"  _.-'  '`.--\"   .'             \\  /     |\n");
            printf("      .''_.-'     .  /     /        __      .'      |\n");
            printf("    ,'_.'         ' /     .       ,\"  `.    |       |\n");
            printf("   .-'           / /      |       |    '    |       '\n");
            printf("                . /       '       '         '      /\n");
            printf("                ,'         \\       .       /      /\n");
            printf("                            \\       `-...-'     .'\n");
            printf("                             `.              _,'\n");
            printf("                               `._        _,\"\n");
            printf("                                  `\"----\"'   \n");

            break;

        case 118:
            printf("                                            _.--.\n");
            printf("                                      __  ,'     \\\n");
            printf("                                    ,'  `\"        .\n");
            printf("                                   |              |\n");
            printf("                        ,'`.      ,'              |\n");
            printf("                  .._  /    \\   .'                |\n");
            printf("                 /   `'      `. |     .          .'\n");
            printf("                .   |   _...__ |'    .           |\n");
            printf("                |   |.\"'      `|     '           .\n");
            printf("                |  ,'           \\   /            `.\n");
            printf("         '`.   .| .              \\ j               |\n");
            printf("          \\ `./ | |               .|              ,\n");
            printf("           \\  . `.|                .            .'\n");
            printf("            \\  `.                  '           _|_\n");
            printf("             \\   `.                 .        .'__ `\n");
            printf("            / .   |                 |        |\"  | `-...._\n");
            printf("           .      |       ,.--.     |     _.'    |        `.\n");
            printf(" .-._      |   `  |      /     \\    |.--'\"       '         |\n");
            printf(" |   `'\"\"'\"|    `       .     .'|                 \\        |\n");
            printf(" |        ||            |    /| |                  \\       |\n");
            printf(" '        ||            |  ,d | '                  |       |\n");
            printf(".         :`             .'\"-' /  /`.            _,'`.      `.\n");
            printf("|          \\.             `..-'  / \\ \\       .\"\"'     `.      |\n");
            printf("'._         '                   /   \\ `.    /           `    .'\n");
            printf("   `-.     .'`. .._____        /     \\  \\   |                |\n");
            printf("    _|     |   \\  ___  '    _,'       .  `  .`-._            '\n");
            printf("  ,' |     |    `. \"\" / __,\"           `-..'     `.           `.\n");
            printf("  |  `-----'     |\"''\"'\"                          '            |\n");
            printf("  '              |                                 .           '\n");
            printf("   \\          _.'                                  |          |\n");
            printf("   |     ,-\"''                                      ._   _..  `.\n");
            printf("   |    /                                             `\"'   `.  '\n");
            printf("   `...'                                                      `\"   \n");

            break;

        case 119:
            printf("                     ,-'\"\"\"--..__  .'\\\n");
            printf("                    .            `\"   \\\n");
            printf("                    '                  \\\n");
            printf("      _____          .                  .\n");
            printf("  ,\"\"'     `'--.._    \\                 '\n");
            printf(" /                `._  \\  \\    +.     :' .\n");
            printf(".                    `._`. `.            |\n");
            printf("|                       `-`  .      _ .  |\n");
            printf("|                      '-._`._\\  \\ ' ||  |\n");
            printf("`.                         `. `.  . \\||  '\n");
            printf("  `.                 .  ...  `._`.|  '` .\n");
            printf("    `._              `   `.:    `.`.   '|\n");
            printf("       `.                     '`  `.\\  ||  _,...._\n");
            printf("         `                   -.     ``.'|,\"       `-._\n");
            printf("          |                \" ._`-._ . -._`._ |  .     `--..  ...\n");
            printf("          |           ,....    `-.-'    .'  `.  ;       ,'  /   \\\n");
            printf("          |           `\"\"'   \"' /     .\"_     `.      .'   .     '\n");
            printf("          |       _       _,.-'/  .      \"\"-.   .   ,'.   j      .\n");
            printf("          |       +'    ,\"    /     +\"    _,.'  |  /.  \\  | . |  |\n");
            printf("          '           ,'     j  .'     ._ ...   | /  `. \\ |   '  |\n");
            printf("         ,.`----...._'`.    /|           _..-'  |/  ,-.  \\|  '   |\n");
            printf("         \".      __  `-.`. / |     +' _.\"  __....._  `.`._| / ,  '\n");
            printf("           `.   `\"-'      `-.|      .'_,-'\"        _.-\"'/ |/ '  /\n");
            printf("             \\         `\"-.._`-.   ,-'         ,-\"'   .`. |,' .'\n");
            printf("              |          `   `-.`./ _.._      |     ,'__ \\| ,'\n");
            printf("              |       __  +' -- .'.'.--.`.     \\  .','..`.+'\n");
            printf("              .      `--' .\"_,.\"  |||  | |      `\" | |  ||\n");
            printf("              `.         _.\"  /\\  || \"\" ||         || \"\"'|\n");
            printf("                `-...,-\"' ,' /  \\ `.`..'/          ' `..'\n");
            printf("                   '        /    `. `--'            `.,'\n");
            printf("                    \\      /       `=+=  ,--------. .'\n");
            printf("                     `.___,           `.| `.____.','\n");
            printf("                                         `-.....-'   \n");

            break;

        case 120:
            printf("                                ..\n");
            printf("                               .  .\n");
            printf("                                  '\n");
            printf("                              ' \\/ '\n");
            printf("                             /  .  `\n");
            printf("                            .   |   .\n");
            printf("                            '   |\n");
            printf("                                |    '\n");
            printf("                           '    |\n");
            printf("..__                      /     |     .\n");
            printf("'   \"-..__               .      |\n");
            printf(" `.       `\"--..____..          |      '                  __..--.\n");
            printf("   ..            |   |..'       |       ..\"-. ____,..---\"'      /\n");
            printf("    .`.          |   ' \\        |      .'/   /              .','\n");
            printf("     `.`.        `    \\ `. _,..-'._   , /   .            _.','\n");
            printf("       `.`.       \\       \"        `\"' /    '          ,' ,'\n");
            printf("         . `.      .   '              /    /        _,' .'\n");
            printf("          `. `.     .   \\            /   .'       .\"  .'\n");
            printf("            `. `.  /`    \\          /   , \\     .' _,'\n");
            printf("              `  `/  \\    \\        /   /   \\  ,' ,'\n");
            printf("             ,\"`./    \\  ,-'\"\"'\"-./   /     \\_.-'\n");
            printf("             |._ `.    ,',-\"\"'\"\"`-.` '    _,' `.\n");
            printf("             |  `-._  . /          \\`._.-' _.-\"|\n");
            printf("              `._   `-|.            .|..-\"'    |\n");
            printf("              /  \\\"._ ||            ||     _,-\".\n");
            printf("             .    \\  `.|            ||..-''/   |\n");
            printf("             '     .   `           .'    ,'    '\n");
            printf("            .       .  .`._      .'`.  .'       .\n");
            printf("                   .|,'   /\"----\"\\   `._|.      '\n");
            printf("           '     ,' `. _,\"-.    ,\"'._  .' `.\n");
            printf("          /    .'  _.'\"     `..'     `\"-.   \\    .\n");
            printf("         .   ,' _,'                      `.  `.  `\n");
            printf("         | .'_,'                           `'. `. .\n");
            printf("         `\"\"'                                 `. `|\n");
            printf("                                                `\"   \n");

            break;

        case 121:
            printf("             .\"-.._          ____\n");
            printf("             \\     `-._     /  /\"\"\"-.\n");
            printf("              .    `\"-.`-_.'`.j      \\\n");
            printf("     _________'  .,---'\"\",|   |...___.'\n");
            printf("   .'          \\ `-.._ ,' |  ,      || \\ ____\n");
            printf("    `.    __,.-+--'\"_.'  ,^./       ||  |____`\"\"---..__\n");
            printf("   _,.`\"\"\"__....--.'   .\"  `..___   ||_.'  `.\"\"'\"\"`--- '.\n");
            printf("  /_.--\"'\"       /   ,'      |   |\"\"'\\  \\    `.       .'\n");
            printf(" .'             '  .' ___    |   |`\"--\\  \\ ____`.   ,'\n");
            printf("  `.             \\,.-'   `.  |  j      \\  \\`.`.   ,'\n");
            printf("    `-.                 /  \\ |  |       \\  \\ `.`.' `._\n");
            printf("       `._             /   |j  j  ..--.  \\  \\  `.`.   `-._\n");
            printf("          `._        ,'    ||  | /  \\  `. '  .   `.`.     `.\n");
            printf("             >.     /      |'. |'    \\   `._,'     `.`.     `.\n");
            printf("           .\"  `.  /       |   |      \\               .` _..\"\n");
            printf("         ,\"    ,'`.         |\".'       \\               `.`.\n");
            printf("       ,'   _,'   |         | |         \\                `.`.\n");
            printf("     ,'  _,'      '        j j           \\                 \\ .\n");
            printf("   ,'  ,\"          .       | |          _.\\....___          \\'\n");
            printf("  '  .'            '       | '         /`   |     `\"\"`---..__|\n");
            printf(".'_.'               .     j .         '  `.  .\n");
            printf("|\"                  '     | |       ,'     \\  \\\n");
            printf(" ''\"''\"\"\"\"''---------.    | |      /        `  \\\n");
            printf("                     '   .' |    .'          \\  \\\n");
            printf("                      .  | .    ,'.           `. .\n");
            printf("                      ' j  |   /   `-.          . \\\n");
            printf("                       .|  | ,'       `-.        . \\\n");
            printf("                       `|  |.            `._      \\ \\\n");
            printf("                        `\"-'                \"._    ` .\n");
            printf("                                               `._  \\|\n");
            printf("                                                  `-.|   \n");
            printf("\n");
            printf("\n");

            break;

        case 122:
            printf("               ,---.    ___\n");
            printf("               |(__)| .',-.`.\n");
            printf("               `.  j  | \\.'.'\n");
            printf("               _'  `\"'  ,-'___\n");
            printf("             ,\"         `\"',--.\\                     _..--.\n");
            printf("             |           __`..''                _,.-'      `-.\n");
            printf("   ,-\"\"'`-.. '          (  `\"\"'         _...--\"'        ,.--..'\n");
            printf(" ,'        .' `._____  ,.`-..--\"\"\"'----.               /\n");
            printf("/   _..._,'   .\"     \\ `..'|            `.        ___.'\n");
            printf("'.-\"  .'    ,'        '---\"               `.     /\n");
            printf("     |    .'.._     ,'                      `.  /\n");
            printf("      \\   `    `._ /      |  !    !  |        |\"\n");
            printf("       `.  `.     |   __  |          j  ,--. _|..._\n");
            printf("         \\   `.\"\"\"\"-.'  `. '           /  ,'\"      `-.\n");
            printf("          `.   `.    `.  |   _____|   |  /            `.\n");
            printf("          |`....'     |_,'   `.   '    `.              |\n");
            printf("          |           |---....____....-\"`        .--.  '\n");
            printf("           .         ,'                  `..._  (    `'\n");
            printf("            `--..,.-'      _.--\"\"\"'\"'.   |,\"\".`. ,--.. \\\n");
            printf("                 |       ,'       .\"\"\"`. ``-\" | |(__)|  `.\n");
            printf("                 |      .         |(__) `-'   '\"   ,\"     |\n");
            printf("                / `     |          `--.          .'_,..-\"'\n");
            printf("               /   `._   ._       .\"\"\"`-         ||\n");
            printf("               '..._  `._  `-....( (__) __    _.','\n");
            printf("              ,'    `.   `---.....`..-\"'  `\"'\"_,\".\n");
            printf("         ,-\"\"`. _.---+..-'            `\"---+-'   `\n");
            printf("        /      `.                       .\" , \\    \\\n");
            printf("        ._    ,--.                     |  |  |.    \\\n");
            printf("         _:--'    `.                   |  `._| `..-|\n");
            printf("     ,-'\"  `.    .' |                  '    `\"--...'-.\n");
            printf("    .        `\"\"'_.-'                   `.           |\n");
            printf("    |         ,-'                         `-.______,.'\n");
            printf("    '.     _.'\n");
            printf("      `---'   \n");

            break;

        case 123:
            printf("           ______\n");
            printf("       _.-\"______`._             ,.\n");
            printf("     ,\"_,\"'      `-.`._         /.|\n");
            printf("   ,',\"   ____      `-.`.___   // |\n");
            printf("  /.' ,-\"'    `-._     `.   | j.  |  /|\n");
            printf(" // .'   __...._  `\"--.. `. ' |   | ' '\n");
            printf("j/  _.-\"'       `._,.\"\".   |  |   |/ '\n");
            printf("|.-'                    `.'/| |   | /\n");
            printf("'                        '/ | |   |/\n");
            printf("                         /  ' '   '\n");
            printf("                   |.   ` .'/.   /\n");
            printf("                   | `. ,','.  ,'\n");
            printf("                   |   \\.' j.-'/\n");
            printf("                   '   '   '. /\n");
            printf("                  |          `\"-...__\n");
            printf("                  |             _..-'\n");
            printf("                 ,|'      __.-7'   _......____\n");
            printf("                . |    ,\"/   ,'`.'__........___`-...__\n");
            printf("                 .    '-'_..' .-\"\"-._         `\"\"'-----`---...___\n");
            printf("                 |____.-','\" /      /`.._,\"\".                 _.-'\n");
            printf("              ,\"`| ,'   '   |      .,--. ;--|             _,-\"\n");
            printf("             |   '.| `-.|   `.     ||   /   '`---.....--\"'.\n");
            printf("             '     `._  |     `+----`._;'.   `-..____..--'\"\n");
            printf("              `.    | \"'|__...-|,|       /     `.\n");
            printf("                |-..|`-.7    /   '      /   |  '|\n");
            printf("                ' |' `.||`--'    |      \\   | . |\n");
            printf("                        |        |       \\  ' | |\n");
            printf("                        `.      .'        .   ' '\n");
            printf("                          `'-+-\"|`.       '  ' /\n");
            printf("                             |`-'  \\     /  /.'\n");
            printf("                             `   _ ,.   / ,'/\n");
            printf("                              ||'.'`.  / /,'\n");
            printf("                               `      ' .'\n");
            printf("                                     /.'   \n");

            break;

        case 124:
            printf("                _   _,.-.' .-.\n");
            printf("            _ .' |,'   .\"\".| |.\"\"._\n");
            printf("           ( || ,',\"\". `._`' `  '  `.\n");
            printf("           `\\ | `\" .-\"`-..`     .    `.\n");
            printf("            |     `..--.._       |     \\\n");
            printf("          _,|      _...'_.'     ,+.     `.\n");
            printf("     ,\"\"'|   `...-'..\"\"(__.._ -\"   `\"--.. `.\n");
            printf("    |`._,'  ,'  /\\ .'\"\"` .'\"\"`. `.    |  `. \\\n");
            printf("    '      / / /  ||    ||    |.`.`.   .   | \\\n");
            printf("     `.__,'-._'  /|` -\"'  `-.'  \\ \\ \\   `\"-'  \\\n");
            printf("      ' `.   /  /_| | |'\"\"| | .-\"\"'`'\"`-,.-\"\\  .\n");
            printf("     . / .\\ .  /  | | `._.' ||        ,'     \\  \\\n");
            printf("    ' / / |/  /_.-+._`-..--\"-.       .   .    \\  `\n");
            printf("   / /.'  '  ,'\"\"'-. `\".\"'\"\"'`..     |.        \\  \\\n");
            printf("  / . |  j  .       . |        |\\__,\" |.  `    '   \\\n");
            printf(" .  | |  |  |       ' |        '|   | ' `  \\    \\   .\n");
            printf(" |    |  |  `.____,'   ..____,' |   |    .       \\\n");
            printf(" |    |  |  | ._  _..---._   _,'    |       .        '\n");
            printf(" |    |  |  | | \"\"  .    |`\"'   \\ `.|     '  '  '     .\n");
            printf(" |    |  |  | |     |    |       `  `      .  .  \\    |\n");
            printf(" |    |  |  | |     '    |        \\  `.    |  |   .   |\n");
            printf(" '    '  |  | |      .   `         \\   \\   |  |   |   |\n");
            printf("  \\      `  | |      |              .   `. |  |   |   |\n");
            printf("   \\      \\ ' |      `    '          `    `+..|___|___|_........\n");
            printf("    \\      \\ \\|       '    .           `.    `.                 |\n");
            printf("     `.     \\ .        .   `             `.    `-.            .'\n");
            printf("    _,'`.    \\'         .   \\              `-.._  `._       ,'\n");
            printf(" _.\"     `._ `.`        |    .                       `._   .\n");
            printf("`._       _,`\"--`.      |     .                         `. |\n");
            printf("   `-._ ,'              |      `.                         `|_\n");
            printf("      ,'         |      |        `.                          `.\n");
            printf("    .'   __...__.|      |          \\ __..._     _,..,.__       `.\n");
            printf("    `-`\"'        `._..--'-.__      .'      `-..'        ``'\"--..-'\n");
            printf("                             `\"---'   \n");

            break;

        case 125:
            printf("              '\n");
            printf("             .\n");
            printf("             | '\n");
            printf("             | |\n");
            printf("          .  ` '                              .\n");
            printf("          '`. . .          .--.              , .\n");
            printf("       ..  `.`| `....___  '   |            ,_' |\n");
            printf("      |  |   .    _,   .`-`,-\"          ,.'    '-.\n");
            printf("      `..`._,'` .'.   '  ,'            /    .....|\n");
            printf("          `.'  ','      '  `-._      ,'     `----'\n");
            printf("          ,'| '/               `.  ,'   \\ .-\"\".   \\\n");
            printf("        |' |`'/ .|               `.     .'  _,'_.\"'\n");
            printf("       /   `.' /_|  __       _...-'   .' |.' .\"    \\\n");
            printf("     ,' `-.   '\" .-\"V `-.  ,'       ,'   |    `-'\"\"'\n");
            printf("    ,--.'. `.   /      / ,' ,      /`.   |          |\n");
            printf("  .'---'  `./\"\"|'.    / /  /      '   `-.|          |\n");
            printf(" /         /   `-....','  /              `.|    | . |\n");
            printf(".|       .'       .'.'   /      _,        .'   .  | '\n");
            printf("||       |        |/    /    _,'  7    _,\" `---'--\"'        _.._\n");
            printf("|`  .   /         |    . _.-\"    /   ,\"     |             ,'    `.\n");
            printf("`.`-', /          |   '.' ,.    /  ,'     ,-'.          .'       |\n");
            printf("  `.              |   _.-' |   '  /    _,'   |         .\"\"`.   _,'\n");
            printf("                  '.-'     '  /  /   ,\"      |        ,\"'.  |.\"\n");
            printf("                   `      .  /  /  ,'        .       /    |,'\n");
            printf("                 ,\".`.      .  '_.'        _.-`.    ,\"-.  /\n");
            printf("               .'`._`.`. '  ' ,'          `_.'\"\".  /\".  |'\n");
            printf("               |.`._`\" .`-.'           .     ___|.'   |'\n");
            printf("           ,--'  `-.' `|   `\"--..__..-\"' | .\" __|   ,'\n");
            printf("         ,' )       _,'            `'\"._.'  \"'   `-'\n");
            printf("        '\",' )__.-'\"                    `.          |.\n");
            printf("          '\"\"                             `-.  .    | |\n");
            printf("                                             `| `.-'`-.\n");
            printf("                                               `.'\n");
            printf("                                                 '   \n");

            break;

        case 126:
            printf("\n");
            printf("                                                 ,--''''-.\n");
            printf("                                               ..    `'  `\n");
            printf("                                                '    .'...'\n");
            printf("                                            '  ,'::     |\n");
            printf("                                               ,..-Y-'  /--\n");
            printf("                                    .              |' _.'\n");
            printf("                                  .' .______ ,-'\"|  ,'\n");
            printf("                           /,  ,. '-'     .-' .\" | '\n");
            printf("                          /  \"'  ' -=L;'\\'    `-.'.\n");
            printf("             ,,          /__       ],L_/'        .'            |\\\n");
            printf("       |`.  '\\  _,          |         .        ,'          =-. `|\n");
            printf("       `. ,' |.`            '`-v      `'-.    |             | -,..\n");
            printf("        _:  \" `\\,.     ___    _'|  ,-,_-  `-..'          .]---> _`'\n");
            printf("      . ___.   ' /'--.  -.=[----`, |   '-  ,'                | </\n");
            printf("             ]..b--`. -'- , ----`` |'--v -'            __-- ' ,,\n");
            printf("            .'|    <\\]``,[ -    '\\\\._  |'  '''`- _  _,|    `''|\n");
            printf("   \\\" ''L     |   X`.  ` /--,    |  -`.:_ `.    ' TX_,.:'..  ,|\n");
            printf("   `   |       \"` =. ----  _|    |      ` _ `\\ |=:| /   '-\\ --'\n");
            printf("   |.   `.          '''-..L    _,'      .' `,.``-() Y.-[ .'\n");
            printf("   '    .            _. _.. -]-,..-,'    v.   \\|  ` '`'\n");
            printf("`.'       `.        ' ---.'- /-[  .',_   -.   ,)L\n");
            printf("  |       .'      __,...-`=..__       '   '     '.\n");
            printf("   ,\"', .'      -`... _-'      `.     ` ,'      | `.\n");
            printf("       .`            .'          .     '        |   \\\n");
            printf("         '           |           |             .'    .\n");
            printf("        \\ `.         '           '            ,'     |\n");
            printf("         \\  `.        `         /           .'     _.'\n");
            printf("          '.  `-.     /`__    ,'.._______,-'--...-` `.\n");
            printf("            `.   `--..'J  \"'.'         ,'       `._\\` ``-...\n");
            printf("              `.   .'   `'|'        _,'          |    _    \"-.\n");
            printf("                `.'|  ..  |     _,-'             `-._| '.---.'\n");
            printf("                / _,_/  |-`---\"'                     `-..|\n");
            printf("               `-\"   | .'\n");
            printf("                     -'\n");

            break;

        case 127:
            printf("                        _.-\".\n");
            printf("                ..-\"\"`.'    '..__,\n");
            printf("                `-. .'     /  ,.`.\n");
            printf("                  ,'      '`. .'  `.\n");
            printf("                 /       .-'        `....\n");
            printf("              ..'.      .\\             .|\n");
            printf("              .`./      | `.            '.\n");
            printf("              |         |  .\\       /|    \\\n");
            printf("             .'         |)  `\\       '   (_`\n");
            printf("            ,|          |    `.            |\n");
            printf("             |          |  _,.-.           |\n");
            printf("             |          |,'     \\          |\n");
            printf("             |          |        \\         |\n");
            printf("             |      \\,  '.        \\        |\n");
            printf("             '           |         `._     |\n");
            printf("              \\          |            `-..,+___\n");
            printf("               \\         |          /       |  `.\n");
            printf("                \\        '         / ,      '    \\\n");
            printf("                 \\      ,  _      /.'      /|    `-.\n");
            printf("                  `.   .    `-.    __     ' |     .'\n");
            printf("                    `..'   -\"'  .-\"| |  ,'  |    |  '-..\n");
            printf("                    /`.        (_`.`\" \\'    |_.-'-\"'-. .`.\n");
            printf("                   .   \\       `._. `\".|    |         `|  .\n");
            printf("                   |    \\`----\"\"`.`. / |,.-\"'`-.        `. '\n");
            printf("                   |     \\        `-+-\"   /     \\         \\ \\\n");
            printf("                  ,'     _\\ ___..-'      .       \\         \\ \\\n");
            printf("                  j\"._,-\".'`.       _.-\"'|     _  \\         . \\\n");
            printf("                 / ,'   /    `.._,-'    _| _.-'   `.        |  \\\n");
            printf("               .' '    ._      `-..__.-\"_|'        |        `..\"`.\n");
            printf("   _..      _,'\"-/     | `-._   .'   `\"' `.      __|        /|  | \\_\n");
            printf(" .'   `--\"\"' _.-'    .-|     `.'          '._  .`  `.      / |  |.'|\n");
            printf(".  \\ .\"\\ _,-'        `.'..-.-'           /   `.-._   .     `.|./__.'\n");
            printf("|`.` | /\"               |.'             / _.'     `-.|\n");
            printf("`_|.'`'                                `-'   \n");
            printf("\n");

            break;

        case 128:
            printf("                                                           .'`.'\n");
            printf("                                                          `     '\n");
            printf("                                             ,-'.`.        `    ``\n");
            printf("            '\"--.                          /'      \\        |    |\n");
            printf("             \\   `                         '.      `.      ',    '\n");
            printf("              .   |                          `- _,.\"-._-._   `. /\n");
            printf("              '   |,`.----.                            \"-.`.  |'\n");
            printf(" ,\".        .'    '       '---.                            \\\\ ||\n");
            printf(" | :     ,-'|    .             '                            ..||\n");
            printf(" |  `._.',||`._.'|              \\.                          ||||\n");
            printf(" `.   / ._| `-...'\\              \\`._                       |. '\n");
            printf("  _,-'             . `--.         \\  `.                     '.'\n");
            printf(".\" .'             _|     `-`\".     .   `.                 .'.\n");
            printf(" '-....'          |           `-. _.'    `._           _.','\n");
            printf("  `.             .'                .-       `.       .'_,'\n");
            printf("    `..__....._ `.               ,'           `-._ .',\"\n");
            printf("          /    `.|               '                `.'....__\n");
            printf("         .                   _:.]                   `\"''-._`.\n");
            printf("         '                 :\"    '                   `.    `. .\n");
            printf("          \\                |                                 `.`.\n");
            printf("           .               |                           .       ` .\n");
            printf("           |               '         |                          ` .\n");
            printf("           '.             .          |                  '        .|\n");
            printf("             |`.          |          |                  |        ||\n");
            printf("             |  `.        '          '                  |       . '\n");
            printf("             |    \"--.     |        /_                  |     -'   |\n");
            printf("             |        `.   |       /  `'\"\"`-._          |    ,'    |\n");
            printf("             '        ,\"'..|      .      '    `.        |    |.    |\n");
            printf("              .     ,'     '.     |\\    .       `       |      | ,/\n");
            printf("              |    /        |     | .   |        `.     |      `'\n");
            printf("              |   .         |    ,' |  .           \\    |\n");
            printf("              |   |         |    .  | .'            .__ '\n");
            printf("              '-..|         |___.   '\"              |../\n");
            printf("             /.-'           \\ .'\n");
            printf("                             '   \n");

            break;

        case 129:
            printf("\n");
            printf("\n");
            printf("                                 __.--.._,-'\"\"-.\n");
            printf("                              ,-' .' ,'  .-\"''-.`.       .--.\n");
            printf("                            ,'    |  |  '`-.    \\ \\       `-.|\n");
            printf("                           /       .   /    `.   \\ \\        ||\n");
            printf("                          /         `..`.    `.   \\ .       ||\n");
            printf("                         /        . .    `.    \\   . .      '.\n");
            printf("                .\"-.    .  ,\"\"'-. | |      \\    \\   `.`.__,'.'\n");
            printf("                 `. `. .   |     `. |       \\    .    `-..-'\n");
            printf("       _______     .  `|   |   '   .'        .   |...--._\n");
            printf("       `.     `\"--.'   '    .      | .        .  |\"\"''\"-._\"-._\n");
            printf("         `.             \\    `-._..'. .       |  |---.._  `-.__\"-..\n");
            printf("    -.     `.           |\\           `.`      |  |'`-.  `-._   +\"-'\n");
            printf("    `.`.     `-.        | `            .`.       | `. `.    `,\"\n");
            printf("      `.`.      `.      |  '.           ` `      `.  \\  `   /\n");
            printf("      | `.`.    __`.    |`/  `.     ...  `.`.     |   `.   .\n");
            printf("      |   \\ .  `._      | `. / `. .'.' |   \\ \\    |     \\  |\n");
            printf("      |.   ` \\    `-.   |   \\   .'.'/' |    \\ \\   |      ._'\n");
            printf("      | `.  `.\\      `. |    \\ / , '.  |_    . \\  '-.\n");
            printf("     ,     .  .\\       `|     . ' / |  | `-...\\ \\'   `._\n");
            printf("     `.     `.  \\       |.    '/ .  |  |       ' .      `-.\n");
            printf("      .`._    \\` \\      | `. /'  '  |  |       | |       ,.'\n");
            printf("       .  `-.  \\`.\\    ,|   //  '   |  |__  .' | |      |\n");
            printf("       |     `._`| `--' `  //  .    |  '  `\"  /| |   . -'\n");
            printf("       '        `|       `//   '    |   .    / | |   |\n");
            printf("      /....._____|       //   .  ___|   |   /  | |  ,|\n");
            printf("     .         _.'      /, _.--\"'-._ `\".| ,'   | |.'\n");
            printf("     |      _,' / ___   `-'.        `. _|'     |,\n");
            printf("     |  _,-\"  ,'.'   `-.._  `.      _,'         `\n");
            printf("     '-\"   _,','          \"- ....--'\n");
            printf("    /  _.-\"_.'\n");
            printf("   /_,'_,-'\n");
            printf(" .'_.-'\n");
            printf(" '\"\n");

            break;

        case 130:
            printf("\n");
            printf("                            /|\n");
            printf("                /`     |   / |\n");
            printf("               . |     |`.'  |  ,          .\n");
            printf("               | |     |     `\"'/       _,'           ,\"'\n");
            printf("               | |     |       /      .\" ,'         ,'/_\n");
            printf("               | |   ,\"| .-\"\"\"''`,`.,'  /      /|  /  ' )\n");
            printf("     .'.       | |\"\"+._|'   .    '     ,__    / ) /   .'\n");
            printf("      `.`.   .'| |     '_,\".`     \\     .'   '   '   /  _\n");
            printf("        `.`./ j  |  _,-'_,'.       `-..'    .        `-'/\n");
            printf("         _\\' `   |,\" _.' `. `.     _..|     |         ,'\n");
            printf(" .    .\"'  \\._____.-' '    `-|  .-'  ,|    _|   ___  /\n");
            printf("  \\`._ `-. `|.___,'| /     _.'      / |  ,\" |.-'   `.'.\n");
            printf("   \\-.`\"-'  _______`'    ,' __.---.' ,^.' _.'_    __ `.`.\n");
            printf("   |    `-.,...... `.   |,-\"     / .'. |-'    `-.\"  | |` \\\n");
            printf("   '      ||\\/  |/`.|  .`       (,'   `|         `.'  '.| \\\n");
            printf("   `-..--.||       || j      ____\\     |       _  |  /     `.---------.\n");
            printf("      |   ||  ___..|||,.--\"\"'|.      .\"|     ,' | |\"/ `. ,'. .   ,.--\"\n");
            printf("      |  .||.'      ||.._    ' )  _,'\\ |`'-.'   | |/    ||.' |   `.\n");
            printf("      |,',|||      . |\"-.`._  `+`\"    \"      `.'  ^,.__,'.   |  ,--'\n");
            printf("       // |||      |j  |\\\\  \"'  `.     |   ,-` `./ '     |   |`.\\\n");
            printf("      .'  |||      ||  | .'      |   .\"`..|_ |  .   \\    |  /|\n");
            printf("      ||  ||`.___.'f   ' ||     ,'--\"`._|,-.`|  '    +.._|,'.|\n");
            printf("      ||  |`-.....'|    .'`.\"\"'`.       /\\ | `.'     |    |  |\n");
            printf(" .'`  ''   `--....-'    | \\|   ``\\     '  \\|   |     |`._,'-\"'\n");
            printf(" |`..''                 |  '    )|.   /`..|'   '     |   \\  /\n");
            printf("  `\"\"'                  |   `-..''|  /    |   /    _..\"`.` /\n");
            printf("                        `         |,'     |  /  ,\"'_,|     \\\n");
            printf("                         `,_   _.-'.      |,' .'-'\"  '    , \\\n");
            printf("                          `.\"\"'     `.   .' .'      /   ,' | .\n");
            printf("                            `._       \\,'  .       /   /   | |\n");
            printf("                               `\"----\"'     \\  _  /  ,'    | |\n");
            printf("                                             `\" 7._,`      | |\n");
            printf("                                                    \\      | '\n");
            printf("                                                     `-. ,.|/\n");
            printf("                                                        '  |\n");

            break;

        case 131:
            printf("                                       ,|\n");
            printf("                                       ||\n");
            printf("                               ,-\"'\"\"`' `._\n");
            printf("                              '----.     __`....._\n");
            printf("                               `    `.  `. ;      `.\n");
            printf("                                `.    `.  `   ,\"`. |\n");
            printf("                                  `.  _.`._   |  ' |\n");
            printf("                                  .','  ,' `.  `--'\n");
            printf("                                 /.' _,'    | /\n");
            printf("                                '/_.'       |.\n");
            printf("                                 `---`\".    ||\n");
            printf("                                       |    ||\n");
            printf("                                      ,'    `|\n");
            printf("                         _           /       |\n");
            printf("                        ' `.        .'       |\n");
            printf("                         .  `._  _,'/|       |\n");
            printf("                        _|     \"'  / |       '\n");
            printf("                    _,-' |        /  '        .\n");
            printf("                 |\"'            ,'  '          \\\n");
            printf("                 |   _        ,'   /            \\\n");
            printf("                 ;  '        /    j              .\n");
            printf("            ,\"--'    `.    .      |              |         ________\n");
            printf("            `.   -.       / '     |              |   _,-\"\"'   __.._\"`-._\n");
            printf("             ,' ,-.`-.__.' /      '              |.-'  _..--'\"       _.-'\n");
            printf("             \\.'   `-.___.'      ,               '__.-\"           _.'\n");
            printf("             /        _..--    . |              /               ,'\n");
            printf("           ,`      .-'         | |           _,'._          _,-'\n");
            printf("       _,-'      ,'           .' '       _.-'     \"-.....-\"'\n");
            printf("     ,'     __ ,'          _.'  /  __..-'\n");
            printf("   ,' _.-\"\"'  /         _.'  _.'-\"'\n");
            printf("  '-'\"       /      _.-' _.-\"\n");
            printf("            /    _.' _.-'\n");
            printf("           .   .'_.-'\n");
            printf("           | ,'.'\n");
            printf("           | .`\n");
            printf("            `\n");

            break;

        case 132:
            printf("\n");
            printf("                                           ,--._\n");
            printf("                                        _,'     `.\n");
            printf("                              ,.-------\"          `.\n");
            printf("                             /                 \"    `-.__\n");
            printf("                            .         \"        _,        `._\n");
            printf("                            |            __..-\"             `.\n");
            printf("                            |        ''\"'                     `._\n");
            printf("                            |                                    `\"-.\n");
            printf("                            '                                        `.\n");
            printf("                           .                                          |\n");
            printf("                          /                                           |\n");
            printf("                       _,'                                           ,'\n");
            printf("                     ,\"                                             /\n");
            printf("                    .                                              /\n");
            printf("                    |                                             /\n");
            printf("                    |                                            .\n");
            printf("                    '                                            |\n");
            printf("                     `.                                          |\n");
            printf("                       `.                                        |\n");
            printf("                         `.                                      '\n");
            printf("                           .                                      .\n");
            printf("                           |                                       `.\n");
            printf("                           '                                        |\n");
            printf("                         ,'                                         |\n");
            printf("                       ,'                                           '\n");
            printf("                      /                                _...._      /\n");
            printf("                     .                              ,-'      `\"'--'\n");
            printf("      ___            |                            ,'\n");
            printf("   ,-'   `\"-._     _.'                          ,'\n");
            printf("  /           `\"--'             _,....__     _,'\n");
            printf(" '                            .'        `---'\n");
            printf(" `                 ____     ,'\n");
            printf("  .           _.-'\"    `---'\n");
            printf("   `-._    _.\"\n");
            printf("       \"\"\"'\n");

            break;

        case 133:
            printf("\n");
            printf("                                      |\n");
            printf("                                     /|\n");
            printf("                                   ,' |\n");
            printf("                                  .   |\n");
            printf("                                    | |\n");
            printf("                                 ' '| |\n");
            printf("                                / / | |\n");
            printf("       _,.-\"\"--._              / /  | |\n");
            printf("     ,'          `.           j '   ' '\n");
            printf("   ,'              `.         ||   / ,                         ___..--,\n");
            printf("  /                  \\        ' `.'`.-.,-\".  .       _..---\"\"'' __, ,'\n");
            printf(" /                    \\        \\` .\"`      `\"'\\   ,'\"_..--''\"\"\"'.'.'\n");
            printf(".                      .      .'-'             \\,' ,'         ,','\n");
            printf("|                      |      ,`               ' .`         .' /\n");
            printf("|                      |     /          ,\"`.  ' `-. _____.-' .'\n");
            printf("'                      |..---.|,\".      | | .  .-'\"\"   __.,-'\n");
            printf(" .                   ,'       ||,|      |.' |    |\"\"`'\"\n");
            printf("  `-._   `._.._____  |        || |      `._,'    |\n");
            printf("      `.   .       `\".     ,'\"| \"  `'           ,+.\n");
            printf("        \\  '         |    '   |   .....        .'  `.\n");
            printf("         .'          '     7  \".              ,'     \\\n");
            printf("                   ,'      |    `..        _,'      F\n");
            printf("                  .        |,      `'----''         |\n");
            printf("                  |      ,\"j  /                   | '\n");
            printf("                  `     |  | .                 | `,'\n");
            printf("                   .    |  `.|                 |/\n");
            printf("                    `-..'   ,'                .'\n");
            printf("                            | \\             ,''\n");
            printf("                            |  `,'.      _,' /\n");
            printf("                            |    | ^.  .'   /\n");
            printf("                             `-'.' j` V    /\n");
            printf("                                   |      /\n");
            printf("                                   |     /\n");
            printf("                                   |   ,'\n");
            printf("                                    `\"\"\n");

            break;

        case 134:
            printf("                                                                                                    \n");
            printf("                                      ``                                                            \n");
            printf("                                       o`                                                           \n");
            printf("                                       -/                                                           \n");
            printf("                                        /-                                                          \n");
            printf("                                        ./`                            .-:`                         \n");
            printf("                                         ::                        `.-:-/`                          \n");
            printf("                                         .:-                     ..:-. -`                           \n");
            printf("                                        .-::-....--.`         `...-`   :                            \n");
            printf("                                   ``...` `:-    :  `....`  .-..-`     :                            \n");
            printf("                                  :```    ./:-...-.`  `-`---``-.    .-:.                            \n");
            printf("                                `-` ..`...``-:  `....-- .-` ..   .-..-                              \n");
            printf("                             `...    --`..  -:  ..`....-` .-` `--` `-                               \n");
            printf("           `-:://:------.....:.`..` -`.-`.-`    :    `-. -. .-.`   -`                               \n");
            printf("                `.-.````......``.--/.-.    .-. .-  .-oss/``.`  ``.`/                                \n");
            printf("                   ..       ``....``:`.::..  `.-  ::+NMd-. `.--.``:.                                \n");
            printf("                    :.............`---mNd+/o`     hmNds/ :`````` ..                                 \n");
            printf("                    `..-.`  ``````  :`oydmmd:  `  .--.`` :``````:-                                  \n");
            printf("                        `-`  `...`  .: .--.`   ..``      :       :                                  \n");
            printf("                          :-:.``  `..-.      .-...-      /..``  `-                                  \n");
            printf("                          ```:.`......:.      .-  :    `-`  ``  -`                                  \n");
            printf("                             ./.`..`   ...     `.-`  `.:.      `.-                                  \n");
            printf("                             -.        .-......````-.`  `-`   ..`                                   \n");
            printf("                             ``..`    -.     :`````.-     `  ..                                     \n");
            printf("                                 ::` ``     `-      .`    ```:                                      \n");
            printf("                            ````..`/```     ``         `.:.```                                      \n");
            printf("                      ``.....```.`-..``...``  ``.....`..`..                                         \n");
            printf("                   ....`` ```...``        `.-.``     ``   :                                         \n");
            printf("                `..````....``                             :               ```.....```               \n");
            printf("               .- `..``     `````               `.   ``   :            ``..```   `...-.``           \n");
            printf("              :` ..`        `````...`   :       ..  .-   `/````````  `.``             `.-/`         \n");
            printf("             .- .-                 `..  :       -..::-.::::-:::--:---.                `--`          \n");
            printf("            -. .-                    `-`-    ``-/.---```.............:.              .-`            \n");
            printf("            : .-                      `::``-.--.``.-.``.        ```.       ``     `.-.              \n");
            printf("           -. -`       ..````````````.-::::``....`       ``..```   -        `-.```.`                \n");
            printf("           .-`-`         `````..-:--:-   `...`        `.:.`        -          ..                    \n");
            printf("           ``:.-`.`   `    ````-.  ```....`        `.-.`:          :           .-                   \n");
            printf("           `.`--.`.-.......```.``.....          `.:.`  ..          `-           .-                  \n");
            printf("            -  `......``........`             `-/.:    :            `-.          /                  \n");
            printf("            `-        ``                   `--. -`:    :              `--`       -.                 \n");
            printf("             .-                         `::/    `-:    :                 .--`    `:                 \n");
            printf("               --`                  `.---.+:`    ::  ``:.                   .--` `:                 \n");
            printf("                 ..-..`        `.--//-``-:- -` .`:/-.:-:`                      .:/.                 \n");
            printf("                     `..........`     ```    ..-..   \n");

            break;

        case 135:
            printf("XH                             HX               \n");
            printf("H;XHX                         HXH               \n");
            printf("H;;;;XH                      XHXH               \n");
            printf("XXXX;;;H                     HX;H               \n");
            printf(" HXHHX;;H                   HXH;H    XH         \n");
            printf(" HXXHHX;;X                 HXXH;H  HX;H         \n");
            printf(" XXXHHHX;H        X  H     HXHX;HHX;;;X         \n");
            printf("  HXHHHHX;H       HH HH   HXHH;;X;;;;X       XHX\n");
            printf("   HXHHHHX;X XH  XXXHHXH  HHHH;XHX;;;H    XHX;;H\n");
            printf("    HXHHHH;;XHXH HX;XHX;HHXHHX;H;H;;XXXHHX;;;;H \n");
            printf(" HHHXXXHHHX;;HXXXHX;;XHXHXHHH;;;XH;HXXX;;;;;XH  \n");
            printf("  HXXXXXXHHX;;H;XXX;;;HX;HHHXX;XHHHXX;;;;;;XH   \n");
            printf("   XHXXXXHHXX;X;;XXX;;;X;XHHXXH;;;HX;;;;;XXH    \n");
            printf("     HHHXXX;;;;;;;;X;;;;;;XHXH;;;HX;;;;;XXH     \n");
            printf("      HXHXXX;;;;;;;;;;;;;;HXH;;;;HX;;;;XXH      \n");
            printf("       XHHX;XHXX ;;;;;;;XXXH;;;;HX;;;;XX;;XHX   \n");
            printf("       HXXH;;HH X ;;;;;X H;H;;XHHHHHHXX;;;;;;HX \n");
            printf("     XHX;HX;;XHHHX;;;;XHHX;X;;;;;;;  H;;;;;;HX  \n");
            printf("  XHX;;;HXHX;;XHHH;;;;HHX;;;H;;;    H;;;;;HX    \n");
            printf(" XH;;;;;XHXH;;;;;;;XH;;;;;;XH      HXX;;HX      \n");
            printf("   XHX;XHXHXX;H;;;;;;;;;H;XHX    HHXXXXX;;XHHHHX\n");
            printf("      XH;;;HHXXHHHHHHHHH;XH    ;;  HXXXXXXXX;;H \n");
            printf("     H;;;;;;XX;XHHXXXXHH;H      H;; HXX;;;;;;H  \n");
            printf("   XH;;;H;;;;HX;HXXXXXH;X        HHHXX;;;;;;H   \n");
            printf("    HHHX;;;;;;H;;HHHHH;XH   ;;    HXXX;;;;HX    \n");
            printf("      H;; ;;;;;HX;;;;;H     HX;;   HX;;;XHH     \n");
            printf("     H;;   ;;;;;;XHHHX      XHHX;;  H;XH;;H     \n");
            printf("    H;;    ;;;;              HHHHHHHH;H;;;XH    \n");
            printf("   H;;   XHX;;;        X;    XHHHHHXXXX;;;;H    \n");
            printf("  H;;XHHXH;H;;  H;     XX;    HHHHXXXXX;;;;XH   \n");
            printf(" XHHHHHHHXX;;  ; H;     HHX;  XHHHXXXXXX;;;;XX  \n");
            printf("        HXH;   H; H;    HHHX;  HHXHXXXXXXX;;;H  \n");
            printf("        HXH   HXH; H;   XHHHHX; H   XHHXXXX;;;X \n");
            printf("       HXXH  HX  H;HH;   HHXXHHHHX     HHXXX;;H \n");
            printf("       HXX;HHX   XH;;H;  HHXXXXXHH      HXXX;;H \n");
            printf("      HXX;;HH   HXX;;;H; H HXXXXXX       HXX;;X \n");
            printf("     HXXX;;H    HXX;;;XH;H HXXXXXH       HXX;;;X\n");
            printf("    HXXX;;X     HXX;;;XXHH  HXXXXH       HXX;;;H\n");
            printf(" HHHXX;;;XH    HXX;;;XH  X  HXHXXX       HXX;;;H\n");
            printf("HXXX;;;;;H     HXX;;;H      XHHHX        HXX;;;H\n");
            printf("HX;HH;;HH     XXX;;;;H                   HHX;H;H\n");
            printf("HH;H;XHH      HX;;;;XX                   XHX;H;X\n");
            printf("  HHHHX      HXX;;;;H                     XHHHX \n");
            printf("           XHXX;;;;XH                           \n");
            printf("           HXX;;H;;H                            \n");
            printf("           XH;;H;;XH                            \n");
            printf("            XH;H;XH                             \n");
            printf("              XHHX\n");

            break;

        case 136:
            printf("                         /|     '\n");
            printf("                        / `.  ,'|,-.____\n");
            printf("                       /    `'  `       `\"\"----...,\n");
            printf("             .    ,__.'                        .-'._\n");
            printf("            / |   ' .'                   ,_         `'`--.._\n");
            printf("         _.'  . ,'                        `.`-._            `'.\n");
            printf("        |      `                            .  .`-._,\"'--._    `-.\n");
            printf("     ,_.'     `                              `. .`._`.     `-._   '\n");
            printf("      .                                     ..'  `. `.`.       `-. `.\n");
            printf("      |                                       `.   `. `.`.        `. \\\n");
            printf("      |                                       ,',.'\"-\\  \\ `.         `\n");
            printf("    ,-'                                       /     .\"\\  `  \\\n");
            printf("     .                              '`._ ,.  /      |  '  `. \\\n");
            printf(" ..._)                               |  \"  `.        `-'.  |  .\n");
            printf("   \\        '.---.._'._  .\"'-._     .'      |            `.|  '\n");
            printf("    `.         `._ .._ `-'     `.`-.|       '              ` /\n");
            printf("      `.          `-. `. `-.__   '-  `._     \\              |.\n");
            printf("       L_            `._ `.   `\"--..__  `\"-../\\             ||-.,\\\n");
            printf("         `.'            `-.`.         `-._     `-._       .' |`.  \\\n");
            printf("            .           _..`.`.._       ..`      __`\"-..-'   |.'  '-'\n");
            printf("            /___     .\"'     `-._`\"----\"'   `  .( )`.          `.  .\n");
            printf("                -.,./      `\"\"   `\"\"'\"\"'`--.   `._   `.        /    \\\n");
            printf("                   /        ,               `._   `\"\"'  _____.'      '\n");
            printf("                             .                 `._      \"...'       /\n");
            printf("                  .         .'                    `\"\"-----'        ' _\n");
            printf("                  '         `-.                                    .'\n");
            printf("                ,'            /                                   _,\n");
            printf("               /         _..-\"|\"--..                             |\n");
            printf("              /       .\"'     |  .'.,----,                  ,.-'\"|\n");
            printf("             .      ,'        |     \\   `--'.        __...-\"`...-'\n");
            printf("             '     /          '      \\       `-----\"'\n");
            printf("            /     '            .      \\        \\\n");
            printf("           .       .           '._,'_.'`.       \\\n");
            printf("           '._.  ).'                    `        `.\n");
            printf("              `\"'                        \\         `\n");
            printf("                                          `.   .   ,'\n");
            printf("                                            `\"-'--'\n");

            break;

        case 137:
            printf("\n");
            printf("                                                                                                     \n");
            printf("                                                                                                    \n");
            printf("                                 :+///////:--.``                                                    \n");
            printf("                              .++-       ``.--+hs-                                                  \n");
            printf("                           `/+:`            .o/` ++                                                 \n");
            printf("                        `:+/`             `++`    -s.                                               \n");
            printf("                      -++-              `++`       `o:                              `--.            \n");
            printf("                   `/+:`      .---::://+s.           /+`                          `++-:ho`          \n");
            printf("                  .s-         y:..``````/+.           .s.                       `/+. .s`.y          \n");
            printf("                 :o`          y`   odmd+ `/+.          `o/                     :o.  .s` :o          \n");
            printf("                +/           `y   `mmmmd`  `++:://///////h                   -o-   .s`  y.          \n");
            printf("              `o-            `y    :sys.    .s.`        :o                 -o:    .s.  :o           \n");
            printf("             -s.            .os/           -s`          s.               .o/`    .s.   y.           \n");
            printf("            /+`           `++` +/     ``.-/o`          `y              `++`     `s.   :o            \n");
            printf("          `o:            /o.   .y+/////:-.`            +/            `/+`      `s.    y`            \n");
            printf("         `s+///////::--:o-   -+/`                   `/+.            :o.       `s.    :o             \n");
            printf("        `s.        ``-yoo:`-o:`                   `oy-`           -o-        `s.     y`             \n");
            printf("       `s-         `++`  oho`                   .+/`.-://///:-.`.o:         `s.     :+              \n");
            printf("       o:         :o. `:o- :o.                -o/           `.-:+////:-.`  `s.      y`              \n");
            printf("      +/        -o: `/+-    `++`            :o:                      `.-://oo/`    :+               \n");
            printf("     /+       `+/``/+.        .o:     ``.-+o-                                //    y`               \n");
            printf("    .y`     `/o``++.      ``.-:/yo/////:-./h+.                               .s   :+                \n");
            printf("     ://////y:.os/:///////ss-.`            y./+-                              y`  y`                \n");
            printf("           `-:/:-.`      :o`               -o  -+/`                           o- :+                 \n");
            printf("                      .:oo                  s.   .++.                         :+ y`                 \n");
            printf("                  .///:+o                   .s     .y                         .y:+                  \n");
            printf("                `o/`  /+                     +:    s-            `ooo//::--/+//yy`                  \n");
            printf("               /o`   /s`                     `y`  -s            `s-`:++-..-:///oo/////:-..`         \n");
            printf("             -o-     -ohs///:.                :+  y`           `o:    `:+/`           `.--++`       \n");
            printf("           `+/`         -s+-.-/////:.`         y.:+       `-//+h:        `/+:`             .o/`     \n");
            printf("          :o.          `+/`:+/.    .-/////:.`  .sy`  `-////-` +/            .++-             -o:    \n");
            printf("        .s:           :o.    `/+/`        `-////hs////.      /+                -++-```......---os   \n");
            printf("        :y/////:.`  .o:         ./+:`           `y.         :+                   /o:::------...:o   \n");
            printf("         y.    .-//+s`           .:os+-`         `y.       :o                  `o:             +:   \n");
            printf("         `:/+/.    .s        .///:.   -++-        .y`     -s                  .s.              y`   \n");
            printf("             `:++:``y   `-/+/:`          :+/.      .s    .s`                 /o`             `:s    \n");
            printf("                 ./+h////-`                `-////:-`-o  .s`                `o:            `:+/.     \n");
            printf("                     `                           `-:/oo+y`                .s.          `/+/.        \n");
            printf("                                                       y+-.`             :o`        `/+/.           \n");
            printf("                                                       /o.-://///:-.`  `o/       `/+/`              \n");
            printf("                                                        y.       `.-://y-     ./+/`                 \n");
            printf("                                                        -s`            y`  ./+:`                    \n");
            printf("                                                         -///////:-.`  y-/+:`                       \n");
            printf("                                                                 `.-://o:`                          \n");
            printf("                                                                               \n");

            break;

        case 138:
            printf("                                                                                                    \n");
            printf("                                                                                                    \n");
            printf("                                                                                                    \n");
            printf("                                                            `.:+oyhhhhhhhhhhyyso+:.                 \n");
            printf("                                                       .:oyhyo+/-.``         ``.:/oyy+-             \n");
            printf("                                                   `:oys+:.                         `:sho`          \n");
            printf("                                                `/ss/.`                                `/h/         \n");
            printf("                                              -ss/``..----------.....``                  `oy.       \n");
            printf("                                            :yy::---.`````````.-----:://///::-`            :h.      \n");
            printf("                                          -yo-`                            ```-:::.         :d.     \n");
            printf("                                        `os.                                     `-/-        +h     \n");
            printf("                                       .y/                                          ./.       y+    \n");
            printf("                                      :y.    `......```                               /-      .m`   \n");
            printf("                                     +y---:::---...-------------..`                    +.      d+   \n");
            printf("                                    os:``                     ````.-----..`            `s     .od   \n");
            printf("`                                  oo`                                 ```.--..         o     /.N.  \n");
            printf("`                                 +s`                                        ``:-.      +   `:` m-  \n");
            printf("`                                :y`                                            `.:.  `-+----`  d:  \n");
            printf("                                .h.                                                -/--`  +`    d:  \n");
            printf("                               `y/       ````````                                  `+`    :`    m-  \n");
            printf("                               +s`..-::--...........--------.....`                `:`     -.    m`  \n");
            printf("                              `d/.``                        `````.----...        ./       .- `./m   \n");
            printf("                              ++                                      ``.-:-.   `/        ./..`/h   \n");
            printf("                             `h`                                           `.:-`+`   -:-  ..   so   \n");
            printf("                             /+                                               `o-   .. /  :`   d/   \n");
            printf("`                            h`                                               .+   .-  /  /   `m.   \n");
            printf("`                           -s     ```.....`````                              +`   :   /  +```+h    \n");
            printf("`                           o:.-----.....``....------.......``               -/   :`   / `/```d/    \n");
            printf("`                          `d:.`                      `````...------...`     +`   : `.:` /`  -d`    \n");
            printf("`                   `.-:/o:++                                       ``..-:.` s    : `:. ./`  so     \n");
            printf("`                .:++/:-oo`d.                                             .--s   `:    `:.-:-m`     \n");
            printf("`              -oo:`   /s`+o                                                -s    /   .:   `ho      \n");
            printf("`            .oo.     .h`+o`                                                `y    --.::`   -h`      \n");
            printf("`           :y-       y:oo`                                                  h`    /::`.- .h-       \n");
            printf("`          /y.       `ds/    .-:+//::::-.`              ..-:::::/-..`        o+   :` /  `:y+        \n");
            printf("`         :h`        `m/   -+/o+-`.-::-..--`         `:+:-.```.-/oo-:/-`     `h.`-`  /  `ho         \n");
            printf("`        `h-          y   +/`/. .sdNNmN+/..+`      ./y/  .+syy+:` /o``-+-     -y.    : `yo          \n");
            printf("`        :h           :/ `h ./ `hNNmmmNddy :s-```./::o  +mmmNNyhh` /+   :/`    -o`  -..y/           \n");
            printf("`        +y            //`y::- .mNNNNmmmms //.-::-` o. -mNmmmNNmm-  y    `+.    .o.`:/s-            \n");
            printf("`        :d             -+oy++``ymmmmmmmh.`o`       o` .mmNNNNmmm`  s    `-+.    `syo/              \n");
            printf("`         h/              .-.`/:.:+oss+:.-:`        ::  +dmmNNmh:  :-     --+     `y+               \n");
            printf("`         .h+`                 `---.----.`           /-` .:///-` ./:       /s.     -m`              \n");
            printf("`          .os-`                                      .::-````.:/:`         ++     .N`              \n");
            printf("`            `/o/.`                                      `.----.             :+`   oy               \n");
            printf("`             `.os--.`                                                        `//`+y`               \n");
            printf("`         `-/++/.    `-`                                     :             .`   .+h:`               \n");
            printf("`         :y/-....-:/.       .      .                       :.             .:     `:++-``           \n");
            printf("`           .-:/oy+.       .-`     .:         .        `.  ::              +//.      `:+so-`        \n");
            printf("`            .so:`    ``.-/.      ./         .y.        .//-              +: `:/-`       .+s+`      \n");
            printf("`            `:/://:/+sho-       :/        .+o-s-   ``-/o/`             `o/     .:::.`````.:d/      \n");
            printf("`                  `yy:`       .+-      `/so. ./hooooo/-              `:h/``       `/dsooo+/-.`     \n");
            printf("`                   .+o+++///+yo` `.-:+oo:`   h+.``                `-+o::ddysoo++++oo:.```````      \n");
            printf("`                            sy+++o+:-`       `+o/-`          ``-+syo-```.sy``````                  \n");
            printf("`                                                .:+++++++ossoo+sy:+osssso/`                        \n");
            printf("`                                                         `:/+++:`                                  \n");
            printf("`                                                                    \n");

            break;

        case 139:
            printf("\n");
            printf("                                                +s.                                                  \n");
            printf("                                              `h`o+                                                 \n");
            printf("                                              /o  -o-           `-.                                 \n");
            printf("                                             `d.    +yo++++/::oo/.s-                                \n");
            printf("                           -/-`         -/+++/s.....:-    ``.:///--h                                \n");
            printf("                           `h-:///:../oso/:--.-.....`           ./+o+/`                             \n");
            printf("                            /s   ``:oo.`           `.--..`        ./`.+o-                           \n");
            printf("                             s/      `s                  .-.       `+  `/o:                         \n");
            printf("                             `d/    .:-                    `-.      ./   `/s.                       \n");
            printf("                            .o/::-.............`             ..      +     `y/                      \n");
            printf("                           /o...---..```````````..-..`        -`     +      /oo                     \n");
            printf("                    ``.--:oh++::-.                `.-:-.       :     /      /`o+                    \n");
            printf("                  /yo:--....`````.:`           -//:-s/ ./.     :    `:     --  y-                   \n");
            printf("                   ./+/`          `/         .o/`  s/   `:-    :..-::/-. .:.  `:h--.`               \n");
            printf("                     `-+s:.       .-        .y-   -y      --  -:``    `-+. `//:..-/+/               \n");
            printf("                       :o-/+:-...-.         y.    ++       /.:`  `---.  `:/o.  ./h.`                \n");
            printf("                       h`   `..--.....-...-:o     :s``     `+-..:/.``-:  /o`  //`y-                 \n");
            printf("                      -y  ``.--.````       .s      oo...`  :`  -+   ` `: y`  :s` ++                 \n");
            printf("                      ++...`                +-     `/o:.`../```o.   -  / y   h:--o+                 \n");
            printf("       ``.``          o+`  `.....``       ``.+:      `-++:-/...s`   /``/ y  .h   o/                 \n");
            printf("     :+/:::/+:.       o/-:::--...``. `.:+++//+s/`       `/oo`  -:   .-.` s- -s   y.                 \n");
            printf("    :s-.-..``-o/     :y+-`         .//-.`      -/         `:o/` +-`    `.h- :s  .h                  \n");
            printf("    `-----:+-  o/    `/h+:-.``     -.   .-----.+-           `+s-..-:-::/+s  /o--s-                  \n");
            printf("           `y  `h`  `s/`  `---::---`  `:...`  `:-             s+ `..:///-  .s` ++                   \n");
            printf("            s-  o/  o+   -::-:.      .y` - -    +             :h/:--.`  `.//` /o                    \n");
            printf("            +/  .s-.+s` :-..``-:`   `/:. `..`   +             oo   `.-:/:-:.`/+                     \n");
            printf("            .y.  `:/+o//y `.-  :+:---` :.`..-``:-            :h--://oo+/:-.+o:                      \n");
            printf("          `/oyh+//::::/+//`... :. ``````.-----.`           `/y/:.       `-:o+.                      \n");
            printf("        `+o:.`    `...`  `-------/..-+.......`            .s/``.-:///+/-.`  .++.            `-.     \n");
            printf("        s/                   `-.:- `o       ./:`         ..+/+/:.``-/y-.-:/:.`.++-`       .+/oo     \n");
            printf("       :s   `-::-`           :  `/ -+`````---``/           .s`       :o    `:/:`./++:-..-++-/o`     \n");
            printf("       +/ `+o:-.-/+.        `+--.:  ------```.:/            .+o/::.   ++`     `:/:.`-:::-./+-       \n");
            printf("      `:s/o.      -y+-`      /..-:. /+::---..-:               /+-`-/-  /o/---:/. `-::/::::.         \n");
            printf("     /+os.      `s+` -/s:--+``-..`/ `::` `...`                 `:o:`:+/-.----/s:                    \n");
            printf("     y. +s-`  `:s.  .+y/  -s    `......:///////:-.`               /s  `.:///:-                      \n");
            printf("     -s. `:++//-  .o+`h  oy:        -+o+:.`    `.-::///:-`        -y                                \n");
            printf("      `++-`    .:o+.  s-`m:      `/+:`                 `.:////////-                                 \n");
            printf("        `:///++:.      ///++/:://:`                                                                 \n");
            printf("                                                                \n");

            break;

        case 140:
            printf("\n");
            printf("                                       `--:----------------.`                                        \n");
            printf("                              `-------.`                  -+++::-.                                  \n");
            printf("                         `-----`                         .:   -:-.:---                              \n");
            printf("                     .:::-                                --.`  `o   `---.                          \n");
            printf("                 `:/o-                                       .---`       `-:-`                      \n");
            printf("              `:/:``/-                                                      `-:-`                   \n");
            printf("            -o+..--:`                                                          `:-.                 \n");
            printf("          :/-`...`                                                                -:.               \n");
            printf("        -/.                                                                         -/`             \n");
            printf("      ./.                                                                           .+::            \n");
            printf("     /:`                  :                                                          :-.:`          \n");
            printf("   `/-                    :`                     .:oyhdyyo/-`                         +` --         \n");
            printf("  `+`        -+ydh+-`      /                 `-odNMMMMMMMMMNmh+.                      `+  ./`       \n");
            printf("  +`      .+hNMMMMMNdo-`   `-.            .:sdNMMMMMMMMMMMMMMMMmy-                     -:  `/`      \n");
            printf(" /.     .sNMMMMMMMMMMMNdy+-.``.      `.:ohmMMMMMMMMMMMMMMMMMMMMMMNy.                    o   `/`     \n");
            printf(" s     /mMMMMMMMMMMMMMMMMMNmmdhysssyhmNMMMMMMNmNNMMMMMMMMMMMMMMMMMMm:                   ::    /`    \n");
            printf(" h    +.dMMMMMMMMMMMmdddmMMMMMMMMMMMMMMMMMms:..../sNMMMMMMMMMMMMMMMMNo`                  :-   `/    \n");
            printf(" s    + yMMMMMMMMNs-`` `./hMMMMMMMMMMMMMMy`        .hMMMMMMMMMMMMMMMMMh:`                 ./.  ./   \n");
            printf(" o    / +MMMMMMMM/        `yMMMMMMMMMMMMm`          .MMMMMMMMMMMMMMMMMMNdo:`                -:` o`  \n");
            printf(" /`   ` .NMMMMMMN          :MMMMMMMMMMMMd           `NMMMMMMMMMMMMMMMMMMMMMmh+:.             `/-.+  \n");
            printf(" `/`     +MMMMMMM/        `yMMMMMMMMMMMMM+         `sMMMMMMMMMMMMMMMMMMMMMMMMMMmy/.`           -/y` \n");
            printf("  `:-`    sMMMMMMNs-`` `.:hMMMMMMMMMMMMMMMy:.` ``./dMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMNd+.          `:/ \n");
            printf("    .:-``  sMMMMMMMMmdhdmMMMMMMMMMMMMMMMMMMMNdhddNMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMNs.          s \n");
            printf("      `.:-`-yNMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMNmhsooosdMMMMMMMMMN/         o \n");
            printf("        `+/- -hNMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMNs:`      `NMMMNNMMMMMo        +`\n");
            printf("       .+.     -smMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMy.          dd+:--yMMmyy+       o \n");
            printf("      -+         ./yNMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMd            o`     +d`  .:      o \n");
            printf("      s             +shNMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM+            :-      +    --    `+ \n");
            printf("      o            /:.+-/ymNMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM/             +      ./    -`   +` \n");
            printf("      +`           + ./    -+hmMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMd             o       -+.` :`  ::  \n");
            printf("      `+           `+o`   `   `yoohmNMMMMMMMMMMMMMMMMMMMMMMMMMMMNm:            o        o.-:s``-/   \n");
            printf("       -:         `-::---.-/.-+:`-/:/:so++ooooo++osdhhmNNNNmdhs+-+.           /-      `/`   `..     \n");
            printf("        ./.              `::   ....  .+--.----.----    ````    `+-          `/.      ::             \n");
            printf("          -:-`         .::`         .+                :/.-------           :/      -/`              \n");
            printf("             ---::.`.::/:.        `::                 `+-                ::`     -:.                \n");
            printf("                 .--`    `--.------                     -::.          -:-.--.----`                  \n");
            printf("                                                           .---.------ \n");

            break;

        case 141:
            printf("\n");
            printf("                     `...........`        ``                                                         \n");
            printf("               ``..-..........  -       `  .`                                  ``.                  \n");
            printf("           ``.-....`         `  :      .    ``.````````        ``....`     ```` ``                  \n");
            printf("        `.....              ``. :     ``     `        `........``     ..```    `.                   \n");
            printf("       ....                .`  :`:`   .     `                       ..        `.                    \n");
            printf("     ...`      `..........-`    : -.  .    ``                     ..         `.                     \n");
            printf("    ..`     ...`                -` --..    .                    `.          `.                      \n");
            printf("   ..`   `.-`                    -.:-:     .                  `.`          ..                       \n");
            printf("  - `  `-.                       ````-    .                  ..           -`                        \n");
            printf(" -   `-.                            `/`   .                .-`          `:.                         \n");
            printf(".`  .-                               `:   -               --           -- `..                       \n");
            printf("- `-`                                 -`  :`            .:`-         .-.``..-:                      \n");
            printf("-.-                                    :` --           .::.-       .-.      ``                      \n");
            printf("..                                      -.`:          -.`.`      `-.`..````````                     \n");
            printf("                                         `..-        -`      ```.-` `. .     ``....`                \n");
            printf("                                           `--      -`````````  -    - `          ``-.`             \n");
            printf("                                             `-..``.`.   .`    `-  `.-  `````````````.:             \n");
            printf("                                               `..`  `.   ..```.  .....` . ```....`````             \n");
            printf("                                             `````.`  `...-.`..  ````  - `-``    ``.`               \n");
            printf("                                         `````  `  ..`     `.`  `-     .` ``..``....`               \n");
            printf("                                      `.``````..`.` `..-..``...`.-```..      `.`  ```               \n");
            printf("                                    ..` `.`   .`  ..``.......-```..  -         -``  `.`             \n");
            printf("                                  `.` `.`      .   ````        .`  . .`        - `....:             \n");
            printf("                                 `-  .`      ``.  .`           -`   - -        `-  ```              \n");
            printf("                                 -  -`    ``.``  .             `.--.:`-.        :    ```            \n");
            printf("                                -  -    `.`      -          ``..``````.:        ..     `.`          \n");
            printf("                               `. -`   `.        -..`````...``         :         :       `.         \n");
            printf("                               - ..   ..        .``..-```              -.   ```.`-``       .`       \n");
            printf("                               - :   .`         .    -                  .-.`-  `/. ````     `.      \n");
            printf("                              .`..  `.          -   .`                     `-... `-   ```     .`    \n");
            printf("                              .`:   -          ..  -                        ..    `.     ```   ``   \n");
            printf("                              `.:  .`          :  -                          `..   .-      `.`  ``  \n");
            printf("                               :.` .          -` `.                            `-`  `..      `.`  ` \n");
            printf("                               : ` .         .`  .                               :`   `-       `.```\n");
            printf("                               -`  .        .`   .`                               :    ..        ``-\n");
            printf("                                :  .      `..... .`                               `.    -           \n");
            printf("                                .. -```-`..`.`  ..                                 -    -           \n");
            printf("                                .:`-.``.`.   -`  .                                 -  `..           \n");
            printf("                                . -..`   -``.....`                                 ....`.-`         \n");
            printf("                                  `.`...`                                          :`.````:/`       \n");
            printf("                                  ..`                                             `-` -  . `--      \n");
            printf("                                                                                 .`  .-``..`  :     \n");
            printf("                                                                                 - .`      `-.-     \n");
            printf("                                                                                  :          .:  \n");

            break;

        case 142:
            printf("                              +H+                       \n");
            printf("                             H;;+          +HHHHHHHHHHH+\n");
            printf("                             +;+ +H+   +HH+;;;;;HHHHH+  \n");
            printf("                            +;;HH;;HHH+;;;;;;+HHH+HH+   \n");
            printf("                         H  H;+H;;++;;;;+HHHHHH+++H+    \n");
            printf("                        H;H H;HH;++;;+HHHHHH++++H+      \n");
            printf("                        +;+HH;HH++HHHHHHH++++++H        \n");
            printf("                         H;;+;;;HHHHHH++++++++H         \n");
            printf("                          +HH+;;;HHH+++++++++H          \n");
            printf("                             H;;+HH+++++++++H           \n");
            printf("                             +;+HH++++++++++            \n");
            printf("                            +;;HHH+++++++++H     +HHHHH+\n");
            printf("                      H+    H;;HHH++++++++H  +HH+;;;;;H \n");
            printf("                   H+ +HH+  H;+HH+++++++++HH+;;;;;;;;H  \n");
            printf("                  H;H  +HHH++;HHH++++++++H;;;;;;;;;;H   \n");
            printf("   +H+           H;++  HHHHH;;HHH+++++++++;;;;;;;;;H    \n");
            printf("  +;;;H         H;++  H+HHH+;;HHH+++++++H;;;;;;;;;H     \n");
            printf("  H+;;+    +HHH+;++H H++HH+;;;+HH+++++++H;;;;;;;;+      \n");
            printf(" ++;;;;H+ +;;;;;++HHH++HH+;;;HHHH++++++++;;;;;;;;H      \n");
            printf(" H;;;;;;;H;++H;;;;+HH+HH+;;;+HHHHH++++++;;;;;;;;H       \n");
            printf("+;;;;;;;;;+   ;;;H+HHHH+;;+HHHHHHHH++++H;;;;;;;H        \n");
            printf("H;;;;;;;;+  H ;;;H++HH+;;+HHHH+++HHHH+++;;;;;;H         \n");
            printf("H;;;;;;;;;++H+;;H+++HH;;;HHHH++++++++HH;;;;;;;H         \n");
            printf("+;+HH+;;;;;;;;;;H++HH+;;+HHH++++++++++H;;;;;;+          \n");
            printf(" +    +HHH++;;;;;++HH;;++HH+++++++++++++;;;;;H          \n");
            printf("       H+++H++;;;+HHH;++HH+++++++++++++H;;;;;+          \n");
            printf("      H+H++++;;;H+HH+;+HHH++++++++++HH+;;;;;+           \n");
            printf("      HH H;;;;;H+++H;++HHH+++++++HH+;;;;;;;;H           \n");
            printf("    +H H+;;;;H++++++;++HHH+++++H+;;;+H;;;;;;H           \n");
            printf("   + H+;;;;H+  H++++;;+HHHH+++H+;;;;;;+H;;;;H           \n");
            printf("   H+;;;;+H     H++;;;;+HHH++H++;;;;;;;;+H;;H           \n");
            printf("  H;;;;;+H       H++;;;;+HHH+++;;;+HHHH+;;H+H           \n");
            printf("  +H;;++++        H;;;;;;+HHH++;H+      +HHHH           \n");
            printf("    H+++H         H;;;;;;;;+H+++            +           \n");
            printf("     HHH          H;;;;;;;;;;+HH+                       \n");
            printf("                  +;;;;;;;;;;;+++H                      \n");
            printf("                   +;;;;;;;;;;;;++H                     \n");
            printf("                   H;;;;;;;;;;;;;;++H                   \n");
            printf("           H       +;;+;;;;;;+;;;;;;;H                  \n");
            printf("          ++H       HHH;;;;;;H;;;;;;;;H                 \n");
            printf("          H++H       H;;;;;;;H;;;;;;;;;H                \n");
            printf("          H;++H      +;;;;+++H+;;;;;;;;;H               \n");
            printf("          H;;++H    +;;;;+++HHH+;;;;;;;;;H              \n");
            printf("          H;;;++H   H;;;;++H    +H;;;;;;;+              \n");
            printf("          H;;;;++H  H;;;;+H   +HH H+;;;;;;+             \n");
            printf("          H;;;;;;;H +;;;;H   H;;+ H++;;;;;H             \n");
            printf("          H;;;;;+H   H;;;;+HH;;H  ++++;;;;H             \n");
            printf("          +;;;;;H     +H+;;;;;;+   H+H;;;;H             \n");
            printf("           +H+;;;H       +HH+;++H+  HH;;;;+             \n");
            printf("              H;;;H         H;++++H  +;;;+              \n");
            printf("               H;;;+H+       +;++++H+;;;;H              \n");
            printf("                +H;;;;+H+    H++++H+;;;;H               \n");
            printf("                  +H+;;;;+HHHHHH+;;;;;;H                \n");
            printf("                     +HH+;;;;;;;;;;;;+H                 \n");
            printf("                         +H+;;;;;+HH+                   \n");
            printf("                            +HHHHH+\n");

            break;

        case 143:
            printf("      ::                                              \n");
            printf("      HHH:                   :HH                      \n");
            printf("      HHHHH:               :HHHH                      \n");
            printf("      HHHHHH: :HHHHHHHHH: :HHHHH                      \n");
            printf("      HHHHHHHHHHHHHHHHHHH:HHHHHH                      \n");
            printf("      :HHHHHHHHHHHHHHHHHHHHHHHHH                      \n");
            printf("      ,HHHHHHHH:,,,,:HHHH:,,:HHH                      \n");
            printf("       HHHHHH:,      ,:H:    ,:H                      \n");
            printf("       HHHHH:,  :HH:  ,:  :H: ,:                      \n");
            printf("      :HHHH:,,:H             :H,:                     \n");
            printf("      HHHHH,,,,       :::       H                     \n");
            printf("      HHHH:,,,,      :::::      :,                    \n");
            printf("      HHHH,,,,,,    ,:::::,     ,:                    \n");
            printf("     ,HHHH,,,,,,,   H::,,:H     ,H,                   \n");
            printf("     :HHHH,,,,,,,,  H: ,, H    ,,HH:,:HHHH:,          \n");
            printf("     H:::HHHH:,,,,,:HHHHHHHHHHHH:HHHHHHHHHHH:         \n");
            printf("    ::HHHH:,:H:,:HH::,,         ,:HHH ,HHHHHH:        \n");
            printf("   :HHHHHHHH:, HH::,,             ,:H :HHHHHHH:       \n");
            printf("  :HHHHHHHHHHHHH:,,,               ,:HH:,, HHHH:      \n");
            printf("  HHHHHHHHHHHH:, :,                  :H,,  HHHHH      \n");
            printf(" ,HHHHHHHHHHHHH: H,                   :H  :HHHHH:     \n");
            printf(" :HHHHHHHHHHHHHH:,                     :HHHHHHHHH     \n");
            printf(" HHHHHHHHHHHHHH,,,                      :HHHHHHHH     \n");
            printf(",HHHHHHHHHHHHH:,,,,                     ,:HHHHHH:     \n");
            printf(":HHHHHHHHHHHH:,,,,,,                    ,,HHH: HHH:   \n");
            printf("HHHHHHHHHHHH:,,,,,,:,                   ,,HHH, HH,H H:\n");
            printf("HHHHHHHHHHHH,,:,,,H H,                 ,,:HH:,,:, H:,H\n");
            printf("HHHHHHHHHHH:,: :,:   :,,H:            ,,,H::::H :H:, H\n");
            printf("HHHHHHHHHHH,,H  HH,  H:H,H,,        ,,,,:H::,,     : :\n");
            printf("HHHHHHHHHHH,:,  ::,, :H, H,,,,,,,,,,,,,,H::,,      ,: \n");
            printf(":HHHHHHHHHHHH,,:,,:H:,:, :,,,,,,,,,,,,,:H:,,,       H \n");
            printf(",HHHHHHHHHH:,:H,      ,:H,,,,,,,,,,,,,:H::,,        : \n");
            printf(" HHHHHHHHHH,,,,         ,:,,,,,,,,:HHHHH:,,,   ,:,  ,:\n");
            printf(" HHHHHHHHHH,,,           H,,,:HHHHHHHHHH:,,   ,:::,  H\n");
            printf(" HHHHHHHHH:,,,   ,:::,   :::HHHHHHHHHHHH:,,   :::::  H\n");
            printf(" HHHHHHHHH,,,    :::::,  ,HHHHHHHHHHHHHH:,,   :::::  H\n");
            printf(" HHHHHHHHH,,,   ,::::::   HHHHHHHHHHHHHH:,,   ::::, ,:\n");
            printf(" HHHHHHHHH,,,   :::::::   HHHHHHHHHHHHHH:,,   ,::,  : \n");
            printf(" HHHHHHHHH,,,   :::::::   HHHHHHHHHHHHHH:,,    ,,   H \n");
            printf(" :HHHHHHHH,,,   :::::::   HHHHHHHHHHHHHH:,,,       ,: \n");
            printf(" ,HHHHHHHH,,,   ::::::,   HHHHHHHHHHHHHHH:,,      ,:  \n");
            printf("  HHHHHHHH,,,   ,:::::   ,HHHHHHHHHHHHHHH:,,,,  ,,H   \n");
            printf("  :HHHHHHH,,,    ,:::,   :HHHHHHHHHHHHHHHH:,,,,,H:    \n");
            printf("   :HHHHHH:,,,    ,:,   ,HHHHHHHHHHHHHHHHHHHHHH:      \n");
            printf("    :HHHHHH,,,          :HHHHHHHHHHHHHHHHHH:,         \n");
            printf("     :HHHHH:,,,        ,HHHHHHHHH:,                   \n");
            printf("      :HHHHH:,,,      ,:HHHHHH:,                      \n");
            printf("        H:HHH:,,,    ,:HH:,                           \n");
            printf("              :HHHHHH:\n");

            break;

        case 144:
            printf("    :--:.                                                                                .--/`      \n");
            printf("    +   -:.                                                                           .::.  --      \n");
            printf("    -:    -:`                                                                    .:///.   `/:       \n");
            printf("     .-    `:-                                                             `-:///-`    .:/:         \n");
            printf("  ----`-.     -.`                                                     `-///:.``    `-:/:`           \n");
            printf("  +` `--:/.     -:.                                               .://:.....`` .-://-----:          \n");
            printf("  `/-    `-//.    -/.                                          -/+:``---`    ..`       .::          \n");
            printf("`----:.     `.`    `::                                       /+-``::-`             .:::-`           \n");
            printf("./``.-:/-`           `+`                                   `o: ./:`           `-/++/:---            \n");
            printf(" -:`    `...`      `. ./                                   o: //`         `.---.``   `:/            \n");
            printf(" .-/:.      `       :  o                                  :o -o         ```       `-::`             \n");
            printf("o``.-:/:--.`        :` o                                  y` s.               `-:::.`               \n");
            printf("-/-    ```..`       :`.o                                 :+ -o           .--://::----               \n");
            printf(" `.::-.             : +-                                 s. o.         `-.``       -/               \n");
            printf("    `-://:.`        :`s                                 `y `s                 `--::.                \n");
            printf("  -::.``           ..+-                                 :+ :/           `..-://:::-                 \n");
            printf(" /-`   `..`        :`s                                  o- +`        `..```    .-:-                 \n");
            printf(" .:::++:.`        ..+-                                  y  /              `--::.`                   \n");
            printf("  `::.`           .`s                                  `o  -         `.---------                    \n");
            printf("  +.   `.-..     ``/:         `    `.-`                ::  .              `.--::                    \n");
            printf("  :::/++:``      ` s        `-/`..-`:.  .:             o` ``        `.--://--`                      \n");
            printf("   -/-`    `       y       .:`:-`  :-.--/.            `+                   `-:                      \n");
            printf("  :/`   ...`       s`      / .- `..```./.            `+`       ``...------::-`                      \n");
            printf("  ./:::/:`         .+.     -`:`-```.-::`           .::`        ``.-:::-.``                          \n");
            printf("    `-:`  .--`    ```/:     ://:++/`.-          `-:.`        ````    `.-:-                          \n");
            printf("    -/..-/:.       `.`-/`  :..::..`  /`      `.-.`            ```.::...``./`                        \n");
            printf("    `..:/.   .`     `..`/. .:--`     :.    .--`              .`    ./:..--:`                        \n");
            printf("      `o``.:/.        `-`-- /        -:  `-.` ``              .:.`   -/`                            \n");
            printf("       ::--/`   `      `-.`::        `o .-` `.`             `  `:--...:/                            \n");
            printf("         `+`  `-` `      -`/          :--  ..           ``   -`  :.```.`  `...---::---..`           \n");
            printf("         .+..:o` .` `    `:`           `  -`             `.  `/-` +`  `.-:-..`` `````...::-`        \n");
            printf("          ...::`:` -.   `-`        `-    ..       ``  ``  `/.`:--:/--:-.`  ..-::-.```.----:/-`      \n");
            printf("             /:+` -/   `/-          /`   `         -   -.  :-.- `-:-`  `-::..`           `.-/+:     \n");
            printf("             ``--:o  ` :/`          ./     `` `    `+` `/:-/` `-:.  `-:-.`  `..-:::-..---..` `-/`   \n");
            printf("                ` +-:: .+-           /   `` :` -   `o:::. ` `-:.  `::.` `.-:-..``..........-:-.`/.  \n");
            printf("                  `.`-`:+`          `/    :-`:--/..+.     `::.  .::. `-::.``.-:/:..::....:/:....-+. \n");
            printf("                      ``:.-         `/     -/--..--`    .::` `-/-``.:-. `.:-.` `-`  +     -.`.-..:s`\n");
            printf("                        `//        `:.      -         .:-` .-:. `-:-``.:-.       :  /`     :   `-`-/\n");
            printf("                          -:-    ..:-      -:      .-:.``-:-` .::. .::.          :  /`     /     - /\n");
            printf("                           //--.::``       ./ ``.---..-:-. .-:-``-:-`           -.  +     -.     . /\n");
            printf("                           .: ..-.`.-      `o..--.-:-..`.::-.`.:-.             .:  :-    `/       `:\n");
            printf("                            :-   `--::`    .+..---.--:---..---.               -:  -:    `/`       :`\n");
            printf("                             --  `-` `::`  //---:::-----...                 `:- `:-    `/.      `:` \n");
            printf("                              ::-:`    `/`.+`                             `::` .:.    `/.      `-`  \n");
            printf("                              :`:`      /--+                           `.:-``.:.     .+.      .-    \n");
            printf("                             .::`       : -`                       ``-::.`.:-.     ./:`     `-`     \n");
            printf("                             /`:       .-:`                    ``-::-.`.:-.      ./:`     `..       \n");
            printf("                      ``` ``:`:`       /--               ```-::--.`.-:-.      `-/:`     `..         \n");
            printf("                    ...-:::-` ..```   -./`         ```-:::--.`.-:--.`      `-//-     `..`           \n");
            printf("                   -:.-:..--....../-`.- .-:- ```-:::-:-.-::---.`     ```-:/:-    ``...`             \n");
            printf("                   .. :-:`:.-`  `.-..   `::/::--..-:---.`    ````.-::::-.`  ``.-:-.                 \n");
            printf("                       -  /.    ...:..///:-``----.`````.--:::::--.`` ```.-:::-.`                    \n");
            printf("                                :-::::.``-:--``.:::::-:-..``..-:://:::::-`                          \n");
            printf("                                /o:.`.::-..::::-..-:///:::::--.`                                    \n");
            printf("                              `/:``::-.://:://:::-.`                                                \n");
            printf("                             :/``/:`.+o+/:-.                                                        \n");
            printf("                           `/. -+``/s/-                                                             \n");
            printf("                           +. /: -+-                                                                \n");
            printf("                          :- /: +/                                                                  \n");
            printf("                          o `o +:                                                                   \n");
            printf("                          + /.-+                                                                    \n");
            printf("                          /.+.+-                                                                    \n");
            printf("                           /://:                                                                    \n");
            printf("                            -o-o:                                                                   \n");
            printf("                              --+o/:-.``...`                                                        \n");
            printf("                                 `-::///::---.                                                      \n");
            printf("                                              `   \n");

            break;

        case 145:
            printf("\n");
            printf("                                                                                                .-:o:\n");
            printf("                       /-                                                                `------:-  \n");
            printf("/o:--`                 .::-                                         `//             `-----   -:.    \n");
            printf("  -:`.----.             --`::         :.                          -:/o-o`      .----.     `::`      \n");
            printf("    -:.   `----- `o/----`:- `:-       :--      `+`             -:- -/`/` `-----`        `:-         \n");
            printf("      .:-      `---++`  .-+.  `/-     / --    :-/           `::`  :-`o----            -::--         \n");
            printf("        .:-          .----./`   .:.:` /  :. -: ..         -:.    -/-.               -/-.-:.         \n");
            printf("          `::             `--    .+y::+   /:`  /  `../..:-                       `::` .:.           \n");
            printf("       /++---::`                  :-      `   `:..-:/++:..                     .:-  .:.             \n");
            printf("          ---. ::`                 -:             `.``---                    -:.  .:.               \n");
            printf("             `---::.                `/.+    :yy`   .--                     ::`  .:.                 \n");
            printf("                 .-+o.              -. do-/+dh`  --`                    `/:   .:.                   \n");
            printf("   ./++/-------------:            `+--//--oo     `/                     ..----:--------/+-          \n");
            printf("       .-----`                      `// `/+: .+--.`:`                           .------`            \n");
            printf("             .-----                 .o` +- .::/`  .--                    .---://:/:                 \n");
            printf("                  `-----.           /`-:      -`    `             .------`  .----`                  \n");
            printf("                        `-----`    /`:+             :       .-----`    .----`                       \n");
            printf("                              +`  :-: ---       .:. /        :-   -----`                            \n");
            printf("                          `::/`  .+-`-/++-`    ---`-+        `.//-`                                 \n");
            printf("                          `o-:/``::--:-  ::`   .+`   :-   `--/  -:`                                 \n");
            printf("                        `-:`+` o.   --    /.   /:     /---/`-+    ::                                \n");
            printf("                    `//+--:+./ `/  ./:`   -:   .-.   `:: -- //-`.-:-+:                              \n");
            printf("                       .----..` .:-`-/---:/.     `+--/`.:+ :.`-/. -+ ./`                            \n");
            printf("                      `+----`     -:`     :.      :-` ---` ...`---.----/:                           \n");
            printf("                     -::--------` +      ::         .--/      -----+.. `-`                          \n");
            printf("                                : /    ::             :.  .--------+-.                              \n");
            printf("                                .:+  ::              -. --/-                                        \n");
            printf("                                 :.::`.-:.            o:+` `:.                                      \n");
            printf("                                 -+:--``/         `    o.-+-..:`                                    \n");
            printf("                                `:`    +   `/+    o.   ./-./.--o`                                   \n");
            printf("                                      --  /- ::  ---/   + .--                                       \n");
            printf("                                      + .//`/`+  /:-+/` `/                                          \n");
            printf("                                     `/:. ::  :.`: .: :- /                                          \n");
            printf("                                     -:        //      `:+`                                         \n");
            printf("                                               /:        `        \n");

            break;

        case 146:
            printf("                                                                                                 `  \n");
            printf("                                                                                               ``.. \n");
            printf("       `                                                                                    `.-  -  \n");
            printf("    ..``.                                ``.`                                          ``.`.``  .   \n");
            printf(" ``:`  `.                              ``. .                         `.              .``.``    `.   \n");
            printf(" :-:   `.``                      `` .`.` `.`          `             `.`.            .``.       .    \n");
            printf(".`  -    .`                    ``. ``    ``          ..``   -`     `.  .          ```.`      -.     \n");
            printf("``  -    `.`              `` . -`     `.      .``````.` . .:..`   ..  -`      `````-.       --      \n");
            printf(" `` -       .             :::...    ``.      `-         - ..  .`  -   `-````.`  ..-`      ```       \n");
            printf("  . ```     `.``      ``  `.:     ..-        .`       ``.``   -  `-``...`     `.``        .         \n");
            printf("  .`  .       `-      :.. ..     `-     `.`   .      `-``..` `.````         ``         `.`          \n");
            printf("   `. ..`     ..    ...`.`.   ```-      `-`.` .`    `-`.`..          .-```..          -`            \n");
            printf("    `.``.`     `-``-`   `.    +.-    -`.`.  -`..     ````       ````.``` `            :.            \n");
            printf("      .. -`      `.-          ``.    -` `   ```     `.`     `..`                   `..`             \n");
            printf("       .``-.`    -      ```````.     `.          ````     `.-`                ````..                \n");
            printf("        -  `.-. -.`    `-`` ````   .`-.. ````.``     ` ``.`                 ```````                 \n");
            printf("        `````` .-.-````:`      ````.::`..````    ```...``                 .`:`                      \n");
            printf("            `...``:-``-/-   ``   `..`-.`       ``.                      -..``                       \n");
            printf("               `..``...-``.-``.     -.       ...`                   ````-`                          \n");
            printf("               `.``..-...`` .` .   .`   ````..`               `-..`.````                            \n");
            printf("              `.`--``  ``.`` `..       --`.`        ``.`       :` `                                 \n");
            printf("             ....`        `..  .        `.`..```.`````         :`                                   \n");
            printf("            `.`              ..`            `.``              -:                                    \n");
            printf("                              -               ``             :-.`                                   \n");
            printf("                              .                 .            ` --                                   \n");
            printf("                              .                  .`          ...                                    \n");
            printf("                              `.       `          ..``       -                                      \n");
            printf("                              .`       .           - -      .                                       \n");
            printf("                              `.       `.          - ````````                                       \n");
            printf("                               -`  ```` ..         -                                                \n");
            printf("                                ...```.````.``  ``.`                                                \n");
            printf("                                 . `.         `.. `.                                                \n");
            printf("                               `.`.-             .` .`                                              \n");
            printf("                              .`..`               `. -                                              \n");
            printf("                         `...```.`                 . ``                                             \n");
            printf("                       .--..`.``..-               `.` ``.``                                         \n");
            printf("                       `.`-..     .             `--- ...-.-.                                        \n");
            printf("                          .`                       -.` .-.                                          \n");
            printf("                                                   `.   ``                                          \n");

            break;

        case 147:
            printf("                              H  \n");
            printf("               +             H + \n");
            printf("  +HHHH+      + H           +; H \n");
            printf(" H+++;;;+H    H +           H; H \n");
            printf("+HH+++;;;;H   H  +   +HHHHH+;; H \n");
            printf("+   H++;;;;H  H; H H+;;;;;;;H  H \n");
            printf("     ++;;;;;+H+;; ++;;;;;;+H;H + \n");
            printf("     H++;;;;H;;H; H;;;;;;H  H;+ +\n");
            printf("      ++;;;;+;;;H H;;+H;;+; +;H H\n");
            printf("      H+;;;;;+;;  H;+  +;;+H;+ +H\n");
            printf("      H+;;;;;H;;  H;HH H;;;;;H H+\n");
            printf("      H;;;;;;H;   H;HHHH;;;;;HHH \n");
            printf("      H;;;;;;H   H+;+HH+;;+HH+H+ \n");
            printf("      +;;;;;;+  ++;;;++;+H    H  \n");
            printf("     +;;;;;;;;+H H+;;;+H       + \n");
            printf("     H;;;;;;;;H  H+;;++;;      H \n");
            printf("     +;;;;;;;;+   H;;+H;;;;    + \n");
            printf("    +;;;;;;;;;;+  H+;++;;;;;; +  \n");
            printf("    H;;;;;;;;;;H  H+;;+H+;;;;+   \n");
            printf("    H;;;;;;;;;+H  H+;;H;;+HH+    \n");
            printf("    H;;;;;;;;;+H  H+;+  ;;;H     \n");
            printf("    H;;;;;;;;;++H H+;H      +    \n");
            printf("    H;;;;;;;;;++HH+;;+      H    \n");
            printf("    H;;;;;;;;;+++H;;+       +    \n");
            printf("    H;;;;;;;;;;+H;;;H        +   \n");
            printf("    H+;;;;;;;;;H;;;;+        H   \n");
            printf("    +++;;;;;;;;;;;;H         H   \n");
            printf("     H++;;;;;;;;;;;+         H   \n");
            printf("     ++++;;;;;;;;;+          +   \n");
            printf("      H+++++;;;;;;H         +    \n");
            printf("      H++++++++++H;;;       H    \n");
            printf("       H++++++++H;;;;;;    +     \n");
            printf("        H++++++H;;;;;;;;  H      \n");
            printf("         H+++H+;;;;;;;;; H       \n");
            printf("          +HH;;;;;;;;;;H+        \n");
            printf("             +H;;;;;;H+          \n");
            printf("               +HHHH+\n");

            break;

        case 148:
            printf("                          H:              \n");
            printf("                         H H            H:\n");
            printf("                        :  H           H H\n");
            printf("                        H  :          H  H\n");
            printf("              H:        :   :         H  :\n");
            printf("            H:         : H  H  :HHH: :  : \n");
            printf("           ::          H  H  H:     :H   :\n");
            printf("          :H           H     :    :   :  H\n");
            printf("          HH           :H : H    : :  H H \n");
            printf("         ::H           H H  :    H H   HH \n");
            printf("         H H           : H ::    :H:  :H: \n");
            printf("         H:H            H HH:H:      : H  \n");
            printf("         HHH             :HHHH :     H H  \n");
            printf("        ::  :              HHH H     HH:  \n");
            printf("        H:: H              H:HHH:   ::H   \n");
            printf("        H:HHH              : :HH:     ::  \n");
            printf("        :H:  H             H H::       H  \n");
            printf("         H:::H              : H::      H  \n");
            printf("         :HH :H             H  H:::   ::  \n");
            printf("           :H  :H           :   H:::::H   \n");
            printf("             H   :H:         : H::HHH:    \n");
            printf("              H     :H       H H::  H     \n");
            printf("               H::    H      H  :::::     \n");
            printf("                :::    H     :   :H:      \n");
            printf("                H:::   :      :  :  :     \n");
            printf("                H:::    :     H  :  H     \n");
            printf("      :H:       :::     H     H  :  :     \n");
            printf("    H:   :H   :H::      H     H  :   :    \n");
            printf("   H       :H:          H     H  :   H    \n");
            printf("  H                    :H     H  :   :    \n");
            printf(" HH      :             H:     H  :    :   \n");
            printf(" :H      H:::         ::      :  :    H   \n");
            printf(": :       :::::      : H     H   :    H   \n");
            printf("H :        :H:::   :H H      :  :     H   \n");
            printf("H  :         :H:::H  H      H   :     H   \n");
            printf("H  :           :H:  H      H    :     H   \n");
            printf(":   :            :H:     H:    :      H   \n");
            printf(" :   :              :HHH:      :      H   \n");
            printf(" H    :                       :       H   \n");
            printf("  H    :                     :        :   \n");
            printf("   H    ::                  :        H    \n");
            printf("    H     ::             :::         :    \n");
            printf("     H:     ::::    :::::           H     \n");
            printf("       H:       ::::               H      \n");
            printf("         H:                       H       \n");
            printf("           :H:                  :H        \n");
            printf("              :HH:           :H:          \n");
            printf("                  :HHHHHHHHH:\n");

            break;

        case 149:
            printf("                                                     `-`                                            \n");
            printf("                    --`                              --`                    `                       \n");
            printf("                    --             .-.     `        .--                     ` `                     \n");
            printf("                    :-`          `..`.-....---.....:--`                                             \n");
            printf("                    ---``....``...-` `-`---:-.....-``                                               \n");
            printf("                    `.-------:-`` `` ` `-````-`                           ```                       \n");
            printf("                      ``````.-``             `-`                                                    \n");
            printf("                         ```-``       `-::`    :`                           `                       \n");
            printf("                      ``````-/`      `-/yh:    `:          `````              `                     \n");
            printf("                        ````-o+       -/hdy`    -`         -``......``                              \n");
            printf("                    ````````.:-`      ``/-.      :         `.:`........`                            \n");
            printf("                 ````` `  `-``                   :          -:    ```...-`                          \n");
            printf("                    ``````-`              ``.    :         `-/ `      `...-`                        \n");
            printf("                         `-`              --`    ..       `-.- `-       `..-`                       \n");
            printf("                      ``  .-` ``   .`    `:`      -.    ``---   ..        .--.                      \n");
            printf("                     ``  `-:.-.````````..-:        .-``..-.`     -`        .-:`                     \n");
            printf("                        `-:`  --.`.-..-..`-.        `::.`         -         .-:                     \n");
            printf("            `   `.      -:`   -    :```  ``/          ..          .`         --.                    \n");
            printf("           `:.-.::``   `/.`   -    :....```..          `-`         -          -:                    \n");
            printf("           `/.-`...-.``-:`    :   ..        :            ..        ..         -:                    \n");
            printf("          `-``   ````../:````.-.../` `    `.-.   -        `-`       -         -:                    \n");
            printf("          -::`          `...`    ..`.`       -   -`         --      `.   `..  -:                    \n");
            printf("           --                   `-      `....-`   -`         `-`        -` `:`::                    \n");
            printf("            .-`                 :....        .-    ..          ./..... :    `:o`                    \n");
            printf("              --`              .-  ..........`-     .-`          -.  `:.     +:           `.        \n");
            printf("                ...--..........:...           :`      -`          .-         `         `..-:        \n");
            printf("                              .`               -       -.          `-                ... `:         \n");
            printf("                             `.  `...`.```.....:        .-          -`            ...   `:          \n");
            printf("                             :...`             ..        `-.        /:        `...     `:           \n");
            printf("                            -`                `./          `..-..:./.-`   `...`       .-            \n");
            printf("                           `:            `....` `-..         -:::-:/......`          -.             \n");
            printf("                          ..-      ```...`       -`          `` -.``               `-`              \n");
            printf("                         :` :......``           -`               :               .:.                \n");
            printf("                        :.  -`                .-.                -.          ``..-`                 \n");
            printf("                        :   `-           ``...`:                  -        `--`..                   \n");
            printf("                       ..    `-`    ```..``    :                  :     `.-`.:.`                    \n");
            printf("                       -`     `--...```        -.                .- ``.:` /..`                      \n");
            printf("                       `-       `-`        ```...-`              /.:`` :...                         \n");
            printf("                        -`        `...``...```   `.-`           :. ..`..`                           \n");
            printf("                         -.         `.-.``         .:-`        ./``-.`                              \n");
            printf("                          .-`          `-`..`````..```.-       /:.`                                 \n");
            printf("                            --.`      `.    ```.-....../` .   `.                                    \n");
            printf("                        ``...`--     ..                `- `    -`                                   \n");
            printf("                     `-.``          .`                 -`      `:`                                  \n");
            printf("                   `--:-`        `..`                 -`        `-`                                 \n");
            printf("                  ./-..-:. ``...``                    :`   `..----:                                 \n");
            printf("                   :.:-.-:..`                         `-.-.+. -/.:`                                 \n");
            printf("                                                        ...:.-:`-`                                  \n");
            printf("                                                          `. `-   \n");

            break;

        case 150:
            printf("\n");
            printf("                                               `/:+`                      ```                        \n");
            printf("                                              :- .+`     `....``        -+-:/:                      \n");
            printf("                                              ./. `/--:::-....--:::::-./:   +.                      \n");
            printf("                                               `/.  .`              `.:`  `/.                       \n");
            printf("                                                `/                       `+`                        \n");
            printf("                                                `o                       /.                         \n");
            printf("                                                :-                       /.                         \n");
            printf("                                               `+                        ./                         \n");
            printf("                                               .:                        `+                         \n");
            printf("                                               `+    `.`           `     .+                         \n");
            printf("                                                :-`-:``.-`      `..` `-.`/.                         \n");
            printf("                                                `+``o/o.` `- `- ```:+-/ ./                          \n");
            printf("                                                 :- //Nh/. .:-/ .:hNh--.+`                          \n");
            printf("                        `-:::::-`                `+```:+ss::.`:/yoo/.``+`                           \n");
            printf("                       `+-`   `.+.              `:+-     ``     `     -:                            \n");
            printf("                       /-       .o              +.`./-.            `-:-`                            \n");
            printf("                       :/       :+:`           ::  --.-::.` ``. `.::.                               \n");
            printf("                        :/-...-/:`./:--..`     o   o    s.::-..::-`                                 \n");
            printf("                         `..-+-`    -+:..-:-.` + `.+:---o````.+-                                    \n");
            printf("                  `...`      :+      `:/-..-//:+:/:-.` `.--:``-:-.-.                                \n");
            printf("                -/:-.-:/-``.:/. -      .s:...-/-````.-:`  `..-:-  `:-                               \n");
            printf("               .o`     `o/--.  `o      o`     `o`     `/.      -``  -:                              \n");
            printf("        ```    -/       /-      +`     s       o`       +`     ` .:` :-                             \n");
            printf("    `-//:::://:-s:`   `:o.``    `.   ``++.`  `:/-`      -/     .- -/  +`                            \n");
            printf("  `//-`       `-:os+:::----:::.````-/:-.-:::::. ./`     `+      /  +` :/                            \n");
            printf(" .o.   ``...:.    `:+.       `-::::-`            `+.    `+      `  :` :s                            \n");
            printf("`o.  `::----:+/`    `+:                           `/:`   /.      `..``/o                            \n");
            printf(":+  `+.       -+`     //                            ./-` `::-..-::-` :./`                           \n");
            printf("o.  :/         -o`     /+                             -/.    `    `  /..:                           \n");
            printf("y   +.          :+      //                             `::        /. :-`/                           \n");
            printf("y   +.           //      o-                              +.       `o``+`/`                          \n");
            printf("s`  /:            +/     .o                              -/        .+ .+./`                         \n");
            printf("+-  .o             /+`    s.                             -:         -- .+.+`                        \n");
            printf("-+   +-             -o:   s`                        ./::-:` .`       `  `/:o`                       \n");
            printf(" o`  `o.              -///-                      `:/-        ``       ````-/o:                      \n");
            printf(" .o   `o`                                      `//`              .:-::::::/++s+                     \n");
            printf("  :/   `+-                                    -+`                 -:        :+:+-                   \n");
            printf("   //    :+`                                 :/`                   +         `o-:+`                 \n");
            printf("    :+`   `//`                              :/                     o          `s`-o`                \n");
            printf("     -+`    .//-                           -+                     .o           o. -+                \n");
            printf("      `+-     `-/:-.                     `-s                      +-           o.  /:               \n");
            printf("       `//`      `.-:::---.....-------::::s.                     .o           `s   `s               \n");
            printf("         .+:`         ````......``````   :/                     `o.           //    s`              \n");
            printf("           -/:`                         `o`                     +-           .o`    s`              \n");
            printf("             ./:`                       -/                    `+-           `o.     s`              \n");
            printf("               .:/-`                    +.                   `+-           `o-      s               \n");
            printf("                 `-/:.`                 o`                  .+-           -+.      `o               \n");
            printf("                    `-/:-.`             o`                `//`          ./:`       :-               \n");
            printf("                       `.-:::-.``       :`              `:/.          .//.        ./                \n");
            printf("                            `.--::::-.-:+`            .:/.         `-/:.        .::`                \n");
            printf("                                  `.://:`          `.//.        `-:/-`       .-/-`                  \n");
            printf("                                  -/-`          `-/+:.````...-:/s:.      `.-/-.                     \n");
            printf("                                 `o         .::::-:---------..` o       `+-`                        \n");
            printf("                                  o`      `-:-`                 ::      .+                          \n");
            printf("                                  o`     ./.                     +`     +.                          \n");
            printf("                                 `o     .o`                      +.     +                           \n");
            printf("                                 ::     o.                      `o`     /`                          \n");
            printf("                                `o`    :+                      `+-      `+-                         \n");
            printf("                                :/     y`                    ./o/-`      `:/.                       \n");
            printf("                               `o`     h/-                  -+. `-s`       `//.`                    \n");
            printf("                              `o.      y`o`                 o`    o.         `:/:`                  \n");
            printf("                              /:       s.o.                 -o.``:s.`           .:/:.`       ````   \n");
            printf("                             :/        :o-                   `///-`-:/:.         ...:///::::/::://` \n");
            printf("                            :/         `o.`..``                       .:+.        .-:/::/++-`    .+:\n");
            printf("                           -+  `://`    `/:..::/-                       `+:`               -+-    `s\n");
            printf("                          -o      -+            //                        -//:.```         `/o-:--:.\n");
            printf("                          /:     `/o-:::::::`   `s                           `-:::::::::--:-`       \n");
            printf("                           :/::://-        `:////-  \n");

            break;

        case 151:
            printf("                /H                   \n");
            printf("               / =/        /H/       \n");
            printf("         /HHHH/ ==H       H   H      \n");
            printf(" /H/  /H/      H==H      /=    H     \n");
            printf("/   HH=          =H      H==    /    \n");
            printf("H== ==           //      /==    H    \n");
            printf("/==             // /      H==   /    \n");
            printf(" H=   /H/==     H H /      H==   /   \n");
            printf("  H=  H=H/=     /H/ H       H==  H   \n");
            printf("   H= H HH/     =/ =/        H===H/  \n");
            printf("   H= H H /      ==H  H       H=H=H/ \n");
            printf("   /==/HH/=       H  H=/       H= HH/\n");
            printf("    H======       / H=/H      /=  / H\n");
            printf("     /H==/==     H H== /      H= /  H\n");
            printf("        HH/HHHHH/ H/==H       /= H =H\n");
            printf("         H///==/H///HH/      /=    //\n");
            printf("         ///====/HHH= H/     H=    / \n");
            printf("        H/===== =H=H  HH     H= =  H \n");
            printf("       H==/=     H H  H=/    H =/ // \n");
            printf("      H=  H=     / /  / H    H // H  \n");
            printf("     H=   /     /=      H    H // /  \n");
            printf("    H=   /=     H       H    H ///   \n");
            printf("   H==  /H=     H       H    H = H/  \n");
            printf("   /=H /H / =   H  =/= =/   H=  //H  \n");
            printf("    / /   H==/H H  /// /=/H H   H/H  \n");
            printf("          H==  /H  /// H==/H=   H=H  \n");
            printf("          H===  H  ///=/=====  /H=H  \n");
            printf("         H/==== /= =/=/====/HH/ /=/  \n");
            printf("        H///===///=   HHHH/    H H   \n");
            printf("       H//HH==///H=  =/        / /   \n");
            printf("      H///  /HHH/H== /        H H    \n");
            printf("      H//H      H/===H     /H/ H     \n");
            printf("       ////H/     /=/  /HH/=  H      \n");
            printf("        //////HHHHHHHH/====/H/       \n");
            printf("         /HH//==========/H/          \n");
            printf("             /HHHHHHHHH/\n");

            break;




    }
}


