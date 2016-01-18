#ifndef _MARBLE_CONTROL_H
#define _MARBLE_CONTROL_H

#include "temporary.h"
#include "controls.h"
#include "marble.h"
#include "grid.h"
#include "shooted_marble.h"
#include <array>

namespace controls
{
	using controls::MarbleControl;
	using components::Marble;
	using components::ShootedMarble;
	using components::Grid;
	using temporary::marble_array;

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
	{
	private:
		using shooted_ptr = std::unique_ptr < ShootedMarble >;

		//marble_ptr �� ���� 2���� �迭
		marble_array _marbles;
		/*
			steeringWheelControl �� ���� �������� ������ ��.
		*/
		shooted_ptr _shootedMarble;

		//���� ����
		/*
			2016. 1. 18.
			��������»����ϰ� getter�� �����.
		*/
		int _currentHeight;

	public:
		MarbleControl();
		MarbleControl(const MarbleControl& rhs) = delete;
		virtual ~MarbleControl();
		MarbleControl& operator=(const MarbleControl& rhs) = delete;

		int getCurrentHeight() const;

		shooted_ptr& getShootedMarble();
		void setShootedMarble(shooted_ptr& shootedMarble);
	};

}
#endif