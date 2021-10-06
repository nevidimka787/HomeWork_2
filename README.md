# HomeWork_2
 
The repository collect my solutions of home tasks. My task number is 3.

The code wrote on ubuntu 18.04.

# Building program

The program is builded by Makefile.
To buil the program:
1. Open terminal in folder whis repository.
2. Paste command "make".

Binarum file is in bin directory. To start program past in terminal "./Task2"

# Program description
The program gets data from the console.
Format of the data:
point -- point
point -- point
...

After that the program check condition (graph is tree) and print result to console.
After that the program open the window and draw wisualisation of the graph.
Wisualisation of graph can be moved by mouse and scaled by keys on the keyboard.

Visualisation control:
Moving mouse whis active left mouse button -> move graph
1) Arrow up    -> scale up grahp
2) Arrow down  -> scale down graph


# Libraries
The program use OpenGL libraries and use "glad" for work with OpenGL's functions.

The program use stb_image for work with imajes (textures).
https://github.com/nothings/stb/blob/master/stb_image.h
