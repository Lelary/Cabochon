//2016. 1. 17
#ifndef _SHOOTED_MARBLE_H
#define _SHOOTED_MARBLE_H
#include "marble.h"
#include "grid.h"
#include "angle.h"

/*
2016. 1. 17

��Ӱ���� ������
wrapper�� composite�� ������ �����ؾ���
Marble�� �ӵ� ���Ϳ� �����Ӹ� �߰��ϱ� ���� �ʿ��ϴ�.

wrapper�� �����ϴ�.
wrapper�� �ۼ�.
*/

namespace components
{
	using mathematics::Velocity;
	using mathematics::Angle;

	class ShootedMarble
	{
	private:
		marble_ptr _marble;
		Velocity _velocity;
	public:
		ShootedMarble();
		ShootedMarble(marble_ptr& marble);
		ShootedMarble(const ShootedMarble& rhs) = delete;
		virtual ~ShootedMarble();
		ShootedMarble& operator=(const ShootedMarble& rhs) = delete;

		/*
		2016. 1. 17

		Velocity ��ŭ �̵��ϸ�, ���� �浹ó���� �ؾ��Ѵ�.
		�ٸ� Marble���� Attach ó���� MarbleControl�� ������
		( marble_array�� �߰��ؾ��ϱ� ����)
		Attach �ϰ� ���� �Ǵ��ϰ� �����ϴ� ���� ���⼭ �ص� �ȴ�.
		(�����ʴ��� ����)

		*/
		void move();

		/*
		2016. 1. 18

		MarbleControl���� marble_ptr�� �������� �ѱ涧 ����� �Լ� �ʿ�
		*/
		//marble_ptr getMarble() const; 
		Velocity getVelocity() const;

		void setVelocity(Velocity velocity);
		void setVelocity(scalar vx, scalar vy);
		void setVelocity(scalar speed, scalar angle);
		void setMarble(marble_ptr& marble);

	};
}

#endif // _SHOOTED_MARBLE_H