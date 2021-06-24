//----------------------------------------------------------------------------
// ReturnItem.h
// Implementation:
// -- This class is responsible for updating the stock: increase the stock by
//    1. It is the Subclass f the Transaction class, get actiontype R and
//    update the stock
// Assumptions:
// -- Inherits all behavior from Transaction parent class, although it has
//    a unique constructor and destructor
//----------------------------------------------------------------------------
#ifndef returnItem_hpp
#define returnItem_hpp

#include <fstream>
#include <iostream>
#include "transaction.hpp"
using namespace std;

class Customer;
class ReturnItem : public Transaction {

public:
    // constructors / destructors
    ReturnItem();
    ~ReturnItem();

    virtual void display() const; // this is to print the borrow info
   
    // processes the ReturnItem transaction
    virtual bool process(string, Movie*, Customer*);
    
    // returns pointer to ReturnItem object
    virtual Transaction* create();
};
#endif
