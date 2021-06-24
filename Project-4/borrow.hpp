//----------------------------------------------------------------------------
// Borrow.h
// Implementation:
// -- This class is responsible for updating the stock: decrease the stock by
//    1. It is Subclass of the Transaction class, get actiontype B and update
//    the stock
// Assumptions:
// -- inherits all behavior from Transaction parent class, although it has
//    a unique constructor and destructor
//----------------------------------------------------------------------------
#ifndef borrow_hpp
#define borrow_hpp

#include <fstream>
#include <iostream>
#include "transaction.hpp"
using namespace std;

class Customer;
class Borrow : public Transaction {
public:
    // constructors / destructors
    Borrow();
    ~Borrow();

    virtual void display() const; // this is to print the borrow info
    
    // processes the borrow transaction
    virtual bool process(string, Movie*, Customer*);
    
    // returns pointer to borrow object
    virtual Transaction* create();
    
};
#endif
