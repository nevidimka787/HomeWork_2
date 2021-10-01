#pragma once

//#include "../Classes/GameEngine.h"

#define OPEN_GL_REALISATION_COMMAND_FULL	0xFFFF
#define OPEN_GL_REALISATION_COMMAND_NOTHING	0x0000

#define OPEN_GL_REALISATION_COMMAND_SELECT	0x0001
#define OPEN_GL_REALISATION_COMMAND_BACK	0x0002

#define OPEN_GL_REALISATION_COMMAND_SHIP_ROTATE		0x0010
#define OPEN_GL_REALISATION_COMMAND_SHIP_0_ROTATE	0x0010
#define OPEN_GL_REALISATION_COMMAND_SHIP_1_ROTATE	0x0020
#define OPEN_GL_REALISATION_COMMAND_SHIP_2_ROTATE	0x0040
#define OPEN_GL_REALISATION_COMMAND_SHIP_3_ROTATE	0x0080


#define OPEN_GL_REALISATION_BUTTON_LOST 2

#define OPEN_GL_REALISATION_FRAMES_AFTER_CALLBAC_COUNT	3
#define SHIP_0_ROTATE_BUTTON	GLFW_KEY_Q
#define SHIP_0_SHOOT_BUTTON		GLFW_KEY_A
#define SHIP_1_ROTATE_BUTTON	GLFW_KEY_L
#define SHIP_1_SHOOT_BUTTON		GLFW_KEY_P
#define SHIP_2_ROTATE_BUTTON	GLFW_KEY_LEFT
#define SHIP_2_SHOOT_BUTTON		GLFW_KEY_DOWN
#define SHIP_3_ROTATE_BUTTON	GLFW_KEY_C
#define SHIP_3_SHOOT_BUTTON		GLFW_KEY_V
