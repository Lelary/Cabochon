// 2016. 2. 17.
#ifndef _MARBLE_BOARD_H
#define _MARBLE_BOARD_H

#include "cabochon_constants.h"
#include "control.h"
#include "marble.h"
#include "object.h"
#include "marble_generator.h"
#include <deque>
#include <array>
namespace controls
{
	/*
	2016. 2. 18.
	MarbleRow �� ����(array->vector)���� ���� ���� �޼ҵ��� �ڵ���� �� ª������������(getRowType() ��),
	�ٸ� Ŭ����(MarbleControl) ���� ���� ��, ���Ŀ� ������Ʈ.
	*/
	/*
	2016. 1. 16
	���� ���� �ִ� ũ�� = ������ ������ �ִ� �ִ���ġ +1
	�������� ������ ���� dead zone
	maxX�� 8������ �����δ�
	�ش� ���� even�� ��� 8�̸�, odd �� ��� 8-1=7 �̴�.
	maxY�� ���� ���� ����
	*/
	using mathematics::scalar;
	using mathematics::IntPosition;
	using components::MarbleColor;
	using MarbleRow = std::vector < components::marble_ptr> ;
	using MarbleRows = std::deque <MarbleRow> ;

	enum class RowType{ None = -1, Even, Odd };
	enum class BoardState{Build, Ready, Play, GameOver, GameClear};

	class MarbleBoard
		: public Control
	{
	private:
		/*		
		// 2016. 2. 17.
		// TODO.-------------------------------------------------------------
		// level �� Positive �� ��� load �� ��,
		// Zero �ϰ�� ���� ���� ���� ��
		// Negative �� ��� �������� ����. (level ���� abs()�� ���� ����)
		//-------------------------------------------------------------------
		*/
		//const char* levelFile = "data\\level_data.txt";
		//const int maxLevel = 3;
		
		//int _level;
		BoardState _boardState;
		MarbleRows _marbles;
		bool _dragged;
		std::array<int, (int)MarbleColor::Num> _colorCount;
		
	public:
		MarbleBoard();
		~MarbleBoard();

		const marble_ptr& getMarble(IntPosition gridPosition)const;
		const marble_ptr& getMarble(int x, int y)const;

		// Marble �� ���� ��� MarbleColor ��ȯ, ���� ��쿣 MarbleColor::None ��ȯ.
		// 2016. 2. 18.
		// Marble �� ���� ���� ,  Marble ��ü�� ���� nullptr�� ǥ���� ������, Color�� None���� ǥ���Ͽ� ����ô�� �Ұ����� �����ؾ���.
		// ���ڸ� �����Ͽ� ����.
		MarbleColor existMarble(IntPosition gridPosition) const;
		MarbleColor existMarble(int x, int y) const;
		bool addMarble(IntPosition gridPosition, MarbleColor color);
		bool addMarble(int x, int y, MarbleColor color);
		bool removeMarble(int x, int y);

		// marble�� ���� ���ο� ������� 0�� ���� �����Ѵ�.
		// RowZero�� Line �Ʒ��� �ִ� Row.
		void removeRowZero();

		int getMarbleCount(MarbleColor c) const;
		int getMarbleCount() const;
		int getHeight() const;
		BoardState getBoardState()const;
		/*
		// �� �Լ��� �� �� �ִ� ��.
		// ��ȯ�� :  ���� Marble �� �ִ� ù�� ° ��.
		// 0��ȯ : ���� ����.										// gameOver() �� ȿ���� ����.
		// getHeight() ��ȯ :������ Ŭ���� �� ����.					// gameClear() �� ȿ���� ����.
		// 10�ʰ��� ��� ȭ�鿡 ���̴� ���� �����Ƿ� ���������.	// �ٸ� �Լ�����.
		// Ž���� �ʿ䰡 ���� �ϴ� ���� ����.
		*/
		int getFloor() const;

		scalar getCeilingPosition() const;

		// ������ �ٿ� Marble�� �ϳ��� ������ true.
		bool gameOver();

		// Marble�� Board�� ���� ���� ������ true.
		bool gameClear();

		BoardState dragDown();

		//void loadBoard(File* file);
		//void buildBoard();

		void makeRandomBoard();
		void updateMarblePositions();

		// 0<=x<50 -> 10
		int positionToIndexX(scalar x, RowType rowType) const;
		int positionToIndexY(scalar y)const ;
		RowType getRowType(scalar y) const;
		RowType getRowType(int y) const; 

		//pure virtual functions
		virtual void render();
		virtual void update(float frameTime);

	};

}

#endif