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
	using mathematics::Position;
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
		MarbleBoard(const MarbleBoard& rhs) = delete;
		~MarbleBoard();
		MarbleBoard& operator=(const MarbleBoard& rhs) = delete;
		// marbleBoard�� �ؽ�ó�� �ϰ������� �ε��Ѵ�.
		void loadTextures(TextureList& textureList);


		// marble_ptr ���� ��ȯ.
		const marble_ptr& getMarble(IntPosition gridPosition) const;
		const marble_ptr& getMarble(int x, int y) const;

		// Marble �� ���� ��� MarbleColor ��ȯ, ���� ��쿣 MarbleColor::None ��ȯ (��ü�� Color�� None���� ǥ���Ͽ� ����ô)
		MarbleColor existMarble(IntPosition gridPosition) const;
		MarbleColor existMarble(int x, int y) const;
	
		// �ش� ������ Marble �߰� (�����δ� ���� �ٲٰ� ī��Ʈ�� �ø�)
		bool addMarble(IntPosition gridPosition, MarbleColor color);
		bool addMarble(int x, int y, MarbleColor color);

		// �ش� ��ġ�� Marble ���� (�����δ� ���� None����, ī��Ʈ�� ����)
		bool removeMarble(int x, int y);

		// �ش� Color�� ���� Marble Instance ����.
		marble_ptr makeMarble(MarbleColor color);
		marble_ptr makeRandomMarble();
		marble_ptr makeRandomMarble(MarbleColorOn colorRange);

		// �����ִ� marble�� ���� ���ο� ������� 0�� ���� �����Ѵ�.
		// RowZero�� Line �Ʒ��� �ִ� Row. 
		void removeRowZero();

		// �ش� ������ Marble ������ ��ȯ�Ѵ�.
		int getMarbleCount(MarbleColor c) const;

		// �����ִ� Marble ������ ��ȯ�Ѵ�.
		int getMarbleCount() const;

		// ���� ����(Row ��) ��ȯ. (Ceiling ���� ������ Row�� ��ȣ�̴�.)
		int getHeight() const;

		// ���� Board�� ���� ���� (���� ������ �����̱⵵ �ϴ�.)
		void setBoardState(BoardState state);

		// ���� Board�� ���� ��ȯ (���� ������ �����̱⵵ �ϴ�.)
		BoardState getBoardState() const;

		/*
		// �� �Լ��� �� �� �ִ� ��.
		// ��ȯ�� :  ���� ���� Marble �� �����ϴ� ù�� ° ��.
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

		// ( Ÿ�̸Ӱ� ���� ��� ���� �� �� ���� )
		// �� �� ������ ó���� �ϸ� ���ݵǴ� �ۿ���� �Բ� ó���Ѵ�.
		// �� �۾����� ���� ���ŵ� ���� ���� BoardState�� ��ȯ�Ѵ�.
		BoardState dragDown();

		//void loadBoard(File* file);
		//void buildBoard();

		// ������ Board Map�� �����Ѵ�. 
		// (Level ��� �߰� �Ŀ� �� Level�� ġ��, negative ������ ����.)
		void makeRandomBoard();

		// ��� Marble���� �ڽ��� ������ �ִ� Dequeue ������ ��ȣ�� ��������,
		// GridPosition �� Position�� �����Ѵ�. (Marble���� ���ĵ�)
		void updateMarblePositions();

		// �ڽ��� �߽����� x��ǥ�� �Ķ���ͷ� �ְ� Column ��ȣ�� ��´�.
		// rowType�� argument�� �ʿ��ϴ�. getRowType(y)�� �� �� �ִ�.
		// example : 0 <= x < 50 -> 10
		int positionToColumnIndex(scalar x, RowType rowType) const;
		// �ڽ��� �߽����� y ��ǥ�� �Ķ���ͷ� �ְ� Row ��ȣ�� ��´�.
		int positionToRowIndex(scalar y) const ;
		// �ڽ��� �߽����� ��ǥ�� �Ķ���ͷ� MarbleBoard������ Index ��ȣ�� ��´�.
		IntPosition positionToIndex(scalar x, scalar y) const;
		// �ڽ��� �߽����� ��ǥ�� �Ķ���ͷ� MarbleBoard������ Index ��ȣ�� ��´�.
		IntPosition positionToIndex(const Position& position) const;

		// �ڽ��� �߽����� y ��ǥ�� ���� Even Row ���� Odd Row���� �� �� �ִ�.
		RowType getRowType(scalar y) const;
		// �ڽ��� Row ��ȣ�� ����, RowType�� Even���� Odd���� �� �� �ִ�. 
		RowType getRowType(int row) const; 

		//pure virtual functions
		virtual void render();
		virtual void update(float frameTime);

	};

}

#endif