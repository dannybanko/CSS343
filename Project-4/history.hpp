//----------------------------------------------------------------------------
// History.h
// Implementation:
// -- This class is responsible for storing the history of customers
//    transactions with movie type
// Assumptions:
// -- Inherits all behavior from Transaction parent class, although it has
//    a unique constructor and destructor
// -- display() makes a call to Customer displayHistor() method
//----------------------------------------------------------------------------
#ifndef history_hpp
#define history_hpp

#include <fstream>
#include <iostream>
#include "transaction.hpp"
#include "customerHash.hpp"
#include "inventoryTree.hpp"
using namespace std;

class Customer;
class History : public Transaction {
public:
    
    // constructor / destructor
    History();
    ~History();
    
    // processes transaction
    virtual bool process(string, Movie*, Customer*);
    
    // returns pointer to History
    virtual Transaction* create();
};
#endif
