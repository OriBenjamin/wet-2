//
// Created by oride on 30/12/2022.
//

#ifndef WET_2_HASHTABLE_H
#define WET_2_HASHTABLE_H

#include <memory>
#include <exception>
#include <iostream>
#include <stdlib.h>

const int INITIAL_HASH_TABLE_SIZE = 10;
const int INITIAL_KEY = 0;


class NodeAlreadyExistInHash :  public std::exception
{
    public:
    const char* what() const noexcept override {return "Node already exist in this Hash Table";}
};

class CantInsertNode : public std::exception
{
    private:
    const char* error;

    public:
    CantInsertNode(const char* error): error(error) {}
    const char* what() const noexcept override {return error;}
};


template<class Value>
class HashTable
{
    private:

    struct HashTableNode
    {
        public:
        std::shared_ptr<Value> value;
        std::unique_ptr<HashTableNode> next;
        int key;

        HashTableNode(): value(), next(), key(INITIAL_KEY) {}
        HashTableNode(std::shared_ptr<Value> value, std::unique_ptr<HashTableNode> next, int key):
        value(value), next(std::move(next)), key(key) {}
        HashTableNode(HashTableNode& node):
        value(node.value), next(std::move(node.next)), key(node.key) {}
        ~HashTableNode() = default;
    };

    int hashTableSize = INITIAL_HASH_TABLE_SIZE;
    int currentAmountOfNodes;
    std::unique_ptr<HashTableNode>* elements;


    int hashFunction(int keyToHash, int HashTableSize)
    {
        return keyToHash % HashTableSize;
    }

    public:
    HashTable(int hashTableSize = INITIAL_HASH_TABLE_SIZE):
    hashTableSize(hashTableSize), currentAmountOfNodes(0)
    {
        elements = new std::unique_ptr<HashTableNode>[hashTableSize];
        for(int i=0; i<hashTableSize; i++)
        {
            elements[i] = nullptr;
        }
    }
    HashTable(const HashTable&) = delete;
    ~HashTable()
    {
        delete[] elements;
    }



    void insert(int key, Value* value)
    {
        if(key<0)
        {
            throw CantInsertNode("Cant insert node in negative key");
        }

        int index = hashFunction(key, hashTableSize);
        if(index < 0)
        {
            throw CantInsertNode("Cant insert node in negative index");
        }
        if(index > hashTableSize-1)
        {
            throw CantInsertNode("Cant insert node, the Hash Table is too small");
        }

        if(elements[index] == nullptr)
        {
            std::shared_ptr<Value> newValue = std::shared_ptr<Value>(value);
            HashTableNode* newNode = new HashTableNode(newValue, nullptr, key);
            std::unique_ptr<HashTableNode> node = std::unique_ptr<HashTableNode>(newNode);
            elements[index] = std::move(node);
            currentAmountOfNodes++;
        }
        else
        {
            if(search(key) != nullptr)
            {
                throw NodeAlreadyExistInHash();
            }

            std::unique_ptr<HashTableNode> oldFirstNode = std::move(elements[index]);
            std::unique_ptr<HashTableNode> newNode = std::unique_ptr<HashTableNode>(new HashTableNode(std::shared_ptr<Value>(value), std::move(oldFirstNode), key));
            elements[index] = std::move(newNode);
            currentAmountOfNodes++;
        }
        checkAndIncrease(*this);
    }

    std::shared_ptr<Value> search(int key)
    {
        int index = hashFunction(key, hashTableSize);
        if(index < 0)
        {
            throw CantInsertNode("Cant insert node in negative index");
        }
        if(index > hashTableSize-1)
        {
            throw CantInsertNode("Cant insert node, the Hash Table is too small");
        }

        if(elements[index] == nullptr)
        {
            return nullptr;
        }
        std::unique_ptr<HashTableNode>* currentNodeInChain = &(elements[index]);
        if((*currentNodeInChain)->key == key)
        {
            return (*currentNodeInChain)->value;
        }
        while((*currentNodeInChain)->next != nullptr)
        {
            currentNodeInChain = &((*currentNodeInChain)->next);
            if((*currentNodeInChain)->key == key)
            {
                return (*currentNodeInChain)->value;
            }
        }
        return nullptr;
    }

    void checkAndIncrease(HashTable& hashTable)
    {
        if(hashTable.currentAmountOfNodes < hashTableSize/2)
        {
            return;
        }
        std::unique_ptr<HashTableNode>* newElements = new std::unique_ptr<HashTableNode>[hashTableSize*2];
        for(int i=0; i<hashTableSize*2; i++)
        {
            newElements[i] = nullptr;
        }
        std::unique_ptr<HashTableNode>* oldElements = elements;
        elements = newElements;
        currentAmountOfNodes = 0;
        hashTableSize*=2;
        for(int i=0; i<hashTableSize/2; i++)
        {
            if(oldElements[i] != nullptr)
            {
                insert(oldElements[i]->key, (oldElements[i]->value).get());
                std::unique_ptr<HashTableNode>* currentNodeInChain = &(oldElements[i]->next);
                while((*currentNodeInChain) != nullptr)
                {
                    insert((*(*currentNodeInChain)).key, (*(*currentNodeInChain)).value.get());
                    currentNodeInChain = &((*currentNodeInChain)->next);
                }
            }
        }
        delete[] oldElements;
    }
    void print()
    {
        for(int i = 0; i < hashTableSize; i++)
        {
            if(elements[i] == nullptr)
            {
                continue;
            }
            std::unique_ptr<HashTableNode>* currentNodeInChain = &(elements[i]);
            int j = 0;
            std::cout << "index in array: " << i << " value: " << *((*currentNodeInChain)->value)  <<  " index in chain: " << j<< std::endl;
            j++;
            while((*currentNodeInChain)->next != nullptr)
            {
                currentNodeInChain = &((*currentNodeInChain)->next);
                std::cout << "index in array: " << i << "value: " << *((*currentNodeInChain)->value)  <<  " index in chain: " << j<< std::endl;
                j++;
            }
        }
    }
};



#endif //WET_2_HASHTABLE_H
