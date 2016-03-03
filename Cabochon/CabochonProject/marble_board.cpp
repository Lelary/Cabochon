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
	:_boardState(BoardState::Build), _dragged(false), _lineDragAnim(0), _marbleDisappearAnim(0)
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

// 실제 메모리를 이동 하는 것이 아니라, None에서 다른 컬러로 변경함.
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

// 실제 메모리를 해제 하는 것이 아니라, None으로 컬러를 바꿈.
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
				return row;				// _marbles의 인덱스.

	// 모두 MarbleColor::None일 경우. 이 상황은 게임이 클리어된상태임. 
	return getHeight();
}
scalar MarbleBoard::getCeilingPosition() const
{
	return -1 * (getHeight()-1)*MARBLE_HEIGHT + LINE;
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

bool MarbleBoard::dragDownOneLine()
{
	// hidden line 을 drag한 턴은 제외 해야 하나 현재 _dragged가 턴마다 갱신되는 변수가아님.
	//if (_dragged == false){return false;}

	// 0이면 카운트가 다 되었으므로 한줄 드래그한다.
	// remove Row Zero;
	// Row Zero 가 삭제되면 자동으로 한칸씩 내려온다.
	removeRowZero();
	_dragged = true;
	return true;		
}
bool MarbleBoard::dragDownHiddenLines()
{
	// 거의 화면 밖에만 Marble 이 존재. 
	// 화면에 minLine 이상 보일 때 까지 더 끌어내림.
	int minLine = 2;
	bool result=false;
	int toDrag = getFloor() - MIN_X + minLine;
	if (toDrag >= 0)	{
		_dragged = result = true;
		for (int i = 0; i < toDrag; i++)
			_marbles.pop_front();
	}
	return result;
}
/*
// 2016. 2. 29.
// dragDownHiddenLines() 와 dragDownOneLine()을 별개의 행동으로 취급함.
// 아래 함수 (dragDown()은 사용하지 않음.)
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

	// if (getHeight()<10) 생략.
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
	
	// marble 들의 
	// marble의 y위치(intposition, position 모두)를
	// 셋업해줘야함.
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
	//모든 Marble의 Position, IntPosition Update;
	scalar x = 0;
	scalar y = LINE;//LINE의 위치.
	bool even = (getRowType(0)==RowType::Odd)?false:true;
	// int position은 자신의 index,
	// position은 offset + index*width, offset+index*height
	for (unsigned int i = 0; i<(int)_marbles.size(); i++){
		for (unsigned int j = 0; j < (int)_marbles[i].size(); j++){
			if (_marbles[i][j] != nullptr){
				_marbles[i][j]->setIndex({ i, j });
				if (even)
					_marbles[i][j]->setPosition(x + j*MARBLE_WIDTH, y - (i + 1)*MARBLE_HEIGHT);
				else
					_marbles[i][j]->setPosition(x + j*MARBLE_WIDTH + (MARBLE_WIDTH / 2.0f), y - (i + 1)*MARBLE_HEIGHT);
			}
		}
		even = !even;
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
	return{ positionToRowIndex(y), positionToColumnIndex(x, getRowType(y)) };
}

IntPosition MarbleBoard::positionToIndex(Position position) const
{
	return positionToIndex(position.x, position.y);
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

int MarbleBoard::getMarbleDisappearAnim() const
{
	return _marbleDisappearAnim; 
}
int MarbleBoard::getLineDragAnim() const
{
	return _lineDragAnim; 
}
bool MarbleBoard::animationFisinished()
{
	if (_marbleDisappearAnim == 0 && _lineDragAnim == 0)
		return true;
	return false;
}
void MarbleBoard::marbleDisappearAnimation(int elapsedFrame)
{
	_marbleDisappearAnim += elapsedFrame;
	if (_marbleDisappearAnim >= MARBLE_DISAPPEAR_ANIM)
	{
		_marbleDisappearAnim = 0;
		_boardState = animationFisinished()==true?BoardState::Play:BoardState::Animation;
	}
	else
	{
		for (marble_ptr& marble : _toRemove)
			marble->disappearing(_marbleDisappearAnim);
	}
}
void MarbleBoard::lineDragAnimation(int elapsedFrame)
{
	// percentage로 내려옴.
	//currentframe/MAXFRAME
	_lineDragAnim += elapsedFrame;
	if (_lineDragAnim >= LINE_DRAG_ANIM){
		for (MarbleRow& row : _marbles)
			for (marble_ptr& marble : row)
			{
				//index설정.
				//ALLMarbles.intPosition = newPosition;
				//position설정.
				//ALL.position = newPosition;
			}
		_lineDragAnim = 0;
		_boardState = animationFisinished() == true ? BoardState::Play : BoardState::Animation;
	}
	else {
		for (MarbleRow& row : _marbles)
			for (marble_ptr& marble : row)
				// 점점 내려옴.
				marble->setPosition(marble->getPosition().x, marble->getPosition().y + MARBLE_HEIGHT*(_lineDragAnim / LINE_DRAG_ANIM));
	}
}
void MarbleBoard::render()
{
	//board 있으면 draw.
	

	//marbles draw
	//0~MIN_X번 Row만 그림. 혹은 (ceiling이 내려왔거나 하는 이유로 _marbles.size()가 더작은 경우는 _marbles.size())
	int minX = (MIN_X < _marbles.size()) ? MIN_X : _marbles.size();

	if (_boardState!=BoardState::Build)
		for (unsigned int i = 0; i < minX; i++)
			for (unsigned int j = 0; j < _marbles[i].size(); j++)
				if (_marbles[i][j]!=nullptr)
					_marbles[i][j]->draw();
}
void MarbleBoard::update(float frameTime)
{
	if (_boardState != BoardState::Play)
		return;

	dragDownHiddenLines();
	

	// 줄내림이 발생했을 때, 
	// marble의 y위치(intposition, position 모두)를 한칸씩 내림.
	if (_dragged)
		updateMarblePositions();
	_dragged = false;
}