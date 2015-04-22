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
    void findDistricts(std::string n);
    void findShortestPath(std::string city1, std::string city2);
    void findShortestDistance(std::string city1, std::string city2);
    int district;
protected:
private:
    //vector<edge> edges;
    std::vector<vertex> vertices;
    
};

#endif // GRAPH_H
