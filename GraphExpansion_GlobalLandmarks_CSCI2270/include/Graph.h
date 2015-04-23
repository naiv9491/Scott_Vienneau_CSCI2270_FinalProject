#ifndef GRAPH_H
#define GRAPH_H
#include<vector>
#include<iostream>

struct vertex;

struct adjVertex{
    vertex *v;
    int weight;
};

struct vertex{
    std::string name;
    int district;
    bool visited;
    int distance;
    vertex *previous;
    std::vector<adjVertex> adj;
};

struct queueVertex{
    int distance;
    std::vector<vertex> path;
};

class Graph
{
public:
    Graph();
    ~Graph();
    void addEdge(std::string v1, std::string v2, int weight);
    void addVertex(std::string name);
    void displayEdges();
    void bredthFirstSearch(std::string startCity, std::string endCity);
    void depthFirstSearchRec(std::string startCity, std::string endCity);
    void depthFirstSearch(std::string startCity, std::string endCity);
    void dijkstra(std::string startCity, std::string endCity);
    void bruteForceSpanning(std::startCity);
    void prim(std::startCity);
    
    int district;
protected:
private:
    //vector<edge> edges;
    std::vector<vertex> vertices;
    void search(vertex v);
    
};

#endif // GRAPH_H
