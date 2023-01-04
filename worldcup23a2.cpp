//#include "worldcup23a2.h"
//
//world_cup_t::world_cup_t()
//{
//	// TODO: Your code goes here
//}
//
//world_cup_t::~world_cup_t()
//{
//	// TODO: Your code goes here
//}
//
//StatusType world_cup_t::add_team(int teamId)
//{
//	Team* team = new Team(teamId);
//    teamsByID.insert(&team->getTeamIDByRef(), team);
//    teamsByAbility.insert(&team->getTeamAbilityByRef(), team);
//    return StatusType::SUCCESS;
//}
//
//StatusType world_cup_t::remove_team(int teamId)
//{
//    Team* team = teamsByID.find(&teamId);
//    teamsByID.remove(&teamId);
//    teamsByAbility.remove(&team->getTeamAbilityByRef());
//	return StatusType::FAILURE;
//}
//
//StatusType world_cup_t::add_player(int playerId, int teamId,
//                                   const permutation_t &spirit, int gamesPlayed,
//                                   int ability, int cards, bool goalKeeper)
//{
//    Team* team = teamsByID.find(&teamId);
//    //remove team
//    std::shared_ptr<PlayerNode> playerNode = makeSet(std::unique_ptr<Player>(
//                new Player(playerId,0,ability,cards,goalKeeper,spirit)
//                 ));
//	hashTable.insert(playerNode);
//    if(team->getTeamRoot()== nullptr)
//    {
//        team->setTeamRoot(playerNode);
//        playerNode->getPlayer()->setTeam(team);
//    } else {
//        unionTeamNodes(playerNode,team->getTeamRoot());
//    }
//    //insert team
//    return StatusType::SUCCESS;
//}
//
//output_t<int> world_cup_t::play_match(int teamId1, int teamId2)
//{
//	// TODO: Your code goes here
//	return StatusType::SUCCESS;
//}
//
//output_t<int> world_cup_t::num_played_games_for_player(int playerId)
//{
//	// TODO: Your code goes here
//	return 22;
//}
//
//StatusType world_cup_t::add_player_cards(int playerId, int cards)
//{
//	// TODO: Your code goes here
//	return StatusType::SUCCESS;
//}
//
//output_t<int> world_cup_t::get_player_cards(int playerId)
//{
//	// TODO: Your code goes here
//	return StatusType::SUCCESS;
//}
//
//output_t<int> world_cup_t::get_team_points(int teamId)
//{
//	// TODO: Your code goes here
//	return 30003;
//}
//
//output_t<int> world_cup_t::get_ith_pointless_ability(int i)
//{
//	// TODO: Your code goes here
//	return 12345;
//}
//
//output_t<permutation_t> world_cup_t::get_partial_spirit(int playerId)
//{
//	// TODO: Your code goes here
//	return permutation_t();
//}
//
//StatusType world_cup_t::buy_team(int teamId1, int teamId2)
//{
//	// TODO: Your code goes here
//	return StatusType::SUCCESS;
//}
