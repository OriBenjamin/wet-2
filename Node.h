//
// Created by liels on 29/11/2022.
//

#ifndef wet_1_NODE_H
#define wet_1_NODE_H
#include <iostream>
#include <stdlib.h>
#include <memory>
template<class Key, class Value>
class Tree;

const int INITIAL_HEIGHT = 0;

template<class Key, class Value>
struct Node
{
public:
    Node<Key,Value>* right, *left, *parent, *next, *prev;
    Key* key;
    Value* value;
    int height;
    int subTreeSize;

    Node();
    Node(Key* key, Value* value);
    ~Node() = default;
    Node(const Node& n) = default;
    Node& operator=(const Node& n) = default;
    bool operator<(const Node<Key,Value>& node) const;

    Key getKey() const;
};


template<class Key, class Value>
Node<Key,Value>::Node():
        right(nullptr), left(nullptr), parent(nullptr), next(nullptr), prev(nullptr),
        key(nullptr), value(nullptr), height(INITIAL_HEIGHT), subTreeSize(0){}

template<class Key, class Value>
Node<Key,Value>::Node(Key* key, Value* value):
        right(nullptr), left(nullptr), parent(nullptr), next(nullptr), prev(nullptr),
        key(key), value(value), height(INITIAL_HEIGHT), subTreeSize(0){}

template<class Key, class Value>
bool Node<Key,Value>::operator<(const Node<Key,Value>& node) const
{
    if(*key < *node.key)
    {
        return true;
    }
    return false;
}


template<class Key, class Value>
bool operator==(const Node<Key,Value>& node1, const Node<Key,Value>& node2)
{
    if(!(node1 < node2) && !(node2 < node1))
    {
        return true;
    }
    return false;
}

template<class Key, class Value>
bool operator>(const Node<Key,Value>& node1, const Node<Key,Value>& node2)
{
    if(!(node1 == node2) && !(node1 < node2))
    {
        return true;
    }
    return false;
}


template<class Key, class Value>
Key Node<Key, Value>::getKey() const
{
    return *key;
}
#endif //wet_1_NODE_H
