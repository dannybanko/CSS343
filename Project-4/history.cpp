//----------------------------------------------------------------------------
// History.cpp
// Implementation:
// -- This class is responsible for storing the history of customers
//    transactions with movie type
// Assumptions:
// -- Inherits all behavior from Transaction parent class, although it has
//    a unique constructor and destructor
// -- display() makes a call to Customer displayHistor() method
//----------------------------------------------------------------------------
#include "history.hpp"

//------------------------------constructor-----------------------------------
History::History() : Transaction() { }

//------------------------------destructor------------------------------------
History::~History() { }

//--------------------------------process-------------------------------------
// will process the history transaction. Calls the customer's displayHistory
// method which will print the history if it exists, or print a message to
// let us know there is no history for this customer
bool History::process(string mediaType, Movie* movie, Customer* customer) {
    customer->displayHistory();
    return true;
}

//---------------------------------create-------------------------------------
// returns a pointer to a History object for factory
Transaction* History::create() {
    return new History();
}
