#ifndef _OBJECTS_H
#define _OBJECTS_H

#include "components.h"
#include "mathematics.h"
#include "vector2.h"
/*
	2016. 1. 5
	class Object

	좌표공간 상에서의 위치와 크기를 가지고 있습니다.
	스프라이트를 갖는 오브젝트에게 상속시키고자 합니다.

	2016. 1. 6.
	TODO
		getcenterX, getcenterY
		set,
		vector2

	2016. 1. 13.
	x, y 를 Vector2<scalar>로 변경
	Vector2<scalar> 를 Position으로 typedef // mathematics.h

	TODO
		나중에 Sprite를 가짐

	2016. 1. 16.
	cpp 작성 1차 완료

*/
namespace components
{
	using mathematics::scalar;
	using mathematics::Position;

	class Object
	{
	private:
		Position _position;
		scalar _width, _height;

		/*
			2016. 1. 13.
			스트라이프 예시

			Stripe stripe;
			*/

	public:
		Object();
		Object(const Position& position, scalar width, scalar height);
		Object(const Object& rhs);
		virtual ~Object();
		Object& operator=(const Object& rhs);

		// the position of Left Top 
		Position getPosition() const;
		// the position of middle
		Position getCentralPosition() const;
		//scalar getCenterOfRotation() const;
		scalar getWidth() const;
		scalar getHeight() const;

		// the position of Left Top 
		void setPosition(const Position& position);
		// the position of Left Top 
		void setPosition(scalar x, scalar y);
		// the position of middle, changes position property.
		void setCentralPosition(const Position& position);
		// the position of middle, changes position property.
		void setCentralPosition(scalar x, scalar y);
		//void setCenterOfRotation(const Position& position);
		//void setCenterOfRotation(scalar x, scalar y);
		void setWidth(scalar width);
		void setHeight(scalar height);

		/*
			2016. 1. 22.
			충돌관련함수를 어디에 작성할지 고민.중.
			현재 클래스에서 삭제 가능 있음.
			Marble 클래스에 오버로딩(parameter 가 다름)한 함수는 삭제 안할 것으로 예상.
		*/
		//bool circularHitTest(const Position& position1, scalar radius1, const Position& position2, scalar radius2);

		/*
			2016. 1. 13
			get/set Center 가 의미하는 바가 애매하다.

			center는 position+(width/2, height/2) 를 계산하게 하고싶은데,
			center 라는 이름 때문에 position은 그대로 두고 회전중심을 변경하는 것으로 오해될 수 있음.

			현재 이게임에는 회전중심이 따로 필요치 않음.

			2016. 1. 21
			->
				// 위치속성 (Position + {width/2, height/2})
				get/set MiddlePosition, 

				// 회전속성 (회전중심)
				get/set Center.

			2016. 1. 22.
			->	CenteralPosition,
				CenterOfRotation
		*/



	};
}

#endif