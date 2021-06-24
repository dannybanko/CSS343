//----------------------------------------------------------------------------
// Factory.h
// Implementation:
// -- Responsible for choosing which Movie class or Trandaction class to
//    create. The facotry is just used to create
// Assumptions:
// -- Data files are formatted properly, although data can be incorrect, the
//    lower level classes will check the validity of the Transaction methods
//    or the Movie type
//----------------------------------------------------------------------------
#ifndef factory_hpp
#define factory_hpp

#include <iostream>
#include <fstream>
#include "classic.hpp"
#include "drama.hpp"
#include "comedy.hpp"
#include "transaction.hpp"
#include "borrow.hpp"
#include "history.hpp"
#include "returnItem.hpp"

const int MAX_ITEMS = 26; // for each letter of alphabet
using namespace std;

class Factory {
public:
    // constructors / destructors
    Factory();
    ~Factory();
    
    // returns location in factory for proper object
    int subscript(char);
    
    // creates the proper child class objects of Transaction or Movie
    Movie* createMovie(char, ifstream&);
    Transaction* createTransaction(char, ifstream&);
    
private:
    Movie* storeMovies[MAX_ITEMS];
    Transaction* storeTransactions[MAX_ITEMS];
    
    int hash(char) const; // location of proper object
};
#endif
