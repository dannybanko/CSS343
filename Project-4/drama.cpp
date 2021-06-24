//----------------------------------------------------------------------------
// Drama.cpp
// Implementation:
// -- This class is responsible for handling the drama movies available in
//    the store. Drama inherits the public variables and methods from Movie.
// Assumptions:
// -- Data file will be formatted correctly, although data may be incorrect
// -- Factory determines which type of movie object is created
//----------------------------------------------------------------------------
#include "drama.hpp"

//--------------------------------constructor---------------------------------
// creates empty Drama movie
Drama::Drama() : Movie() { }

//---------------------------------destructor---------------------------------
// needed to delete Drama
Drama::~Drama() { }

//----------------------------------setData-----------------------------------
// sets the data for the blank drama object after the factory creates a new
// drama movie
void Drama::setData(ifstream& infile) {
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
void Drama::setTempData(ifstream& infile) {
    infile.ignore();
    getline(infile >> ws, director, ',');
    infile.ignore();
    getline(infile >> ws, title, ',');
}

//--------------------------------operator<-----------------------------------
// determines if this is less than the other
bool Drama::operator<(const Movie& other) const {
    const Drama& dramaMovie = static_cast<const Drama&>(other);
    if (director < dramaMovie.director) {
        return true;
    } else if (director == dramaMovie.director && title < dramaMovie.title) {
        return true;
    } else {
        return false;
    }
}

//--------------------------------operator<-----------------------------------
// determines if this is greater than the other
bool Drama::operator>(const Movie& other) const {
    const Drama& dramaMovie = static_cast<const Drama&>(other);
    if (director > dramaMovie.director) {
        return true;
    } else if (director == dramaMovie.director && title > dramaMovie.title) {
        return true;
    } else {
        return false;
    }
}

//-------------------------------operator==-----------------------------------
// determines if this is equal to the other
bool Drama::operator==(const Movie& other) const {
    const Drama& dramaMovie = static_cast<const Drama&>(other);
    return (director == dramaMovie.director && title == dramaMovie.title);
}

//-------------------------------operator!=-----------------------------------
// determines if this is not equal to the other
bool Drama::operator!=(const Movie& other) const {
    const Drama& dramaMovie = static_cast<const Drama&>(other);
    return !(*this == dramaMovie);
}

//----------------------------------create------------------------------------
// returns a new Drama object to the factory to be inserted into binary tree
// data will be set right after object is created in the buildInventory
// funtion in the store class.
Movie* Drama::create() {
    return new Drama();
}
