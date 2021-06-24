//----------------------------------------------------------------------------
// Borrow.cpp
// Implementation:
// -- This class is responsible for updating the stock: decrease the stock by
//    1. It is Subclass of the Transaction class, get actiontype B and update
//    the stock
// Assumptions:
// -- inherits all behavior from Transaction parent class, although it has
//    a unique constructor and destructor
//----------------------------------------------------------------------------
#include "borrow.hpp"

//------------------------------constructor-----------------------------------
Borrow::Borrow() : Transaction() {
    actionType = 'B';
}

//------------------------------destructor------------------------------------
Borrow::~Borrow() { }

//--------------------------------display-------------------------------------
// displays transaction and media types
void Borrow::display() const {
    cout << mediaType << " " << actionType << " ";
}

//--------------------------------process-------------------------------------
// will process the borrow transaction. decreases the stock of the movie held
// in inventory tree and checks to make sure that item is still in stock
// before transaction is processed
bool Borrow::process(string media, Movie* movie, Customer* customer) {
    if (movie != NULL){
        mediaType = media;
        item = movie;
        if (movie->getStock() <= 0) { // check stock
            cout << "Movie: " << movie->getTitle() << " is out of stock" <<
            endl << endl;
            return false; // can't process transaction
        } else {
            movie->decreaseStock();
        }
    }
    return true;  // processed transaction
}

//---------------------------------create-------------------------------------
// returs a pointer to a Borrow transaction for factory
Transaction* Borrow::create() {
    return new Borrow();
}
