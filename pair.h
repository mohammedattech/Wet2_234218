#ifndef PAIR_H
#define PAIR_H


template<class K,class T>
struct pair{
    pair(K key, T data):m_key(key),m_data(data){};
    K m_key;
    T m_data;
};

#endif