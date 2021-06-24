//---------------------------------GraphM.cpp----------------------------------
// Danny Banko, CSS 343A
// Date Created: 11/27/2020
// Date Last Modified: 11/11/2020
//-----------------------------------------------------------------------------
// GraphM Class
// Purpose:
// - GraphM is a class designed to perform Dijkstra's shortest path algorithm
//   on a graph of nodes. It builds the graph from a data file, and then finds
//   the shortest path from all nodes to all other nodes (if a path exists)
//-----------------------------------------------------------------------------
// Implementation and Assumptions:
// - NodeNata is reponsible for all functions creating, deleting, and comparing
//   NodeData objects. Strings will be no longer than 50 characters.
// - The data file is formatted correctly, size first, then node names, then
//   edges, then 0 0 to terminate
// - Uses an adjecency matrix to keep track of node edges, weights, data,
//   and visited/not visited

#include "graphm.hpp"
#include <climits>
#include <iomanip>
//--------------------------------constructor----------------------------------
// constructs a defualt adjecency matrix and TableType
GraphM::GraphM() {
    
    size = 0; // default: no nodes exist yet
    
    for (int row = 0; row < MAXNODES; row++) {  // rows
        for (int col = 0; col < MAXNODES; col++) {  // cols
            
            C[row][col] = INT_MAX;        // default: infinite cost
            T[row][col].visited = false;  // default: not visited
            T[row][col].dist = INT_MAX;   // default: infinite dist
            T[row][col].path = 0;         // default: no paths
        }
    }
}

//--------------------------------buildGraph-----------------------------------
// updates the data array and the adjacency matrix from data31.txt
// Preconditions: GraphM object is allocated including default valuses for all
// private data members.
// Postconditions: Adjecency graph is updated with node edges and sitances,
// and data array is updated with node names
void GraphM::buildGraph(ifstream& infile1) {
    // reads in the number of nodes
    infile1 >> size;
    
    string name;             // variable to save node name to
    getline(infile1, name);  // read node name into variable
    
    for (int i = 1; i <= size; i++) {
        data[i].setData(infile1);  // sets the name of the NodeData
    }
    
    // node edges
    int from, to, distance;
    
    while (infile1 >> from >> to >> distance) {
        // check for 0, note: 0 index isn't used for nodes so this is the end
        // of the node edges data
        if (from == 0) {
            break;
        }
        
        C[from][to] = distance; // sets the distance for edge
    }
}

//--------------------------------insertEdge-----------------------------------
// Insserts row column and dist information into the adjecency matrix. Sets
// distance at [row][col] = distance
// Preconditions:
// Postcondtions:
bool GraphM::insertEdge(int from, int to, int distance) {
    
    if (from > size || from < 1) {  // check validity of nodes
        return false;
    } else if (to > size || to < 1) {
        return false;
    } else if (from == to && distance != 0) { // path to itself
        return false;
    }
    
    if (distance < 0) {  // no such thing as negative distance
        return false;
    }
    
    C[from][to] = distance; // insert distance
    findShortestPath(); // update path information
    return true;
}

//--------------------------------removeEdge-----------------------------------
// Removes row column and dist information from the adjecency matrix. Sets
// distance at [row][col] = INT_MAX
// Preconditions:
// Postconditions:
bool GraphM::removeEdge(int from, int to) {
    if (from > size || from < 1) {  // check validity of nodes
        return false;
    } else if (to > size || to < 1) {
        return false;
    }
    
    C[from][to] = INT_MAX;  // remove edge, or reset to INT_MAX if edge dne
    findShortestPath(); // update path information
    return true;
}

//------------------------------findShortestPath-------------------------------
// Finds the shortest path every node to every other node in the adjecency
// matrix. TabltType T will be updated with shortest path information
// Preconditions: GraphM and dzta are built
// Postconditions: GraphM is filled with updated path and weght information
void GraphM::findShortestPath() {
    
    for (int source = 1; source <= size; source++) {
        T[source][source].dist = 0;
        T[source][source].visited = true;
        
        // finds all neighbor nodes updates path info
        for (int neighbor = 1; neighbor <= size; neighbor++) {
            if (C[source][neighbor] != INT_MAX) {
                T[source][neighbor].dist = C[source][neighbor];
                T[source][neighbor].path = source;
            }
        }
        
        // find shortest distance from source to all other nodes
        for (int i = 1; i <= size; i++) {
            
            int v = 0;
            int minDist = INT_MAX;
            
            // finds smallest path of unvisited nodes
            for (int neighbor = 1; neighbor <= size; neighbor++) {
                if (!T[source][neighbor].visited && C[source][neighbor] <
                        minDist)
                {
                    minDist = C[source][neighbor]; // save shortest distance
                    v = neighbor;  // set neighbot
                }
            }
            
            // node with smallest distance, only 0 if it doesn't exist
            if (v != 0) {
                
                T[source][v].visited = true;  // mark v visited
                
                for (int w = 1; w <= size; w++) { // look for adj nodes to v
                    if (!T[source][w].visited) {  // shouldn't be visited
                        if (C[v][w] < INT_MAX) {  // no path
                            if (v != w) {         // same node
                                if (T[source][w].dist > T[source][v].dist +
                                    C[v][w])
                                {
                                    // update distance
                                    T[source][w].dist = T[source][v].dist +
                                    C[v][w];
                                    // update path
                                    T[source][w].path = v;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

//--------------------------------displayAll-----------------------------------
// Will display all node data (name) and discplay the node numbers, their
// neighbor node, the distance between the to/from node, and the shortest path
// to get from to node to from node
// Preconditions: GraphM is allocated and filled with updated path info
// Postconditions: Each node and their edges/distances have been displayed
void GraphM::displayAll() const {
    cout << "Description" << setw(24) << "From Node" << setw(9) << "To Node"
      << setw(12) << "Dijkstra's" << setw(6) << "Path" << endl;
    
    
    for (int row = 1; row <= size; row++) { // rows of matrix
        cout << data[row] << endl;   // prints node name
        
        // prints node from, to and distance
        for (int col = 1; col <= size; col++) { // cols of matrix
            if (row != col) {
                cout << setw(32) << row << setw(8) << col;
                
                if (T[row][col].dist < INT_MAX) { // path exists
                    cout << setw(8) << T[row][col].dist << setw(11);
                    printPath(row, col);  // prints path of nodes visited
                } else {  // no path
                    cout << setw(9) << "---";
                }
                cout << endl;
            }
        }
    }
    cout << endl;
}

//---------------------------------display-------------------------------------
// Will display a from node and a to node and the distance between them with
// its shortest path calls recusive helpers for path and data information
// Preconditions: GraphM is allocated woth updated path and weight info
// Postconditions: The total path weight and the path are printed, as well as
// the names of each node visited
void GraphM::display(int from, int to) const {
    
    // check if nodes are valid
    if ((from > size || from < 0) || (to > size || to < 0)) {
        cout << setw(4) << from << setw(8) << to;
        cout << setw(10) << "----" << endl << endl;
        return;
    }
    
    cout << setw(4) << from << setw(8) << to;

    if (T[from][to].dist != INT_MAX) {  // check if path exists
        cout << setw(8) << T[from][to].dist << setw(11);
        printPath(from, to);  // helper call
        cout << endl;
        
        printData(from, to);  // helper call
        
    } else {  // path doesn't exist
        cout << setw(10) << "----";
        cout << endl << endl;
    }
}

//---------------------------------printPath-----------------------------------
// recursive helper for displayAll and display. Will recursively print the path
// of nodes visited
// Preconditions: GraphM is allocated and filled with updated information
// Postconditions: The path from from node to node is printed, no changes to
// GraphM information
void GraphM::printPath(int from, int to) const {

    if (T[from][to].dist == INT_MAX) { // path doesn't exisr
        return;
    } else if (from == to) { // path is to itself
        cout << to << " ";
        return;
    } else {  // path exists
        int path = to;
        printPath(from, T[from][to].path);  // recursive call
        
        cout << path << " ";
    }
}

//---------------------------------printData-----------------------------------
// recursive helper for display. Will print all the visited node names in the
// order of which they were visited
// Preconditions: GraphM is allocated and filled with updated information
// Postconditions: The names of the nodes visited are printed, no changes to
// GraphM information
void GraphM::printData(int from, int to) const {

    if (T[from][to].dist == INT_MAX) {  // path doesn't exist
        return;
    } else if (from == to) {  // path to itself
        cout << data[to] << endl << endl;
        return;
    } else {  // path exists
        int dataTo = to;
        printData(from, T[from][to].path); // recursive call
        
        cout << data[dataTo] << endl << endl;
    }
}
