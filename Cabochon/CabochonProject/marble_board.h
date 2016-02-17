// 2016. 2. 17.
#ifndef _MARBLE_BOARD_H
#define _MARBLE_BOARD_H

#include "components.h"
#include "marble.h"
#include "object.h"
#include <deque>
#include <array>
namespace components
{

	/*
	2016. 1. 16
	���� ���� �ִ� ũ�� = ������ ������ �ִ� �ִ���ġ +1
	�������� ������ ���� dead zone
	maxX�� 8������ �����δ�
	�ش� ���� even�� ��� 8�̸�, odd �� ��� 8-1=7 �̴�.
	maxY�� ���� ���� ����
	*/
	const unsigned int maxX = 8;

	using MarbleRow = std::array < components::marble_ptr, maxX > ;
	using MarbleRows = std::deque <MarbleRow> ;

	enum class BoardState{Ready, Play, GameOver, GameClear};

	class MarbleBoard
		: public Object
	{
	private:
		BoardState _boardState;

		MarbleRows _marbles;
		std::array<int, (int)MarbleColor::Num> _colorCount;
	public:
		MarbleBoard();
		~MarbleBoard();

		//marble_ptr getMarble();

		// Marble �� ���� ��� MarbleColor ��ȯ, ���� ��쿣 MarbleColor::None ��ȯ.
		MarbleColor existMarble(int x, int y);

		bool addMarble(int x, int y, marble_ptr marble);

		bool removeMarble(int x, int y);

		// marble�� ���� ���ο� ������� 0�� ���� �����Ѵ�.
		// RowZero�� Line �Ʒ��� �ִ� Row.
		void removeRowZero();

		int getMarbleCount(MarbleColor c);
		int getMarbleCount();
		int getHeight();

		/*
		// �� �Լ��� �� �� �ִ� ��.
		// ��ȯ�� :  ���� Marble �� �ִ� ù�� ° ��.
		// 0��ȯ : ���� ����.										// gameOver() �� ȿ���� ����.
		// getHeight() ��ȯ :������ Ŭ���� �� ����.					// gameClear() �� ȿ���� ����.
		// 10�ʰ��� ��� ȭ�鿡 ���̴� ���� �����Ƿ� ���������.	// �ٸ� �Լ�����.
		// Ž���� �ʿ䰡 ���� �ϴ� ���� ����.
		*/
		int getFloor();

		// ������ �ٿ� Marble�� �ϳ��� ������ true.
		bool gameOver();

		// Marble�� Board�� ���� ���� ������ true.
		bool gameClear();

		BoardState dragDown();

		void loadBoard(File* file);
		void buildBoard();


	};

}

#endif