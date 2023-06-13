#include "Customer.h"
Customer::Customer(int id,int phone):m_id(id),m_phoneNumber(phone),m_Expenses(0),m_isMemeber(false)
{}
bool Customer::isMember() const
{
    return m_isMemeber;
}
void Customer::makeMember()
{
    m_isMemeber=true;
}
int Customer::getPhoneNumber()const
{
    return m_phoneNumber;
}
void Customer::Addexpenses(double value)
{
    m_Expenses +=value;
}
double Customer::getExpenses()const
{
    return m_Expenses;
}