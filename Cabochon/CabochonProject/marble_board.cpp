// 2016. 2. 17.
#include "marble_board.h"
#include "vector2.h"

using components::MarbleColor;
using controls::MarbleBoard;
using controls::BoardState;
using controls::MarbleGenerator; 
using mathematics::Position;
using mathematics::scalar;

MarbleBoard::MarbleBoard()
	:_boardState(BoardState::Build), _dragged(false)
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

	//�޸� ���� ���� �ؾ���.
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
				return row;				// _marbles�� �ε���.

	// ��� nullptr�� ���. �� ��Ȳ�� ������ Ŭ����Ȼ�����. 
	return getHeight();
}

bool MarbleBoard::gameOver()
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

bool MarbleBoard::gameClear()
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

BoardState MarbleBoard::dragDown()
{
	// remove Row Zero;
	// Row Zero �� �����Ǹ� �ڵ����� ��ĭ�� �����´�.
	// ( �ٸ� �Լ�����. )
	removeRowZero();
	_dragged = true;

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
void MarbleBoard::makeRandomBoard()
{
	if (_boardState != BoardState::Build)
		return;
	
	_marbles.clear();
	bool even = true;
	int row = MarbleGenerator::getRandomNumber(4, 20);
	// temporary Row in stack.
	for (int i = 0; i < row; i++)
	{
		MarbleRow marbleRow;
		if (even==true)
			for (int i = 0; i < maxX; i++)
				marbleRow[i] = MarbleGenerator::makeRandomMarble();
		else
			for (int i = 0; i < maxX-1; i++)
				marbleRow[i] = MarbleGenerator::makeRandomMarble();

		_marbles.push_front(std::move(marbleRow));
		even = !even;
	}

	row = MarbleGenerator::getRandomNumber(4, 6);
	for (int i = 0; i < row; i++)
	{
		MarbleRow marbleRow;
		if (even == true)
			for (int i = 0; i < maxX; i++)
				marbleRow[i] = MarbleGenerator::makeMarble(MarbleColor::None);
		else
			for (int i = 0; i < maxX - 1; i++)
				marbleRow[i] = MarbleGenerator::makeMarble(MarbleColor::None);

		_marbles.push_front(std::move(marbleRow));
		even = !even;
	}

	if (getHeight() < 10)
	{
		MarbleRow marbleRow;
		if (even == true)
			for (int i = 0; i < maxX; i++)
				marbleRow[i] = MarbleGenerator::makeMarble(MarbleColor::None);
		else
			for (int i = 0; i < maxX - 1; i++)
				marbleRow[i] = MarbleGenerator::makeMarble(MarbleColor::None);

		_marbles.push_front(std::move(marbleRow));
		even = !even;
	}
	
	// marble ���� 
	// marble�� y��ġ(intposition, position ���)��
	// �¾��������.
	updateMarblePositions();

	_boardState = BoardState::Ready;
}
void MarbleBoard::updateMarblePositions()
{
	//��� Marble�� Position, IntPosition Update;
	int width = Marble::getMarbleWidth();
	int height = Marble::getMarbleHeight();
	scalar line = height * 10;
	scalar x = 0;
	scalar y = line;//line�� ��ġ.
	Position offset;

	// int position�� �ڽ��� index,
	// position�� offset + index*width, offset+index*height
	for (int i = 0; i<_marbles.size();i++){
		for (int j = 0; j < _marbles[i].size(); j++){
			if (_marbles[i][j] != nullptr){
				_marbles[i][j]->setGridPosition({ i, j });
				_marbles[i][j]->setPosition(x + i*width, y + j*height);
			}
		}
	}
	
	_dragged = false;
}

void MarbleBoard::render()
{
	//marbles draw
	//0~10�� Row�� �׸�.
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < maxX; j++)
			if (_marbles[i][j]!=nullptr)
				_marbles[i][j]->draw();
}
void MarbleBoard::update(float frameTime)
{
	// �ٳ����� �߻����� ��, 
	// marble�� y��ġ(intposition, position ���)�� ��ĭ�� ����.
	if (_dragged)
		updateMarblePositions();
	_dragged = false;
}