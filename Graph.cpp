/* Collin Tran
 * ctt200001
 */

#include "Graph.h"

/* The function creates a vector pointer and inserts a specified vertex into it
 * The vector pointer is then inserted into the adjacency vector, creating the adjacency list
 */
void Graph::insertVertex(std::string vertex){
    std::vector<std::string> *edges = new std::vector<std::string>;
    edges->push_back(vertex);
    (*getList()).push_back(edges);
}

/* The function creates inserts edges into the vector pointer containing their specified vertex
 * The adjacency vector is searched for a starting vertex matching the specified one
 * When the vertex is found, the edge is appended to its vector pointer
 * If the vertex isn't found, nothing is inserted into the adjacency list
 */
void Graph::insertEdge(std::string vertex, std::string edge){
    //search the adjacency list for the specified vertex
    for(int i = 0; i < (int)(*getList()).size(); i++){
        //if a starting vertex in the adjacency list matches the specified one, append the edge and exit the loop
        if((*getList()).at(i)->at(0) == vertex){
            (*getList()).at(i)->push_back(edge);
            break;
        }
    }
}

/* The function removes a vertex from the adjacency list
 * This includes all instances of a vertex, including instances where it's an edge of another vertex
 * The vector pointer of the specified vertex is returned
 * If the adjacency list is empty or the vertex isn't found, an empty vector pointer is returned
 */
std::vector<std::string>* Graph::deleteVertex(std::string vertex){
    std::vector<std::string>* v;
    if(!(*getList()).empty()){
        for(int i = (int)(*getList()).size() - 1; i >= 0; i--){
            //check for if the current vector pointer is for the vertex to be removed
            if((*getList()).at(i)->at(0) == vertex){
                //if so, set the hold var to the vector and remove it from the adjacency list
                v = (*getList()).at(i);
                (*getList()).erase((*getList()).begin() + i);
            }
            //otherwise, see if the current vector has any edges that are the vertex
            else{
                for(int k = 1; k <(int)(*getList()).at(i)->size(); k++){
                    std::string potedge = (*getList()).at(i)->at(k);
                    //if so, remove the edge
                    if(potedge.substr(0, potedge.find(',')) == vertex){
                        (*getList()).at(i)->erase((*getList()).at(i)->begin() + k);
                    }
                }
            }
        }
    }
    return v;
}

/* The function removes an edge from a specified vertex
 * The function searches the adjacency list to see if the starting vertex matches the specified one
 *      If so, the function searches the vector pointer of the vertex to see if the edge is there
 *          If so, the edge is removed and saved to the hold variable
 * The edge that was removed is returned
 * If the edge isn't found or the adjacency list is empty, an empty string is returned
 */
std::string Graph::deleteEdge(std::string vertex, std::string edge){
    std::string e = "";
    if(!(*getList()).empty()){
        for(int i = 0; i < (int)(*getList()).size(); i++){
            //finds the specified vector
            if((*getList()).at(i)->at(0) == vertex){
                for(int k = 1; k <(int)(*getList()).at(i)->size(); k++){
                    std::string potedge = (*getList()).at(i)->at(k);
                    //if the edge is connected to the vector, remove it
                    if(potedge.substr(0, potedge.find(',')) == edge){
                        //save edge to hold var 
                        e = potedge;
                        (*getList()).at(i)->erase((*getList()).at(i)->begin() + k);
                    }
                }   
            }
        }
    }
    return e;
}
