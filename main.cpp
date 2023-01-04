//
// Created by oride on 31/12/2022.
//

#include "Player.h"
#include "Team.h"
#include "PlayerNode.h"
#include "Tree.h"
#include <iostream>

int main() {
    const int a1[5] = {2,1,0,3,4};
    std::shared_ptr<PlayerNode> player1 = makeSet(std::unique_ptr<Player>(
            new Player(123,0,5,2,false,permutation_t(a1))
    ));


    const int a2[5] = {3,1,0,2,4};
    std::shared_ptr<PlayerNode> player2 = makeSet(std::unique_ptr<Player>(
            new Player(246,0,5,2,true,permutation_t(a2))
    ));

    unionTeamNodes(player2, player1);

    const int a3[5] = {4,1,0,3,2};
    std::shared_ptr<PlayerNode> player3 = makeSet(std::unique_ptr<Player>(
            new Player(369,0,5,2,true,permutation_t(a3))
    ));

    unionTeamNodes(player3, player1);

    std::cout << "expected teamSpirit: " << permutation_t(a1)*permutation_t(a2)*permutation_t(a3) << std::endl;
    std::cout << "actual teamSpirit: " << player1->getPlayer()->getTeamSpirit() << std::endl;

    const int b1[5] = {3,4,2,1,0};
    std::shared_ptr<PlayerNode> playerb1 = makeSet(std::unique_ptr<Player>(
            new Player(423,0,5,2,false,permutation_t(b1))
    ));
    const int b2[5] = {0,1,2,3,4};
    std::shared_ptr<PlayerNode> playerb2 = makeSet(std::unique_ptr<Player>(
            new Player(546,0,5,2,true,permutation_t(b2))
    ));

    unionTeamNodes(playerb2, playerb1);

    const int b3[5] = {4,3,2,1,0};
    std::shared_ptr<PlayerNode> playerb3 = makeSet(std::unique_ptr<Player>(
            new Player(669,0,5,2,true,permutation_t(b3))
    ));

    unionTeamNodes(playerb3, playerb1);

    playerb1->getPlayer()->setGamesPlayedDistance(2);
    std::cout << "expected teamSpirit: " << permutation_t(b1)*permutation_t(b2)*permutation_t(b3) << std::endl;
    std::cout << "actual teamSpirit: " << playerb1->getPlayer()->getTeamSpirit() << std::endl;
    //b bought a
    unionTeamNodes(player1, playerb1);

    std::cout << "expected teamSpirit: " << permutation_t(b1)*permutation_t(b2)*permutation_t(b3)
                                            * permutation_t(a1)*permutation_t(a2)*permutation_t(a3) << std::endl;
    std::cout << "actual teamSpirit: " << playerb1->getPlayer()->getTeamSpirit() << std::endl;

    std::cout << "expected player1 partialSpirit: " << permutation_t(b1)*permutation_t(b2)*permutation_t(b3)
                                                       * permutation_t(a1)<< std::endl;
    std::cout << "actual player1 partialSpirit: " << getPartialSpirit(player1) << std::endl;


    std::cout << "expected player2 partialSpirit: " << permutation_t(b1)*permutation_t(b2)*permutation_t(b3)
                                                       * permutation_t(a1) *permutation_t(a2)<< std::endl;
    std::cout << "actual player2 partialSpirit: " << getPartialSpirit(player2) << std::endl;

    std::cout << "expected playerb2 partialSpirit: " << permutation_t(b1)*permutation_t(b2)<< std::endl;
    std::cout << "actual playerb2 partialSpirit: " << getPartialSpirit(playerb2) << std::endl;

    std::cout << "expected playerb1 partialSpirit: " << permutation_t(b1)<< std::endl;
    std::cout << "actual playerb1 partialSpirit: " << getPartialSpirit(playerb1) << std::endl;

    std::cout << "expected gamesPlayed: " << 0<< std::endl;
    std::cout << "actual gamedPlayed: " << getGamesPlayed(player1) << std::endl;

    Tree<int, int> tree1;
    int a = 1, b=2, c=3, d=4, e=5;
    tree1.insert(&b,&b);
    tree1.insert(&a,&a);
    tree1.insert(&c,&c);
    tree1.insert(&e,&e);
    tree1.insert(&d,&d);
    tree1.remove(&b);
    tree1.remove(&e);
    tree1.insert(&e,&e);
    // a c d e
    std::cout << *tree1.findByIndex(4);
}