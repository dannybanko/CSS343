//---------------------------------GraphM.h------------------------------------
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

#ifndef graphm_hpp
#define graphm_hpp

#include "nodedata.hpp"
#include <istream>
using namespace std;

const int MAXNODES = 101; // maximum number of nodes for GraphM

class GraphM {

public:
    GraphM(); // constructor
    
    void buildGraph(ifstream&);      // sets graph data from .txt file
    
    bool insertEdge(int, int, int);  // inserts and edge and weight
    bool removeEdge(int, int);       // removed edge and weight
    
    void findShortestPath();  // updates path infomation for all noeds
    
    void displayAll() const;         // displays all path data
    void display(int, int) const;    // displays path data between 2 nodes

private:
    struct TableType {   // adjecency matrix
       bool visited;     // whether node has been visited
       int dist;         // shortest distance from source known so far
       int path;         // previous node in path of min dist
    };
    
    NodeData data[MAXNODES];         // data for graph nodes
    int C[MAXNODES][MAXNODES];       // Cost array, the adjacency matrix
    int size;                        // number of nodes in the graph
    TableType T[MAXNODES][MAXNODES]; // stores visited, distance, path
    
    void printPath(int, int) const;  // helper to print path
    void printData(int, int) const;  // helper to print data (node names)
    
};

#endif
