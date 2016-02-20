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

	2016. 2. 2.
	Image, TextureManager member data �߰�.
	Position ���� setter���� Image�� ��� �� ���� �����Ű���� ��.
*/
namespace components
{
	using mathematics::scalar;
	using mathematics::Position;
	using frameworks::TextureList;
	using mathematics::Origin;

	class Object
	{
	private:
		Position _position;
		scalar _width, _height;

	protected:
		bool _layersLoaded;
		// �� ���̾�� Image�� ��ӹް� distance(Object�� �߽������κ�����)�� ���´�.
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
		// Sprite ����.

		virtual bool isLayersLoaded();
		virtual void adjustLayersPosition();
		virtual void loadLayers(TextureList& textureList) = 0;
		virtual void draw()=0;
		//-----------------------------------------------------
		virtual void update(float frameTime)=0;
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