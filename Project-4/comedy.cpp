//----------------------------------------------------------------------------
// Comedy.cpp
// Implementation:
// -- This class is responsible for handling the comedy movies available in
//    the store. Comedy inherits the public variables and methods from Movie.
// Assumptions:
// -- Data file will be formatted correctly, although data may be incorrect
// -- Factory determines which type of movie object is created
//----------------------------------------------------------------------------
#include "comedy.hpp"

//--------------------------------constructor---------------------------------
// creates empty Comedy movie
Comedy::Comedy() : Movie() { }

//---------------------------------destructor---------------------------------
// needed to delete Drama
Comedy::~Comedy() { }

//----------------------------------setData-----------------------------------
// sets the data for the blank drama object after the factory creates a new
// drama movie
void Comedy::setData(ifstream& infile) {
    infile.ignore();
    infile >> stock;
    
    infile.ignore();
    getline(infile >> ws, director, ',');
    
    infile.ignore();
    getline(infile >> ws, title, ',');
    
    infile >> year;
}

//-------------------------------setTempData----------------------------------
// sets temporary data in processTransactions so movie can be retrieved from
// the inventory tree
void Comedy::setTempData(ifstream& infile) {
    infile.ignore();
    getline(infile >> ws, title, ',');
    infile >> year;
}

//--------------------------------operator<-----------------------------------
// determines if this is less than the other
bool Comedy::operator<(const Movie& other) const {
    const Comedy& comedyMovie = static_cast<const Comedy&>(other);
    if (title < comedyMovie.title) {
        return true;
    } else if (title == comedyMovie.title && year < comedyMovie.year) {
        return true;
    } else {
        return false;
    }
}

//--------------------------------operator<-----------------------------------
// determines if this is greater than the other
bool Comedy::operator>(const Movie& other) const {
    const Comedy& comedyMovie = static_cast<const Comedy&>(other);
    if (title > comedyMovie.title) {
        return true;
    } else if (title == comedyMovie.title && year > comedyMovie.year) {
        return true;
    } else {
        return false;
    }
}

//-------------------------------operator==-----------------------------------
// determines if this is equal to the other
bool Comedy::operator==(const Movie& other) const {
    const Comedy& comedyMovie = static_cast<const Comedy&>(other);
    return (title == comedyMovie.title && year == comedyMovie.year);
}

//-------------------------------operator!=-----------------------------------
// determines if this is not equal to the other
bool Comedy::operator!=(const Movie& other) const {
    const Comedy& comedyMovie = static_cast<const Comedy&>(other);
    return !(*this == comedyMovie);
}

//----------------------------------create------------------------------------
// returns a new Comedy object to the factory to be inserted into binary tree
// data will be set right after object is created in the buildInventory
// funtion in the store class.
Movie* Comedy::create() {
    return new Comedy();
}
