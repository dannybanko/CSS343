//----------------------------------------------------------------------------
// InventoryTree.h
// Implementation:
// -- the internal representation of a binary search tree. Constructors, accessors,
//    and other operators and functions have been defined and overloaded for BST
//    manipulation in this program.
// Assumptions:
// -- Data file will be formatted correctly, although data may be incorrect
// -- Factory determines which type of movie object is created
//----------------------------------------------------------------------------
#ifndef inventoryTree_hpp
#define inventoryTree_hpp

#include <iostream>
#include "movie.hpp"
using namespace std;

class InventoryTree {
public:
    InventoryTree();       // default constructor
    ~InventoryTree();      // destructor, calls makeEmpty
    
    bool isEmpty() const;  // true if tree is empty, otherwise false
    void makeEmpty();      // make the tree empty so isEmpty returns true
    
    void display() const;  // displays contents
     
    bool insert(Movie*);   // inserts Node into sorted position
    bool retrieve(const Movie &, Movie* &) const;  // retrieves
    
private:
    struct Node {
        Movie* data;   // pointer to data object
        Node* left;    // left subtree pointer
        Node* right;   // right subtree pointer
    };
    Node* root;        // root of the tree

    // helper functions
    void makeEmptyHelper(Node*);
    bool insertHelper(Movie*, Node*&);
    bool retrieveHelper(const Node*, const Movie&, Movie*&) const;
    void displayHelper(Node*) const;
};

#endif
