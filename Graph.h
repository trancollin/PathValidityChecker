/* Collin Tran
 * ctt200001
 */

#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <vector>
#include <iostream>

class Graph {
    public:
        //default constructor
        Graph(){};
        //returns the number of vertexes in the adjacency list
        int getSize() const {
            return (int)adjacency.size();
        }
        std::vector<std::vector<std::string>*>* getList() {
            return &adjacency;
        }
        //connects an edge to a specified vertex in the adjacency list
        void insertEdge(std::string vertex, std::string edge);
        
        //inserts a vertex into the adjacency list
        void insertVertex(std::string vertex);
        
        //deletes a vertex from the adjacency list
        std::vector<std::string>* deleteVertex(std::string vertex);
        
        //deletes an edge from the specified vertex
        std::string deleteEdge(std::string vertex, std::string edge);
    
    private:
        //adjacency list, holds vertexes and their respective edges
        //the vertexes are at index 0 of each of the vector pointers
        //all of a vertex's edges follow it in the vector pointers
        //edges are stored with their weights
        std::vector<std::vector<std::string>*> adjacency;
};

#endif