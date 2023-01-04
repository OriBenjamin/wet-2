//
// Created by oride on 31/12/2022.
//

#ifndef WET_2_PLAYERNODE_H
#define WET_2_PLAYERNODE_H

#include <memory>
#include "Player.h"

class PlayerNode
{

public:
    PlayerNode() = delete;
    PlayerNode(std::unique_ptr<Player> player):
            player(std::move(player)), parent(nullptr), treeSize(1) {}
    PlayerNode(PlayerNode& node): player(std::move(node.player)), parent(node.parent), treeSize(node.treeSize) {}

    ~PlayerNode() = default;

    //const getters

    const std::unique_ptr<Player> &getPlayer() const {
        return player;
    }

    void setPlayer(std::unique_ptr<Player> player) {
        this->player = std::move(player);
    }

    const std::shared_ptr<PlayerNode> &getParent() const {
        return parent;
    }

    bool hasParent() const {
        return this->getParent() != nullptr;
    }

    void setParent(std::shared_ptr<PlayerNode> parent) {
        this->parent = parent;
    }

    int getTreeSize() const {
        return treeSize;
    }

    void setTreeSize(int treeSize) {
        PlayerNode::treeSize = treeSize;
    }

private:
    std::unique_ptr<Player> player;
    std::shared_ptr<PlayerNode> parent;
    int treeSize;

};

////operators

//bool operator==(const PlayerNode& node1, const PlayerNode& node2)
//{
//    return *node1.getPlayer() == *node2.getPlayer();
//}

//template<class Value>
//bool operator!=(const ReverseNode<Value>& node1, const ReverseNode<Value>& node2)
//{
//    return !(node1 == node2);
//}

#endif //WET_2_PLAYERNODE_H
