// 2016. 2. 17.
#include "marble_board.h"
#include "vector2.h"
#include "angle.h"
#include "board_link_checker.h"

using mathematics::Angle;
using mathematics::Velocity;
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
using controls::BoardLinkChecker;
using controls::LinkState;
using scenes::TextureList;
using cabochon_constants::MAX_Y;
using cabochon_constants::MIN_X;
using cabochon_constants::MARBLE_WIDTH;
using cabochon_constants::MARBLE_HEIGHT;
using cabochon_constants::LINE;

MarbleBoard::MarbleBoard()
	:_boardState(BoardState::Build), _lineDragFrame(0), _marbleDisappearFrame(0), _lineToDrag(0)
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
bool MarbleBoard::removeMarble(IntPosition index, bool immediatly)
{
	//이미 삭제 중인지 (삭제 하려고 하고 있는지) 검사
	for (IntPosition test : _toRemove)
	{
		if (test == index)
			return false;
	}

	int x = index.x;
	int y = index.y;
	int maxY = (getRowType(x) == RowType::Even) ? MAX_Y : MAX_Y - 1;
	if (x < 0 || y<0 || x>getHeight() || y >= maxY)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error in MarbleBoard : removeMarble() \n Invailed Index"));
	if (_marbles[x][y] == nullptr)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error in MarbleBoard : removeMarble()"));
	if (_marbles[x][y]->getColor() == MarbleColor::None)
		throw(GameError(gameErrorNS::FATAL_ERROR, std::to_string(x) + ", " + std::to_string(y) + " is already MarbleColor::None!"));
	
	if (immediatly){
		_marbles[x][y]->setColor(MarbleColor::None);
	}
	else{
		_toRemove.push_back({ x, y });

		// animation을 위한 velocity 설정.
		scalar randomR = MarbleGenerator::getGaussianRandomNumber(cabochon_constants::MEAN_DROP_SPEED, 1.0f);
		Angle randomAngle = MarbleGenerator::getGaussianRandomNumber(cabochon_constants::MEAN_DROP_ANGLE, 1.0f);
		_marbles[x][y]->setVelocity(randomR, randomAngle);

		// frame 설정.
		beginMarbleDisappear();
	}
	_colorCount[(int)_marbles[x][y]->getColor()]--;
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
		if (marble->getColor() != MarbleColor::None)
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
	// 0이면 카운트가 다 되었으므로 한줄 드래그한다.
	// remove Row Zero;
	// Row Zero 가 삭제되면 자동으로 한칸씩 내려온다.
	removeRowZero();
	_lineToDrag++;
	beginLineDrag();
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
		_lineToDrag += toDrag;
		for (int i = 0; i < toDrag; i++)
			_marbles.pop_front();
		beginLineDrag();
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
		{
			MarbleColorOn colorOn;
			colorOn.bitData.Yellow = true;
			colorOn.bitData.Green = true;
			colorOn.bitData.Mint = true;
			colorOn.bitData.Blue = true;
			colorOn.bitData.Violet = true;
			colorOn.bitData.Pink = true;

			marble = makeRandomMarble(colorOn);
		}
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
	arrangeNotLinkedMarbles(true);
	_boardState = BoardState::Ready;

}
void MarbleBoard::arrangeNotLinkedMarbles(bool immediatly)
{
	BoardLinkChecker linkChecker(*this);
	std::deque<std::vector<LinkState>> linkBoard = linkChecker.getLinkedResult();

	for (int row = 0; row < getHeight(); row++){
		int maxY = (getRowType(row) == RowType::Even) ? MAX_Y : MAX_Y - 1;
		for (int col = 0; col < maxY; col++){
			if (linkBoard[row][col] != LinkState::Linked){
				if (existMarble({ row, col }) != MarbleColor::None)
					removeMarble({ row, col }, immediatly);

			}
		}
	}
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
	// int position은 자신의 index,
	// position은 offset + index*width, offset+index*height
	for (unsigned int i = 0; i<(int)_marbles.size(); i++){
		for (unsigned int j = 0; j < (int)_marbles[i].size(); j++){
			if (_marbles[i][j] != nullptr){
				_marbles[i][j]->setIndex({ i, j });
				_marbles[i][j]->setPosition(indexToPosition({ i, j }));
			}
		}
	}
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
	scalar y = LINE;//LINE의 위치.
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
		for (IntPosition index : _toRemove)
		{
			_marbles[index.x][index.y]->setVelocity({ 0.0f, 0.0f });
		}
		_toRemove.clear();
		// 게임 클리어 검사.
		gameClear();
	}
}

//한줄만처리.
//->여러줄처리
void MarbleBoard::lineDragAnimation(scalar elapsedFrame)
{
	// percentage로 내려옴.
	//currentframe/MAXFRAME
	progressLineDrag(elapsedFrame);

	if (_lineDragFrame > LINE_DRAG_FRAME)
		_lineDragFrame = LINE_DRAG_FRAME;

	for (MarbleRow& row : _marbles)
		for (marble_ptr& marble : row)
		{
			// 점점 내려옴.
			// 실제 위치가 이미 업데이트 되었는지 / 애니메이션 후에 업데이트 되는지에 따라 아래 구현이 바뀜.
			// 2016. 3. 8. 현재는 전자. 
			// 후자의 형식을 취하기 위해서는 애니메이션이 방금끝났는지를 감시하여 board를 업데이트(라인 삭제와 업데이트포지션) 하는 구현이 필요함. removeMarble() 또한 동일.
			scalar progress = _lineDragFrame / LINE_DRAG_FRAME;
			Position realPosition = indexToPosition(marble->getIndex());			
			marble->setPosition(realPosition.x, realPosition.y - MARBLE_HEIGHT*(1-progress));
		}
	
	if (_lineDragFrame >= LINE_DRAG_FRAME){
		updateMarblePositions();
		finishLineDrag();
		_lineToDrag--;

		//gameOver검사. 한줄이 다 내려온 시점에 하는 것이 자연스럽다.
		gameOver();
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
void MarbleBoard::handleAnimation(float frameTime)
{
	if (animationFinished())
		return;
	if (getNumRemoving() > 0) {
		marbleDisappearAnimation(frameTime);
		// 이거 끝나고나서 line 애니메이션 해야하므로 return.
		return;
	}
	lineDragAnimation(frameTime);
}
void MarbleBoard::update(float frameTime)
{
	if (_boardState != BoardState::Play)
		return;

	// 2016. 3. 8.
	// 현재 lineDragAnimation()의 로직이 실제줄내림처리이후 애니메이션을 수행하므로,
	// 아래 함수가 marbleDisappearAnimation()과 같은 턴에 수행되면 안됨.
	// dragDownOneLine() 또한 마찬가지.
	// dragDownHiddenLines();

	// 줄내림이 발생했을 때, 
	// marble의 y위치(intposition, position 모두)를 한칸씩 내림.

	for (const MarbleRow& row : _marbles)
		for (const marble_ptr& marble : row)
			marble->update(frameTime);

	//Line, Drop 애니메이션 프레임 처리
	handleAnimation(frameTime);
}