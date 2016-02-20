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
	using controls::MarbleControl;
	using components::Marble;
	using components::marble_ptr;
	using components::ShootedMarble;
	using controls::MarbleBoard;
	using controls::BoardState;
	using controls::MarbleRows;
	using controls::MarbleColorOn;
	using mathematics::IntPosition;
	using mathematics::Angle;
	using scenes::TextureList;

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
	enum class Quadrant{ none = -1, first = 1, second, third, fourth };

	class MarbleControl
		:public Control
	{
	private:
		using shooted_ptr = std::unique_ptr < ShootedMarble >;
		static const IntPosition noPosition;

		//marble_ptr �� ���� 2���� �迭
		MarbleBoard _marbleBoard;
		// �߻�Ǿ� ���� marbleBoard�� �������� ���� marble. �ٸ� marble_ptr�� �ٸ��� �Ź� ������ ������ �ݺ��Ѵ�.
		shooted_ptr _shootedMarble;
		// ��� ������ marble�� board �� ��ġ. attach �� ������ ��������, break üũ�� ���������� ��ȿ�ϴ�.
		IntPosition _justAttached;		

	public:
		MarbleControl();
		MarbleControl(const MarbleControl& rhs) = delete;
		virtual ~MarbleControl();
		MarbleControl& operator=(const MarbleControl& rhs) = delete;

		// Shooted Marble�� �ִ��� �˻�.
		bool isShooting() const;

		IntPosition getJustAttached() const;
		bool hasJustAttached() const;

		// Shooted Marble�� ���� ��ȯ.
		shooted_ptr& getShootedMarble();
		// ���ο� Shooted Marble�� �����ϰ� �����.
		void setShootedMarble(MarbleColor color, Position position, scalar speed, Angle degree, TextureList& textureList);

		// ���� marbleBoard ���� ��� ���� marble�� �ִ��� on off �� ǥ���Ѵ�.
		MarbleColorOn getExistColors() const;
		// marble board�� ������ ��ȯ�Ѵ�.
		MarbleBoard& getMarbleBoard();
		// marble board�� ������ ��ȯ�Ѵ�. (const)
		const MarbleBoard& getMarbleBoard() const;

		//Grid ��ġ (������ġ) ��ȯ, (�ִ� 6��)
		std::vector<IntPosition> getTestSet(const shooted_ptr& shootedMarble) const;
		//Grid ��ġ (������ġ) ��ȯ, (�ִ� 6��)
		std::vector<IntPosition> getTestSet(const IntPosition& gridPosition) const;
		//Grid ��ġ (������ġ) ��ȯ, (�ִ� 2��)
		//isAttachable �� ���.
		std::vector<IntPosition> getLessTestSet(const shooted_ptr& shootedMarble) const;


		//Quadrant
		Quadrant getQuadrant(const shooted_ptr& shootedMarble) const;
		Quadrant getQuadrant(const Position& marblePosition) const;

		//attach shooted marble
		bool isAttachable(const shooted_ptr& shootedMarble, const IntPosition& gridPosition) const;
		bool isAttachable(const shooted_ptr& shootedMarble) const;

		//test �ϰ� �����ϸ� Attach �Ѵ�.
		bool attach(shooted_ptr& shootedMarble);

		// justAttached �� ������ colorMatch�� �غ���.
		bool smash();

		//pure virtual functions
		virtual void render();
		virtual void update(float frameTime);
	};

}
#endif