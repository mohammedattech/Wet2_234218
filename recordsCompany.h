#ifndef RECORDS_COMPANY_H
#define RECORDS_COMPANY_H

#include "utilesWet2.h"
#include "UnionFind.h"
#include "HashTable.h"
#include "RankAvlTree.h"
#include "Customer.h"
#include "Recording.h"
#include <memory>


class RecordsCompany {
  private:
    UnionFind m_recordings;
    HashTable<std::shared_ptr<Customer>> m_customers;
    RankAvlTree<Customer*,int,double> m_members;
  public:
    RecordsCompany()=default;
    ~RecordsCompany()=default;
    StatusType newMonth(int *records_stocks, int number_of_records);
    StatusType addCostumer(int c_id, int phone);
    Output_t<int> getPhone(int c_id);
    StatusType makeMember(int c_id);
    Output_t<bool> isMember(int c_id);
    StatusType buyRecord(int c_id, int r_id);
    StatusType addPrize(int c_id1, int c_id2, double  amount);
    Output_t<double> getExpenses(int c_id);
    StatusType putOnTop(int r_id1, int r_id2);
    StatusType getPlace(int r_id, int *column, int *hight);
};

#endif