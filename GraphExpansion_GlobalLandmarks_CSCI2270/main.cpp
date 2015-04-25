#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "Graph.h"

using namespace std;

int main()
{
    ifstream inFile;    //Variable to open text file
    string strLine;     //Variable to store each line of the text file
    string *landmarks;     //Dynamic array to store each landmark
    int **landmarkDistanceValues;      //Dynamic two dimensional array to store distances between landmarks


    int numLines = -1;  //Variable to store the number of lines in the file

    Graph g;    //Create an instance of the graph class

    inFile.open("Landmarks.txt");    //Open the file to read in the data

    if(inFile.fail())
        cout << "File did not open." << endl;
    else
    {
        //While not at end of the file, get each line and increment the line counter
        while(inFile.good())
        {
            getline(inFile, strLine);
            numLines++;
        }

        //Initialize both dynamic arrays
        landmarks = new string [numLines-1];
        landmarkDistanceValues = new int *[numLines-1]; //Initialize first dimension of two dimension array
        //Initialize second dimension of 2d array
        for(int i = 0; i < numLines-1; i++)
            landmarkDistanceValues[i] = new int[numLines-1];

        //Clear the file and reset to beginning of file to read in data
        inFile.clear();
        inFile.seekg(0, ios::beg);

        //Get the first line of the file
        getline(inFile, strLine);

        //Find all of the commas in the first line
        int comma1 = strLine.find(',');
        int comma2 = strLine.find(',', comma1+1);

        for(int i = 0; i < numLines-1; i++)
        {
            //Loop through just the first line adding in all landmarks to the landmarks array
            landmarks[i] = strLine.substr(comma1+1, comma2-comma1-1);
            comma1 = comma2;
            comma2 = strLine.find(',', comma2+1);
        }


        //Create variable line length to get the last landmark name in the file without getting the extra \r sequence
        //int lineLength = strLine.substr(comma1+1).length();
        //landmarks[numLines-2] = strLine.substr(comma1+1, lineLength-1);

        int index = 0;  //Variable to keep track of all of the lines traversed in the file

        while(inFile.good())
        {
            //Get line in file
            getline(inFile, strLine);

            int comma3 = strLine.find(',');
            int comma4 = strLine.find(',', comma3+1);

            //Loop through the remaining lines and add all numerical values to the 2d array
            //Update the comma values for each numerical value
            for(int i = 0; i < numLines-1; i++)
            {
                landmarkDistanceValues[index][i] = atoi(strLine.substr(comma3+1, comma4-comma3-1).c_str());
                comma3 = comma4;
                comma4 = strLine.find(',', comma4+1);
            }

            index++;
            if(index == numLines-1)
                break;

        }
    }

    inFile.close();

    //Add all landmarks to the graph as vertices
    for(int k = 0; k < numLines-1; k++)
    {
        g.addVertex(landmarks[k]);
    }


    //Loop through the 2d array and add all edges on the graph between vertices
    for(int i = 0; i < numLines-1; i++)
    {
        for(int j = 0; j < numLines-1; j++)
        {
            //Make sure the distance value is greater than 0
            if(landmarkDistanceValues[i][j] > 0)
            {
                g.addEdge(landmarks[i], landmarks[j], landmarkDistanceValues[i][j]);
                //If one edge was already created, set the corresponding value to -10 so two edges are not created for the same vertices
                landmarkDistanceValues[j][i] = -10;

            }
        }
    }

LOOP:while(1 == 1)
{
    //Print out the main menu with all options
    cout << "===== Main Menu =====" << endl;
    cout << "1. Print Vertices" << endl;
    cout << "2. Initialize Districts" << endl;
    cout << "3. Find Shortest Path" << endl;
    cout << "4. Find Shortest Distance" << endl;
    cout << "5. Delete Edge" << endl;
    cout << "6. Delete Vertex" << endl;
    cout << "7. Quit" << endl;

    //Get user input on what option to run
    string userInput = "";
    getline(cin, userInput);

    if(userInput == "1")
    {
        cout << "1. Breadth First Traversal" << endl;
        cout << "2. Depth First Traversal" << endl;
        cout << "3. Depth First Traversal (Recursive)" << endl;

        string landmark1;
        userInput = "";
        getline(cin, userInput);

        if (userInput == "1")
        {
            cout << "Enter a starting landmark:" << endl;
            getline(cin, landmark1);
            userInput = "";
            g.breadthFirstTraversal(landmark1);
        }
        else if (userInput == "2")
        {
            cout << "Enter a starting landmark:" << endl;
            getline(cin, landmark1);
            userInput = "";
            g.depthFirstTraversal(landmark1);
        }
        else if (userInput == "3")
        {
            cout << "Enter a starting landmark:" << endl;
            getline(cin, landmark1);
            userInput = "";
            g.depthFirstTraversalRecursive(landmark1);
        }

    }

    else if(userInput == "2")
    {
        userInput = "";

        g.findDistricts(landmarks[0]);
    }

    else if(userInput == "3")
    {

        //Two variables to keep track of each city
        string landmark1;
        string landmark2;

        //Find the shortest path between two cities using breadth-first
        cout << "Enter a starting landmark:" << endl;
        getline(cin, landmark1);
        cout << "Enter an ending landmark:" << endl;
        getline(cin, landmark2);
        userInput = ""; //Reset the value of userInput
        g.breadthFirstSearch(landmark1, landmark2);

    }

    else if(userInput == "4")
    {
        //Find shortest distance between two cities using Dijkstra's algorithm
        string landmark1;
        string landmark2;
        cout << "Enter a starting landmark:" << endl;
        getline(cin, landmark1);
        cout << "Enter an ending landmark:" << endl;
        getline(cin, landmark2);

        g.dijkstra(landmark1, landmark2);
    }

    else if(userInput == "5")
    {
        //Delete the edge between two vertices
        string landmark1;
        string landmark2;
        cout << "Enter a starting landmark:" << endl;
        getline(cin, landmark1);
        cout << "Enter an adjacent landmark:" << endl;
        getline(cin, landmark2);
        userInput = "";

        g.deleteEdge(landmark1, landmark2);
    }

    else if(userInput == "6")
    {
        //Delete a vertex from the graph
        string landmark1;
        cout << "Enter a starting landmark:" << endl;
        getline(cin, landmark1);
        userInput = "";

        g.deleteVertex(landmark1);
    }

    else if (userInput == "7")
    {
        //If the user wants to quit
        cout << "Goodbye!" << endl;
        return 0;
    }

    else
    {
        //If the input is invalid
        cout << "Invalid Input, restarting from Main Menu" << endl;
        goto LOOP;
    }

}
    return 0;
}
