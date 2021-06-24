//----------------------------------------------------------------------------
// Factory.cpp
// Implementation:
// -- Responsible for choosing which Movie class or Trandaction class to
//    create. The facotry is just used to create
// Assumptions:
// -- Data files are formatted properly, although data can be incorrect, the
//    lower level classes will check the validity of the Transaction methods
//    or the Movie type
//----------------------------------------------------------------------------
#include "factory.hpp"

//--------------------------------constructor---------------------------------
// sets all indexes to nullptr, and then assignes indexes to pointers to a
// movide genre. Index is assigned based on hashed value of the char type
Factory::Factory() {
    //  makes sure all original values are nullptr
    for (int i = 0; i < MAX_ITEMS; i++) {
        storeMovies[i] = nullptr;
        storeTransactions[i] = nullptr;
    }
    
    // determinds which type of movie to create
    storeMovies[2] = new Classic();
    storeMovies[3] = new Drama();
    storeMovies[5] = new Comedy();
    
    // determines which type of transaction to create
    storeTransactions[1] = new Borrow();
    storeTransactions[7] = new History();
    storeTransactions[17] = new ReturnItem();
}

//-------------------------------destructor-----------------------------------
// frees all memory
Factory::~Factory() {
    for (int i = 0; i < MAX_ITEMS; i++) {
        if (storeMovies[i] != nullptr) {
            delete storeMovies[i];
            storeMovies[i] = nullptr;
        }
        if (storeTransactions[i] != nullptr) {
            delete storeTransactions[i];
            storeTransactions[i] = nullptr;
        }
    }
}

//-----------------------------createMovie------------------------------------
// determins which type of movie object to create based on the hashed value of
// the char type being read in from the movie file. If type is not valid,
// error message will be printed
Movie* Factory::createMovie(char ch, ifstream& movieFile) {
    string temp;
    int subscript = hash(ch);
    
    if (storeMovies[subscript] == nullptr) {
        getline(movieFile, temp, '\n');
        return nullptr;
    } else {
        return storeMovies[subscript]->create();
    }
}

//----------------------------createTransaction-------------------------------
// determins which type of transaction object to create based on the hashed
// value of the char type being read in from the transaction file. If type is
// not valid, error message will be printed
Transaction* Factory::createTransaction(char ch, ifstream& commandFile) {
    string temp;
    int subscript = hash(ch);
    
    if (storeTransactions[subscript] != nullptr) {
        return storeTransactions[subscript]->create();
    } else {
        getline(commandFile, temp, '\n');
        return nullptr;
    }
}

//--------------------------------Subscript-----------------------------------
// will determine the proper spot in the store inventory list to store movie
// or transaction objects. Movies are stored with only alike movies
// e.g classics with classics (for sorting purposes).
int Factory::subscript(char ch) {
    return hash(ch);
}

//----------------------------------hash--------------------------------------
// will return the int hash value of a given char type for a movie or
// transaction
int Factory::hash(char ch) const {
    if (ch < 'a') {
        return ch - 'A';  // letters are assumed to be upper-case
    } else {
        return 0;
    }
}
