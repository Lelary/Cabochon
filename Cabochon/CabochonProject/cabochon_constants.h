#ifndef _CABOCHON_CONSTANTS_H
#define _CABOCHON_CONSTANTS_H
#include "mathematics.h"
#include "vector2.h"
#include "dx9_game_engine\graphics.h"
namespace cabochon_constants
{
	using mathematics::scalar;
	using mathematics::IntPosition;

	const int MAX_Y = 8;
	const int MIN_X = 10;
	const int MARBLE_WIDTH = 50;
	const int MARBLE_HEIGHT = 50;
	
	const scalar LEFT_WALL = 0;
	const scalar RIGHT_WALL = MAX_Y * MARBLE_WIDTH;
	const scalar LINE = MIN_X * MARBLE_HEIGHT;

	const IntPosition NO_POSITION = { -1, -1 };

	const char FONT[] = "Courier New";
	const int POINT_SIZE = 14;
	const COLOR_ARGB FONT_COLOR = SETCOLOR_ARGB(255, 255, 255, 255);

	const scalar MEAN_DROP_SPEED = 100.0f;
	const scalar MEAN_DROP_ANGLE = 0.0f;
	const scalar GRAVITY_ACCELERATION = 980.0f;

	const std::string VERSION = "revision 179";
	const std::string MY_PAGE = "http://lemonelime.net";
}

#endif