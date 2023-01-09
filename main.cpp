/* Collin Tran
 * ctt200001
 */
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <utility>

#include "Graph.h"

using namespace std;

//prototypes
int checkPathValidity(stringstream &ss, string vertex, string neighbor, Graph g, int pathweight);
void sortDrivers(vector<pair<int, string>*> &drivers);
void printDrivers(vector<pair<int, string>*> &drivers);

/* The function prints all of the drivers and their information in the drivers vector once it has been sorted
 * The order is driver name, path weight, and path validity
 *      All of these are separated with a tab
 * If the path weight is 0, the path is invalid
 *      Otherwise, the path is valid
 * All driver information is printed on separate lines
 */
void printDrivers(vector<pair<int, string>*> &drivers){
    //for all drivers in the vector
    for(int i = 0; i < (int)drivers.size(); i++){
        //print driver name and path weight
        cout << drivers.at(i)->second << '\t' << drivers.at(i)->first << '\t';
        //if pathweight is 0, print the path is invalid
        if(drivers.at(i)->first == 0){
            cout << "invalid" << endl;
        }
        //otherwise, print that the path is valid
        else {
            cout << "valid" << endl;
        }
    }
}

/* The function sorts the drivers vector
 * The function uses an insertion sort algorithm
 * Initially, the path weight values of each driver are compared
 * If the path weight values of two drivers are the same, then their names are compared instead
 * The vector is sorted in ascending order
 * At the end of the function, the printDrivers function is called
 */
void sortDrivers(vector<pair<int, string>*> &drivers){
    //for all drivers in the vector
    for(int i = 1; i < (int)drivers.size(); i++){
        //set search index and hold var
        int k = i;
        pair<int, string> *temp = drivers.at(i);
        //traverses until the search index reaches the front of the vector the current driver is not less than the one in front of it
        while(k > 0){
            //if the path weight of the current driver isn't less than the one before it, exit the loop
            if(temp->first > drivers.at(k - 1)->first){
                break;
            }
            //if the path weight of the current driver is less than the one before it, decrement the search index
            else if(temp->first < drivers.at(k - 1)->first){
                drivers.at(k) = drivers.at(k - 1);
                k--;
            }
            //if the path weight of the two drivers are the same, compare their names
            else if(temp->first == drivers.at(k - 1)->first){
                //if the current driver's name comes before the driver before it, decrement the search index
                if(temp->second < drivers.at(k - 1)->second){
                    drivers.at(k) = drivers.at(k - 1);
                    k--;
                }
                //otherwise, exit the loop
                else {
                    break;
                }
            }
        }
        //places the current driver where the search index is
        drivers.at(k) = temp;
    }
    //print the driver vector
    printDrivers(drivers);
}

/* The function check to see if a path in the routes file is valid
 * The traversal through the adjacency list is done recursively
 * The traversal is done until the stringstream is empty
 *      The path's weight is returned once the stringstream is empty
 * Initially, vertex is loaded with the starting vertex from the route, and neighbor is blank
 * If the vertex is in the adjacency list, the neighbor is searched for.
 *      If not, 0 is returned as the path's weight
 * If the vertex is neighbors with the neighbor, the path's weight is added to pathweight, and the function is called again.
 *      If not, 0 is returned as the path's weight
 */
int checkPathValidity(stringstream &ss, string vertex, string neighbor, Graph g, int pathweight){
    //while there are still edges in the route
    if(ss >> neighbor){
        vector<string>* v;
        //checks for the vertex in the adjacency list
        for(int i = 0; i < (int)(*g.getList()).size(); i++){
            if((*g.getList()).at(i)->at(0) == vertex){
                v = (*g.getList()).at(i);
                break;
            }
            //if the vertex isn't there, return 0
            if(i == (int)(*g.getList()).size() - 1){
                return 0;
            }
        }
        //checks for the neighbor in the vertex vector
        for(int k = 1; k < (int)v->size(); k++){
            string potedge = v->at(k);
            //if it's there, add the path's weight to pathweight and recursively call
            if(potedge.substr(0, potedge.find(',')) == neighbor){
                string weight = v->at(k);
                weight.erase(0, weight.find(',') + 1);
                return checkPathValidity(ss, neighbor, "", g, pathweight + stoi(weight));
            }
        }
        //if the neighbor isn't in the vertex's vector, return 0
        return 0;
    }
    //if there are no more edges to check in the route, return the path's weight
    else {
        return pathweight;
    }
}

int main()
{
    //variables
    ifstream inFS;
    string filename;
    string graphline;
    string routeline;
    Graph g;
    
    //read the graph file, and open it
    cin >> filename;
    inFS.open(filename);
    //if the graph file is open, fill the adjacency list
    if(inFS.is_open()){
        //while the graph file isn't empty
        while(getline(inFS, graphline)){
            //create a string stream out of the next line of the file
            stringstream ss(graphline);
            //parse and insert the vertex into the adjacency list
            string vertex;
            ss >> vertex;
            g.insertVertex(vertex);
            
            //while there are still edges in the line, insert them into the adjacency list
            string edge;
            while(ss >> edge){
                g.insertEdge(vertex, edge);
            }
        }
    }
    //close the graph file
    inFS.close();
    
    //read the route file and open it
    cin >> filename;
    inFS.open(filename);
    //if the file is open
    if(inFS.is_open() && !(*g.getList()).empty()){
        //create a vector to hold all driver information
        vector<pair<int, string>*> drivers;
        //while the route file isn't empty
        while(getline(inFS, routeline)){
            stringstream ss(routeline);
            //parse the driver's name into drivername
            string drivername;
            ss >> drivername;
            //parse the first vertex into startvertex
            string startvertex;
            ss >> startvertex;
            //get the weight of the path
            int pathweight = checkPathValidity(ss, startvertex, "", g, 0);
            //create a pair, with the first part being the weight and the second part being the driver's name
            pair<int, string> *p =  new pair<int, string>;
            p->first = pathweight;
            p->second = drivername;
            //append the driver pair to the drivers vector
            drivers.push_back(p);
        }
        //once the route file is empty, sort the driver vector
        sortDrivers(drivers);
    }
    inFS.close();
    return 0;
}
