#include "Graph.h"
#include <string>

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
            cout<<vertices[i].name<<" found."<<endl;
        }
    }

    //If the name was not already associated with a vertex
    //Add it to vertices and update the vertex information via the vertex struct
    if(found == false){
        vertex v;
        v.name = name;
        vertices.push_back(v);
        v.distance = 0;
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
