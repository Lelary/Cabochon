#ifndef _CABOCHON_CONSTANTS_H
#define _CABOCHON_CONSTANTS_H
#include "mathematics.h"
#include "dx9_game_engine\graphics.h"
namespace cabochon_constants
{
	using mathematics::scalar;

	const int MAX_Y = 8;
	const int MIN_X = 10;
	const int MARBLE_WIDTH = 50;
	const int MARBLE_HEIGHT = 50;
	
	const scalar LEFT_WALL = 0;
	const scalar RIGHT_WALL = MAX_Y * MARBLE_WIDTH;
	const scalar LINE = MIN_X * MARBLE_HEIGHT;

	const char FONT[] = "Courier New";
	const int POINT_SIZE = 14;
	const COLOR_ARGB FONT_COLOR = SETCOLOR_ARGB(255, 255, 255, 255);
}

#endif