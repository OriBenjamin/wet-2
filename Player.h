//
// Created by oride on 30/12/2022.
//

#ifndef WET_2_PLAYER_H
#define WET_2_PLAYER_H

class Team;

#include "wet2util.h"
#include "Team.h"
#include <memory>

class Player
{
    private:
    int playerID, gamesPlayedDistance, ability, cards, goalKeeper;
    Team* team;
    permutation_t teamSpirit;
    permutation_t partialSpirit;

    public:
    Player(int playerId, int gamesPlayedDistance, int ability, int cards, int goalKeeper, Team* team, const permutation_t &spirit):
    playerID(playerId), gamesPlayedDistance(gamesPlayedDistance), ability(ability), cards(cards),
    goalKeeper(goalKeeper), team(team), teamSpirit(spirit), partialSpirit(spirit) {}
    Player(const Player&) = default;

    //const getters
    const permutation_t& getPlayerPartialSpirit() const
    {
        return partialSpirit;
    }

    const permutation_t& getTeamSpirit() const
    {
        return teamSpirit;
    }


    int getPlayerGamesPlayedDistance() const
    {
        return this->gamesPlayedDistance;
    }

    int getPlayerID() const
    {
        return this->playerID;
    }


    int getPlayerAbility() const
    {
        return ability;
    }

    int getPlayerCards() const
    {
        return cards;
    }

    int getPlayerGoalKeeper() const
    {
        return goalKeeper;
    }

    Team* getPlayerTeam() const
    {
        return team;
    }

    //getters

    int& getPlayerGamesPlayedDistance()
    {
        return this->gamesPlayedDistance;
    }
    int& getPlayerCards()
    {
        return cards;
    }

    //setters
    void setGamesPlayedDistance(int gamesPlayedDistance)
    {
        Player::gamesPlayedDistance = gamesPlayedDistance;
    }

    void setTeamSpirit(const permutation_t &teamSpirit)
    {
        Player::teamSpirit = teamSpirit;
    }

    void setPartialSpirit(const permutation_t &partialSpirit)
    {
        this->partialSpirit = partialSpirit;
    }

    void setPlayerTeam(Team* team)
    {
        this->team = team;
    }


};

#endif //WET_2_PLAYER_H
