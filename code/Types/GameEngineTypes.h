#pragma once
#include <iostream>

namespace EngineTypes
{
	namespace AgressiveEntity
	{
		typedef uint8_t shoots_count_t;
	}

	namespace Area
	{
		typedef uint32_t points_count_t;
	}

	namespace Asteroid
	{
		typedef uint8_t size_t;
	}

	namespace Bomb
	{
		typedef uint8_t status_t;
	}

	namespace Bonus
	{
		typedef uint8_t inventory_length_t;
		typedef uint16_t inventory_t;
	}

	namespace Buffer
	{
		typedef uint16_t array_length_t;
	}

	namespace Bullet
	{
		typedef uint8_t entity_t;
	}

	namespace Button
	{
		typedef uint32_t id_t;
		typedef uint8_t status_t;
		typedef int32_t text_t;
		typedef uint16_t text_length_t;
		typedef uint8_t text_size_t;
	}

	namespace ControledEntity
	{
		typedef uint16_t heat_box_vertexes_count_t;
	}

	namespace Knife
	{
		typedef uint8_t knife_health_t;
	}

	namespace Log
	{
		typedef uint8_t header_t;
		typedef uint32_t data_t;
		typedef uint8_t length_t;
	}

	namespace Map
	{
		typedef uint8_t elements_array_length_t;
	}

	namespace Menu
	{
		typedef uint8_t buttons_count_t;
	}

	namespace Polygon
	{
		typedef uint32_t points_array_length_t;
	}

	namespace Rectangle
	{
		typedef uint8_t sides_t;
	}

	namespace Ship
	{
		typedef uint8_t inventory_t;
	}
}