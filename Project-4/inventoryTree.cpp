//-----------------------------------------------------------------------------
// InventoryTree.cpp
// Implementation:
// -- the internal representation of a binary search tree. Constructors,
//    accessors, and other operators and functions have been defined and
//    overloaded for BST manipulation in this program.
// Assumptions:
// -- Data file will be formatted correctly, although data may be incorrect
// -- Factory determines which type of movie object is created
//-----------------------------------------------------------------------------
#include "inventoryTree.hpp"

//----------------------------------InventoryTree------------------------------
// Constructs an empty Binary Tree (root is set to nullptr)
InventoryTree::InventoryTree() {
    root = nullptr;  // empty tree
}

//---------------------------------~InventoryTree------------------------------
// Empties the binary tree and deallocates all memory
InventoryTree::~InventoryTree() {
    makeEmpty();  // frees all memory
}

//----------------------------------isEmpty------------------------------------
// Returns true if tree is empty, false if its not empty
// Preconditions: InventoryTree is allocated
// Postconditions: returns true if InventoryTree has no nodes, false if nodes
// exist
bool InventoryTree::isEmpty() const {
    return root == nullptr;
}

//---------------------------------makeEmpty-----------------------------------
// Deleres all Nodes in the tree and deallocates all memory.
// Preconditions: InventoryTree is allocated
// PostConditions: this InventoryTree is empty and all memory has been
// deallocated
void InventoryTree::makeEmpty() {
    makeEmptyHelper(root);
    root = nullptr;
}

//------------------------------makeEmptyHelper--------------------------------
// Recursive helper to empty the tree.
// Preconditions: InventoryTree is allocated
// PostConditions: this InventoryTree is empty and all memory has been
// deallocated
void InventoryTree::makeEmptyHelper(Node* current) {
    if (current == nullptr) {
        return;
    }
    makeEmptyHelper(current->left);  // walk left subtree first
    makeEmptyHelper(current->right); // walk right subtree
    
    // free memory and clean up
    current->left = current->right = nullptr;
    delete current->data;
    current->data = nullptr;
    delete current;
    current = nullptr;
}

//-----------------------------------insert------------------------------------
// Inserts a NodeData object into the proper sorted positions
// Preconditions: InventoryTree is allocated
// Postconditions: NodeData has been inserted into proper spot in this
// InventoryTree unless it is duplicate data
bool InventoryTree::insert(Movie* toInsert) {
    return insertHelper(toInsert, this->root);
}

//--------------------------------insertHelper---------------------------------
// recursive helper to insert NodeData into proper odered position
// Preconditions: InventoryTree is allocated
// Postconditions: NodeData has been inserted into proper spot in this
// InventoryTree unless it is duplicate data
bool InventoryTree::insertHelper(Movie* toInsert, Node*& current) {
    if (current == nullptr) {  // found right spot to insert
        current = new Node();
        current->data = toInsert;
        current->left = current->right = nullptr;
        return true;
    }
    if (*toInsert == *current->data) {  // check for duplicate data
        current->data->increaseStock(toInsert->getStock());
        return false;
    }
    if (*toInsert < *current->data) {  // figure out which subtree to walk
        return insertHelper(toInsert, current->left);  // left subtree
    } else {
        return insertHelper(toInsert, current->right); // right subtree
    }
}

//----------------------------------retrieve----------------------------------
// Takes a target NodeData to find in the InventoryTree and assigns a given
// pointer if NodeData is found.
// Preconditions: given NodeData and this InventoryTree are allocated.
// Postconditions: returns true if this tree contains given NodeData, false
// otherwise.
bool InventoryTree::retrieve(const Movie& target, Movie*& result) const {
    result = nullptr;  // make sure result isn't pointing to anything
    return retrieveHelper(root, target, result);
}

//-------------------------------retrieveHelper--------------------------------
// Recursive helper method to find a target NodeData and assign it to the given
// pointer.
// Preconditions: given NodeData and this InventoryTree are allocated.
// Postconditions: returns true if this tree contains given NodeData, false
// otherwise.
bool InventoryTree::retrieveHelper(const Node* current, const Movie& target,
    Movie*& result) const {
    
    if (current == nullptr) {
        return false;
    }
    if (*current->data == target) {
        result = current->data;
        return true;
    }
    if (target < *current->data) {
        return retrieveHelper(current->left, target, result);  // walk left
    } else {
        return retrieveHelper(current->right, target, result); // walk right
    }
}

//---------------------------------display-------------------------------------
// Displays the contents of the BSTree in sorted order: comedy>drama>classic
// Preconditions: BSTree has been allocated.
// Postconditions: Console output with all the movies in sorted order
void InventoryTree::display() const {
    displayHelper(root);
}

//---------------------------------displayHelper-------------------------------
// Recursive Helper to display the contents of the BSTree (inorder traversal)
// Preconditions: BSTree has been allocated.
// Postconditions: Console output with all the movies in sorted order
void InventoryTree::displayHelper(Node* current) const {
    if (current == nullptr) {
        return;
    }
    displayHelper(current->left);
    current->data->display();
    displayHelper(current->right);
}


