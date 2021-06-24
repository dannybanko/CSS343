//----------------------------------------------------------------------------
// Transaction.cpp
// Implementation:
// -- This class is responsible for handling the transactions performed by
//    customers. Reads from "data4commands.txt and perform the transaction
//    depending on ActionType(B, R, I, H),
// Assumptions:
// -- Data file will be formatted correclty, however data may be incorrect
// -- Factory determines which type of transaction object is created
//----------------------------------------------------------------------------
#include "transaction.hpp"

//-------------------------------constructor----------------------------------
Transaction::Transaction() { }

//-------------------------------destructor-----------------------------------
Transaction::~Transaction() { }

//---------------------------------display------------------------------------
// will display the movie type and the transaction type
void Transaction::display() const {
    cout << mediaType << " " << actionType << ": " << endl;
}

//---------------------------------process------------------------------------
// processes the transactins. Function is overwritten in all the child classes
bool Transaction::process(string media, Movie* movie, Customer* customer) {
    return false;
}

//---------------------------------getters------------------------------------
char Transaction::getMovieType() const { return movieType; }

char Transaction::getActionType() const { return actionType; }

Movie* Transaction::getMovie() { return item; }

//----------------------------------create------------------------------------
// creates the proper type of transaction object
 Transaction* Transaction::create() {
    return new Transaction();
}
