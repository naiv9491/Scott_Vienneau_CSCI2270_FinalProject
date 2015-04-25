#include "Graph.h"
#include <string>
#include <iostream>
#include <queue>
#include <stack>
#include <limits.h>

using namespace std;

Graph::Graph()
{
    //ctor
    districtIDIndex = 1;    //Index to keep track of how many districts
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

 Precondition: Vector class must be included. The string parameter has no extra spaces, and is the correct name of the landmark. The struct vertex has been declared with name and distance variables.
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
        v.districtID = -1;
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

 Precondition: Vector class must be included. The vertices vector and the adjacent vector have been declared. The struct for adjVertex has been initialized with a pointer to the vector and the weight.
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
 void Graph::breadthFirstSearch(string, string)

 Function Description:
 This method takes in two parameters and returns the shortest path between the two cities

 Example:
 Graph g;
 g.breadthFirstSearch("Stonehenge", "Golden Gate Bridge");

 Precondition: Vector class must be included. The vertices vector has to be declared and the vertex struct has to be declared and initialized with the corresponding variables. The adjacent vertices vector/struct has to
 be declared as well with the pointer to the vertex struct. The queue class has to be included.

 Postcondition: Display the integer for the shortest path, and the string representation of the path taken
 */
void Graph::breadthFirstSearch(string landmark1, string landmark2)
{
    vector<vertex> path;    //Vector to store the current path of shortest path
    int distance;   //Integer to store temporary distance of path

    vertex *startingLandmark = NULL;    //Vertex to store the starting landmark
    vertex *endingLandmark = NULL;  //Vertex to store the ending vertex

    vertex u;   //Vertex to store the current vertex

    //Boolean to store if landmark 1 and 2 have been found
    bool landmarks1 = false;
    bool landmarks2 = false;

    queue<queueVertex> shortestPathQueue;   //Queue to store the current path and distance

    //Loop through the vertices looking for landmark 1 and 2
    for (int i = 0; i < vertices.size(); i++)
    {
        if (vertices[i].name == landmark1)
        {
            landmarks1 = true;
            startingLandmark = &vertices[i];
        }
        else if (vertices[i].name == landmark2)
        {
            landmarks2 = true;
            endingLandmark = &vertices[i];
        }
    }

    if(startingLandmark->districtID == -1)
    {
        cout << "Districts have not been initialized" << endl;
        return;
    }
    else if(startingLandmark->districtID != endingLandmark->districtID)
    {
        cout << "The two landmarks are in different districts" << endl;
        return;
    }

    if (landmarks1 && landmarks2)
    {
        //Loop through all vertices setting the starting landmark to visited and the rest to not visited
        for (int i = 0; i < vertices.size(); i++)
        {
            if (vertices[i].name != startingLandmark->name)
            {
                vertices[i].visited = false;
            }
            else
            {
                vertices[i].visited = true;
            }

        }

        startingLandmark->visited = true;

        queueVertex qv; //Create an instance of queue vertex

        qv.distance = 0;
        qv.path.push_back(*startingLandmark);   //Add the starting landmark to the path

        shortestPathQueue.push(qv); //Add the queue vertex to the queue

        while (!(shortestPathQueue.empty()))
        {
            qv = shortestPathQueue.front();   //Store the queue vertex about to be popped
            shortestPathQueue.pop();          //Pop the current queue vertex off the queue

            vertex *v = NULL;   //Vertex to store the adjacent vertex

            int endPath = qv.path.size();   //Variable to store the end of the path

            //Loop through all adjacent vertices
            for (int i = 0; i < qv.path[endPath-1].adj.size(); i++)
            {
                v = qv.path[endPath-1].adj[i].v;

                if (v->visited == false)
                {
                    path = qv.path; //Store the queue vertex path
                    v->visited = true;

                    distance = qv.distance + 1; //Store the queue vertex distance + 1 for the new vertex
                    path.push_back(*v); //Add the adjacent vertex to the queue

                    //Create a temp queue vertex with the new path and distance
                    queueVertex temp;
                    temp.path = path;
                    temp.distance = distance;

                    //If the end vertex has been found
                    if (v->name == landmark2)
                    {
                        //return temp;
                        cout << temp.distance;
                        for (int j = 0; j < temp.path.size(); j++)
                        {
                            cout << " " << temp.path[j].name;
                        }
                    }
                    else
                    {
                        //Add the temp path to the queue
                        shortestPathQueue.push(temp);
                    }

                }
            }
        }
        cout << endl;

    }


    if (landmarks1 == false || landmarks2 == false)
    {
        cout << "One or more landmarks doesn't exist" << endl;
    }

}

/*
 Function Prototype:
 void Graph::depthFirstTraversal(string)

 Function Description: This method prints all the vertices according to the 'depth first' traversal procedure

 Example:
 Graph g;
 g.depthFirstTraversal("Eiffel Tower");

 Precondition: Vector class must be included. The vertices vector has to be initialized as well as the vertex struct. The stack class has to be included and the adjacent vector/struct has to be declared and initialized
 with corresponding variables.

 Postcondition: Will display all the vertices in the graph, in order according to depth first traversal
 */
void Graph::depthFirstTraversal(string startLandmark)
{
    int tracker = 0;    //Integer to store the number of vertices visited
    vertex *startingLandmark = NULL;   //Vertex to store the starting vertex

    bool landmark1 = false; //Boolean to check if the starting vertex has been found

    //Loop through all vertices setting all vertices except the starting vertex to not be visited
    for (int i = 0; i < vertices.size(); i ++)
    {
        vertices[i].visited = false;

        if (vertices[i].name == startLandmark)
        {
            startingLandmark = &vertices[i];
            vertices[i].visited = true;
            landmark1 = true;
        }
    }

    if(landmark1 == false)
    {
        cout << "The landmark was not found" << endl;
        return;
    }

    if(startingLandmark->districtID == -1)
    {
        cout << "Districts have not been initialized" << endl;
        return;
    }

    vertex u;   //Vertex to store the popped off vertex from the stack

    stack<vertex> depthStack;   //Declare the stack and push the starting vertex on
    depthStack.push(*startingLandmark);

    while (!(depthStack.empty()))
    {
        u = depthStack.top();    //Store the vertex to be popped off the stack
        depthStack.pop();

        tracker++;  //Increment tracker for a new vertex being visited

        //If all vertices have been visited, print accordingly
        if (tracker == 10)
        {
            cout << u.districtID << ":" << u.name << endl;
        }
        else
        {
            cout << u.districtID << ":" << u.name << " ";
        }

        //Loop through all adjacent vertices, visit them, and push them onto the stack
        for (int i = 0; i < u.adj.size(); i++)
            {
            if (u.adj[i].v->visited == false)
            {
                u.adj[i].v->visited = true;
                depthStack.push(*u.adj[i].v);
            }
        }
    }

}

/*
 Function Prototype:
 void Graph::depthFirstTraversalRecursive(string)

 Function Description: This method prints all the vertices according to the 'depth first' recursive traversal procedure

 Example:
 Graph g;
 g.depthFirstTraversalRecursive("Eiffel Tower");

 Precondition: Vector class must be included. The search method must be implemented. The vertices vector and vertex struct must be declared and initialized with the corresponding variables.
 The adjacent vector/struct must be implemented with the corresponding variables.

 Postcondition: Will display all the vertices in the graph, in order according to depth first recursive traversal
 */
void Graph::depthFirstTraversalRecursive(string startLandmark)
{
    vertex *startingLandmark = NULL;    //Vertex to store the starting landmark

    bool landmark1 = false; //Boolean to check if the starting vertex has been found

    //Loop through all vertices setting them all to not visited except the starting landmark
    for (int i = 0; i < vertices.size(); i++)
    {
        if (vertices[i].name == startLandmark)
        {
            vertices[i].visited = true;
            startingLandmark = &vertices[i];
            landmark1 = true;
        }
        else
        {
            vertices[i].visited = false;
        }
    }

    if(landmark1 == false)
    {
        cout << "The landmark was not found" << endl;
        return;
    }

    if(startingLandmark->districtID == -1)
    {
        cout << "Districts have not been initialized" << endl;
        return;
    }

    cout << startingLandmark->districtID << ":" << startingLandmark->name << " ";    //Print out the starting landmark

    //Loop through all adjacent vertices to starting landmark and print it out
    for (int i = 0; i < startingLandmark->adj.size(); i++)
    {
        if (startingLandmark->adj[i].v->visited == false)
        {
            cout << startingLandmark->adj[i].v->districtID << ":" << startingLandmark->adj[i].v->name << " ";
            startingLandmark->adj[i].v->visited = true;

            //Call the search method to start printing out all adjacent vertices depth first
            search(*startingLandmark->adj[i].v);

        }
    }
    cout << endl;

}

/*
 Function Prototype:
 void Graph::search(vertex)

 Function Description: This method prints all the adjacent vertices according to the 'depth first' recursive traversal procedure

 Example:
 Graph g;
 search(*startingLandmark->adj[i].v) [This is a private method so it does not need to be called from graph g]

 Precondition: Vector class must be included. The depth first recursive traversal must be implemented as well as the vertex struct and vertices vector with corresponding variables.
 The adjacent vector and struct must be declared and implemented for each vector.

 Postcondition: Will display all the vertices in the graph, in order according to depth first recursive traversal
 */
void Graph::search(vertex u)
{
    u.visited = true;   //Set the sent in vertex to be visited

    //Loop through all adjacent vertices to u
    for (int i = 0; i < u.adj.size(); i++)
    {
        if (u.adj[i].v->visited == false)
        {
            u.adj[i].v->visited = true;

            //If all vertices have been visited print them accordingly
            bool visited = true;
            for (int i = 0; i < vertices.size(); i ++)
            {
                if (vertices[i].visited == false)
                {
                    visited = false;
                }
            }
            if (visited)
            {
                cout << u.adj[i].v->districtID << ":" << u.adj[i].v->name << endl;
            }
            else
            {
                cout << u.adj[i].v->districtID << ":" << u.adj[i].v->name << " ";
            }

            //Recursively call search with the adjacent vertex to print all vertices with depth first
            search(*u.adj[i].v);

        }
    }
}

/*
 Function Prototype:
 void Graph::breadthFirstTraversal(string)

 Function Description: This method prints all the vertices according to the 'breadth first' traversal procedure

 Example:
 Graph g;
 g.breadthFirstTraversal("Eiffel Tower");

 Precondition: Vector class must be included. The vertices vector and vertex struct must be declared and initialized with the corresponding variables.
 The adjacent vector/struct must be implemented with the corresponding variables. The queue class must be included.

 Postcondition: Will display all the vertices in the graph, in order according to breadth first traversal
 */
void Graph::breadthFirstTraversal(string startLandmark)
{
    vertex *startingLandmark = NULL;    //Vertex to store the starting landmark

    bool landmark1 = false; //Boolean to check if the starting vertex has been found

    //Loop through all vertices setting all to be not visited except for the starting vertex
    for (int i = 0; i < vertices.size(); i ++)
    {
        vertices[i].visited = false;
        if (vertices[i].name == startLandmark)
        {
            startingLandmark = &vertices[i];
            vertices[i].visited = true;
            landmark1 = true;
        }
    }

    if(landmark1 == false)
    {
        cout << "The landmark was not found" << endl;
        return;
    }

    if(startingLandmark->districtID == -1)
    {
        cout << "Districts have not been initialized" << endl;
        return;
    }

    cout << startingLandmark->districtID << ":" << startingLandmark->name << " "; //Print out the starting landmark

    vertex u;   //Vertex to store the vertex to be popped off the queue

    queue<vertex> breadthQueue; //Queue to store the traversal path
    breadthQueue.push(*startingLandmark); //Push on the starting landmark

    while (!(breadthQueue.empty()))
    {
        u = breadthQueue.front();  //Store the vertex about to be popped off and pop it off
        breadthQueue.pop();

        //Loop through all adjacent vertices to u
        for (int i = 0; i < u.adj.size(); i++)
        {
            if (u.adj[i].v->visited == false)
            {
                u.adj[i].v->visited = true;

                bool visited = true;

                //If all vertices have been visited then visited will be true
                for (int i = 0; i < vertices.size(); i ++)
                {
                    if (vertices[i].visited == false)
                    {
                        visited = false;
                    }
                }

                //Print out the vertex according to the value of visited
                if (visited)
                {
                    cout << u.adj[i].v->districtID << ":" << u.adj[i].v->name << endl;
                }
                else
                {
                    cout << u.adj[i].v->districtID << ":" << u.adj[i].v->name << " ";
                }

                //Push the adjacent vertex onto the queue
                breadthQueue.push(*u.adj[i].v);
            }
        }
    }
    cout << endl;

}

/*
 Function Prototype:
 void Graph::dijkstra(string, string)

 Function Description: This method will find the shortest distance between two landmarks in a weighted graph.

 Example:
 Graph g;
 g.dijkstra("Niagara Falls", "Eiffel Tower");

 Precondition: Vector class must be included. The vertex struct and vertices vector must be implemented will all corresponding variables including the pointer to the previous vertex.
 The vector class must be included and the adjacent vector/struct must be declared and implemented. The limits.h class must be included.

 Postcondition: Will print the shortest distance between two landmarks and the string path taken between the landmarks.
 */
void Graph::dijkstra(string startLandmark, string endLandmark)
{
    //Create temp vertices for starting and ending landmark
    vertex A;
    A.name = "NULL";
    vertex B;
    B.name = "NULL";

    vertex *finalLandmark;  //Vertex to store the final landmark of the shortest distance path

    //Loop through the vertices looking for starting city and ending city
    for(int i = 0; i < vertices.size(); i++)
    {
        if(startLandmark == vertices[i].name)
        {
            A = vertices[i];
        }

        if(endLandmark == vertices[i].name && endLandmark != startLandmark)
        {
            B = vertices[i];
        }
    }

    //If one or more cities is not found, one or more cities does not exist
    if(A.name == "NULL" || B.name == "NULL")
    {
        cout << "One or more landmarks doesn't exist or the start and end landmark are the same" << endl;
        return;
    }

    if(A.districtID == -1)
    {
        cout << "Districts have not been initialized" << endl;
        return;
    }
    else if(A.districtID != B.districtID)
    {
        cout << "The two landmarks are in different districts" << endl;
        return;
    }

    vertex *startingLandmark = NULL;
    vertex temp;

    int minDistance = 0;

        //Loop through all of the vertices setting visited to false, previous to NULL, set each vertex distance to 0
        for(int j = 0; j < vertices.size(); j++)
        {
            vertices[j].visited = false;
            vertices[j].previous = NULL;
            vertices[j].distance = 0;
        }
        A.visited = false;
        B.visited = false;

        //Loop and if you find starting landmark, set visited to true and set s to the starting landmark
        for(int i = 0; i < vertices.size(); i++)
        {
            if(vertices[i].name == startLandmark)
            {
                vertices[i].visited = true;
                vertices[i].previous = NULL;
                startingLandmark = &vertices[i];
                break;
            }
        }

        //Set s to be visited and distance to be 0 since it is the starting landmark
        startingLandmark->visited = true;
        startingLandmark->distance = 0;
        startingLandmark->previous = NULL;

        //Indices to keep track of the landmark with the minimum distance and the adjacent landmark with the minimum distance
        int minIndex = -1;
        int minAdjIndex = -1;

        int distance;   //Variable to store the temp distance measurement

        //Create a vector of vertices which are solved
        //Add starting landmark to solved
        vector <vertex*> solved;
        solved.push_back(startingLandmark);

        //While the end landmark has not been visited
        while(B.visited == false)
        {
            //Min distance is the max integer value
            minDistance = INT_MAX;

            //Loop through all vertices in solved
            for(int k = 0; k < solved.size(); k++)
            {
                //Loop through all adjacent vertices in solved
                for(int a = 0; a < solved[k]->adj.size(); a++)
                {
                    //If the adjacent vertex has not been visited
                    if(solved[k]->adj[a].v->visited == false)
                    {
                        //Calculate the distance to the adjacent vertex
                        distance = solved[k]->distance+solved[k]->adj[a].weight;

                        //Set the minimum distance if it has not been set yet
                        //Keep track of the minDistance index and minDistance adjacent vertex
                        if(minDistance == INT_MAX)
                        {
                            minDistance = distance;
                            minIndex = k;
                            minAdjIndex = a;
                        }
                        //If the minimum distance is greater than the calculated distance
                        //Keep track of the indexes just like above
                        else if(minDistance > distance)
                        {
                            minDistance = distance;
                            minIndex = k;
                            minAdjIndex = a;
                        }
                    }
                }
            }
            //Set min distance for the adjacent vertex
            solved[minIndex]->adj[minAdjIndex].v->distance = minDistance;
            //The adjacent vertex with minimum distance has now been visited
            solved[minIndex]->adj[minAdjIndex].v->visited = true;

            //Set the previous city for the visited adjacent vertex
            solved[minIndex]->adj[minAdjIndex].v->previous = solved[minIndex];

            //Set final to be the final adjacent vertex
            //Final will keep track of the destination
            finalLandmark = solved[minIndex]->adj[minAdjIndex].v;

            //Check if the ending city has been visited
            if(solved[minIndex]->adj[minAdjIndex].v->name == B.name)
                B.visited = true;
            //Add the minimum distance vertex to solved
            solved.push_back(solved[minIndex]->adj[minAdjIndex].v);
        }

        //Create a vector for the final path
        vector<vertex*> finalPath;

        //Print the distance and the final path
        cout << minDistance << ", ";

        while(finalLandmark != NULL)
        {
            finalPath.push_back(finalLandmark);
            finalLandmark = finalLandmark->previous;
        }

        for(int j = finalPath.size()-1; j >= 0; j--)
        {
            if(j != 0)
                cout << finalPath[j]->name << ", ";
            else
                cout << finalPath[j]->name << endl;
        }

        return;
}

/*
 Function Prototype:
 void Graph::findDistricts(string)

 Function Description: This method will assign all connected components a district. Initially, all landmarks are connect, however,
 some landmarks may be deleted.

 Example:
 Graph g;
 g.findDistricts("Golden Gate Bridge");

 Precondition: Vector class must be included. The vertex struct must be initialized with all corresponding variables. All vertices must have a variable to store district ID.
 The queue class must be included. The adjacent vector/struct must be implemented with the corresponding variables declared in the struct.

 Postcondition: Will assign all connected components in the graph a district. If the graph is split into two different connected components, they
 will have different districts.
 */
void Graph::findDistricts(string startLandmark)
{
    vertex startingLandmark;
    bool foundLandmark = false;

    //Loop through all the vertices and set the visited to false
    for(int j = 0; j < vertices.size(); j++)
    {
        if(vertices[j].districtID == -1)
            vertices[j].visited = false;
    }

    //Loop through all the vertices and set the starting landmark to true, set the district ID and set startingLandmark to the starting landmark
    for(int i = 0; i < vertices.size(); i++)
    {
        if(vertices[i].name == startLandmark)
        {
            foundLandmark = true;
            vertices[i].visited = true;
            vertices[i].districtID = districtIDIndex;
            startingLandmark = vertices[i];
            break;
        }
    }

    if(!foundLandmark)
    {
        cout << "The landmark does not exist" << endl;
        return;
    }

    //Set starting landmark visited to true and created a queue of vertices
    startingLandmark.visited = true;

    queue <vertex> districtQueue;   //Queue to store all vertices in a district

    //Add the starting vertex to the queue
    districtQueue.push(startingLandmark);

    //Loop while the queue is not empty
    while(!districtQueue.empty())
    {
        //Set vertex u to the next element
        //Pop the next element off the queue
        vertex u = districtQueue.front();
        districtQueue.pop();

        //Loop through all adjacent vertices
        for(int a = 0; a < u.adj.size(); a++)
        {
            if(u.adj[a].v->visited == false)
            {
                //Set the adjacent vertices visited to true
                //Set the adjacent vertices district ID
                u.adj[a].v->visited = true;
                u.adj[a].v->districtID = districtIDIndex;

                //Push the adjacent vertex onto the queue
                districtQueue.push(*u.adj[a].v);
            }
        }
    }

    //Loop through all of the vertices
    for(int i = 0; i < vertices.size(); i++)
    {
        //Find the next vertex not visited and increment the district ID
        //Recursively call findDistricts with the found vertex
        if(vertices[i].visited == false)
        {
            districtIDIndex++;
            findDistricts(vertices[i].name);
        }
    }
}

/*
 Function Prototype:
 void Graph::deleteEdge(string, string)

 Function Description: This method will take in two string which will find two landmarks and delete the edge between the vertices and then update the districts

 Example:
 Graph g;
 g.deleteEdge("Golden Gate Bridge", "Niagara Falls")

 Precondition: Vector class must be included. The vertex struct with corresponding variables must be initialized as well as the vertices vector. The adjacent vector/struct
 must be declared and initialized with corresponding variables. The find districts method must be implemented.

 Postcondition: Will delete the edge between two adjacent vertices and update the districts in the graph.
 */
void Graph::deleteEdge(string startLandmark, string endLandmark)
{
    //Vertices to store the starting and ending landmarks
    vertex *startingLandmark = NULL;
    vertex *endingLandmark = NULL;

    //Boolean to store if the start and end landmarks have been found
    bool foundStart = false;
    bool foundEnd = false;

    //Loop through all vertices looking for the starting and ending landmarks
    for(int i = 0; i < vertices.size(); i++)
    {
        if(vertices[i].name == startLandmark)
        {
            startingLandmark = &vertices[i];
            foundStart = true;
        }

        if(vertices[i].name == endLandmark && startLandmark != endLandmark)
        {
            endingLandmark = &vertices[i];
            foundEnd = true;
        }

    }

    //If the landmarks were not found
    if(!foundEnd || !foundStart)
    {
        cout << "One of the landmarks does not exist or they are the same landmark" << endl;
        return;
    }

    if(startingLandmark->districtID == -1)
    {
        cout << "Districts have not been initialized" << endl;
        return;
    }
    else if(startingLandmark->districtID != endingLandmark->districtID)
    {
        cout << "The two landmarks have different districts" << endl;
        return;
    }

    //Boolean to store if the vertices are adjacent
    bool adjacentVertices = false;

    //Loop through all adjacent vertices for starting landmark and if end landmark is found, erase it
    for(int i = startingLandmark->adj.size()-1; i >= 0; i--)
    {
        if(startingLandmark->adj[i].v->name == endLandmark)
        {
            startingLandmark->adj.erase(startingLandmark->adj.begin()+i);
            adjacentVertices = true;
            break;
        }
    }

    //If the vertices are not adjacent
    if(!adjacentVertices)
    {
        cout << "The vertices are not adjacent" << endl;
        return;
    }

    //Loop through all adjacent vertices to ending landmark and delete starting landmark
    for(int i = endingLandmark->adj.size()-1; i >= 0; i--)
    {
        if(endingLandmark->adj[i].v->name == startLandmark)
        {
            endingLandmark->adj.erase(endingLandmark->adj.begin()+i);
            break;
        }
    }


    //Re find all districts for the graph
    districtIDIndex = 1;
    for(int i = 0; i < vertices.size(); i++)
        vertices[i].districtID = -1;

    findDistricts(startLandmark);

}
