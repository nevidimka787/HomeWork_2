#include "OpenGLRealisation.h"
#include <iostream>

OpenGL::OpenGL(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share, GLFWframebuffersizefun Function, GLFWwindow** window)
    : cursore_press_position (new Vec2D()), cursore_release_position(new Vec2D()), cursore_last_position(new Vec2D()), cursore_current_position(new Vec2D())
{
    update_menu = OPEN_GL_REALISATION_FRAMES_AFTER_CALLBAC_COUNT;
    flag_update_menu_can_change = true;
    
    InitOpenGL();
    *window = CreateWindows(width, height, title, monitor, share, Function);
    window_height = height;
    window_width = width;
    InitGlad();
    InitBuffers();
    //InitShaders();
    //InitTextures();
}

//Callback functions

void OpenGL::CallMenuFunction(Menu* menu, Vec2F* clk_pos, uint8_t clk_status)
{
    
}

void OpenGL::FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    update_menu = OPEN_GL_REALISATION_FRAMES_AFTER_CALLBAC_COUNT;
    window_height = height;
    window_width = width;
    window_scale = (float)width / (float)height;
    LimitMenuPosition(current_active_menu);
    glViewport(0, 0, width, height);
}

void OpenGL::LimitMenuPosition(Menu* menu)
{
    Vec2F new_position = Vec2F();
    new_position.y = -menu->GetSize().y - 2.0f / window_scale;
    //std::cout << new_position.y << std::endl;
    if (menu->GetPosition().y > new_position.y)
    {
        menu->SetPosition(&new_position);
    }
    if (menu->GetPosition().y < 0.0f)
    {
        new_position.y = 0.0f;
        menu->SetPosition(&new_position);
    }
}

void OpenGL::ProcessInput(GLFWwindow* window)
{
    if (update_menu > 0 && flag_update_menu_can_change)
    {
        update_menu--;
        current_active_menu->Recalculate();
    }
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
    {
        std::cout << "Debug pause." << std::endl;
        int i = 0;
    }
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        //object_p__menu_functions->Exit();
    }
    if (glfwGetKey(window, GLFW_KEY_BACKSPACE) == GLFW_PRESS && (button_commands & OPEN_GL_REALISATION_COMMAND_BACK) == OPEN_GL_REALISATION_COMMAND_NOTHING)
    {
        update_menu = OPEN_GL_REALISATION_FRAMES_AFTER_CALLBAC_COUNT;
        button_commands |= OPEN_GL_REALISATION_COMMAND_BACK;
        //object_p__menu_functions->Back();
    }
    else if (glfwGetKey(window, GLFW_KEY_BACKSPACE) == GLFW_RELEASE && (button_commands & OPEN_GL_REALISATION_COMMAND_BACK) != OPEN_GL_REALISATION_COMMAND_NOTHING)
    {
        update_menu = OPEN_GL_REALISATION_FRAMES_AFTER_CALLBAC_COUNT;
        button_commands &= OPEN_GL_REALISATION_COMMAND_FULL - OPEN_GL_REALISATION_COMMAND_BACK;
    }
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && (button_commands & OPEN_GL_REALISATION_COMMAND_SELECT) == OPEN_GL_REALISATION_COMMAND_NOTHING)
    {
        update_menu = OPEN_GL_REALISATION_FRAMES_AFTER_CALLBAC_COUNT;
        flag_update_menu_can_change = false;
        flag_move_menu = true;

        button_commands |= OPEN_GL_REALISATION_COMMAND_SELECT;
        glfwGetCursorPos(window, &cursore_press_position->x, &cursore_press_position->y);
        *cursore_last_position = *cursore_press_position;

        Vec2F clk_pos = Vec2F(((float)cursore_press_position->x / window_width - 0.5f) * 2.0f, ((float)cursore_press_position->y / -window_height) * 2.0f / window_scale + 1.0f);
        CallMenuFunction(current_active_menu, &clk_pos, GLFW_PRESS);
    }
    else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE && (button_commands & OPEN_GL_REALISATION_COMMAND_SELECT) != OPEN_GL_REALISATION_COMMAND_NOTHING)
    {
        update_menu = OPEN_GL_REALISATION_FRAMES_AFTER_CALLBAC_COUNT;
        flag_update_menu_can_change = true;
        flag_move_menu = false;

        button_commands &= OPEN_GL_REALISATION_COMMAND_FULL - OPEN_GL_REALISATION_COMMAND_SELECT;
        glfwGetCursorPos(window, &cursore_release_position->x, &cursore_release_position->y);
        *cursore_press_position -= *cursore_release_position;
        if (fabs(cursore_press_position->x) < window_width / 100.0 && fabs(cursore_press_position->y) < window_height / 100.0)
        {
            Vec2F clk_pos = Vec2F(((float)cursore_release_position->x / window_width - 0.5f) * 2.0f, ((float)cursore_release_position->y / -window_height) * 2.0f / window_scale + 1.0f);
            CallMenuFunction(current_active_menu, &clk_pos, GLFW_RELEASE);
        }
        else
        {
            CallMenuFunction(current_active_menu, nullptr, OPEN_GL_REALISATION_BUTTON_LOST);
        }
    }
    if (flag_move_menu)
    {
        glfwGetCursorPos(window, &cursore_current_position->x, &cursore_current_position->y);

        Vec2D move_vector_d = *cursore_current_position - *cursore_last_position;
        Vec2F move_vector = Vec2F(0.0f, (float)move_vector_d.y / window_height * -2.0f / window_scale);

        current_active_menu->Move(&move_vector);
        LimitMenuPosition(current_active_menu);
        *cursore_last_position = *cursore_current_position;
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
    
    grav_gen_buffer.Initialisate(points, 6);

    points[0].Set(1.0f, 1.0f);
    points[1].Set(0.0f, 1.0f);
    points[2].Set(1.0f, 0.0f);
    points[3].Set(0.0f, 0.0f);
    points[4].Set(0.0f, 1.0f);
    points[5].Set(1.0f, 0.0f);

    button_buffer.Initialisate(points, 6);

    points[0].Set(1.0f, 0.02f);
    points[1].Set(0.0f, 0.02f);
    points[2].Set(1.0f,-0.02f);
    points[3].Set(0.0f,-0.02f);
    points[4].Set(0.0f, 0.02f);
    points[5].Set(1.0f,-0.02f);
    
    mega_laser_buffer.Initialisate(points, 6);
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
    grav_gen_shader.Initialisate("code/Shaders/Objects/Vertex/GravGen.glsl", "Shaders/Objects/Fragment/GravGen.glsl");
    mega_laser_shader.Initialisate("code/Shaders/Objects/Vertex/MegaLaser.glsl", "Shaders/Objects/Fragment/MegaLaser.glsl");
    
    button_shader.Initialisate("code/Shaders/Menu/Vertex/Button.glsl", "Shaders/Menu/Fragment/Button.glsl");
}

void OpenGL::InitTextures()
{
    symbols_texture.Initialisate("code/Textures/Sample.bmp");
}

//Draw functions

void OpenGL::DrawFrame()
{
    glClearColor(0.1f, 0.1f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    DrawCurrentMenu();
}

void OpenGL::DrawCurrentMenu()
{
    DrawIndicatedMenu(current_active_menu);
}

void OpenGL::DrawIndicatedMenu(Menu* menu)
{
    button_buffer.Use();
    button_shader.Use();
    symbols_texture.Use();
    button_shader.SetUniform("scale", window_scale);
    for (EngineTypes::Menu::buttons_count_t button = 0; button < menu->GetButtonsCount(); button++)
    {
        DrawObject(&menu->current_buttons[button]);
    }
}

void OpenGL::DrawObject(Button* button, bool update_shader)
{
    if (update_shader)
    {
        button_buffer.Use();
        button_shader.Use();
        symbols_texture.Use();
        button_shader.SetUniform("scale", window_scale);
    }
    Color3F color;
    if (button->GetStatus(BUTTON_STATUS_ACTIVE))
    {
        if (button->GetStatus(BUTTON_STATUS_TRUE))
        {
            color = Color3F(0.1f, 0.6f, 0.1f);
        }
        else
        {
            color = Color3F(0.6f, 0.1f, 0.1f);
        }
        if (button->GetStatus(BUTTON_STATUS_SELECT))
        {
            color *= 0.6f;
        }
    }
    else
    {
        color = Color3F(0.3f, 0.3f, 0.3f);
    }
    button_shader.SetUniform("position", button->GetPosition());
    button_shader.SetUniform("size", button->GetSize());
    button_shader.SetUniform("color", &color);
    button_shader.SetUniform("text", button->GetText(), button->GetTextLength());
    button_shader.SetUniform("text_length", button->GetTextLength());
    button_shader.SetUniform("text_size", button->text_size);
    button_buffer.Draw();
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













