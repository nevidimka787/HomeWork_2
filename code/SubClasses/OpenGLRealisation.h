#pragma once

#include "MenuFunctions.h"

#include "../Classes/Engine.h"

class OpenGL
{
protected:
	uint16_t button_commands = 0x0000;
	GLint window_height;
	GLint window_width;
	//width / height
	float window_scale;
	Vec2D* cursore_current_position;
	Vec2D* cursore_last_position;
	Vec2D* cursore_press_position;
	Vec2D* cursore_release_position;
public:

	StaticBuffer grav_gen_buffer;
	StaticBuffer mega_laser_buffer;

	StaticBuffer button_buffer;

	//buffers

	//This values is set by defaultafter each click on the menu.
	//Each frame this value will be decrease until it reached zero.
	//Menu will be updating while the value is greater then zero.
	uint8_t update_menu;
	//If this flag is active then value of "update_menu" can be decrease.
	bool flag_update_menu_can_change;
	//The flag actives then menu is moving by cursore.
	bool flag_move_menu;

	int clear_frame;
#define CLEAR_FRAME_PERIOD	30;

	//The shader use for draw gravity generators.
	Shader grav_gen_shader;
	//The shader use for draw mega lasers.
	Shader mega_laser_shader;

	//The shader use for draw buttons.
	Shader button_shader;

	//shaders

	//textures

	//The texture stores symbols and signs that will be drawn on the buttons.
	Texture2D symbols_texture;

	//textures
    
    //Menus
    
    Menu* current_active_menu;
    Menu graph_set_menu;
    
    //Menus

	OpenGL(
        int width,
        int height,
        const char* title,
        GLFWmonitor* monitor,
        GLFWwindow* share,
        GLFWframebuffersizefun Function,
        GLFWwindow** window);

	//Callback functions

	void CallMenuFunction(Menu* menu, Vec2F* clk_pos, uint8_t clk_statuse);
	void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
	void LimitMenuPosition(Menu* menu);
	void ProcessInput(GLFWwindow* window);
    
	//The function draw current menu.
	void DrawCurrentMenu();
	//The function draw indicated menu.
	void DrawIndicatedMenu(Menu* menu);
    
    void DrawObject(Button* button, bool update_shader = false);
    
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

    
};
