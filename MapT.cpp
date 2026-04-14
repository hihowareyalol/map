//
// Created by we7289 on 4/19/2021.
//

#include "MapT.h"
#include <unordered_map>
//using namespace std;

const int DEFAULT_BUCKETS = 10;
const double DEFAULT_LOAD = 1.0;

template<class K, class T>
MapT<K, T>::MapT() {
    buckets = new forward_list<K, T>[DEFAULT_BUCKETS];

    numKeys = 0;
    numBuckets = DEFAULT_BUCKETS;
    maxLoad = DEFAULT_LOAD;
}

template<class K, class T>
void MapT<K, T>::Add(K key, T value) {

    Remove(key);

    // Find the appropriate bucket that key lives in
    int bucket = GetHashIndex(key);

    /*check to see if the key already exists, if it does change the value
     *associated with the key
    for (auto it = buckets[bucket].begin(); it != buckets[bucket].end(); ++it)
    {
        if (it->first == key) // does the key exist?
        {
            it->second = value;
            return;
        }
    }*/

    pair<K,T> keyVal;
    keyVal.first = key;
    keyVal.second = value;

    buckets[bucket].push_front(keyVal);
    numKeys++;

    if (LoadFactor() > maxLoad)
    {
        Rehash(2*numBuckets);
    }
}

template<class K, class T>
void MapT<K, T>::Remove(K key) {
    // Find the appropriate bucket that key lives in
    int bucket = GetHashIndex(key);

    for (auto it = buckets[bucket].begin(); it != buckets[bucket].end(); ++it)
    {
        if (it->first == key) // does the key exist?
        {
            buckets[bucket].remove(*it);
            numKeys--;
            return;
        }
    }

}

template<class K, class T>
bool MapT<K, T>::Contains(K key) {
    // Find the appropriate bucket that key lives in
    int bucket = GetHashIndex(key);

    for (auto it = buckets[bucket].begin(); it != buckets[bucket].end(); ++it)
    {
        if (it->first == key) // does the key exist?
        {
            return true;
        }
    }
    return false;
}

template<class K, class T>
T MapT<K, T>::operator[](K key) {
    int bucket = GetHashIndex(key);

    for (auto it = buckets[bucket].begin(); it != buckets[bucket].end(); ++it)
    {
        if (it->first == key) // does the key exist?
        {
            return it->second;
        }
    }

    throw KeyDoesNotExist();
}

template <class K, class T>
MapT<K, T>& MapT<K, T>::operator=(MapT const& other)
{
    delete [] buckets; //clear out "this" buckets

    numBuckets = other.numBuckets;
    buckets = new forward_list<pair<K,T>>[numBuckets];
    numKeys = 0;

    //loop thru all values in other
    for (int b = 0; b < other.numBuckets; b++)
    {
        //loop thru all values in bucket b
        for (auto it = other.buckets[b].begin(); it != other.buckets[b].end(); ++it)
        {
            Add(it->first, it->second);
        }
    }

    return *this;
}

template<class K, class T>
double MapT<K, T>::LoadFactor() {
    return static_cast<double>(numKeys)/numBuckets;
}

template<class K, class T>
void MapT<K, T>::SetMaxLoad(double maxLoad) {
    this->maxLoad = maxLoad;
}

template<class K, class T>
void MapT<K, T>::Rehash(int numBuckets) {
    MapT<K, T> newMap(numBuckets);  // Need to copy over all elements to newMap

    //loop thru all values in other
    for (int b = 0; b < numBuckets; b++)
    {
        //loop thru all values in bucket b
        for (auto it = buckets[b].begin(); it != buckets[b].end(); ++it)
        {
            newMap.Add(it->first, it->second);
        }
    }

    *this = newMap;
}

template<class K, class T>
void MapT<K, T>::ResetIterator() {
    mapIter = buckets[0].begin();
    currBucket = 0;
}

template<class K, class T>
pair<K,T> MapT<K, T>::GetNextPair() {
    pair<K,T> currVal;



    return currVal;
}

template<class K, class T>
int MapT<K, T>::GetHashIndex(const K &key) {
    unordered_map<K,T> mapper;
    typename unordered_map<K,T>::hasher hashFunction = mapper.hash_function();
    return static_cast<int>(hashFunction(key) % numBuckets);
}



