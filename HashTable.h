#ifndef HASH_TABLE
#define HASH_TABLE

#include<iostream>
#include <exception>
#include<memory>
#include "AvlTree.h"
#include "pair.h"
#include<fstream>


template<class T>
class HashTable {
public:
    HashTable();

    ~HashTable();

    void Insert(const T &data, int key);

    T &Find(int key);

    bool member(int key);

    int getSize() const;

    int getLength() const;

    
private:
    void insertToNewTable(AvlTree<T, int> *tree, AvlTree<T, int> **table, int length);

    void Rehash();

    static int hashFuntion(int key, int length);

    static const int initial_value = 7;
    int m_length;
    int m_size;
    AvlTree<T, int> **m_tree;
};

template<class T>
HashTable<T>::HashTable():m_length(initial_value), m_size(0) {
    m_tree = new AvlTree<T, int> *[initial_value];
    for (int i = 0; i < initial_value; i++){
        m_tree[i]=nullptr;
    }
    
}

template<class T>
HashTable<T>::~HashTable() {
    for (int i = 0; i < m_length; i++) {
        if(m_tree[i])
            delete m_tree[i];
    }
    delete[] m_tree;
}

template<class T>
void HashTable<T>::Insert(const T &data, int key) {
    int index = hashFuntion(key, m_length);
    if (member(key)) {
        throw ElementExists();
    }
    if (!m_tree[index]) {
        AvlTree<T, int> *t1 = new AvlTree<T, int>();
        t1->insert(key, data);
        m_tree[index] = t1;
        m_size++;
    } else {
        m_tree[index]->insert(key, data);
        m_size++;
        if (double(m_size) / double(m_length) >= 2) {
            Rehash();
        }
    }
}


template<class T>
T &HashTable<T>::Find(int key) {
    int index = hashFuntion(key, m_length);
    if (!m_tree[index] || !m_tree[index]->search(key)) {
        throw ElementDoesntExist();
    }
    return m_tree[index]->getData(key);
}

template<class T>
bool HashTable<T>::member(int key) {
    int index = hashFuntion(key, m_length);
    if (!m_tree[index] || !m_tree[index]->search(key)) {
        return false;
    }
    return true;
}


template<class T>
void HashTable<T>::Rehash() {
    int newLength = 2 * m_length;
    AvlTree<T, int> **temp = new AvlTree<T, int> *[newLength];
    for(int i=0;i<newLength;i++){
        temp[i]=nullptr;
    }
    for (int i = 0; i < m_length; i++) {
        if (m_tree[i]) {
            insertToNewTable(m_tree[i], temp, newLength);
        }

    }
    for (int i = 0; i < m_length; i++) {
        if (m_tree[i]) {
            delete m_tree[i];
        }
    }
    delete []m_tree;
    m_tree = temp;
    m_length = newLength;

}


template<class T>
int HashTable<T>::hashFuntion(int key, int length) {
    return key % length;
}


template<class T>
int HashTable<T>::getSize() const {
    return m_size;
}

template<class T>
int HashTable<T>::getLength() const {
    return m_length;
}

template<class T>
std::ostream &operator<<(std::ostream &os, const HashTable<T> &hashT) {
    for (int i = 0; i < hashT.m_size; i++) {
        if (hashT.m_lists[i]) {
            std::cout << "index=" << i << ":" << std::endl << *hashT.m_lists[i] << std::endl;
        }
    }
    return os;
}


template<class T>
void HashTable<T>::insertToNewTable(AvlTree<T, int> *tree, AvlTree<T, int> **table, int length) {
    pair<int, T> **inOrderArray = new pair<int, T>*[tree->getSize()];
    //arrayFiller<pair<int, T> *> filler(inOrderArray);
    //tree->fillKeyData(filler);*/
    int x=0;
    tree->fillArray(inOrderArray,&x);
    for (int i = 0; i <tree->getSize(); i++) {
        int key = inOrderArray[i]->m_key;
        T data = inOrderArray[i]->m_data;
        int index = hashFuntion(key, length);
        if (!table[index]) {
            AvlTree<T, int> *t1 = new AvlTree<T, int>();
            t1->insert(key, data);
            table[index] = t1;
        } else {
            table[index]->insert(key, data);
        }
    }
    for (int i = 0; i < tree->getSize(); i++) {
        if (inOrderArray[i]) {
            delete inOrderArray[i];
        }
    }
    delete[]inOrderArray;
}

#endif