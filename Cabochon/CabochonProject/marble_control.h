#ifndef _MARBLE_CONTROL_H
#define _MARBLE_CONTROL_H

#include "temporary.h"
#include "controls.h"
#include "marble.h"
#include "grid.h"
#include "control.h"
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

	1. ���� (ceiling, marble_array).
	2. ���� �÷� 3�� �̻����� Ȯ��
	3. ���� �÷� ���� ���
	4. ceiling �� union ���� ���� ��� ���� ���
	5. ���� �ִϸ��̼�
	6. ����+�����߰�.
*/

	class MarbleControl
		:public Control
	{
	private:
		//marble_ptr �� ���� 2���� �迭
		marble_array _marbles;

		using shooted_ptr = std::unique_ptr < ShootedMarble >;
		// steeringWheelControl �� ���� �������� ������ ��.
		shooted_ptr _shootedMarble;

	public:
		MarbleControl();
		MarbleControl(const MarbleControl& rhs) = delete;
		virtual ~MarbleControl();
		MarbleControl& operator=(const MarbleControl& rhs) = delete;

		//���� ����
		int getCurrentHeight() const;

		//Shooted Marble
		shooted_ptr& getShootedMarble();
		void setShootedMarble(shooted_ptr& shootedMarble);

		//Attach ���ɼ��� �ִ� Grid ��ġ ��ȯ. nullptr�˻�� ���� ����.
		std::vector<IntPosition> getTestSet(const shooted_ptr& shootedMarble) const;
		//Attach ���ɼ��� �ִ� Grid ��ġ ��ȯ. nullptr�˻�� ���� ����.
		std::vector<IntPosition> getTestSet(const IntPosition& gridPosition) const;
		//attach shooted marble
		bool isAttachable(const shooted_ptr& shootedMarble, const IntPosition& gridPosition) const;
		bool isAttachable(const shooted_ptr& shootedMarble) const;
		void attach(shooted_ptr& shootedMarble, const IntPosition& marblePosition);
		void attach(shooted_ptr& shootedMarble);

		// build map
		bool existMarble(const IntPosition& gridPosition) const;
		void addMarble(marble_ptr& marble, const IntPosition& gridPosition);
		void removeMarble(const IntPosition& gridPosition);

	};

}
#endif