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
	// Object���� �Ÿ��� _distance�� �����Ͽ� �׻� �ش� ������Ʈ�� ��ǥ�κ��� ��������� ���� ��ġ�� �׷������� �Ѵ�.
	class Layer
		:public Image
	{
	private:
		// Layer�� ������ Object���� ����� ��ġ.
		Position _distance;
		virtual void setX(float newX);
		virtual void setY(float newY);
	public:
		Layer();
		virtual ~Layer();
		virtual Position getDistance() const;
		virtual void setDistance(const Position& object, const Position& distance);
		virtual void setDistanceFromCenter(const Position& object, scalar objectWidth, scalar objectHeight, const Position& distance);

		// object�� ��ġ�� ���� Layer�� ��ġ�� �����Ѵ�.
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