#pragma once

#include "GraphRealisation.h"
#include "../Classes/Engine.h"

class OpenGL;

class OpenGL
{
protected:
	uint16_t button_commands = 0x0000;
	GLint window_height;
	GLint window_width;
	//width / height
	float window_scale;
	Vec2D cursore_press_position;
	Vec2F cursore_current_position;
	Vec2F cursore_last_position;
    bool flag_mouse_clk;
public:

    unsigned update_camera;
    
	StaticBuffer point_buffer;
	StaticBuffer connection_buffer;

	//buffers

	//The shader use for draw gravity generators.
	Shader point_shader;
	//The shader use for draw mega lasers.
	Shader connection_shader;

	//shaders
    
    Camera camera;

	//textures

	//The texture stores symbols and signs that will be drawn on the buttons.
	Texture2D symbols_texture;

	//textures

	OpenGL(
        int width,
        int height,
        const char* title,
        GLFWmonitor* monitor,
        GLFWwindow* share,
        GLFWframebuffersizefun Function,
        GLFWwindow** window);

	//Callback functions

	void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
	void ProcessInput(GLFWwindow* window);
    
    
    void DrawFrame();

	//Multydraw functions

	//Get data functions

	bool CanDrawFrame(GLFWwindow* window);
	float GetScale();

	//Get data functions

	//Initialisations functions

	GLFWwindow* CreateWindows(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share, GLFWframebuffersizefun Function);

	void InitBuffers();
	void InitGlad();
	void InitOpenGL();
	void InitShaders();
	void InitTextures();
    
    
    void DrawObject(Point* point, bool update_shader = false);
    void DrawObject(PhysicConnection* connection, bool update_shader = false);
    void DrawObject(Graph* graph, bool update_shader = false);

    
};




























