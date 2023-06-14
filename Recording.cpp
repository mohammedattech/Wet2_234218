#include "Recording.h"
Recording::Recording(int collumn,int height):m_collumn(collumn),m_heapHeight(height),m_heightDelta(0),m_parent(nullptr),m_purchases(0),m_groupSize(1)
{
    m_parent=this;
}
int Recording::getCollumn()const
{
    return m_collumn;
}
int Recording::getHeapHeight() const
{
    return m_heapHeight;
}
int Recording::getHeightDelta() const
{
    return m_heightDelta;
}
Recording* Recording::getParent() const
{
    return m_parent;
}
int Recording::getGroupSize() const
{
    return m_groupSize;
}
int Recording::getPurchases() const
{
    return m_purchases;
}
void Recording::setCollumn(int collumn)
{
    m_collumn=collumn;
}
void Recording::setgroupSize(int size)
{
    m_groupSize=size;
}
void Recording::setHeapHeight(int heapHeight)
{
    m_heapHeight=heapHeight;
}
void Recording::setHeightDelta(int heightDelta)
{
    m_heightDelta=heightDelta;
}
void Recording::incrementPurchases()
{
    m_purchases++;
}
void Recording::setParent(Recording* node)
{
    m_parent=node;
}
