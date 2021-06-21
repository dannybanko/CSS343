//--------------------------------bintree.h------------------------------------
// Danny Banko, CSS 343A
// Date Created: 10/18/2020
// Date last modified: 10/25/2020
//-----------------------------------------------------------------------------
// BinTree class
// Purpose:
// -- BinTree is a Binary Tree ADT that uses a NodeData class to store data
//    which will be stored in the BinTree. This class helps search for elements
//    in a more efficient manner than other data structure. Class can't remove
//    nodes (not required)
//-----------------------------------------------------------------------------
// Assumptions:
// -- NodeData class does all the operation overloading within its own member
//    functions
// -- NodeDatas with equal values are discarded (no duplicate data)
// -- Smaller NodeDatas are stored in left subtree, bigger NodeDatas in right
//    subtree
// -- tree Node is a struct that uses NodeData class
// -- getHeight and helper functions assumes tree is unsorted, accurately
//    returning height of a Node. Leaf is at height 1
// -- opperator<< prints tree in inrder format
// -- Asuumes max size of array to be 100 elements, meaning array is static and
//    doesn't resize for the number of Nodes in the BinTree

#ifndef bintree_hpp
#define bintree_hpp

#include <iostream>
#include "nodedata.hpp"
using namespace std;

class BinTree {
    friend ostream& operator<<(ostream&, const BinTree&); // output overload
    
public:
    BinTree();                // default constructor
    BinTree(const BinTree &); // copy constructor
    ~BinTree();               // destructor, calls makeEmpty
    
    bool isEmpty() const;     // true if tree is empty, otherwise false
    void makeEmpty();         // make the tree empty so isEmpty returns true
    
    BinTree& operator=(const BinTree &);    // assigns this to param BinTree
    bool operator==(const BinTree &) const; // == overload
    bool operator!=(const BinTree &) const; // != overload
    
    bool insert(NodeData*);  // inserts Node into sorted position
    bool retrieve(const NodeData &, NodeData* &) const;  // retrieves
    int getHeight(const NodeData&) const;// gets the high of the given NodeData
       
    
    void bstreeToArray(NodeData* []);  // converts a BinTree into an array
    void arrayToBSTree(NodeData* []);  // converts an array into a BinTree
    
    void displaySideways() const;  // prints BinTree as if you were viewing it
                                   // from the side
    
private:
    struct Node {
        NodeData* data;    // pointer to data object
        Node* left;        // left subtree pointer
        Node* right;       // right subtree pointer
    };
    Node* root;            // root of the tree

    // utility functions and helper functions
    void copy(const BinTree&);
    void copyHelper(Node*&, const Node*);
    void makeEmptyHelper(Node*);
    
    void heightRetrieveHelper(Node*, const NodeData&, Node*&) const;
    int heightHelper(Node*) const;
    
    bool equalsHelper(Node*, const Node*) const;
    bool insertHelper(NodeData*, Node*&);
    bool retrieveHelper(const Node*, const NodeData&, NodeData*&) const;
    
    void inorderHelper(ostream&, Node*) const;   // helper for operator <<
    void sideways(Node*, int) const;
    
    void toArrayHelper(NodeData* [], Node*, int&);
    void toBTreeHelper(NodeData* [], Node*&, int, int);
    
};

#endif /* bintree_hpp */
