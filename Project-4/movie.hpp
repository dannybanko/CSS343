//----------------------------------------------------------------------------
// Movie.hpp
// Implementation:
// -- This class is responsible for handling the movies available in the store.
//    It reads from "data4movies.txt" and creates a movie object depending on
//    depending on movie genre (F, D, or C) and other inputted movie information.
// Assumptions:
// -- Data file will be formatted correctly, although data may be incorrect
// -- Factory determines which type of movie object is created
//----------------------------------------------------------------------------
#ifndef movie_hpp
#define movie_hpp

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
using namespace std;

class Movie {
public:
    // constructor / destructor
    Movie();
    virtual ~Movie();
    
    virtual void display() const;  // prints Movie
    
    // sets data for factory
    virtual void setData(ifstream&);
    virtual void setTempData(ifstream&) = 0;
    
    // getters
    virtual string getTitle() const;
    string getDirector() const;
    int getYear() const;
    int getStock() const;
    
    // deals with the stock of each movie
    void increaseStock();  // + 1
    void decreaseStock();  // - 1

    void increaseStock(int count);  // increase by count items
    
    // comparison operators pure vitual as movies have their own
    // comparison criteria
    virtual bool operator>(const Movie&) const = 0;
    virtual bool operator<(const Movie&) const = 0;
    virtual bool operator==(const Movie&) const = 0;
    virtual bool operator!=(const Movie&) const = 0;
    
    virtual Movie* create() = 0;

protected:
    char genre;      // genre of movie
    string title;    // movie title
    string director; // director name
    int stock;       // stock
    int year;        // release year
};
#endif

