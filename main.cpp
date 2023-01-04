//
// Created by liels on 31/12/2022.
//

#include <unordered_map>
#include <string>
#include "HashTable.h"
#include "worldcup23a2.h"

using namespace std;
int main()
{

    world_cup_t* cup2022 = new world_cup_t();
    cup2022->add_team(22);
    cup2022->add_team(23);
    cup2022->add_team(24);
    cup2022->add_team(25);

    cup2022->add_player(213,22,permutation_t::neutral(),0,5,5,false);
    cup2022->add_player(214,23,permutation_t::neutral(),0,5,5,false);
    cup2022->add_player(215,24,permutation_t::neutral(),0,5,5,false);
    cup2022->remove_team(22);
    cup2022->remove_team(23);
    cup2022->print();
    cup2022->remove_team(25);
    cup2022->remove_team(24);
/*    cup2022->print();*/
   return 0;
}