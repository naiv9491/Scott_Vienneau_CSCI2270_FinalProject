# Scott_Vienneau_CSCI2270_FinalProject
Final Project for CSCI 2270, University of Colorado, Boulder, Spring 2015

Created by Tyler Scott and Michael Vienneau

---------------
Project Summary
---------------
Our project is an expansion on the Graph data structure. We will be implementing new traversal algorithms, vertex and edge deletion, as well as other useful graph functions. The program will run by executing a driver file which will display a main menu allowing the user to select different options. The implementations for the graph methods will be included in a Graph class which will consist of a '.cpp' and '.h' file. The vertices and edges will be added by reading in a previously generated text file. The theme of the graph will be global landmarks and the edges will be weighted distances between each landmark.

----------
How to Run
----------


------------
Dependencies
------------
Our program does use some functionality from C++ 11, so whatever compiler you are using must be able to recognize those functions calls. Depending on the IDE/Compiler, there are settings which can enable the compiler to recognize C++ 11. Also, the folder which contains the project must have the Landmarks.txt file or the program will not run correctly.

-------------------
System Requirements
-------------------
Our program is not Operating System/IDE dependent. You can run the program on any operating system or IDE as long as you have a C++ 11 compiler. The program was made in Code::Blocks on Linux so that would be the easiest IDE since there is a project file for Code::Blocks. If you are using a different IDE such as XCode, you might need to create a new project, and add 'main.cpp', 'Graph.h', and 'Graph.cpp' to the project. Lastly, you must add the 'Landmarks.txt' file in the newly created project for the program to execute correctly.

-------------
Group Members
-------------
Tyler Scott & Michael Vienneau

------------
Contributors
------------
There have been no contributors thus far.

------------------
Open Issues & Bugs
------------------
Currently, the deleteVertex method does not actually deleted/free up memory associated with a vertex, however, it just pseudo-deletes the vertex by nullifying all values in the vertex struct. For example, it will set the distance to 0, eraseID to -10 and name to be "". By doing this, the deleted vertex will not be found in any of the search, shortest path, or shortest distance algorithms. If anyone would like to try and enhance our program by trying to fully delete the vertex it would be greatly appreciated. We were having trouble with getting correct adjacent vertices for all remaining vertices in the vertices vector.
