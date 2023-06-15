#ifndef CUSTOMER_H
#define CUSTOMER_H
class Customer
{    
public:
    Customer(int id,int phone);
    ~Customer()=default;
    bool isMember() const;
    void makeMember();
    int getPhoneNumber() const;
    void Addexpenses(double value);
    double getExpenses() const;
    void setExpenses(double amount);
private:
    int m_id;
    int m_phoneNumber;
    double m_Expenses;
    bool m_isMemeber;
};
#endif