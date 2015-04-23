#include "Graph.h"
#include <string>
#include <iostream>
#include <queue>

using namespace std;

Graph::Graph()
{
    //ctor
}

Graph::~Graph()
{
    //dtor
}

/*
 Function Prototype:
 void Graph::addVertex(string)
 
 Function Description:
 This method takes in a name for a landmark and checks to make sure a vertex has not already been associate with that name. If it has not, it will create
 a new vertex with the name and add it to the vertices vector
 
 Example:
 Graph g;
 g.addVector("Eiffel Tower");
 
 Precondition: The string parameter has no extra spaces, and is the correct name of the landmark. The struct vertex has been declared with name and distance variables.
 The vertices vector has been declared.
 
 Postcondition: The string name given will be created into a vertex and added to the vertices vector. If the name was already created as a vector the program will say that name was found.
 */
void Graph::addVertex(string name)
{
    bool found = false; //Variable to check if the vertex has been already created
    
    //Loop through all of the vertices
    for(int i = 0; i < vertices.size(); i++)
    {
        //If the name has been associated with a vertex
        if(vertices[i].name == name)
        {
            found = true;
            cout<< vertices[i].name<<" found."<<endl;
        }
    }
    
    //If the name was not already associated with a vertex
    //Add it to vertices and update the vertex information via the vertex struct
    if(found == false){
        vertex v;
        v.name = name;
        v.distance = 0;
        vertices.push_back(v);
    }
}

/*
 Function Prototype:
 void Graph::addEdge(string, string, int)
 
 Function Description:
 This method takes in two names for landmarks, finds if the two names correspond to vertices, and adds an edge between
 the vertices with the corresponding parameter for weight.
 
 Example:
 Graph g;
 g.addEdge("Eiffel Tower", "Taj Mahal", 2000);
 
 Precondition: The vertices vector and the adjacent vector have been declared. The struct for adjVertex has been initialized with a pointer to the vector and the weight.
 If no movies have been added to the vertices vector, then v1 and v2 will not be found. The starting landmark is string v1 and the ending landmark is v2.
 The weight between the landmarks will be given by int weight. All this information can be found in the generated text file.
 
 Postcondition: An edge will be added between the two vertices with the corresponding weight. The adjacent vector for v1 will have v2 added, and the adjacent vector
 for v2 will have v1 added. The edge will be created in both directions.
 */
void Graph::addEdge(string v1, string v2, int weight)
{
    //Loop through all of the vertices
    for(int i = 0; i < vertices.size(); i++)
    {
        //If the starting city matches v1
        if(vertices[i].name == v1)
        {
            //Loop through all of the vertices again looking for v2
            for(int j = 0; j < vertices.size(); j++)
            {
                if(vertices[j].name == v2 && i != j)
                {
                    //Create an adjacent vertex for v2, add its weight and push it to the adjacent vector for v1
                    adjVertex av;
                    av.v = &vertices[j];
                    av.weight = weight;
                    vertices[i].adj.push_back(av);
                    //Repeat the process above but add an edge between v2 and v1 the other direction
                    adjVertex av2;
                    av2.v = &vertices[i];
                    av2.weight = weight;
                    vertices[j].adj.push_back(av2);
                }
            }
        }
    }
}

/*
 Function Prototype:
 void Graph::displayEdges()
 
 Function Description:
 This method takes in no parameters and displays all vertices with their corresponding adjacent vertices
 
 Example:
 Graph g;
 g.displayEdges();
 
 Precondition: The vertices vector has to be declared and the vertex struct has to be declared and initialized with the name variable. The adjacent vertices vector has to
 be declared as well with the pointer to the vertex struct
 
 Postcondition: All vertices will be displayed with a following list displaying all adjacent vertices to the original vertex.
 */
void Graph::displayEdges()
{
    //Loop through all vertices
    for(int i = 0; i < vertices.size(); i++)
    {
        //cout << vertices[i].name << endl;
        cout << vertices[i].name << "-->";
        
        //For each vertex, loop through all adjacent vertices
        for(int j = 0; j < vertices[i].adj.size(); j++)
        {
            cout << vertices[i].adj[j].v->name;
            if(j != vertices[i].adj.size()-1)
                cout << "***";
        }
        
        cout << endl << endl;
        
    }
}
/*
 Function Prototype:
 void Graph::breadthFirstSearch(string, string)
 
 Function Description:
 This method takes in two parameters and returns the shortest path between the two cities
 
 Example:
 Graph g;
 g.breadthFirstSearch("Stonehenge", "Golden Gate Bridge");
 
 Precondition: The vertices vector has to be declared and the vertex struct has to be declared and initialized with the name variable. The adjacent vertices vector has to
 be declared as well with the pointer to the vertex struct
 
 Postcondition: Display the integer for the shortest path, and the string representation of the path taken
 */
void Graph::breadthFirstSearch(string city1, string city2){
    vector<vertex> path;
    int distance;
    vertex *s = NULL;
    vertex *e = NULL;
    vertex u;
    bool found1 = false;
    bool found2 = false;
    bool dist = true;
    queue<queueVertex> myQueue;
    for (int i = 0; i < vertices.size(); i++){
        if (vertices[i].name == city1){
            found1 = true;
            s = &vertices[i];
        }else if (vertices[i].name == city2){
            found2 = true;
            e = &vertices[i];
        }
    }
    if (found1 && found2){
        for (int i = 0; i < vertices.size(); i++){
            if (vertices[i].name != s->name){
                vertices[i].visited = false;
            }else{
                vertices[i].visited = true;
            }
            
        }
        s->visited = true;
        queueVertex qv;
        qv.distance = 0;
        qv.path.push_back(*s);
        myQueue.push(qv);
        while (!(myQueue.empty())){
            qv = myQueue.front();
            myQueue.pop();
            vertex *v = NULL;
            int end = qv.path.size();
            for (int i = 0; i < qv.path[end-1].adj.size(); i++){
                v = qv.path[end-1].adj[i].v;
                if (v->visited == false){
                    path = qv.path;
                    v->visited = true;
                    distance = qv.distance + 1;
                    path.push_back(*v);
                    queueVertex temp;
                    temp.path = path;
                    temp.distance = distance;
                    if (v->name == city2){
                        //return temp;
                        cout << temp.distance;
                        for (int j = 0; j < temp.path.size(); j++){
                            cout << "," << temp.path[j].name;
                        }
                    }else {
                        myQueue.push(temp);
                    }
                    
                }
            }
        }
        cout << endl;
        
    }
    
    
    if (found1 == false || found2 == false){
        cout << "One or more cities doesn't exist" << endl;
    }
    
    
    
}
