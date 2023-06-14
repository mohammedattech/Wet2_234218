#ifndef RECORDING_H
#define RECORDING_H
class Recording
{
public:
    Recording(int collumn,int heapHeight);
    ~Recording()=default;
    int getCollumn() const;
    int getHeapHeight() const;
    int getHeightDelta() const;
    Recording* getParent() const;
    int getPurchases() const;
    int  getGroupSize() const;
    void setCollumn(int collumn);
    void setHeapHeight(int heapHeight);
    void setHeightDelta(int heightDelta);
    void setParent(Recording* node);
    void incrementPurchases();
    void setgroupSize(int size);
private:
    int m_collumn;
    int m_heapHeight;
    int m_heightDelta;
    Recording* m_parent;
    int m_purchases;
    int m_groupSize;
};

#endif