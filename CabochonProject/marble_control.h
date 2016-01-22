#ifndef _MARBLE_CONTROL_H
#define _MARBLE_CONTROL_H

#include "temporary.h"
#include "controls.h"
#include "marble.h"
#include "grid.h"
#include "shooted_marble.h"
#include <array>
#include <vector>

namespace controls
{
	using controls::MarbleControl;
	using components::Marble;
	using components::marble_ptr;
	using components::ShootedMarble;
	using components::Grid;
	using temporary::marble_array;
	using mathematics::IntPosition;

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

	class MarbleControl
	{
	private:
		//marble_ptr 에 대한 2차원 배열
		marble_array _marbles;

		using shooted_ptr = std::unique_ptr < ShootedMarble >;
		// steeringWheelControl 로 부터 소유권이 이전될 것.
		shooted_ptr _shootedMarble;

	public:
		MarbleControl();
		MarbleControl(const MarbleControl& rhs) = delete;
		virtual ~MarbleControl();
		MarbleControl& operator=(const MarbleControl& rhs) = delete;

		//현재 높이
		int getCurrentHeight() const;

		//Shooted Marble
		shooted_ptr& getShootedMarble();
		void setShootedMarble(shooted_ptr& shootedMarble);

		//Attach 가능성이 있는 Grid 위치 반환. nullptr검사는 하지 않음.
		std::vector<IntPosition> getTestSet(const shooted_ptr& shootedMarble) const;
		//Attach 가능성이 있는 Grid 위치 반환. nullptr검사는 하지 않음.
		std::vector<IntPosition> getTestSet(const IntPosition& gridPosition) const;
		//attach shooted marble
		bool isAttachable(const shooted_ptr& shootedMarble, const IntPosition& gridPosition) const;
		bool isAttachable(const shooted_ptr& shootedMarble) const;
		void attach(shooted_ptr& shootedMarble, const IntPosition& marblePosition);
		void attach(shooted_ptr& shootedMarble);

		// build map
		bool existMarble(const IntPosition& gridPosition);
		void addMarble(marble_ptr& marble, const IntPosition& gridPosition);
		void removeMarble(const IntPosition& gridPosition);

	};

}
#endif