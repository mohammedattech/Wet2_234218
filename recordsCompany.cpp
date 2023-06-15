#include "recordsCompany.h"
#include"customerReset.h"
StatusType RecordsCompany::newMonth(int *records_stocks, int number_of_records){
    if(number_of_records<0){
        return StatusType::INVALID_INPUT;
    }
    try{
        m_recordings.reInitialize(records_stocks,number_of_records);
    }
    catch (badAlloc& e){
        return StatusType::ALLOCATION_ERROR;
    }
    customerReset reset;
    m_members.reset(reset);
    return StatusType::SUCCESS;
}   


Output_t<int> RecordsCompany::getPhone(int c_id){
    if(c_id<0){
        return StatusType::INVALID_INPUT;
    }
    Customer* cust;
    try{
        cust=m_customers.Find(c_id).get();
    }
    catch (ElementDoesntExist& exception){
        return StatusType::DOESNT_EXISTS;
    }
    return cust->getPhoneNumber();
}

Output_t<bool> RecordsCompany::isMember(int c_id){
    if(c_id<0){
        return StatusType::INVALID_INPUT;
    }
    Customer* cust;
    try{
        cust=m_customers.Find(c_id).get();
    }
    catch (ElementDoesntExist& exception){
        return StatusType::DOESNT_EXISTS;
    }
    return cust->isMember();
}


StatusType RecordsCompany::addPrize(int c_id1, int c_id2, double  amount){
    if(c_id1<0||c_id2<0||amount<=0){
        return StatusType::INVALID_INPUT;
    }
    m_members.addExtra(c_id1,c_id2,amount);
    return StatusType::SUCCESS;
}

StatusType RecordsCompany::putOnTop(int r_id1, int r_id2)
{
    if(r_id1<0||r_id2<0)
    {
        return StatusType::INVALID_INPUT;
    }
    if (r_id1>=m_recordings.getNumberOfMembers()||r_id2>=m_recordings.getNumberOfMembers())
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
    if(r_id>=m_recordings.getNumberOfMembers())
    {
        return StatusType::DOESNT_EXISTS;
    }
    m_recordings.find(r_id,column,hight);
    return StatusType::SUCCESS;
}
StatusType RecordsCompany::addCostumer(int c_id, int phone)
{
    if(c_id<0||phone<0)
    {
        return StatusType::INVALID_INPUT;
    }
    bool exists;
    try
    {
        m_customers.Find(c_id);
        exists=true;
    }
    catch(const ElementDoesntExist& e)
    {
        exists=false;   
    }
    if(exists)
    {
        return StatusType::ALREADY_EXISTS;
    }
    std::shared_ptr<Customer> newCustomer(nullptr);
    try
    {
        newCustomer=std::shared_ptr<Customer>(new Customer(c_id,phone));
    }
    catch(const std::exception& e)
    {
        return StatusType::ALLOCATION_ERROR;
    }
    m_customers.Insert(newCustomer,c_id);
    return StatusType::SUCCESS;  
}
StatusType RecordsCompany::makeMember(int c_id)
{
    if(c_id<0)
    {
        return StatusType::INVALID_INPUT;
    }
    Customer* customer;
    try
    {
        customer=m_customers.Find(c_id).get();   
    }
    catch(const ElementDoesntExist& e)
    {
        return StatusType::DOESNT_EXISTS;
    }
    if(m_members.search(c_id))
    {
        return StatusType::ALREADY_EXISTS;
    }
    try
    {
        m_members.insert(c_id,customer);
    }
    catch(const std::bad_alloc& e)
    {
        return StatusType::ALLOCATION_ERROR;
    }
    customer->makeMember();
    return StatusType::SUCCESS;   
}
StatusType RecordsCompany::buyRecord(int c_id, int r_id)
{
    if(c_id<0||r_id<0)
    {
        return StatusType::INVALID_INPUT;
    }
    if(r_id>=m_recordings.getNumberOfMembers())
    {
        return StatusType::DOESNT_EXISTS;
    }
    Customer* customer;
    try
    {
        customer=m_customers.Find(c_id).get();
    }
    catch(const std::exception& e)
    {
        return StatusType::DOESNT_EXISTS;   
    }
    if(customer->isMember())
    {
        customer->Addexpenses(UnionFind::BASE_RECORDING_PRICE+(double)m_recordings[r_id].getPurchases());   
    }
    m_recordings[r_id].incrementPurchases();
    return StatusType::SUCCESS;
}
Output_t<double> RecordsCompany::getExpenses(int c_id)
{
    if(c_id<0)
    {
        return StatusType::INVALID_INPUT;
    }
    if(!m_members.search(c_id))
    {
        return StatusType::DOESNT_EXISTS;
    }
    Customer* customer=m_members.getData(c_id);
    double totalExpenses=customer->getExpenses()-m_members.getExtra(c_id);
    return totalExpenses;
}