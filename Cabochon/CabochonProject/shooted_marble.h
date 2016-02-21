//2016. 1. 17
#ifndef _SHOOTED_MARBLE_H
#define _SHOOTED_MARBLE_H
#include "marble.h"
#include "angle.h"
#include "marble_board.h"

/*
2016. 1. 17

상속관계로 만들지
wrapper로 composite로 만들지 결정해야함
Marble에 속도 벡터와 움직임를 추가하기 위해 필요하다.

wrapper가 간단하다.
wrapper로 작성.

2016. 2. 19.
상속관계로 변경.
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

		// 이전 위치
		Position _prevCentralPosition;
		// 현재 Index
		IntPosition _currentIndex;
		// 이전 Index
		IntPosition _prevIndex;

		void setCurrentIndex(IntPosition index);
	public:
		ShootedMarble();
		ShootedMarble(MarbleColor color);
		ShootedMarble(const ShootedMarble& rhs) = delete;
		virtual ~ShootedMarble();
		ShootedMarble& operator=(const ShootedMarble& rhs) = delete;

		// the position of Left Top 
		virtual void setPosition(const Position& position);
		// the position of Left Top 
		virtual void setPosition(scalar x, scalar y);
		// the position of middle, changes position property.
		virtual void setCentralPosition(const Position& position);
		// the position of middle, changes position property.
		virtual void setCentralPosition(scalar x, scalar y);

		// 이전 위치.
		virtual Position getPrevCentralPosition() const;

		// updateIndex 호출 시 마다 _currentIndex, _prevIndex 가 업데이트 된다.
		// 이전 호출과 비교했을때 변경점이 있으면 true 리턴.
		bool updateIndex(const MarbleBoard& board);

		// ShootedMarble이 MarbleBoard 상에서 몇번 자리 위에 있는지 검사하는 함수.
		IntPosition getCurrentIndex() const;
		// ShootedMarble이 MarbleBoard 상에서 몇번 자리 위에 있었는지 검사하는 함수.
		IntPosition getPrevIndex() const;

		/*
		2016. 1. 17

		Velocity 만큼 이동하며, 벽과 충돌처리를 해야한다.
		다른 Marble과의 Attach 처리는 MarbleControl이 맡으며
		( marble_array에 추가해야하기 때문)
		Attach 하게 될지 판단하고 정지하는 것은 여기서 해도 된다.
		(하지않더라도 무관)

		*/
		virtual void move(const MarbleBoard& board, float frameTime);
		
		// 속도 설정 함수.
		static scalar getDefaultSpeed();
		virtual Velocity getVelocity() const;
		virtual void setVelocity(Velocity velocity);
		virtual void setVelocity(scalar vx, scalar vy);
		virtual void setVelocity(scalar speed, Angle angle);
	};
}

#endif // _SHOOTED_MARBLE_H