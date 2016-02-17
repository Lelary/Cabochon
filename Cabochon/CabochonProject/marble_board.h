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
		MarbleColor existMarble(int x, int y)
		{
			if (_marbles[x][y] != nullptr)
				return _marbles[x][y]->getColor();
			else
				return MarbleColor::None;
		}

		bool addMarble(int x, int y, marble_ptr marble)
		{
			if (_marbles[x][y] != nullptr)
				return false;
			
			_marbles[x][y] = std::move(marble);
			_colorCount[(int)marble->getColor()]++;
			return true;
		}

		bool removeMarble(int x, int y)
		{
			if (_marbles[x][y] != nullptr)
				return false;

			//메모리 해제 전에 해야함.
			_colorCount[(int)_marbles[x][y]->getColor()]--;	
			_marbles[x][y].reset();
		}

		// marble의 존재 여부와 상관없이 0번 줄을 삭제한다.
		// RowZero는 Line 아래에 있는 Row.
		void removeRowZero()
		{
			_marbles.pop_front();
		}

		int getMarbleCount(MarbleColor c)
		{
			if (c == MarbleColor::None || c == MarbleColor::Num)
				throw("getMarbleCount() : Invalid MarbleColor Parameter.");

			return _colorCount[(int)c];
		}
		int getMarbleCount()
		{
			int sum = 0;
			for (int i : _colorCount)
			{
				sum += i;
			}
			return sum;
		}
		int getHeight()
		{
			return _marbles.size();
		}
		/*
		// 이 함수로 알 수 있는 것.
		// 반환값 :  현재 Marble 이 있는 첫번 째 줄.
		// 0반환 : 게임 오버.										// gameOver() 가 효율이 나음.
		// getHeight() 반환 :게임이 클리어 된 상태.					// gameClear() 가 효율이 나음.
		// 10초과일 경우 화면에 보이는 것이 없으므로 내려줘야함.	// 다른 함수에서.
		// 탐색할 필요가 없게 하는 것이 좋음.
		*/
		int getFloor() 
		{
			for (int row = 0; row < _marbles.size(); row++)
				for (const marble_ptr& marble : _marbles[row])
					if (marble != nullptr)
						return row;				// _marbles의 인덱스.

			// 모두 nullptr일 경우. 이 상황은 게임이 클리어된상태임. 
			return getHeight();
		}

		// 마지막 줄에 Marble이 하나라도 있으면 true.
		bool gameOver()
		{
			// 혹은 getFloor()==0
			for (const marble_ptr& marble : _marbles.front())
				if (marble != nullptr)
				{
					_boardState = BoardState::GameOver;
					return true;
				}
			return false;
		}

		// Marble이 Board에 남아 있지 않으면 true.
		bool gameClear()
		{
			// 방법 1 :  if(getMarbleCount()==0)
			// 방법 2 :  if(getFloor()==getHeight())
			
			if (getMarbleCount() == 0)
			{
				_boardState = BoardState::GameClear;
				return true;
			}
			return false;
		}

		BoardState dragDown()
		{
			// remove Row Zero;
			// Row Zero 가 삭제되면 자동으로 한칸씩 내려온다.
			// ( 다른 함수에서. )
			removeRowZero();

			if (gameOver())
				return _boardState = BoardState::GameOver;

			if (gameClear())
				return _boardState = BoardState::GameClear;
				
			// 화면 밖에만 Marble 이 존재. 
			// 화면에 보일 때 까지 더 끌어내림.
			int toDrag = getFloor() - 10;
			if (toDrag > 0)
			{
				for (int i = 0; i < toDrag; i++)
					_marbles.pop_front();
			}
			return _boardState = BoardState::Play;
		}

		void loadBoard(File* file);
		void buildBoard();


	};

}

#endif