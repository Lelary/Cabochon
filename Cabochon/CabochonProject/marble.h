#ifndef _MARBLE_H
#define _MARBLE_H
#include "object.h"
#include "texture_list.h"
#include "cabochon_constants.h"
/*
	2016. 1. 5
	class Marble

	������ ������ ��Ÿ���ϴ�. 
	Object�� ��ӹ޾� �ڽ��� ��ǥ�������� ��ġ�� ����մϴ�.
*/
/*
	2016. 1. 15
	cpp �ۼ� 1�� �Ϸ�
*/

namespace components
{
	using mathematics::IntPosition;
	using components::Marble;
	using components::marble_ptr;
	using scenes::TextureList; 
	using cabochon_constants::NO_POSITION;
	
	enum class MarbleColor { None=-1, Red, Orange, Yellow, Green, Blue, Purple, Gray, Num};

	class Marble
		:public Object
	{
	public:
		static const int marbleWidth = cabochon_constants::MARBLE_WIDTH;
		static const int marbleHeight = cabochon_constants::MARBLE_HEIGHT;
	private:
		IntPosition _gridPosition;
		MarbleColor _color;

	public:
		Marble(MarbleColor color);
		Marble(const IntPosition& gridPosition = NO_POSITION, MarbleColor color = MarbleColor::None);
		Marble(const Marble& rhs);
		virtual ~Marble();
		Marble& operator=(const Marble& rhs);

		virtual void loadLayers(TextureList& textureList);
		virtual MarbleColor getColor() const; 
		virtual MarbleColor setColor(MarbleColor color);

		virtual void setGridPosition(IntPosition gridPosition);
		virtual IntPosition getGridPosition() const;

		// marble�� ȸ�� ������ ������ ���� ������, layer �� ȸ����Ų��.
		virtual void rotate(scalar degree);
		virtual void draw();
		virtual void update(float frameTime);

		virtual bool circularHitTest(const Marble& anotherMarble, scalar scale = 1.0f) const;
		static bool circularHitTest(const Marble& marble1, const Marble& marble2, scalar scale = 1.0f);


	};
}
#endif