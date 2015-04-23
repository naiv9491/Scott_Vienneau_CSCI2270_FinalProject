#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

int main()
{
    ifstream inFile;    //Variable to open text file
    string strLine;     //Variable to store each line of the text file
    string *landmarks;     //Dynamic array to store each landmark
    int **landmarkDistanceValues;      //Dynamic two dimensional array to store distances between landmarks


    int numLines = 0;  //Variable to store the number of lines in the file

    //Graph g;    //Create an instance of the graph class

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

        for(int i = 0; i < numLines-2; i++)
        {
            //Loop through just the first line adding in all landmarks to the landmarks array
            landmarks[i] = strLine.substr(comma1+1, comma2-comma1-1);
            comma1 = comma2;
            comma2 = strLine.find(',', comma2+1);
        }

        landmarks[numLines-2] = strLine.substr(comma1+1);

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

    /*

    //Add all landmarks to the graph as vertices
    for(int k = 0; k < numLines-1; k++)
        g.addVertex(landmarks[k]);

    //Loop through the 2d array and add all edges on the graph between vertices
    for(int i = 0; i < numLines-1; i++)
    {
        for(int j = 0; j < numLines-1; j++)
        {
            if(landmarkDistanceValues[i][j] > 0)
            {
                g.addEdge(landmarks[i], landmarks[j], landmarkDistanceValues[i][j]);
                //If one edge was already created, set the corresponding value to -10 so two edges are not created
                landmarkDistanceValues[j][i] = -10;
            }
        }
    }
    */

    LOOP:while(1 == 1)
    {
        //Print out the main menu with all options
        cout << "===== Main Menu =====" << endl;
        cout << "1. Print Vertices" << endl;
        cout << "2. Find Shortest Path" << endl;
        cout << "3. Find Shortest Distance" << endl;
        cout << "4. Minimum Spanning Tree Algorithms" << endl;
        cout << "5. Quit" << endl;

        //Get user input on what option to run
        string userInput = "";
        getline(cin, userInput);

        if(userInput == "1")
        {
            //Print out the vertices and corresponding edges
        }

        else if(userInput == "2")
        {
            //Print sub-menu to show which shortest path algorithm
            cout << endl << "1. Breadth-First Search" << endl;
            cout << "2. Depth-First Search Recursive" << endl;
            cout << "3. Depth-First Search Non-Recursive" << endl;

            //Get user input on which shortest path algorithm
            userInput = "";
            getline(cin, userInput);

            //Two variables to keep track of each city
            string city1;
            string city2;

            if(userInput == "1")
            {
                //Find the shortest path between two cities using breadth-first
                cout << "Enter a starting city:" << endl;
                getline(cin, city1);
                cout << "Enter an ending city:" << endl;
                getline(cin, city2);
                userInput = ""; //Reset the value of userInput
            }
            else if(userInput == "2")
            {
                //Find the shortest path between two cities using depth-first recursive
                cout << "Enter a starting city:" << endl;
                getline(cin, city1);
                cout << "Enter an ending city:" << endl;
                getline(cin, city2);
                userInput = "";
            }
            else if(userInput == "3")
            {
                //Find the shortest path between two cities using breadth-first
                cout << "Enter a starting city:" << endl;
                getline(cin, city1);
                cout << "Enter an ending city:" << endl;
                getline(cin, city2);
                userInput = ""; //Reset the value of user input
            }
            else
            {
                cout << "Invalid Input, restarting from Main Menu" << endl;
                goto LOOP;  //Go back to main menu
            }
        }

        else if(userInput == "3")
        {
            //Find shortest distance between two cities using Dijkstra's algorithm
            string city1;
            string city2;
            cout << "Enter a starting city:" << endl;
            getline(cin, city1);
            cout << "Enter an ending city:" << endl;
            getline(cin, city2);
        }

        else if(userInput == "4")
        {
            //Print sub menu to display which minimum spanning tree algorithm
            cout << endl << "1. Brute Force Algorithm" << endl;
            cout << "2. Primm's Algorithm" << endl;

            //Get user input on which algorithm to run
            userInput = "";
            getline(cin, userInput);

            //Variable to store the name of the starting city for minimum spanning tree
            string city1;

            if(userInput == "1")
            {
                //Find the minimum spanning tree using brute force
                cout << "Enter a starting city:" << endl;
                getline(cin, city1);
                userInput = ""; //Reset the value of the user input
            }
            else if(userInput == "2")
            {
                //Find the minimum spanning tree using Primm
                cout << "Enter a starting city:" << endl;
                getline(cin, city1);
                userInput = ""; //Reset the value of the user input
            }
            else
            {
                cout << "Invalid Input, restarting from Main Menu" << endl;
                goto LOOP;  //Go back to main menu
            }
        }

        else if(userInput == "5")
        {
            //If user wants to quit
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
