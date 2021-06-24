//----------------------------------------------------------------------------
// Classic.h
// Implementation:
// -- This class is responsible for handling the classic movies available in
//    the store. Classic inherits the public variables and methods from Movie.
// Assumptions:
// -- Data file will be formatted correctly, although data may be incorrect
// -- Factory determines which type of movie object is created
//----------------------------------------------------------------------------
#ifndef classic_hpp
#define classic_hpp

#include <fstream>
#include <iostream>
#include "movie.hpp"
using namespace std;

class Classic : public Movie {
public:
    // constructor / destructor
    Classic();
    ~Classic();

    virtual void display() const;  // displays the movie
    
    virtual void setData(ifstream&);     // sets data members
    virtual void setTempData(ifstream&); // sets data to process Transaction
    
    // comparison operators for sorting
    virtual bool operator>(const Movie&) const;
    virtual bool operator<(const Movie&) const;
    virtual bool operator==(const Movie&) const;
    virtual bool operator!=(const Movie&) const;
    
    virtual Movie* create(); // returns a pointer to a Classic
    
private:
    string actorFName;   // actor's first name
    string actorLName;   // actor's lsat name
    int month;           // release month
};

#endif
