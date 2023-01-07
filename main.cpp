////
//// Created by liels on 31/12/2022.
////
//
//#include <unordered_map>
//#include <string>
//#include "HashTable.h"
//#include "worldcup23a2.h"
//
//using namespace std;
//int main()
//{
//
//    world_cup_t* cup2022 = new world_cup_t();
//    cup2022->add_team(22);
//    cup2022->add_team(23);
//    cup2022->add_team(24);
//    cup2022->add_team(25);
//
//    cup2022->add_player(213,22,permutation_t::neutral(),0,5,5,false);
//    cup2022->add_player(314,22,permutation_t::neutral(),0,5,5,true);
//    cup2022->add_player(214,23,permutation_t::neutral(),0,5,5,true);
//    cup2022->add_player(215,24,permutation_t::neutral(),0,5,5,false);
//    cout << "player 213 played:" << cup2022->num_played_games_for_player(213).ans()<<std::endl;
//    cup2022->play_match(22,23);
//    cout << "team 22 points:" << cup2022->get_team_points(22).ans()<<std::endl;
//    cup2022->play_match(22,23);
//    cup2022->play_match(22,23);
//    cout << "team 22 points:" << cup2022->get_team_points(22).ans()<<std::endl;
//    cout << "player 213 played:" << cup2022->num_played_games_for_player(213).ans()<<std::endl;
//    cout << "player 213 cards:" << cup2022->get_player_cards(213).ans()<<std::endl;
//    cup2022->add_player_cards(213,6);
//    cout << "player 213 cards:" << cup2022->get_player_cards(213).ans()<<std::endl;
//    cout << "team 24 points:" << cup2022->get_team_points(24).ans()<<std::endl;
//    cout << "3rd pointless ability" << cup2022->get_ith_pointless_ability(3).ans()<<std::endl;
//    cout << "spirit:" << cup2022->get_partial_spirit(213).ans()<<std::endl;
//    cup2022->remove_team(22);
//    cout << "3rd pointless ability" << cup2022->get_ith_pointless_ability(3).ans()<<std::endl;
//    cup2022->buy_team(25,24);
//    cout << "1st pointless ability" << cup2022->get_ith_pointless_ability(1).ans()<<std::endl;
//    cup2022->remove_team(23);
//    cup2022->print();
//    cup2022->remove_team(25);
//    cup2022->remove_team(24);
//    delete cup2022;
///*    cup2022->print();*/
//   return 0;
//}