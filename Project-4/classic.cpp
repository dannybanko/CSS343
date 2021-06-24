//----------------------------------------------------------------------------
// Classic.cpp
// Implementation:
// -- This class is responsible for handling the classic movies available in
//    the store. Classic inherits the public variables and methods from Movie.
// Assumptions:
// -- Data file will be formatted correctly, although data may be incorrect
// -- Factory determines which type of movie object is created
//----------------------------------------------------------------------------
#include "classic.hpp"

//--------------------------------constructor---------------------------------
Classic::Classic() : Movie() { }

//---------------------------------destructor---------------------------------
Classic::~Classic() { }

//----------------------------------display-----------------------------------
// will display the movies data members for the displayInventory method in
// the store class
void Classic::display() const {
    cout << left << setw(8) << setfill(' ') << "stock:" << left << setw(4)
         << setfill(' ') << stock;
    cout << left << setw(11) << setfill(' ') << "director: " << left
         << setw(20) << setfill(' ') << director;
    cout << left << setw(8) << setfill(' ') << "title: " << left
         << setw(35) << setfill(' ') << title;
    cout << left << setw(6) << setfill(' ') <<  "year:" << year << "  ";
    cout << left << setw(7) << setfill(' ') << "month:" << month << " ";
    cout << endl;
}

//----------------------------------setData-----------------------------------
// sets the data for the blank classic object after the factory creates a new
// classic movie
void Classic::setData(ifstream& infile) {
    infile.ignore();
    infile >> stock;
    
    infile.ignore();
    getline(infile >> ws, director, ',');
    
    infile.ignore();
    getline(infile >> ws, title, ',');
    
    infile.ignore();
    infile >> actorFName;
    infile.ignore();
    infile >> actorLName;
    infile.ignore();
    infile >> month;
    infile.ignore();
    infile >> year;
}

//-------------------------------setTempData----------------------------------
// sets temporary data in processTransactions so movie can be retrieved from
// the inventory tree
void Classic::setTempData(ifstream& infile) {
    infile >> month >> year >> actorFName >> actorLName;
}

//--------------------------------operator<-----------------------------------
// determines if this is less than the other
bool Classic::operator<(const Movie& other) const {
    const Classic& classicMovie = static_cast<const Classic&>(other);
    if (year < classicMovie.year) {
        return true;
    } else if (year == classicMovie.year && actorFName <
               classicMovie.actorFName) {
        return true;
    } else if (actorFName == classicMovie.actorFName && actorLName <
               classicMovie.actorLName) {
        return true;
    } else {
        return false;
    }
}

//--------------------------------operator<-----------------------------------
// determines if this is greater than the other
bool Classic::operator>(const Movie& other) const {
    const Classic& classicMovie = static_cast<const Classic&>(other);
    if (year > classicMovie.year) {
        return true;
    } else if (year == classicMovie.year && actorFName >
               classicMovie.actorFName) {
        return true;
    } else if (actorFName == classicMovie.actorFName && actorLName >
               classicMovie.actorLName){
        return true;
    } else {
        return false;
    }
}

//-------------------------------operator==-----------------------------------
// determines if this is equal to the other
bool Classic::operator==(const Movie& other) const {
    const Classic& classicMovie = static_cast<const Classic&>(other);
    return (year == classicMovie.year && month == classicMovie.month);
}

//-------------------------------operator!=-----------------------------------
// determines if this is not equal to the other
bool Classic::operator!=(const Movie& other) const {
    const Classic& classicMovie = static_cast<const Classic&>(other);
    return !(*this == classicMovie);
}

//----------------------------------create------------------------------------
// returns a new Comedy object to the factory to be inserted into binary tree
// data will be set right after object is created in the buildInventory
// funtion in the store class.
Movie* Classic::create() {
    return new Classic();
}
