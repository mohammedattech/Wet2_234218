#ifndef UNION_FIND_H
#define UNION_FIND_H
#include "Recording.h"
class UnionFind
{
public:
    UnionFind();
    ~UnionFind();
    void reInitialize(int* sizes,int length);
    int getNumberOfSets()const;
    void Union(int id1,int id2);
    void find(int id,int* collumn,int* height=nullptr);
    Recording& operator[](int id);
private:
    Recording* m_sets;
    int m_numberOfSets;
    Recording* findAux(Recording* record,int* height,int* collumn,int& deltaSum);
};

#endif