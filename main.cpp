#include <iostream>
#include <vector>
#include <time.h>
#include "Pokemon.h"
#include <string>
#include <time.h>
#include "Battle.h"
using namespace std;

int main() {
    /*
     * first ask user to choose their pokemon
     * then we create pokemon based on input
     * for example if charizard we create a charizard using base stats and a random level between 70 - 100
     * this charizard will have some assortment of moves based on what he can learn
     */
    cout<<"                       Welcome to Pokemon C++"<< endl<<"                        Designed by: Viraj"<< endl;
    cout<<"                                .::.\n"
          "                              .;:**'               \n"
          "                              `                   \n"
          "  .:XHHHHk.              db.   .;;.     dH  MX    \n"
          "oMMMMMMMMMMM       ~MM  dMMP :MMMMMR   MMM  MR      ~MRMN\n"
          "QMMMMMb  \"MMX       MMMMMMP !MX' :M~   MMM MMM  .oo. XMMM 'MMM\n"
          "  `MMMM.  )M> :X!Hk. MMMM   XMM.o\"  .  MMMMMMM X?XMMM MMM>!MMP\n"
          "   'MMMb.dM! XM M'?M MMMMMX.`MMMMMMMM~ MM MMM XM `\" MX MMXXMM\n"
          "    ~MMMMM~ XMM. .XM XM`\"MMMb.~*?**~ .MMX M t MMbooMM XMMMMMP\n"
          "     ?MMM>  YMMMMMM! MM   `?MMRb.    `\"\"\"   !L\"MMMMM XM IMMM\n"
          "      MMMX   \"MMMM\"  MM       ~%:           !Mh.\"\"\" dMI IMMP\n"
          "      'MMM.                                             IMX\n"
          "       ~M!M                                             IMP"<<endl;
    cout<<"\n"
          "                   ______                        \n"
          "                 .' ___  |    .-.       .-.      \n"
          "                / .'   \\_|  __| |__   __| |__    \n"
          "                | |        |__   __| |__   __|   \n"
          "                \\ `.___.'\\    | |       | |      \n"
          "                 `.____ .'    '-'       '-'      \n"
          "                                                 "<<endl;
    Pokemon myPkmn;
    Pokemon CPU_pkmn;
    srand(time(NULL));
    while (!(choose_pokemon(myPkmn)));
    cout<<"\n\n";
    while (!(CPU_choosePkmn(CPU_pkmn, myPkmn.pkmn_type())));
    system("PAUSE");
    cout<<(string(50,'\n'));
    Battle(myPkmn,CPU_pkmn);
    /*
     * Next step:
     * create battle sequence:
     * "Go Pokemon"
     * "Your opponent sent out ..."
     * First Ascii art to draw pokemon each round
     * Square around the moves to make it look nice
     * options to select each move
     * Pkmn used x ... (its super/not very /not at all effective)
     * it did x damage
     * "Press enter to continue"
     * repeat
     */
}

