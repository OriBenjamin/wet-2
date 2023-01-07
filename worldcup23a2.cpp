#include "worldcup23a2.h"

void world_cup_t::print()
{
    hashTable.print();
}

world_cup_t::world_cup_t(): teamsByID(), teamsByAbility(), hashTable()
{

}

world_cup_t::~world_cup_t()
{
    this->teamsByID.deleteTree(true);
    this->teamsByAbility.deleteTreeKeys();
}

StatusType world_cup_t::add_team(int teamId)
{
    if(teamId <=0)
    {
        return StatusType::INVALID_INPUT;
    }
    Team* team = new Team(teamId);
    try
    {
        teamsByID.insert(&team->getTeamIDByRef(), team);
        Pair<int,int>* abilityKey = new Pair<int,int>(team->getTeamAbilityByRef(), team->getTeamIDByRef());
        teamsByAbility.insert(abilityKey, team);
        return StatusType::SUCCESS;
    }
	catch(std::bad_alloc&)
    {
        delete team;
        return StatusType::ALLOCATION_ERROR;
    }
    catch(NodeAlreadyExist& e)
    {
        delete team;
        return StatusType::FAILURE;
    }
}

StatusType world_cup_t::remove_team(int teamId)
{
    try
    {
        if(teamId <=0)
        {
            return StatusType::INVALID_INPUT;
        }
        Team* team = teamsByID.find(&teamId);
        if(team->getTeamRoot() != nullptr) //team is not empty
        {
            team->getTeamRoot()->getPlayer()->setPlayerTeam(nullptr);
        }
        teamsByID.remove(&teamId);
        Pair<int,int>* abilityKey = new Pair<int,int>(team->getTeamAbilityByRef(), team->getTeamIDByRef());
        Team* removedTeam = teamsByAbility.removeWithKey(abilityKey);
        delete removedTeam;
        delete abilityKey;
        return StatusType::SUCCESS;
    }
    catch(NodeDoesNotExist& e)
    {
        return StatusType::FAILURE;
    }

}

StatusType world_cup_t::add_player(int playerId, int teamId,
                                   const permutation_t &spirit, int gamesPlayed,
                                   int ability, int cards, bool goalKeeper)
{
        if(playerId <= 0 || teamId <=0 || !(spirit.isvalid()) || gamesPlayed < 0 || cards < 0)
        {
            return StatusType::INVALID_INPUT;
        }
    Player* player;
    try
    {
        Team* team = teamsByID.find(&teamId);
        player = new Player(playerId, gamesPlayed, ability, cards, goalKeeper, team, spirit);
        std::shared_ptr<PlayerNode> playerNode = makeSet(std::move(std::unique_ptr<Player>(player)));
        hashTable.insert(playerId, playerNode);
        if(team->getTeamRoot() == nullptr)
        {
            team->getTeamRoot() = hashTable.search(playerId);
        }
        else
        {
           unionTeamNodes(hashTable.search(playerId),team->getTeamRoot()); //always first root (team) is merged to second root (team)
        }
        Pair<int,int>* teamToRemove = new Pair<int,int>(team->getTeamAbilityByRef(), team->getTeamIDByRef());
        teamsByAbility.removeWithKey(teamToRemove);
        delete teamToRemove;
        updateTeam(team, hashTable.search(playerId)->getPlayer()->getPlayerAbility(), hashTable.search(playerId)->getPlayer()->getPlayerGoalKeeper());
        Pair<int,int>* newAbilityKey = new Pair<int,int>(team->getTeamAbilityByRef(), team->getTeamIDByRef());
        teamsByAbility.insert(newAbilityKey, team);
        //delete player;
        //delete playerNode;
        return StatusType::SUCCESS;
    }
    catch(NodeDoesNotExist& e) //there is not such team
    {
        return StatusType::FAILURE;
    }
    catch(NodeAlreadyExistInHash& e) //player already exist
    {
        delete player;
        return StatusType::FAILURE;
    }
    catch(std::bad_alloc& e) //cant increase hashTable size
    {
        delete player;
        return StatusType::FAILURE;
    }
}

output_t<int> world_cup_t::play_match(int teamId1, int teamId2)
{
    try
    {
        if(teamId1 <= 0 || teamId2 <=0 || teamId1 == teamId2)
        {
            return output_t<int>(StatusType::INVALID_INPUT);
        }
        Team* team1 = teamsByID.find(&teamId1);
        Team* team2 = teamsByID.find(&teamId2);
        if(!(team1->getHasGoalKeeper() && team2->getHasGoalKeeper()))
        {
            return output_t<int>(StatusType::FAILURE);
        }

        team1->getTeamRoot()->getPlayer()->getPlayerGamesPlayedDistance()++;
        team2->getTeamRoot()->getPlayer()->getPlayerGamesPlayedDistance()++;

        if(team1->getPlayersAbilitySum() + team1->getTeamPoints() > team2->getPlayersAbilitySum() + team2->getTeamPoints())
        {
            team1->getTeamPoints() += 3;
            return output_t<int>(1);
        }
        else if(team1->getPlayersAbilitySum() + team1->getTeamPoints() < team2->getPlayersAbilitySum() + team2->getTeamPoints())
        {
            team2->getTeamPoints() += 3;
            return output_t<int>(3);
        }
        else
        {
            int team1Strength = team1->getTeamRoot()->getPlayer()->getTeamSpirit().strength();
            int team2Strength = team2->getTeamRoot()->getPlayer()->getTeamSpirit().strength();
            if(team1Strength > team2Strength)
            {
                team1->getTeamPoints() += 3;
                return output_t<int>(2);
            }
            else if(team1Strength < team2Strength)
            {
                team2->getTeamPoints() += 3;
                return output_t<int>(4);
            }
            else
            {
                team1->getTeamPoints()++;
                team2->getTeamPoints()++;
                return output_t<int>(0);
            }
        }
    }
    catch(NodeDoesNotExist&) //there is/are not such team/teams
    {
        return output_t<int>(StatusType::FAILURE);
    }
}

output_t<int> world_cup_t::num_played_games_for_player(int playerId)
{
    if(playerId <= 0)
    {
        return output_t<int>(StatusType::INVALID_INPUT);
    }
    std::shared_ptr<PlayerNode> playerNode = hashTable.search(playerId);
    if(playerNode == nullptr)
    {
        return output_t<int>(StatusType::FAILURE);
    }
    return output_t<int>(getGamesPlayed(playerNode));
}

StatusType world_cup_t::add_player_cards(int playerId, int cards)
{
	if(playerId <= 0 || cards < 0)
    {
        return StatusType::INVALID_INPUT;
    }
    std::shared_ptr<PlayerNode> playerNode = hashTable.search(playerId);
    if(playerNode == nullptr || findTeamNode(playerNode)->getPlayer()->getPlayerTeam() == nullptr)
    {
        return StatusType::FAILURE;
    }
    playerNode->getPlayer()->getPlayerCards() += cards;
    return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_player_cards(int playerId)
{
    if(playerId <= 0)
    {
        return StatusType::INVALID_INPUT;
    }
    std::shared_ptr<PlayerNode> playerNode = hashTable.search(playerId);
    if(playerNode == nullptr)
    {
        return StatusType::FAILURE;
    }
	return output_t<int>(playerNode->getPlayer()->getPlayerCards());
}

output_t<int> world_cup_t::get_team_points(int teamId)
{
    try
    {
        if(teamId <= 0)
        {
            return output_t<int>(StatusType::INVALID_INPUT);
        }
        Team* team = teamsByID.find(&teamId);
        return output_t<int>(team->getTeamPoints());
    }
    catch(NodeDoesNotExist&) //there is no such team
    {
        return output_t<int>(StatusType::FAILURE);
    }
}

output_t<int> world_cup_t::get_ith_pointless_ability(int i)
{
    try
    {
        if(i < 0 || i > teamsByID.getSize() || teamsByID.getSize() == 0)
        {
            return output_t<int>(StatusType::FAILURE);
        }
        // i+1 because starts with index 0
        Node<Pair<int,int>, Team>* node = teamsByAbility.findNodeByIndex(teamsByAbility.getRoot(), 0, i+1);
        return output_t<int>(node->getKey().getSecond());
    }
    catch(NodeDoesNotExist&) //there is no a team in that index. in fact, we cant reach this situation according to the check of i in the beginning of the function
    {
        return output_t<int>(StatusType::FAILURE);
    }
}

output_t<permutation_t> world_cup_t::get_partial_spirit(int playerId)
{
    if(playerId <= 0)
    {
        return output_t<permutation_t>(StatusType::INVALID_INPUT);
    }
    std::shared_ptr<PlayerNode> playerNode = hashTable.search(playerId);
    if(playerNode == nullptr || findTeamNode(playerNode)->getPlayer()->getPlayerTeam() == nullptr)
    {
        return output_t<permutation_t>(StatusType::FAILURE);
    }
    return output_t<permutation_t>(getPartialSpirit(playerNode));
}

StatusType world_cup_t::buy_team(int teamId1, int teamId2)
{
	try
    {
        if(teamId1 <=0 || teamId2 <= 0 || teamId1 == teamId2)
        {
            return StatusType::INVALID_INPUT;
        }
        Team* team1 = teamsByID.find(&teamId1);
        Team* team2 = teamsByID.find(&teamId2);
        std::shared_ptr<PlayerNode> teamNode1 = team1->getTeamRoot();
        std::shared_ptr<PlayerNode> teamNode2 = team2->getTeamRoot();
        if(teamNode1 != nullptr)
        {
            team1->getTeamRoot() = unionTeamNodes(teamNode2,teamNode1);
            team1->getTeamRoot()->getPlayer()->setPlayerTeam(team1);
        } else
        {
            team1->getTeamRoot() = teamNode2;
            if(teamNode2!=nullptr)
            {
                team1->getTeamRoot()->getPlayer()->setPlayerTeam(team1);
            }
        }
        team2->getTeamRoot() = nullptr;
        // update ability
        Pair<int,int>* teamToRemove = new Pair<int,int>(team1->getTeamAbilityByRef(), team1->getTeamIDByRef());
        teamsByAbility.removeWithKey(teamToRemove);
        delete teamToRemove;
        updateTeam(team1, team2->getPlayersAbilitySum(), team2->getHasGoalKeeper());
        Pair<int,int>* newAbilityKey = new Pair<int,int>(team1->getTeamAbilityByRef(), team1->getTeamIDByRef());
        teamsByAbility.insert(newAbilityKey, team1);
        team1->getTeamPoints() += team2->getTeamPoints();
        // remove team2
        remove_team(team2->getTeamId());
        return StatusType::SUCCESS;
    }
    catch(NodeDoesNotExist&) //there is/are no such team/teams
    {
        return StatusType::FAILURE;
    }
}
