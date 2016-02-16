#ifndef _LAYER_H
#define _LAYER_H
#include "dx9_game_engine\image.h"
#include "components.h"
#include "vector2.h"

namespace components
{
	using mathematics::Position;
	using mathematics::Origin;
	using mathematics::scalar;

	class Layer
		:public Image
	{
	private:
		Position _distance;
		virtual void setX(float newX);
		virtual void setY(float newY);
	public:
		Layer();
		virtual ~Layer();
		virtual Position getDistance();
		virtual void setDistance(const Position& object, const Position& distance);
		virtual void setDistanceFromCenter(const Position& object, scalar objectWidth, scalar objectHeight, const Position& distance);
		virtual void adjustPosition(const Position& object);

		// Object의 width에 맞추고 계산.
		// s<1이면 작아짐, s>1이면 커짐
		virtual void setScaleFromWidth(float s, float objectWidth);

		// Object의 height에 맞추고 계산.
		// s<1이면 작아짐, s>1이면 커짐
		virtual void setScaleFromHeight(float s, float objectHeight);

	};
}
#endif