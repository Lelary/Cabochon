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
		const MarbleBoard& _marbleBoard;

		// ���� ��ġ
		Position _prevPosition;
		// ���� Index
		IntPosition _currentIndex;
		// ���� Index
		IntPosition _prevIndex;
		// index�� ��� ����.
		bool _indexChanged;

		void setCurrentIndex(IntPosition index);
	public:
		ShootedMarble(const MarbleBoard& marbleBoard);
		ShootedMarble(MarbleColor color, const MarbleBoard& marbleBoard);
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

		// ���� ��ġ.
		virtual Position getPrevCentralPosition() const;

		// updateIndex ȣ�� �� ���� _currentIndex, _prevIndex �� ������Ʈ �ȴ�.
		// ���� ȣ��� �������� �������� ������ true ����.
		bool updateIndex(const MarbleBoard& board);
		// ShootedMarble�� MarbleBoard �󿡼� ��� �ڸ� ���� �ִ��� �˻��ϴ� �Լ�.
		IntPosition getCurrentIndex() const;
		// ShootedMarble�� MarbleBoard �󿡼� ��� �ڸ� ���� �־����� �˻��ϴ� �Լ�.
		IntPosition getPrevIndex() const;
		bool indexChanged() const;
		// ���� ��ġ�� MarbleBoard �� �ε��� ������ ���.
		bool isInInvalidIndex() const;
		// ���� ��ġ�� MarbleBoard �� �ε��� ������ ���. // �׷��� ������Ʈ��������.
		// ������ ó�� ��ġ�� invalid��.
		bool wasInInvalidIndex() const;

		/*
		2016. 1. 17

		Velocity ��ŭ �̵��ϸ�, ���� �浹ó���� �ؾ��Ѵ�.
		�ٸ� Marble���� Attach ó���� MarbleControl�� ������
		( marble_array�� �߰��ؾ��ϱ� ����)
		Attach �ϰ� ���� �Ǵ��ϰ� �����ϴ� ���� ���⼭ �ص� �ȴ�.
		(�����ʴ��� ����)

		*/
		virtual void move(const MarbleBoard& board, float frameTime);
		
		// �ӵ� ���� �Լ�.
		static scalar getDefaultSpeed();

		virtual void update(float frameTIme);
	};
}

#endif // _SHOOTED_MARBLE_H