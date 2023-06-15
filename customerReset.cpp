#include "customerReset.h"



void customerReset::operator()(Customer* cust){
    cust->setExpenses(0);
}