//--------------------------------bintree.cpp----------------------------------
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

#include "bintree.hpp"

//----------------------------------BinTree------------------------------------
// Constructs an empty Binary Tree (root is set to nullptr)
BinTree::BinTree() {
    root = nullptr;  // empty tree
}

//----------------------------------BinTree------------------------------------
// Constructs a deep copy of the parameter BinTree
BinTree::BinTree(const BinTree& other) {
    copy(other);
}

//---------------------------------~BinTree------------------------------------
// Empties the binary tree and deallocates all memory
BinTree::~BinTree() {
    makeEmpty();  // frees all memory
}

//------------------------------------copy-------------------------------------
// Makes a deep copy of the given tree.
// Preconditions: both BinTree objects are allocated
// Postconditions: returns this as a deep copy of the parameter BinTree
void BinTree::copy(const BinTree& other) {
    copyHelper(root, other.root);
}

//---------------------------------copyHelper----------------------------------
// Recursive helper to make a deep copy of the given tree.
// Preconditions: both BinTree objects are allocated
// Postconditions: returns this as a deep copy of the parameter BinTree
void BinTree::copyHelper(Node*& current, const Node* other) {
    if (other == nullptr) {
        return;
    }
    // copy NodeData
    current = new Node;
    current->data = new NodeData(*other->data);
    current->left = current->right = nullptr;
    
    copyHelper(current->left, other->left);    // walk left
    copyHelper(current->right, other->right);  // walk right
}

//----------------------------------isEmpty------------------------------------
// Returns true if tree is empty, false if its not empty
// Preconditions: BinTree is allocated
// Postconditions: returns true if BinTree has no nodes, false if nodes exist
bool BinTree::isEmpty() const {
    return root == nullptr;
}

//---------------------------------makeEmpty-----------------------------------
// Deleres all Nodes in the tree and deallocates all memory.
// Preconditions: BinTree is allocated
// PostConditions: this BinTree is empty and all memory has been deallocated
void BinTree::makeEmpty() {
    makeEmptyHelper(root);
    root = nullptr;
}

//------------------------------makeEmptyHelper--------------------------------
// Recursive helper to empty the tree.
// Preconditions: BinTree is allocated
// PostConditions: this BinTree is empty and all memory has been deallocated
void BinTree::makeEmptyHelper(Node* current) {
    if (current == nullptr) {
        return;
    }
    makeEmptyHelper(current->left);  // walk left subtree first
    makeEmptyHelper(current->right); // walk right subtree
    
    // free memory and clean up
    delete current->data;
    current->data = nullptr;
    delete current;
    current = nullptr;
}

//---------------------------------operator=-----------------------------------
// Performs a deep copy of the given Binary Tree using copy() private function.
// Preconditions: both BinTree objects are allocated
// Postconditions: returns this as a deep copy of the parameter BinTree object.
// all previous data in this have been properly deleted
BinTree& BinTree::operator=(const BinTree& other) {
    if (*this != other) {
        makeEmpty();  // free this memory
        copy(other);  // copy other
    }
    return *this;
}

//---------------------------------operator==----------------------------------
// Compares two BinTrees (preorder traversal) to make sure all the Nodes are
// the same and in the same spots
// Preconditions: both BinTrees are allocated
// Postconditions: returns true if all Nodes contain the same NodeData and if
// all nodes are in the correct (same_ positions, false otherwise
bool BinTree::operator==(const BinTree& other) const {
    return equalsHelper(root, other.root);
}

//------------------------------equalsHelper-----------------------------------
// Recursive helper for the operator==
// Preconditions: both Nodes are allocated
// Postconditions: returns true if the left and right subtrees of current Node
// and other Node are equal, and if the NodeDatas are equals determined by
// NodeData class operator==, false otherwise
bool BinTree::equalsHelper(Node* current, const Node* other) const {
    if (current == nullptr) {
        if (other == nullptr) {
            return true;
        }
        return false;
    }
    // current != nullptr
    if (other == nullptr) {
        return false;
    }
    if (*current->data != *other->data) {
        return false;
    }
    if (!equalsHelper(current->left, other->left)) {
        return false;
    }
    // left subtree is equal, check right subtree
    return equalsHelper(current->right, other->right);
}

//---------------------------------operator!=----------------------------------
// Compares two BinTrees (preorder traversal) to make sure all the Nodes are
// the same (if they are the same return false, return true if they aren't)
// Preconditions: Both BinTrees are allocates
// Postconditions: returns false if all this BinTree has all the same nodes and
// NodeData in the same spot as other BinTree, false otherwise
bool BinTree::operator!=(const BinTree& other) const {
    return !(*this == other);
}

//-----------------------------------insert------------------------------------
// Inserts a NodeData object into the proper sorted positions
// Preconditions: BinTree is allocated
// Postconditions: NodeData has been inserted into proper spot in this BinTree
// unless it is duplicate data
bool BinTree::insert(NodeData* toInsert) {
    if (toInsert == nullptr) {
        return false;  // NodeData doesn't exist
    }
    return insertHelper(toInsert, this->root);
}

//--------------------------------insertHelper---------------------------------
// recursive helper to insert NodeData into proper odered position
// Preconditions: BinTree is allocated
// Postconditions: NodeData has been inserted into proper spot in this BinTree
// unless it is duplicate data
bool BinTree::insertHelper(NodeData* toInsert, Node*& current) {
    if (current == nullptr) {  // found right spot to insert
        current = new Node;
        current->data = toInsert;
        current->left = current->right = nullptr;
        return true;
    }
    if (*toInsert == *current->data) {  // check for duplicate data
        return false;
    }
    if (*toInsert < *current->data) {  // figure out which subtree to walk
        return insertHelper(toInsert, current->left);  // left subtree
    } else {
        return insertHelper(toInsert, current->right); // right subtree
    }
}

//----------------------------------retrieve----------------------------------
// Takes a target NodeData to find in the BinTree and assigns a given pointer
// if NodeData is found.
// Preconditions: given NodeData and this BinTree are allocated.
// Postconditions: returns true if this tree contains given NodeData, false
// otherwise.
bool BinTree::retrieve(const NodeData& target, NodeData*& result) const {
    result = nullptr;  // make sure result isn't pointing to anything
    return retrieveHelper(root, target, result);
}

//-------------------------------retrieveHelper--------------------------------
// Recursive helper method to find a target NodeData and assign it to the given
// pointer.
// Preconditions: given NodeData and this BinTree are allocated.
// Postconditions: returns true if this tree contains given NodeData, false
// otherwise.
bool BinTree::retrieveHelper(const Node* current, const NodeData& target,
    NodeData*& result) const {
    
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

//----------------------------------getHeight----------------------------------
// Finds the height of a given data if it exists in the tree. Does not
// require the tree to be a Binary search tree (ordered)
// Preconditions: this BinTree and given NodeData are allocated
// Postconditions: returns 0 if not found, returns 1 + max height of both
// subtrees otherwise
int BinTree::getHeight(const NodeData& target) const {
    Node* result = nullptr; // create pointer to retrieve Node
    heightRetrieveHelper(root, target, result);  // retrieve the targer data
    if (result == nullptr) {
        return 0;  // NodeData doesnt exist
    }
    return heightHelper(result); // returns height of target data
}

//---------------------------heightRetrieveHelper-----------------------------
// Retrieves the target Node from an unordered BinTree (if it exists)
// Preconditions: this BinTree and given NodeData are allocated
// Postconditions: assigns a pointer to Node if found
void BinTree::heightRetrieveHelper(Node* current, const NodeData& target,
    Node*& result) const {
    
    if (current == nullptr) {
        return;
    }
    if (*current->data == target) {
        result = current;
        return;
    }
    heightRetrieveHelper(current->left, target, result); // walk left
    if (result != nullptr) {
        return;
    }
    heightRetrieveHelper(current->right, target, result); // walk right
}

//--------------------------------heightHelper---------------------------------
// Recursive helper to find the height of a given Node in the tree
// Preconditions: this BinTree and parameter Node are allocated
// Postconditions: returns 0 if not found, returns 1 + max height of both
// subtrees otherwise
int BinTree::heightHelper(Node* current) const {
    if (current == nullptr) {
        return 0;
    }
    
    int left = heightHelper(current->left);
    int right = heightHelper(current->right);
    
    // increase index everytime we walk to a different node
    if (left > right) {
        return 1 + left;
    } else {
        return 1 + right;
    }
}

//-------------------------------bsTreeToArray---------------------------------
// Removes all Nodes in this BinTree and places their NodeData into an array
// (inorder format)
// Preconditions: BinTree is allocated
// Postconditions: BinTree has been emptied, and array is filled with BinTrees
// data (inorder)
void BinTree::bstreeToArray(NodeData* output[]) {
    int index = 0;
    toArrayHelper(output, root, index);
    root = nullptr;
}

//-------------------------------toArrayHelper---------------------------------
// Recursive helper for emptying the tree into an array
// Preconditions: BinTree is allocated, index represents position in array
// where the next subtree will be stored
// Postconditions: current Node is deleted, and its left and right subtrees
// have been placed into the array (inorder)
void BinTree::toArrayHelper(NodeData* output[], Node* current, int& index) {
    if (current == nullptr) {
        return;
    }
    toArrayHelper(output, current->left, index);
    output[index] = current->data;
    index++;  // update array index
    toArrayHelper(output, current->right, index);
    
    // free memory
    current->left = current->right = nullptr;
    delete current;
    current = nullptr;
}

//-------------------------------arrayToBSTree---------------------------------
// Takes all NodeData from an array and constructs a balances BinTree (inorder)
// Array is emptied afterwards.
// Preconditions: BinTree and array are allocated
// Postconditions: balanced BinTree has been constructed with arrays NodeDatas,
// empty BinTree if array is empty
void BinTree::arrayToBSTree(NodeData* input[]) {
    int high = 0;  // last NodeData
    int low = 0;   // first NodeData
    for (int i = 0; i < 100; i++) {  // update high index
        if (input[i] != nullptr) {
            high = i;
        }
    }
    if (high == 0) {
        return;  // array is empty
    }
    toBTreeHelper(input, root, low, high);
}

//-------------------------------toBTreeHelper---------------------------------
// Recursive helper to convert an array to a binary tree.
// Preconditions: BinTree and array are allocated
// Postconditions: currents left subtree is assigned to the left of midpoint
// from low index to midpoint, right subtree is assigned from midpoint to high
// index. 
void BinTree::toBTreeHelper(NodeData* input[], Node*& current,
    int low, int high) {
    if (low > high) {
        return;
    }
    int mid = (low + high) / 2;   // calculate inorder position
    current = new Node;
    current->data = input[mid];
    current->left = current->right = nullptr;
    
    input[mid] = nullptr;
    toBTreeHelper(input, current->left, low, mid - 1);
    toBTreeHelper(input, current->right, mid + 1, high);
}

//------------------------- displaySideways ---------------------------------
// Displays a binary tree as though you are viewing it from the side;
// hard coded displaying to standard output.
// Preconditions: NONE
// Postconditions: BinTree remains unchanged.
void BinTree::displaySideways() const {
    sideways(root, 0);
}

//---------------------------- Sideways -------------------------------------
// Helper method for displaySideways
// Preconditions: NONE
// Postconditions: BinTree remains unchanged.
void BinTree::sideways(Node* current, int level) const {
    if (current != NULL) {
        level++;
        sideways(current->right, level);
        // indent for readability, 4 spaces per depth level
        for (int i = level; i >= 0; i--) {
            cout << "    ";
        }
        cout << *current->data << endl;
        // display information of object
        sideways(current->left, level);
    }
}

//--------------------------------operator<<-----------------------------------
// Prints out the tree in inorder format, with each NodeData separated by a
// space. E.g. (aaa bbb ccc)
// Preconditions: BinTree is allocated.
// Postconditions: NodeData has been printed to the given ostream
ostream& operator<<(ostream& output, const BinTree& tree) {
    tree.inorderHelper(output, tree.root);
    return output << endl;
}

//-------------------------------outputHelper----------------------------------
// Recursive helper to print the tree in inorder format to the given ostream.
// Preconditions: BinTree is allocated.
// Postconditions: Current's NodeData has been printed to the given ostream
// after it's left subtree but before it's right subtree.
void BinTree::inorderHelper(ostream& output, Node* current) const {
    if (current == nullptr) {
        return;
    }
    inorderHelper(output, current->left);
    cout << *current->data << " ";     // e.g. "aaa bbb ccc"
    inorderHelper(output, current->right);
}
