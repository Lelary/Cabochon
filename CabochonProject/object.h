#ifndef _OBJECTS_H
#define _OBJECTS_H

#include "components.h"
#include "mathematics.h"
#include "vector2.h"
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

	2016. 1. 16.
	cpp �ۼ� 1�� �Ϸ�

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
			��Ʈ������ ����

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
			�浹�����Լ��� ��� �ۼ����� ���.��.
			���� Ŭ�������� ���� ���� ����.
			Marble Ŭ������ �����ε�(parameter �� �ٸ�)�� �Լ��� ���� ���� ������ ����.
		*/
		//bool circularHitTest(const Position& position1, scalar radius1, const Position& position2, scalar radius2);

		/*
			2016. 1. 13
			get/set Center �� �ǹ��ϴ� �ٰ� �ָ��ϴ�.

			center�� position+(width/2, height/2) �� ����ϰ� �ϰ������,
			center ��� �̸� ������ position�� �״�� �ΰ� ȸ���߽��� �����ϴ� ������ ���ص� �� ����.

			���� �̰��ӿ��� ȸ���߽��� ���� �ʿ�ġ ����.

			2016. 1. 21
			->
				// ��ġ�Ӽ� (Position + {width/2, height/2})
				get/set MiddlePosition, 

				// ȸ���Ӽ� (ȸ���߽�)
				get/set Center.

			2016. 1. 22.
			->	CenteralPosition,
				CenterOfRotation
		*/



	};
}

#endif