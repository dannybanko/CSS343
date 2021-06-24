//----------------------------------------------------------------------------
// CustomerHash.cpp 
// Implementation:
// -- This class is responsible for storing Customers for quick look up and
//    retrieval. This class will find a proper index to store a custumer and
//    will insert Customers to the proper index based on their Customer ID
// Assumptions:
// -- Customers hashValues will be decided based on the customers 4-digit id.
// -- id's will be unique
// -- if there are multiple values at the same list index, they will be
//    connected by a linked list
//----------------------------------------------------------------------------
#include "customerHash.hpp"

//-------------------------------constructor----------------------------------
// all values are initialized to default values
CustomerHash::CustomerHash() {
    for (int i = 0; i < MAX_CUSTOMERS; i++) {
        customerList[i] = nullptr;
    }
}

//--------------------------------destructor----------------------------------
// makes a call to make empty which we free all memory
CustomerHash::~CustomerHash() {
    makeEmpty();
}

//---------------------------------makeEmpty----------------------------------
// makeEmpty frees all memory in the hash table, properly emptying the table
// from al. customer objects
void CustomerHash::makeEmpty() {
    for (int i = 0; i < MAX_CUSTOMERS; i++) {
        if (customerList[i] != nullptr) {
            delete customerList[i];
            customerList[i] = nullptr;
        }
    }
}

//-----------------------------------insert-----------------------------------
// insert will insert a Customer* in the customerList using a hash value
// given by the private function hash(int id), if there is a collision, uses
// linear probing (find next available index) to insert.
bool CustomerHash::insert(Customer* toInsert) {
    int index = hash(toInsert->getID());
    
    if (customerList[index] == nullptr) {
        customerList[index] = toInsert;
        return true;
    }
    
    // solve collisions using linear probing
    int newIndex = (index + 1);
    for (int i = 0; i < MAX_CUSTOMERS; i++) {
        
        // start @ begginning if end of array has been reached
        if (newIndex == MAX_CUSTOMERS) index = 0;
        
        if (customerList[i] == nullptr) {
            customerList[i] = toInsert;
            return true;
        }
        newIndex++; // walk to next array index
        
    }
    // unsuccessful inset, return false
    return false;
}

//----------------------------------retrieve----------------------------------
// retrieve will find the desired customer if it exists in the hash table.
// takes into account linear probing for collisions, so retrieve checks to
// make sure that the correct custoner is retrieved.
bool CustomerHash::retrieve(int id, Customer*& toRetrieve) const {
    int index = hash(id); // get index
    
    // need to check if index holds the right cusotmer
    if (customerList[index] != nullptr && customerList[index]->getID() == id)
    {
        toRetrieve = customerList[index];
        return true;
    }
    
    // linear probe if not above case
    int newIndex = (index + 1);
    for (int i = 0; i < MAX_CUSTOMERS; i++) {
        
        // start @ begginning if end of array has been reached
        if (newIndex == MAX_CUSTOMERS) newIndex = 0;
        
        if ((customerList[newIndex] != nullptr) && // might need to be index
            (customerList[newIndex]->getID()== id)) {
            toRetrieve = customerList[newIndex];
            return true;
        }
    }
    return false;
}

//------------------------------------hash------------------------------------
// will return a hash value used as an index to store customer object
int CustomerHash::hash(int id) const {
    return id % MAX_CUSTOMERS;
}

//-----------------------------------dislay-----------------------------------
// displays all the customers in the customer hash. Used for testing to
// ensure all customers are being read and stored accordingly
void CustomerHash::display() const {
    for (int i = 0; i < MAX_CUSTOMERS; i++) {
        if (customerList[i] != nullptr) {
            customerList[i]->displayCustomer();
        }
    }
}
