//2016. 1. 17
#ifndef _SHOOTED_MARBLE_H
#define _SHOOTED_MARBLE_H
#include "marble.h"
#include "grid.h"
#include "angle.h"

/*
2016. 1. 17

상속관계로 만들지
wrapper로 composite로 만들지 결정해야함
Marble에 속도 벡터와 움직임를 추가하기 위해 필요하다.

wrapper가 간단하다.
wrapper로 작성.
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

		Velocity 만큼 이동하며, 벽과 충돌처리를 해야한다.
		다른 Marble과의 Attach 처리는 MarbleControl이 맡으며
		( marble_array에 추가해야하기 때문)
		Attach 하게 될지 판단하고 정지하는 것은 여기서 해도 된다.
		(하지않더라도 무관)

		*/
		void move();

		/*
		2016. 1. 18

		MarbleControl에게 marble_ptr의 소유권을 넘길때 사용할 함수 필요
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