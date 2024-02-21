#pragma once
#ifndef HASHTABLE_HPP

#include <iostream>
#include <initializer_list>
#include <stdexcept>

#include "LinkedList.hpp"

template<typename KeyT, typename DataT>
class HashTable
{
private:
    LinkedList<DataT>** bucketArray;
    size_t size;

    virtual size_t hash(KeyT key) = 0;
    virtual size_t getRightSize(size_t newSize);

public:
    HashTable(size_t newSize);
    virtual ~HashTable();


    DataT* insert(KeyT key, DataT* data);

    HashTable* remove(KeyT key);
    HashTable* remove(size_t index);

    DataT* operator[](KeyT key);
    size_t getIndex(KeyT key);
    size_t getSize() { return size; }
    //LinkedList<DataT>** getBucketArray() { return bucketArray; }

    void print();
};

template<typename KeyT, typename DataT>
size_t HashTable<KeyT, DataT>::getRightSize(size_t newSize)
{
    size_t rightSize = 10;
    while (rightSize <= newSize)
        rightSize *= 10;
    return rightSize;
}

template<typename KeyT, typename DataT>
HashTable<KeyT, DataT>::HashTable(size_t newSize)
    : size(getRightSize(newSize)), bucketArray(new LinkedList<DataT>*[size])
{
    for (size_t i = 0; i < size; i++)
    {
        bucketArray[i] = new LinkedList<DataT>();
    }
}



template<typename KeyT, typename DataT>
HashTable<KeyT, DataT>::~HashTable()
{
    for (size_t i = 0; i < size; i++)
    {
        delete bucketArray[i];
    }
    delete[] bucketArray;
}

template<typename KeyT, typename DataT>
DataT* HashTable<KeyT, DataT>::operator[](KeyT key)
{
    size_t index = hash(key);
    return bucketArray[index]->find(key);
}

template<typename KeyT, typename DataT>
DataT* HashTable<KeyT, DataT>::insert(KeyT key, DataT* data)
{
    size_t index = hash(key);
    return bucketArray[index]->pushBack(data);
}

template<typename KeyT, typename DataT>
HashTable<KeyT, DataT>* HashTable<KeyT, DataT>::remove(KeyT key)
{
    size_t index = hash(key);
    bucketArray[index]->remove(key);
    return this;
}

template<typename KeyT, typename DataT>
HashTable<KeyT, DataT>* HashTable<KeyT, DataT>::remove(size_t index)
{
    delete bucketArray[index];
    bucketArray[index] = new LinkedList<DataT>();
    return this;
}

template<typename KeyT, typename DataT>
size_t HashTable<KeyT, DataT>::getIndex(KeyT key)
{
    return hash(key);
}

template<typename KeyT, typename DataT>
void HashTable<KeyT, DataT>::print()
{
    for (size_t i = 0; i < size; i++)
    {
        std::cout << "Bucket " << i << ": ";
        bucketArray[i]->print();
    }
}



#endif // !HASHTABLE_HPP
        