//----------------------------------------------------------------------------
// Movie.cpp
// Implementation:
// -- This class is responsible for handling the movies available in the store.
//    It reads from "data4movies.txt" and creates a movie object depending on
//    depending on movie genre (F, D, or C) and other inputted movie information.
// Assumptions:
// -- Data file will be formatted correctly, although data may be incorrect
// -- Factory determines which type of movie object is created
//----------------------------------------------------------------------------
#include "movie.hpp"

//--------------------------------constructor---------------------------------
Movie::Movie() {
    genre = ' ';
    title = "";
    director = "";
    year = 0;
    stock = 0;
}

//---------------------------------destructor---------------------------------
Movie::~Movie() { }

//----------------------------------display-----------------------------------
// will display the movies data members for the displayInventory method in
// the store class
void Movie::display() const {
    cout << left << setw(8) << setfill(' ') << "stock:" << left << setw(4)
         << setfill(' ') << stock;
    cout << left << setw(11) << setfill(' ') << "director: " << left
         << setw(20) << setfill(' ') << director;
    cout << left << setw(8) << setfill(' ') << "title: " << left
         << setw(35) << setfill(' ') << title;
    cout << left << setw(6) << setfill(' ') <<  "year:" << year << " ";
    cout << endl;
}

//----------------------------------setData-----------------------------------
// sets the data for the blank movie object after the factory creates a new
// movie
void Movie::setData(ifstream& infile) {
    infile.get();
    getline(infile, director, ',');
    
    infile.get();
    getline(infile, title, ',');
    
    infile.get();
    infile >> year;
}

//----------------------------------stock-------------------------------------
void Movie::increaseStock() { stock++; }

void Movie::decreaseStock() { stock--; }

void Movie::increaseStock(int count) { stock += count; } // for duplicate

//----------------------------------getters-----------------------------------
string Movie::getTitle() const { return title; }

string Movie::getDirector() const {  return director; }

int Movie::getYear() const { return year; }

int Movie::getStock() const { return stock; }
