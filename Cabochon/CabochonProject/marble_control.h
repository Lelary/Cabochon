#ifndef _MARBLE_CONTROL_H
#define _MARBLE_CONTROL_H

#include "controls.h"
#include "marble.h"
#include "control.h"
#include "shooted_marble.h"
#include "marble_board.h"
#include <array>
#include <vector>

namespace controls
{
	using mathematics::IntPosition;
	using mathematics::Angle;
	using components::Marble;
	using components::marble_ptr;
	using components::ShootedMarble;
	using controls::MarbleControl;
	using controls::MarbleBoard;
	using controls::BoardState;
	using controls::MarbleRows;
	using controls::MarbleColorOn;
	using scenes::TextureList;

/*
	2016. 1. 18.
	TODO.

	1. 부착 (ceiling, marble_array).
	2. 같은 컬러 3개 이상인지 확인
	3. 같은 컬러 삭제 등록
	4. ceiling 과 union 되지 않은 블록 삭제 등록
	5. 삭제 애니메이션
	6. 삭제+점수추가.
*/
	enum class Quadrant{ none = -1, first = 1, second, third, fourth };

	class MarbleControl
		:public Control
	{
	private:
		using shooted_ptr = std::unique_ptr < ShootedMarble >;

		//marble_ptr 에 대한 2차원 배열
		MarbleBoard _marbleBoard;
		// 발사되어 아직 marbleBoard에 부착되지 않은 marble. 다른 marble_ptr과 다르게 매번 생성과 삭제를 반복한다.
		shooted_ptr _shootedMarble;
		// 방금 부착된 marble의 board 상 위치. attach 가 성공한 시점부터, smash 체크가 끝날때까지 유효하다.
		IntPosition _justAttached;		

	public:
		MarbleControl();
		MarbleControl(const MarbleControl& rhs) = delete;
		virtual ~MarbleControl();
		MarbleControl& operator=(const MarbleControl& rhs) = delete;

		// Shooted Marble이 있는지 검사.
		bool isShooting() const;
		
		IntPosition getJustAttached() const;
		bool hasJustAttached() const;

		// Shooted Marble의 참조 반환.
		shooted_ptr& getShootedMarble();
		// 새로운 Shooted Marble을 설정하고 만든다.
		void setShootedMarble(MarbleColor color, Position position, scalar speed, Angle degree, TextureList& textureList);

		// 지금 marbleBoard 위에 어느 색깔 marble이 있는지 on off 로 표시한다.
		MarbleColorOn getExistColors() const;
		// marble board의 참조를 반환한다.
		MarbleBoard& getMarbleBoard();
		// marble board의 참조를 반환한다. (const)
		const MarbleBoard& getMarbleBoard() const;

		//Grid 위치 (인접위치) 반환, (최대 6개) , smash()에 사용.
		std::vector<IntPosition> getTestSet(const shooted_ptr& shootedMarble) const;
		//Grid 위치 (인접위치) 반환, (최대 6개) , smash()에 사용.
		std::vector<IntPosition> getTestSet(IntPosition gridPosition) const;
		//Grid 위치 (인접위치) 반환, (최대 2개) , isAttachable 에 사용.
		std::vector<IntPosition> getLessTestSet(const shooted_ptr& shootedMarble) const;

		//Quadrant
		Quadrant getQuadrant(const shooted_ptr& shootedMarble) const;
		Quadrant getQuadrant(Position marblePosition) const;

		//attach shooted marble
		bool isAttachable(const shooted_ptr& shootedMarble, IntPosition gridPosition) const;
		bool isAttachable(const shooted_ptr& shootedMarble) const;

		// test 하고 가능하면 Attach 한다.
		// Attach 되었을 경우 true
		bool attach(shooted_ptr& shootedMarble);

		// justAttached 가 있으면 colorMatch를 해본다.
		// Smash 된 Marble이 있을 경우 true
		bool smash();

		//pure virtual functions
		virtual void render();
		virtual void update(float frameTime);
	};

}
#endif