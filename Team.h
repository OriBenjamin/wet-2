//
// Created by oride on 31/12/2022.
//

#ifndef WET_2_TEAM_H
#define WET_2_TEAM_H

class PlayerNode;
class Player;

#include "wet2util.h"
#include <memory>
#include "Player.h"

class Team
{

    private:
    int teamID, points, playersAbilitySum;
    bool hasGoalKeeper;
    std::shared_ptr<PlayerNode> teamRoot;

    public:
    Team() = delete;
    Team(int teamID):
    teamID(teamID), points(0), playersAbilitySum(0),
    hasGoalKeeper(false), teamRoot(nullptr) {}
    Team(const Team&) = delete;
    ~Team() = default;

    //const getters
    const std::shared_ptr<PlayerNode>& getTeamRoot() const
    {
        return teamRoot;
    }
    int getTeamId() const
    {
        return teamID;
    }
    int getTeamPoints() const
    {
        return points;
    }
    int getPlayersAbilitySum() const
    {
        return playersAbilitySum;
    }
    bool getHasGoalKeeper() const
    {
        return hasGoalKeeper;
    }

    //getters
    int& getTeamIDByRef()
    {
        return teamID;
    };
    int& getTeamAbilityByRef()
    {
        return playersAbilitySum;
    };
    std::shared_ptr<PlayerNode>& getTeamRoot()
    {
        return teamRoot;
    }

    int& getTeamPoints()
    {
        return points;
    }

    bool& getHasGoalKeeper()
    {
        return hasGoalKeeper;
    }



};

std::shared_ptr<PlayerNode> makeSet(std::unique_ptr<Player> player);
std::shared_ptr<PlayerNode> unionTeamNodes(std::shared_ptr<PlayerNode> teamNode1, std::shared_ptr<PlayerNode> teamNode2);
std::shared_ptr<PlayerNode> findTeamNode(std::shared_ptr<PlayerNode> playerNode);
int getGamesPlayed(std::shared_ptr<PlayerNode> playerNode);
permutation_t getPartialSpirit(std::shared_ptr<PlayerNode> playerNode);
void updateTeam(Team* team, int extraAbility, bool extraGoalKeeper);

#endif //WET_2_TEAM_H
