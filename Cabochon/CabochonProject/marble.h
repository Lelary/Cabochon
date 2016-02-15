#ifndef _MARBLE_H
#define _MARBLE_H
#include "object.h"
#include "texture_list.h"
/*
	2016. 1. 5
	class Marble

	������ ������ ��Ÿ���ϴ�. 
	Object�� ��ӹ޾� �ڽ��� ��ǥ�������� ��ġ�� ����մϴ�.

	TODO :
		����������� ��ǥ ����

	_px, _py �� puzzle x puzzle y �� �ǹ��մϴ�.
	-> vector2<int>, IntPosition

*/
/*
	2016. 1. 15
	cpp �ۼ� 1�� �Ϸ�
*/

namespace components
{
	using components::Marble;
	using components::marble_ptr;
	using mathematics::IntPosition;
	using frameworks::TextureList;

	class Marble
		:public Object
	{
	public:
		static const int noPosition = -1;
	private:
		IntPosition _gridPosition;

	public:
		Marble();
		Marble(const IntPosition& gridPosition);
		Marble(const Marble& rhs);
		virtual ~Marble();
		Marble& operator=(const Marble& rhs);

		void loadLayers(TextureList& textureList);
		void draw();
		void update(scalar frameTime);

		bool circularHitTest(const Marble& anotherMarble) const;
		static bool circularHitTest(const Marble& marble1, const Marble& marble2);


	};
}
#endif