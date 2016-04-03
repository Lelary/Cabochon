#ifndef _MARBLE_H
#define _MARBLE_H
#include "object.h"
#include "angle.h"
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
	using mathematics::Angle;
	using mathematics::Velocity;
	using mathematics::IntPosition;
	using components::Marble;
	using components::marble_ptr;
	using scenes::TextureList; 
	using cabochon_constants::NO_POSITION;
	
	enum class MarbleColor { None=-1, Yellow, Green, Mint, Blue, Violet, Pink, Num};

	class Marble
		:public Object
	{
	public:
		static const int marbleWidth = cabochon_constants::MARBLE_WIDTH;
		static const int marbleHeight = cabochon_constants::MARBLE_HEIGHT;
	private:
		IntPosition _index;
		MarbleColor _color;
		Velocity _velocity;	// velocity, marble�� �ڽ��� velocity�� ������ ���� ������� �ʴ´�. (�ܺο��� �ʿ��Ҷ��� ���)

	public:
		Marble(MarbleColor color);
		Marble(const IntPosition& index = NO_POSITION, MarbleColor color = MarbleColor::None, Velocity velocity = {0.0f, 0.0f});
		Marble(const Marble& rhs);
		virtual ~Marble();
		Marble& operator=(const Marble& rhs);

		virtual void loadLayers(TextureList& textureList);
		virtual MarbleColor getColor() const; 
		virtual MarbleColor setColor(MarbleColor color);

		virtual void setIndex(IntPosition index);
		virtual IntPosition getIndex() const;

		virtual Velocity getVelocity() const;
		virtual void setVelocity(Velocity velocity);
		virtual void setVelocity(scalar vx, scalar vy);
		virtual void setVelocity(scalar speed, Angle angle);

		// marble�� ȸ�� ������ ������ ���� ������, layer �� ȸ����Ų��.
		virtual void rotate(scalar degree);
		virtual void draw();
		virtual void update(float frameTime);

		virtual bool circularHitTest(const Marble& anotherMarble, scalar scale = 1.0f) const;
		static bool circularHitTest(const Marble& marble1, const Marble& marble2, scalar scale = 1.0f);		
		
		void disappearing(scalar progressedFrame, scalar totalFrame, Position position);
	};
}
#endif