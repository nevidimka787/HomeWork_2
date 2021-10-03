
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

OpenGL* main_draw;

int main()
{
    Connection* connections = new Connection[CONNENTIONS_COUNT];
    connections[0] = Connection(1, 2);
    connections[1] = Connection(1, 3);
    connections[2] = Connection(2, 3);
    connections[3] = Connection(1, 1);
    connections[4] = Connection(2, 1);
    Graph graph = Graph(connections, CONNENTIONS_COUNT);
        
        
    GLFWwindow* window = nullptr;
    main_draw = new OpenGL(
        SCR_WIDTH,                      //width
        SCR_HEIGHT,                     //height
        "Graph visualisation",          //window name
        nullptr,                        //monitor
        nullptr,                        //share
        LocalFramebufferSizeCallback,   //callback function
        &window                         //pointer to window
    );
    
    
    while(true)
    {
        main_draw->ProcessInput(window);
        
        main_draw->DrawFrame();
        main_draw->DrawObject(&graph, true);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
        glfwSwapInterval(1);//vertical synchronisation
    }
}

void LocalFramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    main_draw->FramebufferSizeCallback(window, width, height);
}
