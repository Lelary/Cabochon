#ifndef _MARBLE_H
#define _MARBLE_H
#include "object.h"
#include "texture_list.h"
#include "cabochon_constants.h"
/*
	2016. 1. 5
	class Marble

	게임의 구슬을 나타냅니다. 
	Object를 상속받아 자신의 좌표공간상의 위치를 기술합니다.

	TODO :
		퍼즐공간상의 좌표 생성

	_px, _py 는 puzzle x puzzle y 를 의미합니다.
	-> vector2<int>, IntPosition

*/
/*
	2016. 1. 15
	cpp 작성 1차 완료
*/

namespace components
{
	using components::Marble;
	using components::marble_ptr;
	using mathematics::IntPosition;
	using scenes::TextureList;
	
	enum class MarbleColor { None=-1, Red, Orange, Yellow, Green, Blue, Purple, Gray, Num};

	class Marble
		:public Object
	{
	public:
		static const int marbleWidth = cabochon_constants::MARBLE_WIDTH;
		static const int marbleHeight = cabochon_constants::MARBLE_HEIGHT;
		static const IntPosition noPosition;
	private:
		IntPosition _gridPosition;
		MarbleColor _color;

	public:
		Marble(MarbleColor color);
		Marble(const IntPosition& gridPosition = noPosition, MarbleColor color = MarbleColor::None);
		Marble(const Marble& rhs);
		virtual ~Marble();
		Marble& operator=(const Marble& rhs);

		void loadLayers(TextureList& textureList);
		MarbleColor getColor() const; 
		MarbleColor setColor(MarbleColor color);

		void setGridPosition(IntPosition gridPosition);
		IntPosition getGridPosition() const;

		void rotate(scalar degree);
		void draw();
		void update(float frameTime);

		bool circularHitTest(const Marble& anotherMarble, scalar scale = 1.0f) const;
		static bool circularHitTest(const Marble& marble1, const Marble& marble2, scalar scale = 1.0f);


	};
}
#endif