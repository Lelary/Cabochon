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
	MarbleRow 의 변경(array->vector)으로 인해 많은 메소드의 코드들이 더 짧아질수있으나(getRowType() 등),
	다른 클래스(MarbleControl) 부터 수정 후, 차후에 업데이트.
	*/
	/*
	2016. 1. 16
	구슬 판의 최대 크기 = 구슬이 가질수 있는 최대위치 +1
	구슬판의 마지막 행은 dead zone
	maxX는 8이지만 실제로는
	해당 행이 even인 경우 8이며, odd 일 경우 8-1=7 이다.
	maxY는 차후 변경 가능
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
		// level 은 Positive 일 경우 load 한 맵,
		// Zero 일경우 끝이 없는 무한 맵
		// Negative 일 경우 랜덤맵을 생성. (level 값은 abs()를 통해 얻음)
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

		// Marble 이 있을 경우 MarbleColor 반환, 없을 경우엔 MarbleColor::None 반환.
		// 2016. 2. 18.
		// Marble 이 없는 것을 ,  Marble 객체가 없는 nullptr로 표시할 것인지, Color만 None으로 표시하여 없는척을 할것인지 결정해야함.
		// 후자를 선택하여 진행.
		MarbleColor existMarble(IntPosition gridPosition) const;
		MarbleColor existMarble(int x, int y) const;
		bool addMarble(IntPosition gridPosition, MarbleColor color);
		bool addMarble(int x, int y, MarbleColor color);
		bool removeMarble(int x, int y);

		// marble의 존재 여부와 상관없이 0번 줄을 삭제한다.
		// RowZero는 Line 아래에 있는 Row.
		void removeRowZero();

		int getMarbleCount(MarbleColor c) const;
		int getMarbleCount() const;
		int getHeight() const;
		BoardState getBoardState()const;
		/*
		// 이 함수로 알 수 있는 것.
		// 반환값 :  현재 Marble 이 있는 첫번 째 줄.
		// 0반환 : 게임 오버.										// gameOver() 가 효율이 나음.
		// getHeight() 반환 :게임이 클리어 된 상태.					// gameClear() 가 효율이 나음.
		// 10초과일 경우 화면에 보이는 것이 없으므로 내려줘야함.	// 다른 함수에서.
		// 탐색할 필요가 없게 하는 것이 좋음.
		*/
		int getFloor() const;

		scalar getCeilingPosition() const;

		// 마지막 줄에 Marble이 하나라도 있으면 true.
		bool gameOver();

		// Marble이 Board에 남아 있지 않으면 true.
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