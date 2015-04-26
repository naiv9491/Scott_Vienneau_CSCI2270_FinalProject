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
1. Clone Scott_Vienneau_CSCI2270_FinalProject to your computer. 
(git clone https://github.com/tylersco/Scott_Vienneau_CSCI2270_FinalProject.git)

2. If you are using Code::Blocks open up the project by double clicking the GraphExpansion_GlobalLandmarks_CSCI2270.cbp file in the GraphExpansion_GlobalLandmarks_CSCI2270 folder and click the Compile and Run button. 
   If you are not using Code::Blocks you need to create a new project in some C++ IDE using a C++ 11 compiler and add the 'main.cpp', 'Graph.cpp', and 'Graph.h' files in the GraphExpansion_GlobalLandmarks_CSCI2270 folder. Also, make sure the 'Landmarks.txt' file is in your new project directory. After completing these steps you can run the program through your own IDE. 

   If you wish to run your code through command line, you must be in the GraphExpansion_GlobalLandmarks_CSCI2270 folder by using a command such as 'cd'. Once you are there, cd into the src folder and copy the Graph.cpp into the GraphExpansion_GlobalLandmarks_CSCI2270 folder's main level so that the Graph.cpp and main.cpp are in the same folder. Next, go into the include folder and copy the Graph.h file into the GraphExpansion_GlobalLandmarks_CSCI2270 folder's main level so that itself, the Graph.cpp file, and the main.cpp file are in the same folder. Once here, you should be able to call the ls function or something similar depending on the shell and see 'main.cpp', 'Graph.cpp', 'Graph.h' and 'Landmarks.txt' all in the same level of the project folder.

  Type in this code to run the program:
      g++ -std=c++11 main.cpp Graph.cpp Graph.h
      ./a.out
      
  Note that this will not work if main.cpp, Graph.cpp, Graph.h, and Landmarks.txt are not in the same folder.
  
Project Documentation: https://github.com/tylersco/Scott_Vienneau_CSCI2270_FinalProject/blob/master/GraphExpansion_GlobalLandmarks_CSCI2270/Graph%20Documentation.txt

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
