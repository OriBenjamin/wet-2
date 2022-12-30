//
// Created by oride on 30/12/2022.
//

#ifndef WET_2_HASHTABLE_H
#define WET_2_HASHTABLE_H


const int INITIAL_ARRAY_SIZE = 10;

template <class Value>
class HashTable {
    Node<Value>* valuesArray;
    int size;

    HashTable(): valuesArray(new Node<Value>[INITIAL_ARRAY_SIZE]), size(INITIAL_ARRAY_SIZE) {}

    //gets a key and returns the matching index in the array
    int hashFunction(int key)
    {

    }

    void insert( int key, Value value)
    {
        int index = hashFunction(key);
        if(valuesArray[index].size)
    }
};



#endif //WET_2_HASHTABLE_H
