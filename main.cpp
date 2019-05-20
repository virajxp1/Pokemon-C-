#include <iostream>
#include <vector>
#include <time.h>
#include "Pokemon.h"
#include <string>
#include <time.h>

using namespace std;

int main() {
    /*
     * first ask user to choose their pokemon
     * then we create pokemon based on input
     * for example if charizard we create a charizard using base sta4ts and a random level between 70 - 100
     * this charizard will have some assortment of moves based on what he can learn
     */
    cout<<"Welcome to Pokemon C++" << endl;
    //system("PAUSE");
    Pokemon myPkmn;
    srand(time(NULL));
    while(!(choose_pokemon(myPkmn)));
    myPkmn.printDetails();
    /*
     * Next step:
     * create type advantage/disvantage chart
     * create function to pick opponents pokemon
     * 50% chance it chooses a pokemon with no advantage or disadvantage
     * 25% chance it chooses a pokemon with type advantage
     * 25% chance it chooses a pokemon with type disadvantage
     *
     * Next Next step:
     * create battle sequence
     * make it pretty with ascii art
     */
}

