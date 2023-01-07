//
// Created by liels on 28/11/2022.
//

#ifndef HW1_TREE_H
#define HW1_TREE_H

#include <stdlib.h>
#include <string>
#include "Node.h"
#include <iostream>
#include <stdexcept>

class NodeAlreadyExist : public std::exception
{
public:
    const char* what() const noexcept override {return "Node already exist in this tree";}
};
class NodeDoesNotExist : public std::exception
{
public:
    const char* what() const noexcept override {return "Node does not exist in this tree";}
};
class OnlyOneNodeInTree : public std::exception
{
public:
    const char* what() const noexcept override {return "There is only one node in this tree";}
};

template<class Key, class Value>
class Tree
{
    Node<Key,Value>* root;
    int size;

public:
    Tree():
            root(NULL), size(0) {}

    Tree(Node<Key,Value>* root, int size):
            root(root), size(size) {}

    Tree(const Tree<Key,Value>& tree) = default;

    //destructors
    ~Tree();
    void deleteTree(bool deleteValues);
    void deleteTreeNodes(Node<Key,Value>* node, bool deleteValues, bool deleteKeys);
    void deleteTreeWithKeys();

    //operators
    Tree& operator=(const Tree& t) = default;

    //const getters
    Node<Key, Value> *getRoot() const {return root;}
    int getSize() const {return size;}

    //setters
    void setRoot(Node<Key, Value> *root) {
        Tree::root = root;
    }

    //built-in functions
    Node<Key,Value>* insertNode(Node<Key,Value>* currentNode,Node<Key,Value>* nodeForInsertion);
    void insert(Key* key, Value* value);
    Node<Key, Value> *getRotated(Node<Key, Value> *currentNode, int rightChildBalanceFactor,
                                 int leftChildBalanceFactor, int balanceFactor);

    Value* removeWithKey(Key* key);
    Value* remove(Key* key);
    Node<Key,Value>* removeNode(Node<Key,Value>* currentNode, Key* key);
    void balanceTree(Node<Key, Value>* currentNode);

    Value* find(Key* key) const;
    Node<Key,Value>* findNode(Node<Key,Value>* currentNode, Key* key) const;
    bool exists(Key* key) const;
    Value* findByIndex(int index) const;
    Node<Key,Value>* findNodeByIndex(Node<Key,Value>* currentNode, int previousIndex, int index) const;
    int getBalanceFactor(const Node<Key,Value>* node) const;
    void connectSonParent(Node<Key, Value> *currentNode,Node<Key, Value> *son);
};

template<class Key, class Value>
Tree<Key,Value>::~Tree()
{
    deleteTree(false);
}

template<class Key, class Value>
void Tree<Key,Value>::deleteTree(bool deleteValues)
{
    deleteTreeNodes(root, deleteValues, false);
    root = nullptr;
}

template<class Key, class Value>
void Tree<Key,Value>::deleteTreeWithKeys()
{
    deleteTreeNodes(root, true, true);
    root = nullptr;
}

template<class Key, class Value>
void Tree<Key,Value>::deleteTreeNodes(Node<Key,Value>* node, bool deleteValues, bool deleteKeys)
{
    if(!node) return;
    if(node->right)
    {
        deleteTreeNodes(node->right, deleteValues,deleteKeys);
        node->right = nullptr;
    }
    if(node->left)
    {
        deleteTreeNodes(node->left, deleteValues,deleteKeys);
        node->left = nullptr;
    }

    if(deleteValues)
    {
        delete node->value;
        node->value = nullptr;
    }

    if(deleteKeys)
    {
        delete node->key;
        node->key = nullptr;
    }
    delete node;
    node = nullptr;
}

template<class Key, class Value>
void updateHeight(Node<Key,Value>* node)
{
    if(node != nullptr)
    {
        int leftHeight = (node->left) ? node->left->height : -1;
        int rightHeight = (node->right) ? node->right->height : -1;
        node->height = (leftHeight >= rightHeight) ? (leftHeight + 1) : (rightHeight + 1);
        int leftSubTreeSize = (node->left) ? node->left->subTreeSize : 0;
        int rightSubTreeSize = (node->right) ? node->right->subTreeSize : 0;
        node->subTreeSize = leftSubTreeSize + rightSubTreeSize + 1;
    }
}

template<class Key, class Value>
void Tree<Key,Value>::insert(Key* key, Value* value)
{
    if(value == nullptr)
    {
        throw std::invalid_argument("invalid argument- cant insert an empty node");
    }
    Node<Key, Value> *nodeForInsertion = new Node<Key, Value>(key, value);
    root = insertNode(root, nodeForInsertion);
    balanceTree(nodeForInsertion);
    if(nodeForInsertion->next)
    {
        nodeForInsertion->next->prev = nodeForInsertion;
    }
    if(nodeForInsertion->prev)
    {
        nodeForInsertion->prev->next = nodeForInsertion;
    }
    this->size++;
}

template<class Key, class Value>
Node<Key,Value>* Tree<Key,Value>::insertNode(Node<Key,Value>* currentNode, Node<Key,Value>* nodeForInsertion)
{
    if(currentNode == nullptr)
    {
        return nodeForInsertion;
    }
    if(*nodeForInsertion->key == *currentNode->key)
    {
        throw NodeAlreadyExist();
    }
    else if(*nodeForInsertion->key < *currentNode->key)
    {
        if(!nodeForInsertion->next || *nodeForInsertion->next->key > *currentNode->key)
        {
            nodeForInsertion->next = currentNode;
        }
        currentNode->left = insertNode(currentNode->left, nodeForInsertion);
        currentNode->left->parent = currentNode;
    }
    else
    {
        if(!nodeForInsertion->prev || *nodeForInsertion->prev->key < *currentNode->key)
        {
            nodeForInsertion->prev = currentNode;
        }
        currentNode->right = insertNode(currentNode->right, nodeForInsertion);
        currentNode->right->parent = currentNode;
    }

    return currentNode;
}

template<class Key, class Value>
int Tree<Key,Value>::getBalanceFactor(const Node<Key,Value>* node) const
{
    if (node == nullptr) return 0;
    int leftHeight = (node->left) ? node->left->height : -1;
    int rightHeight = (node->right) ? node->right->height : -1;
    return leftHeight - rightHeight;
}

template<class Key, class Value>
Node<Key, Value> * Tree<Key, Value>::getRotated(Node<Key, Value> *currentNode, int rightChildBalanceFactor, int leftChildBalanceFactor,
                                                int balanceFactor)
{
    if(balanceFactor == 2 && leftChildBalanceFactor >= 0)
    {
        Node<Key,Value>* A = currentNode;
        Node<Key,Value>* Al = currentNode->left;
        Node<Key,Value>* Alr = currentNode->left->right; //can be null
        if(Alr) Alr->parent = A;
        Al->parent = A->parent;
        Al->right = A;
        A->parent = Al;
        A->left = Alr;
        if(Al->parent) {
            if(Al->parent->right == A)
            {
                Al->parent->right = Al;
            } else
            {
                Al->parent->left = Al;
            }
        }
        updateHeight(Alr);
        updateHeight(A);
        updateHeight(Al);
        return Al;
    }
    if(balanceFactor==2 && leftChildBalanceFactor==-1)
    {
        Node<Key,Value>* A = currentNode;
        Node<Key,Value>* Al = currentNode->left;
        Node<Key,Value>* Alr = currentNode->left->right;
        Node<Key,Value>* Alrr = currentNode->left->right->right; //can be null
        Node<Key,Value>* Alrl = currentNode->left->right->left; //can be null
        if(Alrr) Alrr->parent = A;
        Alr->parent = A->parent;
        A->parent = Alr;
        if(Alrl) Alrl->parent = Al;
        A->left = Alrr;
        Al->right = Alrl;
        Al->parent = Alr;
        Alr->left = Al;
        Alr->right = A;
        if(Alr->parent) {
            if(Alr->parent->right == A)
            {
                Alr->parent->right = Alr;
            } else
            {
                Alr->parent->left = Alr;
            }
        }
        updateHeight(Alrr);
        updateHeight(Alrl);
        updateHeight(A);
        updateHeight(Al);
        updateHeight(Alr);
        return Alr;
    }
    else if(balanceFactor==-2 && rightChildBalanceFactor<=0)
    {
        Node<Key,Value>* A = currentNode;
        Node<Key,Value>* Ar = currentNode->right;
        Node<Key,Value>* Arl = currentNode->right->left; //can be null
        if(Arl) Arl->parent = A;
        Ar->parent = A->parent;
        Ar->left = A;
        A->parent = Ar;
        A->right = Arl;
        if(Ar->parent) {
            if(Ar->parent->right == A)
            {
                Ar->parent->right = Ar;
            } else
            {
                Ar->parent->left = Ar;
            }
        }
        updateHeight(A);
        updateHeight(Arl);
        updateHeight(Ar);
        return Ar;
    }
    else if(balanceFactor==-2 && rightChildBalanceFactor==1)
    {
        Node<Key,Value>* A = currentNode;
        Node<Key,Value>* Ar = currentNode->right;
        Node<Key,Value>* Arl = currentNode->right->left;
        Node<Key,Value>* Arll = currentNode->right->left->left; //can be null
        Node<Key,Value>* Arlr = currentNode->right->left->right; //can be null
        if(Arll) Arll->parent = A;
        Arl->parent = A->parent;
        A->parent = Arl;
        Ar->parent = Arl;
        if(Arlr) Arlr->parent = Ar;
        A->right = Arll;
        Ar->left = Arlr;
        Arl->right = Ar;
        Arl->left = A;
        if(Arl->parent)
        { //(now Arl is the root)
            if(Arl->parent->right == A)
            {
                Arl->parent->right = Arl;
            }
            else
            {
                Arl->parent->left = Arl;
            }
        }
        updateHeight(Arll);
        updateHeight(Arlr);
        updateHeight(A);
        updateHeight(Ar);
        updateHeight(Arl);
        return Arl;
    }

    return currentNode;
}

template<class Key,class Value>
void Tree<Key, Value>::balanceTree(Node<Key, Value>* currentNode)
{
    if(currentNode)
    {
        updateHeight(currentNode);
        int rightChildBalanceFactor = getBalanceFactor(currentNode->right);
        int leftChildBalanceFactor = getBalanceFactor(currentNode->left);
        int balanceFactor = getBalanceFactor(currentNode);
        Node<Key, Value> *rotatedTree = getRotated(currentNode, rightChildBalanceFactor, leftChildBalanceFactor,
                                                   balanceFactor);

        if (root == currentNode) {
            root = rotatedTree;
        }

        balanceTree(currentNode->parent);
    }
}

template<class Key, class Value>
Value* Tree<Key,Value>::removeWithKey(Key* key)
{
    Node<Key,Value>* removedNode = removeNode(root, key);
    if(!removedNode->parent)
    {
        if(removedNode->right) root = removedNode->right;
        else if(removedNode->left) root = removedNode->left;
        else root = nullptr;
    }
    else if(!removedNode->parent->parent) root = removedNode->parent;
    balanceTree(removedNode->parent);
    Value* val = removedNode->value;
    delete removedNode->key;
    delete removedNode->value;
    delete removedNode;
    removedNode = nullptr;
    this->size--;
    return val;
}

template<class Key, class Value>
Value* Tree<Key,Value>::remove(Key* key)
{
    Node<Key,Value>* removedNode = removeNode(root, key);
    if(!removedNode->parent)
    {
        if(removedNode->right) root = removedNode->right;
        else if(removedNode->left) root = removedNode->left;
        else root = nullptr;
    }
    else if(!removedNode->parent->parent) root = removedNode->parent;
    balanceTree(removedNode->parent);
    Value* val = removedNode->value;
    delete removedNode;
    removedNode = nullptr;
    this->size--;
    return val;
}

template<class Key, class Value>
Node<Key,Value>* Tree<Key,Value>::removeNode(Node<Key, Value> *currentNode, Key* key)
{
    if(currentNode == nullptr)
    {
        throw NodeDoesNotExist();
    }
    if(*key == *currentNode->key)
    {
        if(currentNode->left && !currentNode->right)
        {
            connectSonParent(currentNode,currentNode->left);
            if(currentNode->prev) currentNode->prev->next = currentNode->next;
            if(currentNode->next) currentNode->next->prev = currentNode->prev;
            return currentNode;
        }

        else if(currentNode->right && !currentNode->left)
        {
            connectSonParent(currentNode,currentNode->right);
            if(currentNode->prev) currentNode->prev->next = currentNode->next;
            if(currentNode->next) currentNode->next->prev = currentNode->prev;
            return currentNode;
        }
        else if(currentNode->right && currentNode->left)
        {
            //swap
            Key* currentKey = currentNode->key;
            Value* currentValue = currentNode->value;
            currentNode->key = currentNode->next->key;
            currentNode->value = currentNode->next->value;
            currentNode->next->key = currentKey;
            currentNode->next->value = currentValue;
            return removeNode(currentNode->next, key);
        }
        else
        {
            if(currentNode->parent)
            {
                if(currentNode->parent->left == currentNode) currentNode->parent->left = nullptr;
                else currentNode->parent->right = nullptr;
            }
            if(currentNode->prev) currentNode->prev->next = currentNode->next;
            if(currentNode->next) currentNode->next->prev = currentNode->prev;
            return currentNode;
        }
    }
    else if(*key < *currentNode->key)
    {
        return removeNode(currentNode->left,key);
    }
    else
    {
        return removeNode(currentNode->right,key);
    }
}

template<class Key, class Value>
void Tree<Key,Value>::connectSonParent(Node<Key, Value> *currentNode,Node<Key, Value> *son) {
    son->parent = currentNode->parent;
    if(currentNode->parent)
    {
        if(currentNode->parent->left == currentNode) currentNode->parent->left = son;
        else currentNode->parent->right = son;
    }
    if(son->next == currentNode) son->next = currentNode->next;
    if(son->prev == currentNode) son->prev = currentNode->prev;
    if(son->parent) {
        if (son->parent->next == currentNode) son->parent->next = currentNode->next;
        if (son->parent->prev == currentNode) son->parent->prev = currentNode->prev;
    }
    updateHeight(son);
    updateHeight(son->parent);
}


template<class Key, class Value>
bool Tree<Key,Value>::exists(Key* key) const
{
    bool isExist = true;
    try
    {
        find(key);
    }
    catch(NodeDoesNotExist&)
    {
        isExist = false;
    }
    return isExist;
}

template<class Key, class Value>
Value* Tree<Key,Value>::find(Key* key) const
{
    return findNode(root, key)->value;
}

template<class Key, class Value>
Node<Key,Value>* Tree<Key,Value>::findNode(Node<Key,Value>* currentNode, Key* key) const
{

    if(currentNode == nullptr)
    {
        throw NodeDoesNotExist();
    }
    if(*currentNode->key == *key)
    {
        return currentNode;
    }
    else if(*key < *currentNode->key)
    {
        return findNode(currentNode->left, key);
    }
    else
    {
        return findNode(currentNode->right, key);
    }

}

template<class Key, class Value>
Value* Tree<Key,Value>::findByIndex(int index) const
{
    return findNodeByIndex(root, 0, index)->value;
}

template<class Key, class Value>
Node<Key,Value>* Tree<Key,Value>::findNodeByIndex(Node<Key,Value>* currentNode, int previousIndex, int index) const
{

    if(currentNode == nullptr)
    {
        throw NodeDoesNotExist();
    }
    int currentIndex = (currentNode->left) ? currentNode->left->subTreeSize+1+previousIndex : 1+previousIndex;
    if(currentIndex == index)
    {
        return currentNode;
    }
    else if(index < currentIndex)
    {
        return findNodeByIndex(currentNode->left, previousIndex, index);
    }
    else
    {
        return findNodeByIndex(currentNode->right, currentIndex, index);
    }

}


#endif //HW1_TREE_H



