//----------------------------------------------------------------------------
// Transaction.h
// Implementation:
// -- This class is responsible for handling the transactions performed by
//    customers. Reads from "data4commands.txt and perform the transaction
//    depending on ActionType(B, R, I, H),
// Assumptions:
// -- Data file will be formatted correclty, however data may be incorrect
// -- Factory determines which type of transaction object is created
//----------------------------------------------------------------------------
#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <fstream>
#include <iostream>
#include "movie.hpp"
using namespace std;

class Customer; // prevent circular include
class Transaction {

public:
    // constructors / destructors
    Transaction();
    virtual ~Transaction();

    virtual void display() const; // print the current transaction
    
    // processes the Transaction
    virtual bool process(string, Movie*, Customer*);
    
    virtual Transaction* create();  // creates proper transaction

    // getters
    char getMovieType() const;  // get the media type F, C, D
    char getActionType() const; // get transaction type, B, R, I, H
    Movie* getMovie();  // get movie
    
protected:
    Customer* client; // pointer to Customer for the Transaction
    char actionType;  // B, R, I, H - Borrow, Return, Inventory, History
    char movieType;   // F, C, D  Funny, Classic, or Drama
    string mediaType; // dvd, vcr, etc.
    Movie* item;      // pointer to Movie for the Transaction
};
#endif
