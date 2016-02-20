//2016. 1. 17
#ifndef _SHOOTED_MARBLE_H
#define _SHOOTED_MARBLE_H
#include "marble.h"
#include "angle.h"
#include "marble_board.h"

/*
2016. 1. 17

��Ӱ���� ������
wrapper�� composite�� ������ �����ؾ���
Marble�� �ӵ� ���Ϳ� �����Ӹ� �߰��ϱ� ���� �ʿ��ϴ�.

wrapper�� �����ϴ�.
wrapper�� �ۼ�.

2016. 2. 19.
��Ӱ���� ����.
*/

namespace components
{
	using mathematics::Velocity;
	using mathematics::Angle;
	using controls::MarbleBoard;

	class ShootedMarble
		:public Marble
	{
	private:
		static const scalar defaultSpeed;
		Velocity _velocity;
		Position _prevCentralPosition;

	public:
		ShootedMarble();
		ShootedMarble(MarbleColor color);
		ShootedMarble(const ShootedMarble& rhs) = delete;
		virtual ~ShootedMarble();
		ShootedMarble& operator=(const ShootedMarble& rhs) = delete;

		virtual void setPosition(const Position& position);
		// the position of Left Top 
		virtual void setPosition(scalar x, scalar y);
		// the position of middle, changes position property.
		virtual void setCentralPosition(const Position& position);
		// the position of middle, changes position property.
		virtual void setCentralPosition(scalar x, scalar y);

		virtual Position getPrevCentralPosition() const;

		/*
		2016. 1. 17

		Velocity ��ŭ �̵��ϸ�, ���� �浹ó���� �ؾ��Ѵ�.
		�ٸ� Marble���� Attach ó���� MarbleControl�� ������
		( marble_array�� �߰��ؾ��ϱ� ����)
		Attach �ϰ� ���� �Ǵ��ϰ� �����ϴ� ���� ���⼭ �ص� �ȴ�.
		(�����ʴ��� ����)

		*/
		virtual void move(const MarbleBoard& board, float frameTime);
		
		static scalar getDefaultSpeed();
		virtual Velocity getVelocity() const;
		virtual void setVelocity(Velocity velocity);
		virtual void setVelocity(scalar vx, scalar vy);
		virtual void setVelocity(scalar speed, Angle angle);

	};
}

#endif // _SHOOTED_MARBLE_H