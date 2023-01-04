//
// Created by oride on 31/12/2022.
//

#include "Team.h"
#include "PlayerNode.h"

std::shared_ptr<PlayerNode> makeSet(std::unique_ptr<Player> player)
{
    return std::make_shared<PlayerNode>(*(new PlayerNode(std::move(player))));
}

//team1 joins team2
std::shared_ptr<PlayerNode> unionTeamNodes(std::shared_ptr<PlayerNode> teamNode1, std::shared_ptr<PlayerNode> teamNode2)
{
    //update ptr to team and team fields
    if(teamNode1->getTreeSize() > teamNode2->getTreeSize())
    {
        teamNode2->setParent(teamNode1);
        teamNode1->setTreeSize(teamNode2->getTreeSize()+teamNode1->getTreeSize());
        teamNode2->setTreeSize(1);
        teamNode1->getPlayer()->setGamesPlayedDistance(teamNode1->getPlayer()->getGamesPlayedDistance() - teamNode2->getPlayer()->getGamesPlayedDistance());
        // ps1 = ts2 * ps1
        teamNode1->getPlayer()->setPartialSpirit(teamNode2->getPlayer()->getTeamSpirit() * teamNode1->getPlayer()->getPartialSpirit());
        // ps2 = (ps1)^-1 * ps2
        teamNode2->getPlayer()->setPartialSpirit(teamNode1->getPlayer()->getPartialSpirit().inv() * teamNode2->getPlayer()->getPartialSpirit());
        // ts1 = ts2 * ts1
        teamNode1->getPlayer()->setTeamSpirit(teamNode2->getPlayer()->getTeamSpirit() * teamNode1->getPlayer()->getTeamSpirit());
        return teamNode1; //returns new root
    } else //if team1 is smaller or in default
    {
        teamNode1->setParent(teamNode2);
        teamNode2->setTreeSize(teamNode2->getTreeSize()+teamNode1->getTreeSize());
        teamNode1->setTreeSize(1);
        teamNode1->getPlayer()->setGamesPlayedDistance(teamNode1->getPlayer()->getGamesPlayedDistance() - teamNode2->getPlayer()->getGamesPlayedDistance());
        // ps1 =  (ps2)^-1 * ts2 * ps1
        teamNode1->getPlayer()->setPartialSpirit((teamNode2->getPlayer()->getPartialSpirit()).inv() * teamNode2->getPlayer()->getTeamSpirit() * teamNode1->getPlayer()->getPartialSpirit());
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
        partialSpirit = teamNode->getPlayer()->getPartialSpirit() * partialSpirit;
        gamesPlayed = teamNode->getPlayer()->getGamesPlayedDistance() + gamesPlayed;
        teamNode = teamNode->getParent();
    }
    partialSpirit = teamNode->getPlayer()->getPartialSpirit() * partialSpirit;
    gamesPlayed = teamNode->getPlayer()->getGamesPlayedDistance() + gamesPlayed;
    // shrink paths
    std::shared_ptr<PlayerNode> tempParent;
    permutation_t oldPartialSpirit;
    int oldGamesPlayed;
    while(playerNode->hasParent())
    {
        tempParent = playerNode->getParent();
        oldPartialSpirit = playerNode->getPlayer()->getPartialSpirit();
        oldGamesPlayed = playerNode->getPlayer()->getGamesPlayedDistance();
        playerNode->setParent(teamNode);
        playerNode->getPlayer()->setPartialSpirit((teamNode->getPlayer()->getPartialSpirit()).inv()*partialSpirit);
        playerNode->getPlayer()->setGamesPlayedDistance(gamesPlayed - teamNode->getPlayer()->getGamesPlayedDistance());
        partialSpirit = partialSpirit * oldPartialSpirit.inv();
        gamesPlayed = gamesPlayed -= oldGamesPlayed;

        playerNode = playerNode->getParent();
    }
    return teamNode;
}

int getGamesPlayed(std::shared_ptr<PlayerNode> playerNode)
{
    if(!playerNode->hasParent()) return playerNode->getPlayer()->getGamesPlayedDistance();
    std::shared_ptr<PlayerNode> teamNode = findTeamNode(playerNode);
    return  teamNode->getPlayer()->getGamesPlayedDistance() + playerNode->getPlayer()->getGamesPlayedDistance();
}

permutation_t getPartialSpirit(std::shared_ptr<PlayerNode> playerNode)
{
    if(!playerNode->hasParent()) return playerNode->getPlayer()->getPartialSpirit();
    std::shared_ptr<PlayerNode> teamNode = findTeamNode(playerNode);
    return teamNode->getPlayer()->getPartialSpirit() * playerNode->getPlayer()->getPartialSpirit();
}