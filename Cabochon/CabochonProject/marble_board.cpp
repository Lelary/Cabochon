// 2016. 2. 17.
#include "marble_board.h"

using components::MarbleColor;
using components::MarbleBoard;
using controls::BoardState;
using controls::MarbleGenerator;

MarbleBoard::MarbleBoard()
	:_boardState(BoardState::Ready)
{
}
MarbleBoard::~MarbleBoard()
{
}

MarbleColor MarbleBoard::existMarble(int x, int y)
{
	if (_marbles[x][y] != nullptr)
		return _marbles[x][y]->getColor();
	else
		return MarbleColor::None;
}

bool MarbleBoard::addMarble(int x, int y, marble_ptr marble)
{
	if (_marbles[x][y] != nullptr)
		return false;

	_marbles[x][y] = std::move(marble);
	_colorCount[(int)marble->getColor()]++;
	return true;
}

bool MarbleBoard::removeMarble(int x, int y)
{
	if (_marbles[x][y] != nullptr)
		return false;

	//메모리 해제 전에 해야함.
	_colorCount[(int)_marbles[x][y]->getColor()]--;
	_marbles[x][y].reset();
}

void MarbleBoard::removeRowZero()
{
	_marbles.pop_front();
}

int MarbleBoard::getMarbleCount(MarbleColor c)
{
	if (c == MarbleColor::None || c == MarbleColor::Num)
		throw("getMarbleCount() : Invalid MarbleColor Parameter.");

	return _colorCount[(int)c];
}
int MarbleBoard::getMarbleCount()
{
	int sum = 0;
	for (int i : _colorCount)
	{
		sum += i;
	}
	return sum;
}
int MarbleBoard::getHeight()
{
	return _marbles.size();
}

int MarbleBoard::getFloor()
{
	for (int row = 0; row < _marbles.size(); row++)
		for (const marble_ptr& marble : _marbles[row])
			if (marble != nullptr)
				return row;				// _marbles의 인덱스.

	// 모두 nullptr일 경우. 이 상황은 게임이 클리어된상태임. 
	return getHeight();
}

bool MarbleBoard::gameOver()
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

bool MarbleBoard::gameClear()
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

BoardState MarbleBoard::dragDown()
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
void MarbleBoard::makeRandomBoard()
{
	if (_boardState != BoardState::Build)
		return;

	_marbles.clear();
	int row = MarbleGenerator::getRandomNumber(4, 20);
	// temporary Row in stack.
	for (int i = 0; i < row; i++)
	{
		MarbleRow marbleRow;
		for (marble_ptr& marble : marbleRow)
			marble = MarbleGenerator::makeRandomMarble();
		_marbles.push_front(std::move(marbleRow));
	}

	row = MarbleGenerator::getRandomNumber(4, 6);
	for (int i = 0; i < row; i++)
	{
		MarbleRow marbleRow;
		for (marble_ptr& marble : marbleRow)
			marble = MarbleGenerator::makeMarble(MarbleColor::None);
		_marbles.push_front(std::move(marbleRow));
	}

	if (getHeight() < 10)
	{
		row = 10 - getHeight();
		for (int i = 0; i < row; i++)
		{
			MarbleRow marbleRow;
			for (marble_ptr& marble : marbleRow)
				marble = MarbleGenerator::makeMarble(MarbleColor::None);
			_marbles.push_front(std::move(marbleRow));
		}
	}


	_boardState = BoardState::Ready;
}
