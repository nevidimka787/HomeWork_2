#pragma once
#include <iostream>

namespace EngineTypes
{
    namespace Area
	{
		typedef uint32_t points_count_t;
	}
	
	namespace Buffer
	{
		typedef uint16_t array_length_t;
	}
	
	namespace Button
	{
		typedef uint32_t id_t;
		typedef uint8_t status_t;
		typedef int32_t text_t;
		typedef uint16_t text_length_t;
		typedef uint8_t text_size_t;
	}

	namespace Menu
	{
		typedef uint8_t buttons_count_t;
	}
}
