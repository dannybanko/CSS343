//----------------------------------------------------------------------------
// Store.cpp
// Implementation:
// -- This class is the driver for all the other classses in this program.
//    Store is responsible for running the movie business and calling all
//    neccessary funtions to build and run the business from lower level
//    classes.
// Assumptions:
// -- Customer data files are formatted properly
// -- Transaction data files are formatted properly however, data can be
//    incorrect
// -- Transaction data files are formatted properly hpwever, data can be
//    incorrect
//----------------------------------------------------------------------------
#include "store.hpp"

//-------------------------------constructor----------------------------------
// default constructor, methods will build data members
Store::Store() { }

//--------------------------------destructor----------------------------------
// needed to delete Store object
Store::~Store() { }

//-----------------------------buildVustomerList------------------------------
// will read in from the data4customers.txt file, create a pointer to a
// Customer object, which is passed into CustomerHash table insert function
// which will insert the customer into its proper hashed spot. This will
// constinue until the .txt file has no more Customer data.
void Store::buildCustomerList(ifstream& customerFile) {
    for (;;) {
        Customer* toInsert = new Customer(customerFile);
        
        if (customerFile.eof()) {
            delete toInsert;
            toInsert = nullptr;
            break;
        }
        
        bool success = table.insert(toInsert);
        
        if (!success) {
            delete toInsert;
            toInsert = nullptr;
        }
    }
}

//-----------------------------buildInventory---------------------------------
// will read in from data4mocies.txt file, create a new empty movie object of
// the proper type (from factory class) and then set the movies data, then it
// will insert the movie object into its personal BinTree based on the movie
// type; Classic, Drama, Comedy.
void Store::buildInventory(ifstream& movieFile) {
    char ch = ' ';
    
    while (!movieFile.eof()) {
        movieFile >> ch;
        if (movieFile.eof()) { break; }
        
        Movie* toInsert = factory.createMovie(ch, movieFile);
        
        if (toInsert != nullptr) {
            toInsert->setData(movieFile);
            bool success = inventory[factory.subscript(ch)].insert(toInsert);
            
            if (!success) {
                delete toInsert;
                toInsert = nullptr;
                
            }
        }
    }
}

//----------------------------processTransactions-----------------------------
// will read in from data4commands.txt file, and execute transactions using
// Transaction class definitions. Handles errors for invalid transactions,
// customer ids, transaction types, and movie
void Store::processTransactions(ifstream& commandsFile) {
    char ch = ' ';           // actionType
    char media = ' ';        // dvd
    char movieGenre = ' ';   // genre
    int id;                  // customer id
    
    string mediaType = "";   // used in process
    Customer* tempCustomer = nullptr;  // temporary customer
    Movie* tempMovie = nullptr;        // temporary movie
    Movie* toRetrieve = nullptr;       // movie to retrive from inventory
    bool deleteTransaction = false;
    while (!commandsFile.eof()) { // read until eof()
        deleteTransaction = false;
        commandsFile >> ch;  // transaction type
        
        if (commandsFile.eof()) {break;}
        
        if (ch == 'I') { // Inventory Transaction, just prints inventory
            displayInventory();
        } else { // H, B, or R
            
            // creates proper Transaction
            Transaction* newTransaction =
            factory.createTransaction(ch, commandsFile);
            deleteTransaction = true;
            
            if (newTransaction != nullptr) { // check validity of Transaction
                commandsFile >> id;
                
                if (commandsFile.eof()) {break;}
                
                if (table.retrieve(id, tempCustomer)) {  // get Customer
                    
                    if (ch == 'H') { // History
                        newTransaction->process(mediaType, tempMovie,
                                                tempCustomer); // display Hist
                    } else { // Borrow or Return
                        commandsFile >> media; // dvd
                        if (media == 'D') {
                            commandsFile >> movieGenre; // genre
                            // create proper movie type
                            tempMovie = factory.createMovie(movieGenre,
                                                        commandsFile);
                        }
                        if (tempMovie != nullptr) {
                            tempMovie->setTempData(commandsFile); // set data
                            
                            bool found = inventory[factory.
                            subscript(movieGenre)].retrieve(*tempMovie,
                                            toRetrieve); // finds movie
                            
                            // movie doesnt exist
                            if (found == false) {
                                cout << "Invalid Movie Request: " <<
                                tempMovie->getTitle() << " not found" << endl
                                << endl;
                            }
                            delete tempMovie;
                            tempMovie = nullptr;
                            
                            // process Transaction
                            bool processed = newTransaction->
                            process(mediaType, toRetrieve, tempCustomer);
                            
                            // movie exists, transaction is valid
                            if (found && processed) {
                                tempCustomer->addHistory(newTransaction);
                                deleteTransaction = false;
                            }
                        } else { // Movie doesn't exist
                            cout << "Invalid Movie Genre: " << movieGenre <<
                            " not found" << endl << endl;
                        }
                    }
                } else { // Customer doesn't exist
                    cout << "Invalid Customer ID: " << id << " not found" <<
                    endl << endl;
                }
                
            } else { // Transaction type doesn't exist
                cout << "Invalid Transaction Type: " << ch << " not found" <<
                endl << endl;
            }

            if (deleteTransaction) {
                delete newTransaction;
                newTransaction = nullptr;
            }
        }
    }
}

//----------------------------displayCustomers--------------------------------
// Used for testing purposes, displays all the customers in the customer hash
// table
void Store::displayCustomers() const {
    cout << "List of Current Customers:" << endl << endl;
    table.display();
}


//----------------------------displayInventory--------------------------------
// Used to display all the Inventory items. Will dicplay all Comedies, Dramas
// then classics. This function is called for transaction type 'I'
void Store::displayInventory() const {
    cout << "----------------------------StoreInventory";
    cout << "----------------------------" << endl << endl;
    for (int i = MAX_INVENTORY - 1; i >= 0; i--) { // comedy, drama, classic
        if (!inventory[i].isEmpty()) {
            inventory[i].display();
            cout << endl;
        }
    }
    cout << "-------------------------------------------------";
    cout << "---------------------" << endl << endl;
}


