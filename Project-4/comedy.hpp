//----------------------------------------------------------------------------
// Comedy.h
// Implementation:
// -- This class is responsible for handling the comedy movies available in
//    the store. Comedy inherits the public variables and methods from Movie.
// Assumptions:
// -- Data file will be formatted correctly, although data may be incorrect
// -- Factory determines which type of movie object is created
//----------------------------------------------------------------------------
#ifndef comedy_hpp
#define comedy_hpp

#include <fstream>
#include <iostream>
#include "movie.hpp"
using namespace std;

class Comedy: public Movie {
public:
    // constructor / destructor
    Comedy();
   ~Comedy();

    virtual void setData(ifstream&);     // sets data members
    virtual void setTempData(ifstream&); // sets data to process Transaction

    
    // comparison operators for sorting
    virtual bool operator>(const Movie&) const;
    virtual bool operator<(const Movie&) const;
    virtual bool operator==(const Movie&) const;
    virtual bool operator!=(const Movie&) const;
    
    virtual Movie* create(); // returns pointer to Comedy
};
#endif

