//
// Created by oride on 31/12/2022.
//

#include "Team.h"
#include "PlayerNode.h"

PlayerNode* makeSet(std::unique_ptr<Player> player)
{
    return new PlayerNode(std::move(player));
}

//team1 joins team2!=nullptr
std::shared_ptr<PlayerNode> unionTeamNodes(std::shared_ptr<PlayerNode> teamNode1, std::shared_ptr<PlayerNode> teamNode2)
{
    //update ptr to team and team spirit's fields
    if(teamNode1 == nullptr) return teamNode2;
    if(teamNode1->getTreeSize() > teamNode2->getTreeSize())
    {
        teamNode2->setParent(teamNode1);
        teamNode1->setTreeSize(teamNode2->getTreeSize()+teamNode1->getTreeSize());
        teamNode2->setTreeSize(1);
        teamNode1->getPlayer()->setGamesPlayedDistance(teamNode1->getPlayer()->getPlayerGamesPlayedDistance() - teamNode2->getPlayer()->getPlayerGamesPlayedDistance());
        // ps1 = ts2 * ps1
        teamNode1->getPlayer()->setPartialSpirit(teamNode2->getPlayer()->getTeamSpirit() * teamNode1->getPlayer()->getPlayerPartialSpirit());
        // ps2 = (ps1)^-1 * ps2
        teamNode2->getPlayer()->setPartialSpirit(teamNode1->getPlayer()->getPlayerPartialSpirit().inv() * teamNode2->getPlayer()->getPlayerPartialSpirit());
        // ts1 = ts2 * ts1
        teamNode1->getPlayer()->setTeamSpirit(teamNode2->getPlayer()->getTeamSpirit() * teamNode1->getPlayer()->getTeamSpirit());
        return teamNode1; //returns new root
    }
    else //if team1 is smaller or in default
    {
        teamNode1->setParent(teamNode2);
        teamNode2->setTreeSize(teamNode2->getTreeSize()+teamNode1->getTreeSize());
        teamNode1->setTreeSize(1);
        teamNode1->getPlayer()->setGamesPlayedDistance(teamNode1->getPlayer()->getPlayerGamesPlayedDistance() - teamNode2->getPlayer()->getPlayerGamesPlayedDistance());
        // ps1 =  (ps2)^-1 * ts2 * ps1
        teamNode1->getPlayer()->setPartialSpirit((teamNode2->getPlayer()->getPlayerPartialSpirit()).inv() * teamNode2->getPlayer()->getTeamSpirit() * teamNode1->getPlayer()->getPlayerPartialSpirit());
        // ts2 = ts2 * ts1
        teamNode2->getPlayer()->setTeamSpirit(teamNode2->getPlayer()->getTeamSpirit() * teamNode1->getPlayer()->getTeamSpirit());
        return teamNode2; //returns new root
    }
}

std::shared_ptr<PlayerNode> findTeamNode(std::shared_ptr<PlayerNode> playerNode)
{
    std::shared_ptr<PlayerNode> teamNode = playerNode;
    int gamesPlayed = 0;
    permutation_t partialSpirit = permutation_t::neutral();
    while(teamNode->hasParent())
    {
        partialSpirit = teamNode->getPlayer()->getPlayerPartialSpirit() * partialSpirit;
        gamesPlayed = teamNode->getPlayer()->getPlayerGamesPlayedDistance() + gamesPlayed;
        teamNode = teamNode->getParent();
    }
    partialSpirit = teamNode->getPlayer()->getPlayerPartialSpirit() * partialSpirit;
    gamesPlayed = teamNode->getPlayer()->getPlayerGamesPlayedDistance() + gamesPlayed;
    // shrink paths
    std::shared_ptr<PlayerNode> tempParent;
    permutation_t oldPartialSpirit;
    int oldGamesPlayed;
    while(playerNode->hasParent())
    {
        tempParent = playerNode->getParent();
        oldPartialSpirit = playerNode->getPlayer()->getPlayerPartialSpirit();
        oldGamesPlayed = playerNode->getPlayer()->getPlayerGamesPlayedDistance();
        playerNode->setParent(teamNode);
        playerNode->getPlayer()->setPartialSpirit((teamNode->getPlayer()->getPlayerPartialSpirit()).inv()*partialSpirit);
        playerNode->getPlayer()->setGamesPlayedDistance(gamesPlayed - teamNode->getPlayer()->getPlayerGamesPlayedDistance());
        partialSpirit = partialSpirit * oldPartialSpirit.inv();
        gamesPlayed = gamesPlayed - oldGamesPlayed;
        playerNode = playerNode->getParent();
    }
    return teamNode;
}

int getGamesPlayed(std::shared_ptr<PlayerNode> playerNode)
{
    if(!playerNode->hasParent()) return playerNode->getPlayer()->getPlayerGamesPlayedDistance();
    std::shared_ptr<PlayerNode> teamNode = findTeamNode(playerNode);
    return  teamNode->getPlayer()->getPlayerGamesPlayedDistance() + playerNode->getPlayer()->getPlayerGamesPlayedDistance();
}

permutation_t getPartialSpirit(std::shared_ptr<PlayerNode> playerNode)
{
    if(!playerNode->hasParent()) return playerNode->getPlayer()->getPlayerPartialSpirit();
    std::shared_ptr<PlayerNode> teamNode = findTeamNode(playerNode);
    return teamNode->getPlayer()->getPlayerPartialSpirit() * playerNode->getPlayer()->getPlayerPartialSpirit();
}

void updateTeam(Team* team, int extraAbility, bool extraGoalKeeper)
{
    if(team->getHasGoalKeeper() == false && extraGoalKeeper)
    {
        team->getHasGoalKeeper() = true;
    }
    team->getTeamAbilityByRef() += extraAbility;
}