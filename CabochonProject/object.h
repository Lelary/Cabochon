#include "components.h"
#include "typedefs.h"
using components::Object;

/*
	2016. 1. 5
	class Object

	��ǥ���� �󿡼��� ��ġ�� ũ�⸦ ������ �ֽ��ϴ�.
	��������Ʈ�� ���� ������Ʈ���� ��ӽ�Ű���� �մϴ�.

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