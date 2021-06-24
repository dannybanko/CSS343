//----------------------------------------------------------------------------
// CustomerHash.h
// Implementation:
// -- This class is responsible for storing Customers for quick look up and
//    retrieval. This class will find a proper index to store a custumer and
//    will insert Customers to the proper index based on their Customer ID
// Assumptions:
// -- Customers hashValues will be decided based on the customers 4-digit id.
// -- id's will be unique
// -- if there are multiple values at the same list index, they will be
//    connected by a linked list
//----------------------------------------------------------------------------
#ifndef customerHash_hpp
#define customerHash_hpp

#include <iostream>
#include "customer.hpp"
using namespace std;

const int MAX_CUSTOMERS = 10000;  // array indexes 0-9999, max amount of
                                  // customers
class CustomerHash {
public:
    // constructor/destructors
    CustomerHash();
    ~CustomerHash();
    
    void makeEmpty();        // empties the hashTable

    bool insert(Customer*);  // will insert pointer Customer
    bool retrieve(int, Customer*&) const; // finds desired Customer
    
    void display() const;    // displays customer

private:
    Customer* customerList[MAX_CUSTOMERS];   // hashTable for customers, 10,000
                                             // max customers id's 0001-9999
    int hash(int) const; // gives index value for lookup/insert
};

#endif
