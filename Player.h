//
// Created by oride on 30/12/2022.
//

#ifndef WET_2_PLAYER_H
#define WET_2_PLAYER_H

class Team;

#include "wet2util.h"
#include "Team.h"
#include <memory>

class Player{

public:
    Player(int playerId, int gamesPlayedDistance, int ability, int cards, int goalKeeper,
           const permutation_t &spirit) : playerID(playerId), gamesPlayedDistance(gamesPlayedDistance),
                                                 ability(ability), cards(cards), goalKeeper(goalKeeper),
                                                 team(nullptr), teamSpirit(spirit), partialSpirit(spirit) {}
    Player(const Player&) = default;

    const permutation_t &getPartialSpirit() const {
        return partialSpirit;
    }

    const permutation_t &getTeamSpirit() const {
        return teamSpirit;
    }

    void setGamesPlayedDistance(int gamesPlayedDistance) {
        this->gamesPlayedDistance = gamesPlayedDistance;
    }

    int getGamesPlayedDistance() const {
        return this->gamesPlayedDistance;
    }

    int getPlayerID() const {
        return this->playerID;
    }

    // setters

    void setTeam(Team* team) {
        this->team = team;
    }

    void setTeamSpirit(const permutation_t &teamSpirit) {
        this->teamSpirit = teamSpirit;
    }

    void setPartialSpirit(const permutation_t &partialSpirit) {
        this->partialSpirit = partialSpirit;
    }

private:
    int playerID, gamesPlayedDistance, ability, cards, goalKeeper;
    Team* team;
    permutation_t teamSpirit;
    permutation_t partialSpirit;
};

//bool operator==(const Player& player1, const Player& player2)
//{
//    return player1.getPlayerID() == player2.getPlayerID();
//}

#endif //WET_2_PLAYER_H
