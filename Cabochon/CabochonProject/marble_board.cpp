// 2016. 2. 17.
#include "marble_board.h"
#include "vector2.h"

using components::MarbleColor;
using controls::MarbleBoard;
using controls::BoardState;
using controls::RowType;
using controls::MarbleGenerator; 
using mathematics::Position;
using mathematics::scalar;
using components::marble_ptr;
using cabochon_constants::MAX_X;
using cabochon_constants::MIN_Y;
using cabochon_constants::MARBLE_WIDTH;
using cabochon_constants::MARBLE_HEIGHT;
using cabochon_constants::LINE;
using mathematics::IntPosition;

MarbleBoard::MarbleBoard()
	:_boardState(BoardState::Build), _dragged(false)
{
	//_marbles.push_front(move(MarbleRow()));
}
MarbleBoard::~MarbleBoard()
{
}

const marble_ptr& MarbleBoard::getMarble(IntPosition gridPosition) const
{
	return getMarble(gridPosition._x, gridPosition._y);
}
const marble_ptr& MarbleBoard::getMarble(int x, int y) const
{
	return _marbles[x][y];
}

MarbleColor MarbleBoard::existMarble(IntPosition gridPosition) const
{
	return existMarble(gridPosition._x, gridPosition._y);
}
MarbleColor MarbleBoard::existMarble(int x, int y) const
{
	if (_marbles[x][y] != nullptr)
		return _marbles[x][y]->getColor();
	else
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error in MarbleBoard : existMarble()!"));
}

bool MarbleBoard::addMarble(IntPosition gridPosition, MarbleColor color)
{
	return addMarble(gridPosition._x, gridPosition._y, color);
}
// ���� �޸𸮸� �̵� �ϴ� ���� �ƴ϶�, None���� �ٸ� �÷��� ������.
bool MarbleBoard::addMarble(int x, int y, MarbleColor color)
{
	if (_marbles[x][y] == nullptr)
		throw(GameError(gameErrorNS::FATAL_ERROR ,"Error in MarbleBoard : addMarble()"));

	if (_marbles[x][y]->getColor() != MarbleColor::None)
		return false;

	_colorCount[(int)color]++;
	_marbles[x][y]->setColor(color);
	return true;
}

// ���� �޸𸮸� ���� �ϴ� ���� �ƴ϶�, None���� �÷��� �ٲ�.
bool MarbleBoard::removeMarble(int x, int y)
{
	if (_marbles[x][y] == nullptr)
		return false;

	_colorCount[(int)_marbles[x][y]->getColor()]--;
	_marbles[x][y]->setColor(MarbleColor::None);
	return true;
}

void MarbleBoard::removeRowZero()
{
	_marbles.pop_front();
}

int MarbleBoard::getMarbleCount(MarbleColor c) const
{
	if (c == MarbleColor::None || c == MarbleColor::Num)
		throw(GameError(gameErrorNS::FATAL_ERROR, "getMarbleCount() : Invalid MarbleColor Parameter."));

	return _colorCount[(int)c];
}
int MarbleBoard::getMarbleCount() const
{
	int sum = 0;
	for (int i : _colorCount)
	{
		sum += i;
	}
	return sum;
}
int MarbleBoard::getHeight() const
{
	return _marbles.size();
}
BoardState MarbleBoard::getBoardState() const
{
	return _boardState;
}
int MarbleBoard::getFloor() const
{
	for (int row = 0; row < (int)_marbles.size(); row++)
		for (const marble_ptr& marble : _marbles[row])
			if (marble != nullptr)
				return row;				// _marbles�� �ε���.

	// ��� nullptr�� ���. �� ��Ȳ�� ������ Ŭ����Ȼ�����. 
	return getHeight();
}
scalar MarbleBoard::getCeilingPosition() const
{
	return -1 * getHeight()*MARBLE_HEIGHT + LINE;
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
		if (even == true)
		{
			_marbles.push_front(MarbleRow(MAX_X));
			for (int i = 0; i < MAX_X; i++)
				_marbles.front().push_back(MarbleGenerator::makeRandomMarble());
		}
		else
		{
			_marbles.push_front(MarbleRow(MAX_X-1));
			for (int i = 0; i < MAX_X - 1; i++)
				_marbles.front().push_back(MarbleGenerator::makeRandomMarble());
		}
		even = !even;
	}

	row = MarbleGenerator::getRandomNumber(4, 6);
	for (int i = 0; i < row; i++)
	{
		if (even == true)
		{
			_marbles.push_front(MarbleRow(MAX_X));
			for (int i = 0; i < MAX_X; i++)
				_marbles.front().push_back(MarbleGenerator::makeMarble(MarbleColor::None));
		}
		else
		{
			_marbles.push_front(MarbleRow(MAX_X - 1));
			for (int i = 0; i < MAX_X - 1; i++)
				_marbles.front().push_back(MarbleGenerator::makeMarble(MarbleColor::None));
		}
		even = !even;
	}

	// if (getHeight()<10) ����.
	while (getHeight() < 10)
	{
		if (even == true)
		{
			_marbles.push_front(MarbleRow(MAX_X));
			for (int i = 0; i < MAX_X; i++)
				_marbles.front().push_back(MarbleGenerator::makeMarble(MarbleColor::None));
		}
		else
		{
			_marbles.push_front(MarbleRow(MAX_X - 1));
			for (int i = 0; i < MAX_X - 1; i++)
				_marbles.front().push_back(MarbleGenerator::makeMarble(MarbleColor::None));
		}
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
	scalar x = 0;
	scalar y = LINE;//LINE�� ��ġ.
	bool even = (getRowType(0)==RowType::Odd)?false:true;
	// int position�� �ڽ��� index,
	// position�� offset + index*width, offset+index*height
	for (int i = 0; i<(int)_marbles.size(); i++){
		for (int j = 0; j < (int)_marbles[i].size(); j++){
			if (_marbles[i][j] != nullptr){
				_marbles[i][j]->setGridPosition({ i, j });
				if (even)
					_marbles[i][j]->setPosition(x + i*MARBLE_WIDTH, y + j*MARBLE_HEIGHT);
				else
					_marbles[i][j]->setPosition(x + i*MARBLE_WIDTH + (MARBLE_WIDTH/2.0f), y + j*MARBLE_HEIGHT);
			}
		}
		even = !even;
	}
	
	_dragged = false;
}
int MarbleBoard::positionToIndexX(scalar x, RowType rowType) const
{
	if (getRowType(x) == RowType::Odd)
		return static_cast<int>(floorf(x - (MARBLE_WIDTH/2.0f) / MARBLE_WIDTH));
	else
		return static_cast<int>(floorf(x / MARBLE_WIDTH));
}
int MarbleBoard::positionToIndexY(scalar y) const
{
	return static_cast<int>(ceilf((LINE - y) / MARBLE_HEIGHT));
}
RowType MarbleBoard::getRowType(scalar y) const
{
	return getRowType(positionToIndexY(y));
}
RowType MarbleBoard::getRowType(int y) const
{
	//grid �ȿ� ���ų� Board�� Build �Ǿ���������.
	if (y < 0 || y >= getHeight() || getHeight()<1)
		return RowType::None;
	//grid�� ������
	else if (y == 0){
		if (_marbles[0][MAX_X-1] != nullptr)
			return RowType::Even;
		else
			return RowType::Odd;
	}
	else {
		if (getRowType(0) == RowType::Even){
			if (y % 2 == 0)
				return RowType::Even;
			else
				return RowType::Odd;
		}
		else if (getRowType(0) == RowType::Odd){
			if (y % 2 == 0)
				return RowType::Odd;
			else
				return RowType::Even;
		}
		else
			return RowType::None;
	}
}


void MarbleBoard::render()
{
	//marbles draw
	//0~10�� Row�� �׸�.
	if (_boardState!=BoardState::Build)
		for (int i = 0; i < MIN_Y; i++)
			for (int j = 0; j < _marbles[i].size(); j++)
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