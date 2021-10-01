
#include "NotMy/glad.h"
#include <GLFW/glfw3.h>

#include <iostream>

#include "Types/AllTypes.h"
#include "Constants/AllConstants.h"
#include "Classes/Engine.h"

#include "SubClasses/GraphRealisation.h"
#include "SubClasses/OpenGLRealisation.h"

#define CONNENTIONS_COUNT 5

#define SCR_WIDTH   800
#define SCR_HEIGHT  800

void LocalFramebufferSizeCallback(GLFWwindow* window, int width, int height);

OpenGL* main_graw;

int main()
{
    Connection* connections = new Connection[CONNENTIONS_COUNT];
    connections[0].Set(1, 2);
    connections[1].Set(1, 3);
    connections[2].Set(2, 3);
    connections[3].Set(1, 1);
    connections[4].Set(2, 1);
    Graph graph = Graph(connections, CONNENTIONS_COUNT);
    delete[] connections;
    std::cout << "Graph view:\n" << graph << std::endl
        << "All points count: " << graph.GetPointsCount() << std::endl
        << graph.GetConnectionsCount(Connection(1, 2)) << std::endl;
        
        
    GLFWwindow* window = nullptr;
    main_graw = new OpenGL(
        SCR_WIDTH,                      //width
        SCR_HEIGHT,                     //height
        "Graph visualisation",          //window name
        nullptr,                        //monitor
        nullptr,                        //share
        LocalFramebufferSizeCallback,   //callback function
        &window                         //pointer to window
    );
    
    while(true);
}

void LocalFramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    main_graw->FramebufferSizeCallback(window, width, height);
}
