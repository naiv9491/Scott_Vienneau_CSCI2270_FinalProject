#ifndef GRAPH_H
#define GRAPH_H
#include <vector>
#include <iostream>

struct vertex;  //Struct declaration of vertex

//Struct to store all adjacent vertices to one vertex
struct adjVertex{
    vertex *v;
    int weight; //Store the weight between the vertices
};

//Vertex struct
struct vertex{
    std::string name;
    bool visited;   //If the vertex has been visited
    int distance;   //Distance from a starting vertex
    std::vector<adjVertex> adj; //Vector to store all adjacent vertices
    vertex *previous;   //Pointer to point to the previous vertex for use in Dijkstra's algorithm
    int districtID; //Integer to store the ID of the vertex district
};

//Queue vertex used in Dijkstra'a algorithm
struct queueVertex{
    int distance;
    std::vector<vertex> path;
};

//Graph class declaration
class Graph
{
public:
    Graph();    //Constructor
    ~Graph();   //Destructor
    void addEdge(std::string v1, std::string v2, int weight);   // Add edge to graph
    void addVertex(std::string name);   //Add vertex to graph
    void breadthFirstSearch(std::string startLandmark, std::string endLandmark); //Search the graph using breadth-first search
    void depthFirstTraversalRecursive(std::string startLandmark);   //Search the graph using depth-first search recursively
    void depthFirstTraversal(std::string startLandmark);  //Search the graph using depth-first search non-recursive
    void dijkstra(std::string startLandmark, std::string endLandmark);  //Search the graph and find shortest distance using Dijkstra's algorithm
    void breadthFirstTraversal(std::string startLandmark);  //Traverse the graph according to the breadth first procedure
    void findDistricts(std::string startLandmark);  //Method to assign all of the vertices a district
    void deleteEdge(std::string startLandmark, std::string endLandmark);    //Method to delete an edge between vertices

protected:
private:
    //vector<edge> edges;
    std::vector<vertex> vertices;   //Vector store all vertices
    int districtIDIndex;

    void search(vertex v);  //Algorithm used with depth-first search recursive

};

#endif // GRAPH_H
