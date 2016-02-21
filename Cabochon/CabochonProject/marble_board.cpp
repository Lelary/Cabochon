// 2016. 2. 17.
#include "marble_board.h"
#include "vector2.h"

using mathematics::Position;
using mathematics::scalar;
using mathematics::IntPosition;
using components::MarbleColor;
using components::marble_ptr;
using controls::MarbleColorOn;
using controls::MarbleBoard;
using controls::BoardState;
using controls::RowType;
using controls::MarbleGenerator;
using scenes::TextureList;
using cabochon_constants::MAX_Y;
using cabochon_constants::MIN_X;
using cabochon_constants::MARBLE_WIDTH;
using cabochon_constants::MARBLE_HEIGHT;
using cabochon_constants::LINE;

MarbleBoard::MarbleBoard()
	:_boardState(BoardState::Build), _dragged(false)
{
	_colorCount.assign(0);
}
MarbleBoard::~MarbleBoard()
{
}

const marble_ptr& MarbleBoard::getMarble(IntPosition gridPosition) const
{
	return getMarble(gridPosition.x, gridPosition.y);
}
const marble_ptr& MarbleBoard::getMarble(int x, int y) const
{
	return _marbles[x][y];
}

MarbleColor MarbleBoard::existMarble(IntPosition gridPosition) const
{
	return existMarble(gridPosition.x, gridPosition.y);
}
MarbleColor MarbleBoard::existMarble(int x, int y) const
{
	if (x < 0 || x >= _marbles.size())
		return MarbleColor::None;

	if (y < 0 || y >= _marbles[x].size())
		return MarbleColor::None;

	if (_marbles[x][y] != nullptr)
		return _marbles[x][y]->getColor();
	else
		throw (GameError(gameErrorNS::FATAL_ERROR, "Error in MarbleBoard : existMarble()!"));
}

bool MarbleBoard::addMarble(IntPosition gridPosition, MarbleColor color)
{
	return addMarble(gridPosition.x, gridPosition.y, color);
}
// ���� �޸𸮸� �̵� �ϴ� ���� �ƴ϶�, None���� �ٸ� �÷��� ������.
bool MarbleBoard::addMarble(int x, int y, MarbleColor color)
{
	int maxY = (getRowType(x) == RowType::Even) ? MAX_Y : MAX_Y - 1;
	if (x < 0 || y<0 || x>getHeight() || y >= maxY)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error in MarbleBoard : addMarble() \n Invailed Index"));

	if (_marbles[x][y] == nullptr)
		throw(GameError(gameErrorNS::FATAL_ERROR ,"Error in MarbleBoard : addMarble() \n nullptr"));
	if (_marbles[x][y]->getColor() != MarbleColor::None)
		throw(GameError(gameErrorNS::FATAL_ERROR, std::to_string(x) + ", " + std::to_string(y) + " already has MarbleColor !"));

	_colorCount[(int)color]++;
	_marbles[x][y]->setColor(color);
	return true;
}

// ���� �޸𸮸� ���� �ϴ� ���� �ƴ϶�, None���� �÷��� �ٲ�.
bool MarbleBoard::removeMarble(int x, int y)
{
	int maxY = (getRowType(x) == RowType::Even) ? MAX_Y : MAX_Y - 1;
	if (x < 0 || y<0 || x>getHeight() || y >= maxY)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error in MarbleBoard : removeMarble() \n Invailed Index"));
	if (_marbles[x][y] == nullptr)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error in MarbleBoard : removeMarble()"));
	if (_marbles[x][y]->getColor() == MarbleColor::None)
		throw(GameError(gameErrorNS::FATAL_ERROR, std::to_string(x) + ", " + std::to_string(y) + " is already MarbleColor::None!"));

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
void MarbleBoard::setBoardState(BoardState state)
{
	_boardState=state;
}
BoardState MarbleBoard::getBoardState() const
{
	return _boardState;
}
int MarbleBoard::getFloor() const
{
	for (int row = 0; row < (int)_marbles.size(); row++)
		for (const marble_ptr& marble : _marbles[row])
			if (marble->getColor() != MarbleColor::None)
				return row;				// _marbles�� �ε���.

	// ��� MarbleColor::None�� ���. �� ��Ȳ�� ������ Ŭ����Ȼ�����. 
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
	int toDrag = getFloor() - MIN_X;
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
			_marbles.push_front(MarbleRow(MAX_Y));
		else
			_marbles.push_front(MarbleRow(MAX_Y - 1));

		for (marble_ptr& marble : _marbles.front())
			marble = makeRandomMarble();

		even = !even;
	}

	row = MarbleGenerator::getRandomNumber(4, 6);
	for (int i = 0; i < row; i++)
	{
		if (even == true)
			_marbles.push_front(MarbleRow(MAX_Y));
		else
			_marbles.push_front(MarbleRow(MAX_Y - 1));

		for (marble_ptr& marble : _marbles.front())
			marble = makeMarble(MarbleColor::None);

		even = !even;
	}

	// if (getHeight()<10) ����.
	while (getHeight() < MIN_X)
	{
		if (even == true)
			_marbles.push_front(MarbleRow(MAX_Y));
		else
			_marbles.push_front(MarbleRow(MAX_Y - 1));

		for (marble_ptr& marble : _marbles.front())
			marble = makeMarble(MarbleColor::None);

		even = !even;
	}
	
	// marble ���� 
	// marble�� y��ġ(intposition, position ���)��
	// �¾��������.
	updateMarblePositions();

	_boardState = BoardState::Ready;

}
marble_ptr MarbleBoard::makeMarble(MarbleColor color)
{
	marble_ptr marble = MarbleGenerator::makeMarble(color);
	if (marble->getColor() != MarbleColor::None)
		_colorCount[(int)marble->getColor()]++;
	return marble;
}
marble_ptr MarbleBoard::makeRandomMarble()
{
	marble_ptr marble = MarbleGenerator::makeRandomMarble();
	if (marble->getColor() != MarbleColor::None)
		_colorCount[(int)marble->getColor()]++;
	return marble;
}
marble_ptr MarbleBoard::makeRandomMarble(MarbleColorOn colorRange)
{
	marble_ptr marble = MarbleGenerator::makeRandomMarble(colorRange);
	if (marble->getColor() != MarbleColor::None)
		_colorCount[(int)marble->getColor()]++;
	return marble;
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
					_marbles[i][j]->setPosition(x + j*MARBLE_WIDTH, y - i*MARBLE_HEIGHT);
				else
					_marbles[i][j]->setPosition(x + j*MARBLE_WIDTH + (MARBLE_WIDTH/2.0f), y - i*MARBLE_HEIGHT);
			}
		}
		even = !even;
	}
	
	_dragged = false;
}
int MarbleBoard::positionToColumnIndex(scalar x, RowType rowType) const
{
	if (getRowType(x) == RowType::Odd)
		return static_cast<int>(floorf((x - MARBLE_WIDTH/2.0f) / MARBLE_WIDTH));
	else
		return static_cast<int>(floorf(x / MARBLE_WIDTH));
}
int MarbleBoard::positionToRowIndex(scalar y) const
{
	return static_cast<int>(ceilf((LINE - y) / MARBLE_HEIGHT));
}
RowType MarbleBoard::getRowType(scalar y) const
{
	return getRowType(positionToRowIndex(y));
}

IntPosition MarbleBoard::positionToIndex(scalar x, scalar y) const
{
	return{ positionToRowIndex(y), positionToColumnIndex(x, getRowType(y)) };
}

IntPosition MarbleBoard::positionToIndex(const Position& position) const
{
	return positionToIndex(position.x, position.y);
}

RowType MarbleBoard::getRowType(int row) const
{
	if (_marbles.at(row).size() == MAX_Y)
		return RowType::Even;
	else
		return RowType::Odd;
}

bool MarbleBoard::isInvalidIndex(IntPosition index) const
{
	if (index.x < 0 || index.x>getHeight())
		return true;

	int maxY = (getRowType(index.x) == controls::RowType::Even)
		? cabochon_constants::MAX_Y : cabochon_constants::MAX_Y - 1;

	if (index.y < 0 || index.y >= maxY)
		return true;

	return false;
}

void MarbleBoard::loadTextures(TextureList& textureList)
{
	for (MarbleRow& marbleRow : _marbles)
		for (marble_ptr& marble : marbleRow)
			marble->loadLayers(textureList);
}
void MarbleBoard::render()
{
	//board ������ draw.
	

	//marbles draw
	//0~MIN_X�� Row�� �׸�. Ȥ�� (ceiling�� �����԰ų� �ϴ� ������ _marbles.size()�� ������ ���� _marbles.size())
	int minX = (MIN_X < _marbles.size()) ? MIN_X : _marbles.size();

	if (_boardState!=BoardState::Build)
		for (unsigned int i = 0; i < minX; i++)
			for (unsigned int j = 0; j < _marbles[i].size(); j++)
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