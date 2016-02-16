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

		// Object�� width�� ���߰� ���.
		// s<1�̸� �۾���, s>1�̸� Ŀ��
		virtual void setScaleFromWidth(float s, float objectWidth);

		// Object�� height�� ���߰� ���.
		// s<1�̸� �۾���, s>1�̸� Ŀ��
		virtual void setScaleFromHeight(float s, float objectHeight);

	};
}
#endif