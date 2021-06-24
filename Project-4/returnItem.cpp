//----------------------------------------------------------------------------
// ReturnItem.cpp
// Implementation:
// -- This class is responsible for updating the stock: increase the stock by
//    1. It is the Subclass f the Transaction class, get actiontype R and
//    update the stock
// Assumptions:
// -- Inherits all behavior from Transaction parent class, although it has
//    a unique constructor and destructor
//----------------------------------------------------------------------------
#include "returnItem.hpp"

//------------------------------constructor-----------------------------------
ReturnItem::ReturnItem() : Transaction() {
    actionType = 'R';
}

//------------------------------destructor------------------------------------
ReturnItem::~ReturnItem() { }

//--------------------------------display-------------------------------------
// displays transaction and media types
void ReturnItem::display() const {
    cout << mediaType << " " << actionType << " ";
}

//--------------------------------process-------------------------------------
// will process the return transaction. increases the stock of the movie held
// in inventory tree
bool ReturnItem::process(string media, Movie* movie, Customer* customer) {
    if (movie != NULL){
        mediaType = media;
        item = movie;
        item->increaseStock();
    }
    return true;
}

//---------------------------------create-------------------------------------
// returs a pointer to a ReturnItem transaction for factory
Transaction* ReturnItem::create() {
    return new ReturnItem();
}
