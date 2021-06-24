//----------------------------------------------------------------------------
// Customer.h
// Implementation:
// -- Customers hold a 4-digit unique id a last name and a first name.
//    Customers will be held in a hash table for quick look up and retrieval.
//    Customers will also be in charge of holding their own Transaction
//    history with the use of STL stack for LIFO.
// Asumptions:
// -- The data file will be formatted correctly, as well as id's will be a
//    unique 4-digit number.
// -- Customers keep track of thier own Transaction history
// -- STL stack is used to LIFO display Transaction history
//----------------------------------------------------------------------------
#ifndef customer_hpp
#define customer_hpp

#include <iostream>
#include <fstream>
#include <vector> // used to store Customer's Transaction history
#include <iomanip>
#include "transaction.hpp"
using namespace std;

class Customer {
public:
    
    // constructory / destructors
    Customer();
    Customer(ifstream&);
    ~Customer();
    
    // history functions
    void addHistory(Transaction*);
    void displayHistory();
    
    // display the Customer
    void displayCustomer() const;
    
    // getters for Customer retrieval and comparison
    int getID() const;
    string getLastName() const;
    string getFirstName() const;
    
    // operator overloads
    bool operator==(const Customer&) const;
    bool operator!=(const Customer&) const;
    
private:
    int id; // 4 digit id
    string lastName;  // customer last name
    string firstName; // customer first name
    vector<Transaction*> history;
};
#endif

