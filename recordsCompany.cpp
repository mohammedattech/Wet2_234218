#include "recordsCompany.h"
StatusType RecordsCompany::putOnTop(int r_id1, int r_id2)
{
    if(r_id1<0||r_id2<0)
    {
        return StatusType::INVALID_INPUT;
    }
    if (r_id1>=m_recordings.getNumberOfSets()||r_id2>=m_recordings.getNumberOfSets())
    {
        return StatusType::DOESNT_EXISTS;
    }
    int column1;
    int column2;
    m_recordings.find(r_id1,&column1);
    m_recordings.find(r_id2,&column2);
    if(column1==column2)
    {
        return StatusType::FAILURE;
    }
    m_recordings.Union(r_id2,r_id1);
    return StatusType::SUCCESS;
}
    
StatusType RecordsCompany::getPlace(int r_id, int *column, int *hight)
{
    if(r_id<0)
    {
        return StatusType::INVALID_INPUT;
    }
    if(r_id>=m_recordings.getNumberOfSets())
    {
        return StatusType::DOESNT_EXISTS;
    }
    m_recordings.find(r_id,column,hight);
    return StatusType::SUCCESS;
}