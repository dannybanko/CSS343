//----------------------------------------------------------------------------
// Store.h
// Implementation:
// -- This class is the driver for all the other classses in this program.
//    Store is responsible for running the movie business and calling all
//    neccessary funtions to build and run the business from lower level
//    classes.
// Assumptions:
// -- Customer data files are formatted properly
// -- Transaction data files are formatted properly however, data can be
//    incorrect
// -- Transaction data files are formatted properly hpwever, data can be
//    incorrect
//----------------------------------------------------------------------------
#ifndef store_hpp
#define store_hpp

#include <iostream>
#include <fstream>
#include <stack>
#include "customer.hpp"
#include "factory.hpp"
#include "customerHash.hpp"
#include "inventoryTree.hpp"
using namespace std;

const int MAX_INVENTORY = 10;  // 10 different items (arbitrary value)

class Store {
public:
    
    // constuctors/destructors
    Store();  // constructor
    ~Store(); // destructor
    
    void buildCustomerList(ifstream&);   // populates the customers
    void buildInventory(ifstream&);      // pupulates inventory tree
    void processTransactions(ifstream&); // runs the transactions
    
    // testing
    void displayCustomers() const;  // used for testing, shows all customers
    void displayInventory() const;  // used for testing, shows all movies
    
    // retrieving customers
    bool findCustomer(int) const;    // tells us if the customer exists
    Customer getCustomer(int) const; // returns the customer for transations
    
    
private:
    CustomerHash table;   // hashTable for customers
    Factory factory;      // factory to choose which movie or
                          // Transaction to build
    
    InventoryTree inventory[MAX_INVENTORY];  // holds all movie items
};
#endif
