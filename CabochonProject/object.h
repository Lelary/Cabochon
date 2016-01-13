#include "components.h"
#include "mathematics.h"
#include "vector2.h"
using components::Object;
using mathematics::scalar;
using mathematics::Position;

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

	2016. 1. 13.
	x, y �� Vector2<scalar>�� ����
	Vector2<scalar> �� Position���� typedef // mathematics.h

	TODO
		���߿� Sprite�� ����

*/
class Object
{
private:
	Position _position;
	scalar _width, _height;

	/*
		2016. 1. 13.
		��Ʈ������ ����

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
		get/set Center �� �ǹ��ϴ� �ٰ� �ָ��ϴ�.

		center�� position+(width/2, height/2) �� ����ϰ� �ϰ������,
		center ��� �̸� ������ position�� �״�� �ΰ� ȸ���߽��� �����ϴ� ������ ���ص� �� ����.
	
		���� �̰��ӿ��� ȸ���߽��� ���� �ʿ�ġ ����.

	*/
};