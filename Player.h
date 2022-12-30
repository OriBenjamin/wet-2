//
// Created by oride on 30/12/2022.
//

#ifndef WET_2_PLAYER_H
#define WET_2_PLAYER_H
#include "wet2util.h"
#include <memory>

class Player{

private:
    int playerID, gamesPlayedDistance, ability, cards, goalKeeper;
    std::weak_ptr<Team> team;
    permutation_t partialSpirit;

public:
    Player(int playerId, int gamesPlayedDistance, int ability, int cards, int goalKeeper,
           const permutation_t &partialSpirit) : playerID(playerId), gamesPlayedDistance(gamesPlayedDistance),
                                                 ability(ability), cards(cards), goalKeeper(goalKeeper),
                                                 team(nullptr), partialSpirit(permutation_t()) {}

};
#endif //WET_2_PLAYER_H
