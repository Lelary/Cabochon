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
	구슬 판의 최대 크기 = 구슬이 가질수 있는 최대위치 +1
	구슬판의 마지막 행은 dead zone
	maxX는 8이지만 실제로는
	해당 행이 even인 경우 8이며, odd 일 경우 8-1=7 이다.
	maxY는 차후 변경 가능
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

		// Marble 이 있을 경우 MarbleColor 반환, 없을 경우엔 MarbleColor::None 반환.
		MarbleColor existMarble(int x, int y);

		bool addMarble(int x, int y, marble_ptr marble);

		bool removeMarble(int x, int y);

		// marble의 존재 여부와 상관없이 0번 줄을 삭제한다.
		// RowZero는 Line 아래에 있는 Row.
		void removeRowZero();

		int getMarbleCount(MarbleColor c);
		int getMarbleCount();
		int getHeight();

		/*
		// 이 함수로 알 수 있는 것.
		// 반환값 :  현재 Marble 이 있는 첫번 째 줄.
		// 0반환 : 게임 오버.										// gameOver() 가 효율이 나음.
		// getHeight() 반환 :게임이 클리어 된 상태.					// gameClear() 가 효율이 나음.
		// 10초과일 경우 화면에 보이는 것이 없으므로 내려줘야함.	// 다른 함수에서.
		// 탐색할 필요가 없게 하는 것이 좋음.
		*/
		int getFloor();

		// 마지막 줄에 Marble이 하나라도 있으면 true.
		bool gameOver();

		// Marble이 Board에 남아 있지 않으면 true.
		bool gameClear();

		BoardState dragDown();

		void loadBoard(File* file);
		void buildBoard();


	};

}

#endif