#ifndef _VECTOR2_H
#define _VECTOR2_H
#include "mathematics.h"

namespace mathematics
{
	struct Position
	{
		scalar _x;
		scalar _y;
	};

	struct IntPosition
	{
		int _x;
		int _y;

		bool operator==(const IntPosition& rhs) const
		{
			if (this->_x == rhs._x && this->_y == rhs._y)
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
