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
	:_boardState(BoardState::Build), _dragged(false), _lineDragFrame(0), _marbleDisappearFrame(0), _lineToDrag(0)
{
	_colorCount.assign(0);
}
MarbleBoard::~MarbleBoard()
{
}

const marble_ptr& MarbleBoard::getMarble(IntPosition index) const
{
	return _marbles.at(index.x).at(index.y);
}

MarbleColor MarbleBoard::existMarble(IntPosition index) const
{
	int x = index.x;
	int y = index.y;

	if (x < 0 || x >= _marbles.size())
		return MarbleColor::None;

	if (y < 0 || y >= _marbles[x].size())
		return MarbleColor::None;

	if (_marbles[x][y] != nullptr)
		return _marbles[x][y]->getColor();
	else
		throw (GameError(gameErrorNS::FATAL_ERROR, "Error in MarbleBoard : existMarble()!"));
}

// ���� �޸𸮸� �̵� �ϴ� ���� �ƴ϶�, None���� �ٸ� �÷��� ������.
bool MarbleBoard::addMarble(IntPosition index, MarbleColor color)
{
	int x = index.x;
	int y = index.y;
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
bool MarbleBoard::removeMarble(IntPosition index)
{
	int x = index.x;
	int y = index.y;
	int maxY = (getRowType(x) == RowType::Even) ? MAX_Y : MAX_Y - 1;
	if (x < 0 || y<0 || x>getHeight() || y >= maxY)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error in MarbleBoard : removeMarble() \n Invailed Index"));
	if (_marbles[x][y] == nullptr)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error in MarbleBoard : removeMarble()"));
	if (_marbles[x][y]->getColor() == MarbleColor::None)
		throw(GameError(gameErrorNS::FATAL_ERROR, std::to_string(x) + ", " + std::to_string(y) + " is already MarbleColor::None!"));

	_colorCount[(int)_marbles[x][y]->getColor()]--;
	//_marbles[x][y]->setColor(MarbleColor::None);
	_toRemove.push_back({ x, y });
	beginMarbleDisappear();
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
	return -1 * (getHeight()-1)*MARBLE_HEIGHT + LINE;
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

bool MarbleBoard::dragDownOneLine()
{
	// hidden line �� drag�� ���� ���� �ؾ� �ϳ� ���� _dragged�� �ϸ��� ���ŵǴ� �������ƴ�.
	//if (_dragged == false){return false;}

	// 0�̸� ī��Ʈ�� �� �Ǿ����Ƿ� ���� �巡���Ѵ�.
	// remove Row Zero;
	// Row Zero �� �����Ǹ� �ڵ����� ��ĭ�� �����´�.
	removeRowZero();
	_lineToDrag++;
	beginLineDrag();
	_dragged = true;
	return true;		
}
bool MarbleBoard::dragDownHiddenLines()
{
	// ���� ȭ�� �ۿ��� Marble �� ����. 
	// ȭ�鿡 minLine �̻� ���� �� ���� �� �����.
	int minLine = 2;
	bool result=false;
	int toDrag = getFloor() - MIN_X + minLine;
	if (toDrag >= 0)	{
		_lineToDrag += toDrag;
		_dragged = result = true;
		for (int i = 0; i < toDrag; i++)
			_marbles.pop_front();
		beginLineDrag();
	}
	return result;
}
/*
// 2016. 2. 29.
// dragDownHiddenLines() �� dragDownOneLine()�� ������ �ൿ���� �����.
// �Ʒ� �Լ� (dragDown()�� ������� ����.)
BoardState MarbleBoard::dragDown()
{
	BoardState state;
	dragDownHiddenLines();
	//state=dragDownOneLine();
	return state=BoardState::Play;
}
*/
void MarbleBoard::makeRandomBoard()
{
	if (_boardState != BoardState::Build)
		return;
	
	_marbles.clear();
	bool even = true;
	
	//int row = MarbleGenerator::getRandomNumber(4, 20);
	int row = 5;

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

	//row = MarbleGenerator::getRandomNumber(4, 6);
	row = 5;
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
	// int position�� �ڽ��� index,
	// position�� offset + index*width, offset+index*height
	for (unsigned int i = 0; i<(int)_marbles.size(); i++){
		for (unsigned int j = 0; j < (int)_marbles[i].size(); j++){
			if (_marbles[i][j] != nullptr){
				_marbles[i][j]->setIndex({ i, j });
				_marbles[i][j]->setPosition(indexToPosition({ i, j }));
			}
		}
	}
	_dragged = false;
}
int MarbleBoard::positionToColumnIndex(scalar x, RowType rowType) const
{
	if (rowType == RowType::Odd)
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
	int indexY = positionToRowIndex(y);

	if (indexY >= _marbles.size())
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error in MarbleBoard::getRowType() !"));

	return getRowType(indexY);
}

IntPosition MarbleBoard::positionToIndex(scalar x, scalar y) const
{
	int rowIndex = positionToRowIndex(y);
	if (rowIndex < getHeight() && rowIndex >= 0)
		return{ positionToRowIndex(y), positionToColumnIndex(x, getRowType(y)) };
	else
		return cabochon_constants::NO_POSITION;
}

IntPosition MarbleBoard::positionToIndex(Position position) const
{
	return positionToIndex(position.x, position.y);
}

Position MarbleBoard::indexToPosition(IntPosition index) const
{
	scalar x = 0;
	scalar y = LINE;//LINE�� ��ġ.
	bool even = (getRowType(index.x) == RowType::Odd) ? false : true;

	if (even)
		return{ x + index.y*MARBLE_WIDTH, y - (index.x + 1)*MARBLE_HEIGHT };
	else
		return{ x + index.y*MARBLE_WIDTH + (MARBLE_WIDTH / 2.0f), y - (index.x + 1)*MARBLE_HEIGHT };
}

RowType MarbleBoard::getRowType(int row) const
{
	if (row >= _marbles.size())
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error in MarbleBoard::getRowType() !"));
 	if (_marbles.at(row).size() == MAX_Y)
		return RowType::Even;
	else
		return RowType::Odd;
}

bool MarbleBoard::isInvalidIndex(IntPosition index) const
{
	if (index.x < 0 || index.x>=getHeight())
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

scalar MarbleBoard::getMarbleDisappearFrame() const
{
	return _marbleDisappearFrame; 
}
scalar MarbleBoard::getLineDragFrame() const
{
	return _lineDragFrame; 
}
int MarbleBoard::getNumRemoving() const
{
	return _toRemove.size();
}
bool MarbleBoard::animationFinished()
{
	if (_marbleDisappearFrame == 0 && _lineDragFrame == 0 && _lineToDrag==0)
		return true;
	return false;
}
void MarbleBoard::marbleDisappearAnimation(scalar elapsedFrame)
{
	progressMarbleDisappear(elapsedFrame);

	for (IntPosition index : _toRemove)
	{
		Position position;
		position = indexToPosition(index);
		_marbles[index.x][index.y]->disappearing(_marbleDisappearFrame, MARBLE_DISAPPEAR_FRAME, position);
	}

	if (_marbleDisappearFrame >= MARBLE_DISAPPEAR_FRAME)
	{
		finishMarbleDisappear();
		_toRemove.clear();
	}
}

//���ٸ�ó��.
//->������ó��
void MarbleBoard::lineDragAnimation(scalar elapsedFrame)
{
	// percentage�� ������.
	//currentframe/MAXFRAME
	progressLineDrag(elapsedFrame);

	if (_lineDragFrame > LINE_DRAG_FRAME)
		_lineDragFrame = LINE_DRAG_FRAME;

	for (MarbleRow& row : _marbles)
		for (marble_ptr& marble : row)
		{
			// ���� ������.
			// ���� ��ġ�� �̹� ������Ʈ �Ǿ����� / �ִϸ��̼� �Ŀ� ������Ʈ �Ǵ����� ���� �Ʒ� ������ �ٲ�.
			// 2016. 3. 8. ����� ����. 
			// ������ ������ ���ϱ� ���ؼ��� �ִϸ��̼��� ��ݳ��������� �����Ͽ� board�� ������Ʈ(���� ������ ������Ʈ������) �ϴ� ������ �ʿ���. removeMarble() ���� ����.
			scalar progress = _lineDragFrame / LINE_DRAG_FRAME;
			Position realPosition = indexToPosition(marble->getIndex());			
			marble->setPosition(realPosition.x, realPosition.y - MARBLE_HEIGHT*(1-progress));
		}
	
	if (_lineDragFrame >= LINE_DRAG_FRAME){
		finishLineDrag();
		_lineToDrag--;
	}
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
void MarbleBoard::handleAnimation(float frameTime)
{
	if (animationFinished())
		return;
	if (getNumRemoving() > 0) {
		marbleDisappearAnimation(frameTime);
		// �̰� �������� line �ִϸ��̼� �ؾ��ϹǷ� return.
		return;
	}
	lineDragAnimation(frameTime);
}
void MarbleBoard::update(float frameTime)
{
	if (_boardState != BoardState::Play)
		return;

	dragDownHiddenLines();

	handleAnimation(frameTime);

	// �ٳ����� �߻����� ��, 
	// marble�� y��ġ(intposition, position ���)�� ��ĭ�� ����.
	if (_dragged)
		updateMarblePositions();
	_dragged = false;
}