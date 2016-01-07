#include "components.h"
#include "typedefs.h"
using components::Object;

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
*/
class Object
{
private:
	scalar _x, _y;
	scalar _width, _height;



public:
	scalar getX();
	scalar getY();
	scalar getWidth();
	scalar getHeight();

	void setX(scalar x);
	void setY(scalar y);
	void setWidth(scalar width);
	void setHeight(scalar height);
};