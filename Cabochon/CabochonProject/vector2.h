#ifndef _VECTOR2_H
#define _VECTOR2_H
#include "mathematics.h"

namespace mathematics
{
	template < typename T >
	struct Vector2
	{
		T _x;
		T _y;
	};

	/*
		vector2¿¡
		operator overloading
		Ãß°¡
	*/

	Position convertOrigin(const Position& oldPosition, Origin newOrigin, scalar width, scalar height)
	{
		Position newPosition;

		switch (newOrigin)
		{
		case Origin::LEFT_TOP:
			newPosition._x = oldPosition._x - width / 2.0f;
			newPosition._y = oldPosition._y - height / 2.0f;
			break;

		case Origin::CENTER:
			newPosition._x = oldPosition._x + width / 2.0f;
			newPosition._y = oldPosition._y + height / 2.0f;
			break;
		}
		return newPosition;
	}
}
#endif
