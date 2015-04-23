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
    void displayEdges();    //Display all edges and vertices in the graph
    void bredthFirstSearch(std::string startCity, std::string endCity); //Search the graph using breadth-first search
    void depthFirstSearchRecursive(std::string startCity, std::string endCity);   //Search the graph using depth-first search recursively
    void depthFirstSearch(std::string startCity, std::string endCity);  //Search the graph using depth-first search non-recursive
    void dijkstra(std::string startCity, std::string endCity);  //Search the graph and find shortest distance using Dijkstra's algorithm
    void bruteForceSpanning(std::string startCity);    //Find the minimum spanning tree using a brute force algorithm
    void primm(std::string startCity);    //Find the minimum spanning tree using Primm's algorithm

protected:
private:
    //vector<edge> edges;
    std::vector<vertex> vertices;   //Vector store all vertices

    void search(vertex v);  //Algorithm used with depth-first search recursive

};

#endif // GRAPH_H
