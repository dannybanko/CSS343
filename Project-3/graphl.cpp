//---------------------------------GraphL.cpp----------------------------------
// Danny Banko, CSS 343A
// Date Created: 11/02/2020
// Date Last Modified: 11/11/2020
//-----------------------------------------------------------------------------
// GraphL Class
// Purpose:
// - GraphL is a Depth First Search class that will perform depth first-search
//   on a graph and provide a DFS ordering of the nodes visited. This class is
//   to help perform depth first searches on graphs, which can properly build
//   a graph from a data file.
//-----------------------------------------------------------------------------
// Implementation and Assumptions:
// - NodeNata is reponsible for all functions creating, deleting, and comparing
//   NodeData objects. Strings will be no longer than 50 characters.
// - The data file is formatted correctly, sice first, then node names, then
//   edges, then 0 0 to terminate
// - Uses an adjecency list (array of lists) to keep track of node edges.
// - EdgeNode struct holds the node's data

#include "graphl.hpp"
#include <iomanip>
#include <climits>
//-------------------------------constructor-----------------------------------
// constructs a GraphL and sets all values to false or nullptr
GraphL::GraphL() {
    size = 0;  // default size
    
    for (int i = 1; i <= MAXNODESL; i++) {
        nodeArr[i].visited = false;  // not visited
        nodeArr[i].edgeHead = nullptr;  // no list head
        nodeArr[i].data = nullptr;  // no data
    }
}

//-------------------------------destructor------------------------------------
// destrucotr for GraphL, calls privare function makeEmpty()
GraphL::~GraphL() {
    makeEmpty();  // private function call
}

//--------------------------------makeEmpty------------------------------------
// will free all alocated memory and destruct the GraphL object. Only called in
// ~GraphL()
// Preconditions: GraphL object is allocated
// PostConditions: GraphL is empty and all memory has been freed
void GraphL::makeEmpty() {
    // delete NodeData
    for (int i = 1; i <= size; i++) {
        
        nodeArr[i].visited = false;  // update visited information
        delete nodeArr[i].data;  // delete name
        nodeArr[i].data = nullptr;
    }
    
    // delete EdgeNodes
    for (int i = 1; i <= size; i++) {
        if (nodeArr[i].edgeHead != nullptr) {  // head exists
            EdgeNode* nodeToDelete = nodeArr[i].edgeHead; // point to head
            
            while (nodeToDelete != nullptr) {  // travel the list
                nodeArr[i].edgeHead = nodeArr[i].edgeHead->nextEdge;
                delete nodeToDelete;  // delete node
                nodeToDelete = nullptr;
                nodeToDelete = nodeArr[i].edgeHead; // move head
            }
        }
    }
}

//--------------------------------buildGraph-----------------------------------
// builds the graph with all the nodes, node information, and the list of edges
// Preconditions: GraphL is allocated
// Postconditions: All graph data has been created (edge lists) and all data
// is updated
void GraphL::buildGraph(ifstream &infile) {
   
    // read in size
    infile >> size;
    
    string name;            // variable to save node name
    getline(infile, name);  // read node name into variable
    
    // set node names
    for (int i = 1; i <= size; i++) {
        getline(infile, name);
        NodeData* data = new NodeData(name);
        nodeArr[i].data = data;
    }
    
    int from, to; // from-node to-node
    
    while (infile >> from >> to) {
        // stop reading if 0
        if (from == 0) {
            break;
        } else {
            setEdge(from, to); // sets the edge in adjecency list
        }
    }
}

//-----------------------------depthFirstSearch--------------------------------
// performs depth-first search on the graph, uses helper function. Will print
// the path ordering of nodes visited
void GraphL::depthFirstSearch() {
    
    cout << "Depth-First ordering:";
    
    // all nodes are not visited at this point
    for (int i = 1; i <= size; i++) {
        if (!nodeArr[i].visited) {   // check if visited
            dfsHelper(i); // calls helper
        }
    }
    cout << endl << endl;
}

//----------------------------------dfsHelper----------------------------------
// helper for depthFirstSearch() will check the adjacent nodes to the given
// parameter node and perfom dfs until all nodes are visited
void GraphL::dfsHelper(int v) {
    
    cout << setw(2) << v;  // prints path

    nodeArr[v].visited = true;  // mark v visted
    EdgeNode* current = nodeArr[v].edgeHead;
    
    while (current != nullptr) {  // walk the list
        if (!nodeArr[current->adjGraphNode].visited) {  // check if visited
            dfsHelper(current->adjGraphNode);
        }
        current = current->nextEdge;  // update current
    }
}

//----------------------------------setEdge------------------------------------
// sets the edges in the adjecency list (array of lists)
// Preconditions: GraphL is allocated and all its data is default
// Postconditions: The edge information in the adjecency list has been updated
void GraphL::setEdge(int from, int to) {
    // first node at index
    if (nodeArr[from].edgeHead == nullptr) {
        EdgeNode* node = new EdgeNode;
        node->adjGraphNode = to;  // add adge
        nodeArr[from].edgeHead = node; // point to head
        nodeArr[from].edgeHead->nextEdge = nullptr;
        
    } else { // additional nodes at index get put in edge List
        EdgeNode* node = new EdgeNode;
        node->adjGraphNode = to; // add edge
        node->nextEdge = nodeArr[from].edgeHead; // move pointer
        nodeArr[from].edgeHead = node; // assign head
    }
}

//--------------------------------displayGraph---------------------------------
// will display all the nodes and their edges using couts
// Preconditions: GraphL is allocated
// Postconditions: Graphs nodes and their edges have been printed
void GraphL::displayGraph() {
    cout << "Graph:" << endl;
    
    for (int i = 1; i <= size; i++) {
        cout << "Node " << i << "         " << *nodeArr[i].data << endl;
        
        EdgeNode* current = nodeArr[i].edgeHead;
        
        while (current != nullptr) {  // walk the list
            cout << setw(7) << "  edge  " << i << "  "
                << current->adjGraphNode;
            cout << endl;
            
            current = current->nextEdge;  // update current
        }
    }
    cout << "\n";
}
