//----------------------------------------------------------------------------
// Customer.cpp
// Implementation:
// -- Customers hold a 4-digit unique id a last name and a first name.
//    Customers will be held in a hash table for quick look up and retrieval.
//    Customers will also be in charge of holding their own Transaction
//    history with the use of STL stack for LIFO.
// Asumptions:
// -- The data file will be formatted correctly, as well as id's will be a
//    unique 4-digit number.
// -- Customers keep track of thier own Transaction history
// -- STL stack is used to LIFO display Transaction history
//----------------------------------------------------------------------------
#include "customer.hpp"

//--------------------------------constructor---------------------------------
// sets default values for the Customer, won't be used in this assignment
Customer::Customer() {
    id = 0000;
    lastName = "";
    firstName = "";
}

//--------------------------------constructor---------------------------------
// reads in data from the data4customers.txt file to build customer and set
// data members
Customer::Customer(ifstream& infile) {
    infile >> id;
    if (infile.eof()) {
        return;
    }
    infile >> lastName >> firstName;
}

//---------------------------------destructor---------------------------------
// nneded to delete customer objects. No leeks possible.
Customer::~Customer() {
    for(int i=0; i < history.size(); i++) {
        Transaction* temp = history[i];
        delete temp;
        temp = nullptr;
    }
}

//---------------------------------addHistory---------------------------------
// adds a Transaction object to the Customers transaction history
void Customer::addHistory(Transaction* transaction) {
    history.push_back(transaction);
}

//-------------------------------displayHistory-------------------------------
// displays all the Transactions in the history collection, if history is
// empty, then message will print saying so.
void Customer::displayHistory() {
    if (history.size() == 0) {
        cout << "No Transaction history for Customer: " << id << endl << endl;
    } else {
        cout << "Transaction History for Customer: " << id << " " << lastName
        << ", " << firstName << endl;
    
        for (int i = (int)history.size() - 1; i >= 0 ; i--) { // loop through STL stack
            Transaction* temp = history[i];  // use top Transaction
            cout << "Action Type: " << temp->getActionType() <<
            "   Movie Title: ";  // print action type
            cout << temp->getMovie()->getTitle(); // print title
            cout << endl;
        }
        cout << endl;
    }
}

//------------------------------displayCustomer-------------------------------
// Used for hash Tables displayCustomers method. Mainly used for testing to
// make sure that all data is correct and all customers are read properly
void Customer::displayCustomer() const {
    cout << firstName << " " << lastName << " " << id << endl;
}

//-----------------------------------getters----------------------------------
int Customer::getID() const { return id; }

string Customer::getLastName() const { return lastName; }

string Customer::getFirstName() const { return firstName; }

//----------------------------------overloads---------------------------------
bool Customer::operator==(const Customer& other) const {
    return id == other.id;
}

bool Customer::operator!=(const Customer& other) const {
    return id != other.id;
}


