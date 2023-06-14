#include "UnionFind.h"
UnionFind::UnionFind():m_sets(nullptr),m_numberOfSets(0)
{}
UnionFind::~UnionFind()
{
    if(m_sets)
    {
        delete[] m_sets;
    }
}
void UnionFind::reInitialize(int* sizes,int length)
{
    if(m_sets)
    {
        delete[] m_sets;
    }
    m_sets=new Recording[length];
    for (int i = 0; i < length; i++)
    {
        m_sets[i].setCollumn(i);
        m_sets[i].setHeapHeight(sizes[i]);
    }
    m_numberOfSets=length;
}
int UnionFind::getNumberOfSets()const
{
    return m_numberOfSets;
}
Recording& UnionFind::operator[](int id)
{
    return m_sets[id];
}
void UnionFind::find(int id,int* height,int* collumn)
{
    
    int deltaSum=0;
    if (!height)
    {
        int trashHeight=0;
        findAux(m_sets+id,&trashHeight,collumn,deltaSum);
    }
    else
    {
        findAux(m_sets+id,height,collumn,deltaSum);
    }
}
Recording* UnionFind::findAux(Recording* record,int* height,int* collumn,int& deltaSum)
{
    if(record->getParent()==record)
    {
        (*collumn)=record->getCollumn();
        (*height)+=record->getHeightDelta();
        deltaSum+=record->getHeightDelta();
        return record;
    }
    deltaSum+=record->getHeightDelta();
    (*height)+=record->getHeightDelta();
    record->setParent(findAux(record->getParent(),height,collumn,deltaSum));
    deltaSum-=record->getHeightDelta();
    record->setHeightDelta((*height)-deltaSum);
    return record->getParent();
}
void UnionFind::Union(int id1,int id2)
{
    int trashCollumn;
    int trashHeight=0;
    int deltaSum=0;
    Recording* root1=findAux(m_sets+id1,&trashHeight,&trashCollumn,deltaSum);
    deltaSum=0;
    trashHeight=0;
    Recording* root2=findAux(m_sets+id2,&trashHeight,&trashCollumn,deltaSum);
    if(root1==root2)
    {
        return;
    }
    if(root1->getGroupSize()>=root2->getGroupSize())
    {
        root2->setHeightDelta(root2->getHeightDelta()-root1->getHeightDelta()+root1->getHeapHeight());
        root2->setParent(root1);
        root1->setHeapHeight(root2->getHeapHeight()+root1->getHeapHeight());
        root1->setgroupSize(root1->getGroupSize()+root2->getGroupSize());
    }
    else
    {
        root2->setHeightDelta(root2->getHeightDelta()+root1->getHeapHeight());
        root2->setHeapHeight(root2->getHeapHeight()+root1->getHeapHeight());
        root2->setgroupSize(root2->getGroupSize()+root1->getGroupSize());
        root2->setCollumn(root1->getCollumn());
        root1->setHeightDelta(root1->getHeightDelta()-root2->getHeightDelta());
        root1->setParent(root2);
    }
}