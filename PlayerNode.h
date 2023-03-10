//
// Created by oride on 31/12/2022.
//

#ifndef WET_2_PLAYERNODE_H
#define WET_2_PLAYERNODE_H

#include <memory>
#include <ostream>
#include "Player.h"

class PlayerNode
{
private:
    std::unique_ptr<Player> player;
    std::shared_ptr<PlayerNode> parent;
    int treeSize;

public:
    PlayerNode() = delete;
    explicit PlayerNode(std::unique_ptr<Player> player):
            player(std::move(player)), parent(nullptr), treeSize(1) {}
    PlayerNode(PlayerNode& node): player(std::move(node.player)), parent(node.parent), treeSize(node.treeSize) {}

    ~PlayerNode() = default;

    //const getters
    const std::unique_ptr<Player>& getPlayer() const
    {
        return player;
    }

    const std::shared_ptr<PlayerNode> &getParent() const
    {
        return parent;
    }

    bool hasParent() const
    {
        return this->getParent() != nullptr;
    }


    void setPlayer(std::unique_ptr<Player> player)
    {
        this->player = std::move(player);
    }

    int getTreeSize() const
    {
        return treeSize;
    }

    //getters
    std::unique_ptr<Player>& getPlayer()
    {
        return player;
    }

    //setters
    void setParent(std::shared_ptr<PlayerNode> parent)
    {
        this->parent = parent;
    }


    void setTreeSize(int treeSize)
    {
        PlayerNode::treeSize = treeSize;
    }


};


#endif //WET_2_PLAYERNODE_H
