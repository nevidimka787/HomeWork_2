#include "OpenGLRealisation.h"
#include <iostream>

OpenGL::OpenGL(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share, GLFWframebuffersizefun Function, GLFWwindow** window) :
    cursore_press_position(Vec2D()),
    cursore_last_position(Vec2F()),
    cursore_current_position(Vec2F()),
    flag_mouse_clk(false)
{
    
    InitOpenGL();
    *window = CreateWindows(width, height, title, monitor, share, Function);
    window_height = height;
    window_width = width;
    InitGlad();
    InitBuffers();
    InitShaders();
    InitTextures();
}

//Callback functions

void OpenGL::FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    window_height = height;
    window_width = width;
    window_scale = (float)width / (float)height;
    glViewport(0, 0, width, height);
}

void OpenGL::ProcessInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
    {
        std::cout << "Debug pause." << std::endl;
        int i = 0;
    }
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        exit(0);
    }
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
        if(flag_mouse_clk)
        {
            glfwGetCursorPos(window, &cursore_press_position.x, &cursore_press_position.y);

            cursore_current_position = Vec2F(
                ((float)cursore_press_position.x / window_width - 0.5f) * 2.0f,
                ((float)cursore_press_position.y / -window_height) * 2.0f / window_scale + 1.0f);
        }
        else
        {
            flag_mouse_clk = true;
            update_camera = OPEN_GL_REALISATION_FRAMES_AFTER_CALLBAC_COUNT;

            glfwGetCursorPos(window, &cursore_press_position.x, &cursore_press_position.y);

            cursore_current_position = Vec2F(
                ((float)cursore_press_position.x / window_width - 0.5f) * 2.0f,
                ((float)cursore_press_position.y / -window_height) * 2.0f / window_scale + 1.0f);
            
            camera.Move(cursore_current_position - cursore_last_position);
            
            cursore_last_position = cursore_current_position;
        }
    }
    else if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
    {
        flag_mouse_clk = false;
    }
}



//Callback functions

//Initialisation functions

GLFWwindow* OpenGL::CreateWindows(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share, GLFWframebuffersizefun Function)
{
    GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        exit(-1);
    }

    window_scale = (float)width / (float)height;
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, Function);

    return window;
}

#define VERTEX_ARRAY_LENGTH 6

void OpenGL::InitBuffers()
{
    Vec2F points[VERTEX_ARRAY_LENGTH];

    points[0].Set(1.0f, 1.0f);
    points[1].Set(-1.0f, 1.0f);
    points[2].Set(1.0f, -1.0f);
    points[3].Set(-1.0f, -1.0f);
    points[4].Set(-1.0f, 1.0f);
    points[5].Set(1.0f, -1.0f);
    
    point_buffer.Initialisate(points, 6);
    connection_buffer.Initialisate(points, 6);
}

void OpenGL::InitGlad()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        exit(-1);
    }
}

void OpenGL::InitOpenGL()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);
}

void OpenGL::InitShaders()
{
    point_shader.Initialisate("Shaders/Objects/Vertex/Point.glsl", "Shaders/Objects/Fragment/Point.glsl");
    connection_shader.Initialisate("Shaders/Objects/Vertex/Connection.glsl", "Shaders/Objects/Fragment/Connection.glsl");
}

void OpenGL::InitTextures()
{
    symbols_texture.Initialisate("Textures/Symbols.bmp");
}

//Draw functions

void OpenGL::DrawFrame()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    Point p1 = Point(1, Vec2F(0.2f, 0.2f), 0.2f, 100);
    Point p2 = Point(2, Vec2F(-0.2f, -0.2f), 0.2f, 100);
    PhysicConnection c = PhysicConnection(&p1, &p2, 1.0f, 10.0f);
    DrawObject(&p1, true);
    DrawObject(&p2);
    DrawObject(&c, true);
}

void OpenGL::DrawObject(Point* point, bool update_shader)
{
    if(update_shader)
    {
        point_buffer.Use();
        point_shader.Use();
        symbols_texture.Use();
        point_shader.SetUniform("scale", window_scale);
        point_shader.SetUniform("camera_position", camera.position);
        point_shader.SetUniform("camera_size", camera.size);
    }
    point_shader.SetUniform("position", point->position);
    point_shader.SetUniform("radius", point->radius);
    int* str = point->GetNumberAsTextI();
    int text_length = (int)point->GetNumberTextLength();
    point_shader.SetUniform("text", str, text_length);
    delete[] str;
    point_shader.SetUniform("text_length", text_length);
    point_shader.SetUniform("text_size", (int)point->text_size);
    point_buffer.Draw();
}

void OpenGL::DrawObject(PhysicConnection* connection, bool update_shader)
{
    if(update_shader)
    {
        connection_buffer.Use();
        connection_shader.Use();
        connection_shader.SetUniform("scale", window_scale);
        connection_shader.SetUniform("camera_position", camera.position);
        connection_shader.SetUniform("camera_size", camera.size);
    }
    connection_shader.SetUniform("segment", connection->GetSegment());
    connection_shader.SetUniform("rounded", connection->rounded);
    connection_buffer.Draw();
}

void OpenGL::DrawObject(Graph* graph, bool update_shader)
{
    
}

//Multydraw functions

//Get data functions

bool OpenGL::CanDrawFrame(GLFWwindow* window)
{
    return glfwWindowShouldClose(window) == false;
}

float OpenGL::GetScale()
{
    return window_scale;
}

//Get data functions











