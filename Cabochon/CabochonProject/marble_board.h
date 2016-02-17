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

			//�޸� ���� ���� �ؾ���.
			_colorCount[(int)_marbles[x][y]->getColor()]--;	
			_marbles[x][y].reset();
		}

		// marble�� ���� ���ο� ������� 0�� ���� �����Ѵ�.
		// RowZero�� Line �Ʒ��� �ִ� Row.
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
		// �� �Լ��� �� �� �ִ� ��.
		// ��ȯ�� :  ���� Marble �� �ִ� ù�� ° ��.
		// 0��ȯ : ���� ����.										// gameOver() �� ȿ���� ����.
		// getHeight() ��ȯ :������ Ŭ���� �� ����.					// gameClear() �� ȿ���� ����.
		// 10�ʰ��� ��� ȭ�鿡 ���̴� ���� �����Ƿ� ���������.	// �ٸ� �Լ�����.
		// Ž���� �ʿ䰡 ���� �ϴ� ���� ����.
		*/
		int getFloor() 
		{
			for (int row = 0; row < _marbles.size(); row++)
				for (const marble_ptr& marble : _marbles[row])
					if (marble != nullptr)
						return row;				// _marbles�� �ε���.

			// ��� nullptr�� ���. �� ��Ȳ�� ������ Ŭ����Ȼ�����. 
			return getHeight();
		}

		// ������ �ٿ� Marble�� �ϳ��� ������ true.
		bool gameOver()
		{
			// Ȥ�� getFloor()==0
			for (const marble_ptr& marble : _marbles.front())
				if (marble != nullptr)
				{
					_boardState = BoardState::GameOver;
					return true;
				}
			return false;
		}

		// Marble�� Board�� ���� ���� ������ true.
		bool gameClear()
		{
			// ��� 1 :  if(getMarbleCount()==0)
			// ��� 2 :  if(getFloor()==getHeight())
			
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
			// Row Zero �� �����Ǹ� �ڵ����� ��ĭ�� �����´�.
			// ( �ٸ� �Լ�����. )
			removeRowZero();

			if (gameOver())
				return _boardState = BoardState::GameOver;

			if (gameClear())
				return _boardState = BoardState::GameClear;
				
			// ȭ�� �ۿ��� Marble �� ����. 
			// ȭ�鿡 ���� �� ���� �� �����.
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