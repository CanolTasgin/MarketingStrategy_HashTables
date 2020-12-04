#ifndef HASH_TABLE_H_
#define HASH_TABLE_H_

#include <vector>
#include <string>
#include "LinkedList.h"

using namespace std;
// Seperate Chaining
//
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x
// Hashable find( x )     --> Return item that matches x
// void makeEmpty( )      --> Remove all items
//

template <class HashedObj>
class HashTable
{
public:
    explicit HashTable(const HashedObj & notFound, int size = 101);
    HashTable(const HashTable & rhs)
        : ITEM_NOT_FOUND(rhs.ITEM_NOT_FOUND), theLists(rhs.theLists) { }

    HashedObj & find(HashedObj & x);

    void makeEmpty();
    void insert(const HashedObj & x);
    void remove(const HashedObj & x);

    const HashTable & operator=(const HashTable & rhs);
private:
    vector<List<HashedObj> > theLists;   // The array of Lists
    HashedObj ITEM_NOT_FOUND;
};

int hashh(const string & key, int tableSize);
int hashh(int key, int tableSize);

template <class HashedObj>
int hashh(HashedObj & key, int tableSize);

/**
* Internal method to test if a positive number is prime.
* Not an efficient algorithm.
*/
bool isPrime(int n)
{
    if (n == 2 || n == 3)
        return true;

    if (n == 1 || n % 2 == 0)
        return false;

    for (int i = 3; i * i <= n; i += 2)
        if (n % i == 0)
            return false;

    return true;
}

/**
* Internal method to return a prime number at least as large as n.
* Assumes n > 0.
*/
int nextPrime(int n)
{
    if (n % 2 == 0)
        n++;

    for (; !isPrime(n); n += 2)
        ;

    return n;
}

/**
* Construct the hash table.
*/
template <class HashedObj>
HashTable<HashedObj>::HashTable(const HashedObj & notFound, int size)
    : ITEM_NOT_FOUND(notFound), theLists(nextPrime(size))
{
}

/**
* Insert item x into the hash table. If the item is
* already present, then do nothing.
*/
template <class HashedObj>
void HashTable<HashedObj>::insert(const HashedObj & x)
{
    List<HashedObj> & whichList = theLists[hashh(x, theLists.size())];
    ListItr<HashedObj> itr = whichList.find(x);

    if (!itr.isPastEnd()){
        HashedObj & temp = itr.retrieve();
        temp++;                                 //increase the counter here if exist
    }
    else  {
        whichList.insert(x, whichList.zeroth());
    }
}

/**
* Remove item x from the hash table.
*/
template <class HashedObj>
void HashTable<HashedObj>::remove(const HashedObj & x)
{
    theLists[hashh(x, theLists.size())].remove(x);
}

/**
* Find item x in the hash table.
* Return the matching item or ITEM_NOT_FOUND if not found
*/
template <class HashedObj>
HashedObj & HashTable<HashedObj>::find(HashedObj & x)
{
    ListItr<HashedObj> itr;
    itr = theLists[hashh(x, theLists.size())].find(x);
    if (itr.isPastEnd())
        return ITEM_NOT_FOUND;
    else
        return itr.retrieve();
}

/**
* Make the hash table logically empty.
*/
template <class HashedObj>
void HashTable<HashedObj>::makeEmpty()
{
    for (int i = 0; i < theLists.size(); i++)
        theLists[i].makeEmpty();
}

/**
* Deep copy.
*/
template <class HashedObj>
const HashTable<HashedObj> &
HashTable<HashedObj>::operator=(const HashTable<HashedObj> & rhs)
{
    if (this != &rhs)
        theLists = rhs.theLists;
    return *this;
}


/**
* A hash routine for string objects.
*/
int hashh(const string & key, int tableSize)
{
    int hashVal = 0;

    for (int i = 0; i < key.length(); i++)
        hashVal = 37 * hashVal + key[i];

    hashVal %= tableSize;
    if (hashVal < 0)
        hashVal += tableSize;

    return hashVal;
}


/**
* A hash routine for ints.
*/
int hashh(int key, int tableSize)
{
    if (key < 0) key = -key;
    return key % tableSize;
}

template <class HashedObj>
int hashh(HashedObj & key, int tableSize)
{
    string temp;
    if(key.str1 < key.str2)
        temp = key.str1 + key.str2;
    else
        temp = key.str2 + key.str1;

    int hashVal = 0;
    
        for (int i = 0; i < temp.length(); i++)
        hashVal = 37 * hashVal + temp[i];

    hashVal %= tableSize;
    if (hashVal < 0)
        hashVal += tableSize;

    return hashVal;
}

#endif
