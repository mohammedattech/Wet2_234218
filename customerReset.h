#ifndef CUSTOMER_RESET_H
#define CUSTOMER_RESET_H
#include "Customer.h"

class customerReset{
public:
    customerReset();
    void operator()(Customer* cust);
};






#endif