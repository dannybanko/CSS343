//----------------------------------------------------------------------------
// Main
// Implementation:
// -- Responsible for building and running the movie business. Will create the
//    store and then perform all functions to run the business.
// -- Opens files and checks to make sure they can be read
// -- Calls all store methods to build and run the store.
//----------------------------------------------------------------------------
#include "store.hpp"
#include <iostream>
#include <fstream>
using namespace std;

int main() {
    // data files that contain customer, inventory, and transaction data
    ifstream infile1("data4customers.txt");  // customer file
    if (!infile1) {
        cout << "Error reading customers file)" << endl;
        return 1;
    }
    ifstream infile2("data4movies.txt");     // movie file
    if (!infile2) {
        cout << "Error reading movies file" << endl;
        return 1;
    }
    ifstream infile3("data4commands.txt");   // transaction file
    if (!infile3) {
        cout << "Error reading commands file" << endl;
        return 1;
    }
    
    // builds the business (Customer Hash-Table, and Inventory Trees)
    Store movieStore;
    movieStore.buildCustomerList(infile1);
    movieStore.buildInventory(infile2);
   
    // runs the business
    movieStore.processTransactions(infile3);
    return 0;
}
