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

class Team {

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

    int &getTeamIDByRef() {
        return teamID;
    };
    int &getTeamAbilityByRef() {
        return playersAbilitySum;
    };
    const std::shared_ptr<PlayerNode> &getTeamRoot() const {
        return teamRoot;
    }

    void setTeamRoot(const std::shared_ptr<PlayerNode> &teamRoot) {
        //edit fields
        this->teamRoot = teamRoot;
    }
};

std::shared_ptr<PlayerNode> makeSet(std::unique_ptr<Player> player);
std::shared_ptr<PlayerNode> unionTeamNodes(std::shared_ptr<PlayerNode> teamNode1, std::shared_ptr<PlayerNode> teamNode2);
std::shared_ptr<PlayerNode> findTeamNode(std::shared_ptr<PlayerNode> playerNode);
int getGamesPlayed(std::shared_ptr<PlayerNode> playerNode);
permutation_t getPartialSpirit(std::shared_ptr<PlayerNode> playerNode);

#endif //WET_2_TEAM_H
