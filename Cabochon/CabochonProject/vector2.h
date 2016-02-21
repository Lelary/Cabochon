#ifndef _VECTOR2_H
#define _VECTOR2_H
#include "mathematics.h"

namespace mathematics
{
	struct Position
	{
		scalar x;
		scalar y;

		Position operator+(const Position& rhs) const
		{
			return { x + rhs.x, y + rhs.y };
		}
		Position operator-(const Position& rhs) const
		{
			return { x - rhs.x, y - rhs.y };
		}
	};

	struct IntPosition
	{
		int x;
		int y;

		IntPosition operator+(const IntPosition& rhs) const
		{
			return{ x + rhs.x, y + rhs.y };
		}
		IntPosition operator-(const IntPosition& rhs) const
		{
			return{ x - rhs.x, y - rhs.y };
		}

		bool operator==(const IntPosition& rhs) const
		{
			if (this->x == rhs.x && this->y == rhs.y)
				return true;
			else
				return false;
		}
		bool operator!=(const IntPosition& rhs) const
		{
			return !(*this == rhs);
		}
	};

}
#endif
