//---------------------------------GraphL.h------------------------------------
// Danny Banko, CSS 343A
// Date Created: 11/02/2020
// Date Last Modified: 11/11/2020
//-----------------------------------------------------------------------------
// GraphL Class
// Purpose:
// - GraphL is a Depth First Search class that will perform depth first-search
//   on a graph and provide a DFS ordering of the nodes visited. This class is
//   to holp perform depth first searches on graphs, which can properly build
//   a graph from a data file.
//-----------------------------------------------------------------------------
// Implementation and Assumptions:
// - NodeNata is reponsible for all functions creating, deleting, and comparing
//   NodeData objects. Strings will be no longer than 50 characters.
// - The data file is formatted correctly, sice first, then node names, then
//   edges, then 0 0 to terminate
// - Uses an adjecency list (array of lists) to keep track of node edges.
// - EdgeNode struct holds the node's data

#ifndef graphl_hpp
#define graphl_hpp

#include "nodedata.hpp"
#include <iostream>
using namespace std;

int const MAXNODESL = 101;  // used as max number of nodes in the graph

class GraphL {

public:
    GraphL();  // constructor
    ~GraphL(); // destructor
    
    void buildGraph(ifstream&); // builds the graph
    void depthFirstSearch();    // performs depth-first search with helper
    void displayGraph();        // displays the graph
  
private:
    int size;  // number of nodes
    
    struct EdgeNode;        // forward reference for the compiler
    struct GraphNode {      // structs used for simplicity
        EdgeNode* edgeHead; // head of the list of edges
        NodeData* data;     // data information about each node
        bool visited;
    };
    
    struct EdgeNode {
        int adjGraphNode;  // subscript of the adjacent graph node
        EdgeNode* nextEdge;
    };

    GraphNode nodeArr[MAXNODESL]; // adjecency list
    
    void makeEmpty();     // used in destructor
    void dfsHelper(int);  // helper for depthFirstSearch()
    void setEdge(int, int);  // sets edges in build graph
};
#endif
