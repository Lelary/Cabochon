#ifndef _OBJECTS_H
#define _OBJECTS_H

#include "components.h"
#include "vector2.h"
#include "dx9_game_engine\image.h"
#include "texture_list.h"
#include "layer.h"
#include <vector>
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

	2016. 2. 2.
	Image, TextureManager member data 추가.
	Position 관련 setter에서 Image의 멤버 값 또한 변경시키도록 함.
*/
namespace components
{
	using mathematics::scalar;
	using mathematics::Position;
	using scenes::TextureList;
	using mathematics::Origin;

	class Object
	{
	private:
		Position _position;
		scalar _width, _height;

	protected:
		bool _layersLoaded;
		// 각 레이어는 Image를 상속받고 distance(Object의 중심점으로부터의)를 갖는다.
		std::vector<Layer> _layers;

	public:
		Object();
		Object(const Position& position, scalar width, scalar height);
		Object(const Object& rhs);
		virtual ~Object();
		Object& operator=(const Object& rhs);

		// the position of Left Top 
		virtual Position getPosition() const;
		// the position of middle
		virtual Position getCentralPosition() const;
		//scalar getCenterOfRotation() const;
		virtual scalar getWidth() const;
		virtual scalar getHeight() const;

		// the position of Left Top 
		virtual void setPosition(const Position& position);
		// the position of Left Top 
		virtual void setPosition(scalar x, scalar y);
		// the position of middle, changes position property.
		virtual void setCentralPosition(const Position& position);
		// the position of middle, changes position property.
		virtual void setCentralPosition(scalar x, scalar y);
		//void setCenterOfRotation(const Position& position);
		//void setCenterOfRotation(scalar x, scalar y);
		virtual void setWidth(scalar width);
		virtual void setHeight(scalar height);


		static Position convertOrigin(const Position& oldPosition, Origin newOrigin, scalar width, scalar height);
		//---------------------------------------------------
		// Sprite 관련.

		virtual bool isLayersLoaded();
		virtual void adjustLayersPosition();
		virtual void loadLayers(TextureList& textureList) = 0;
		virtual void draw()=0;
		//-----------------------------------------------------
		virtual void update(float frameTime)=0;
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