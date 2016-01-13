#include "components.h"
#include "mathematics.h"
#include "vector2.h"
using components::Object;
using mathematics::scalar;
using mathematics::Position;

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

*/
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
	Object(const Object& rhs);
	virtual ~Object();
	Object& operator=(const Object& rhs);

	scalar getPosition() const;
	scalar getCenter() const;
	scalar getWidth() const;
	scalar getHeight() const;

	void setPosition(const Position& position);
	void setPosition(scalar x, scalar y);
	void setCenter(const Position& position);
	void setCenter(scalar x, scalar y);
	void setWidth(scalar width);
	void setHeight(scalar height);

	/*
		2016. 1. 13
		get/set Center 가 의미하는 바가 애매하다.

		center는 position+(width/2, height/2) 를 계산하게 하고싶은데,
		center 라는 이름 때문에 position은 그대로 두고 회전중심을 변경하는 것으로 오해될 수 있음.
	
		현재 이게임에는 회전중심이 따로 필요치 않음.

	*/
};