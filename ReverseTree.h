//
// Created by liels on 30/12/2022.
//

#ifndef WET2_REVERSETREE_H
#define WET2_REVERSETREE_H

#include "ReverseNode.h"

template<class Value>
class ReverseTree
{
    private:
    ReverseNode<Value> root;

    public:
    ReverseTree() = default;
    ReverseTree(const ReverseNode<Value>& root): root(root) {}
    ReverseTree(const ReverseTree<Value>&) = delete;
    ~ReverseTree() = default;

    //const getters
    const ReverseNode<Value>& getRoot() const
    {
        return root;
    }

    //getters
    ReverseNode<Value>& getRoot()
    {
        return root;
    }
};

template<class Value>
std::shared_ptr<ReverseNode<Value>> makeSetOfReverseNodes(const ReverseNode<Value>& node)
{
    return new ReverseTree(node);
}

template<class Value>
std::shared_ptr<ReverseNode<Value>>& unionSetOfReverseNodes(const std::shared_ptr<ReverseNode<Value>>& root1, const std::shared_ptr<ReverseNode<Value>>& root2)
{
    if(root1->getTreeSize() >= root2->getTreeSize())
    {
        root2->getParent() = root1;
        root1->getTreeSize() += root2->getTreeSize();
        return root1;
    }
    else
    {
        root1->getParent() = root2;
        root2->getTreeSize() += root1->getTreeSize();
        return root2;
    }
}

template<class Value>
std::shared_ptr<ReverseNode<Value>>& findRoot(const std::shared_ptr<ReverseNode<Value>>& node, const std::shared_ptr<ReverseNode<Value>>& originalNode = node)
{
    if(node->getParent() == nullptr)
    {
        updatePathAfterFindRoot(originalNode, node);
        return node;
    }
    findRoot(node->getParent(), originalNode);
}

template<class Value>
void updatePathAfterFindRoot(const std::shared_ptr<ReverseNode<Value>>& node, const std::shared_ptr<ReverseNode<Value>>& root)
{
    if(node->getParent() == nullptr)
    {
        return;
    }
    std::shared_ptr<ReverseNode<Value>> oldParent = node->getParent();
    node->getParent() == root;
    updatePathAfterFindRoot(oldParent, root);
}


#endif //WET2_REVERSETREE_H
