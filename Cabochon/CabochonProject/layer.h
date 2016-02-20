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
	// Object와의 거리를 _distance에 저장하여 항상 해당 오브젝트의 좌표로부터 상대적으로 같은 위치에 그려지도록 한다.
	class Layer
		:public Image
	{
	private:
		// Layer를 소유한 Object와의 상대적 위치.
		Position _distance;
		virtual void setX(float newX);
		virtual void setY(float newY);
	public:
		Layer();
		virtual ~Layer();
		virtual Position getDistance() const;
		virtual void setDistance(const Position& object, const Position& distance);
		virtual void setDistanceFromCenter(const Position& object, scalar objectWidth, scalar objectHeight, const Position& distance);

		// object의 위치에 맞춰 Layer의 위치를 갱신한다.
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