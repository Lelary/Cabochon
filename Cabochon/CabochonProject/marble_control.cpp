//2016. 1. 16.

#include "marble_control.h"

using controls::MarbleControl;
using components::Marble;
using components::marble_ptr;
using components::MarbleColor;
using components::ShootedMarble;
using controls::RowType;
using mathematics::Position;
using mathematics::IntPosition;
using mathematics::scalar;
using shooted_ptr = std::unique_ptr < ShootedMarble >;
using controls::MarbleColorOn;
using controls::MarbleBoard;
using frameworks::TextureList;
using cabochon_constants::MAX_Y;
using controls::Quadrant;
using cabochon_constants::MARBLE_HEIGHT;
using cabochon_constants::MARBLE_WIDTH;
using cabochon_constants::LINE;

MarbleControl::MarbleControl()
	:_justAttached({ -1, -1 })
{

}

MarbleControl::~MarbleControl()
{
	/*
	2016. 1. 16.
	Nothing to do yet.
	*/
}
bool MarbleControl::isShooting() const
{
	if (_shootedMarble == nullptr)
		return false;
	else
		return true;
}

IntPosition MarbleControl::getJustAttached() const
{
	return _justAttached;
}
bool MarbleControl::hasJustAttached() const
{
	if (getJustAttached()._x == -1 || getJustAttached()._y == -1)
		return false;
	else
		return true;
}
//Shooted Marble
shooted_ptr& MarbleControl::getShootedMarble()
{
	return _shootedMarble;
}
void MarbleControl::setShootedMarble(MarbleColor color, Position position, scalar speed, mathematics::Angle degree, TextureList& textureList)
{
	shooted_ptr shootedMarble=std::make_unique<ShootedMarble>(color);
	shootedMarble->setCentralPosition(position);
	shootedMarble->setVelocity(speed, degree);
	_shootedMarble = std::move(shootedMarble);
	_shootedMarble->loadLayers(textureList);
}

MarbleColorOn MarbleControl::getExistColors() const
{
	MarbleColorOn colors;
	for (int c = 0; c < (int)MarbleColor::Num; c++)
	{
		if (_marbleBoard.getMarbleCount((MarbleColor)c) > 0)
			colors.data |= (true << c);
	}
	return colors;
}
MarbleBoard& MarbleControl::getMarbleBoard()
{
	return _marbleBoard;
}
const MarbleBoard& MarbleControl::getMarbleBoard() const
{
	return _marbleBoard;
}
//Attach 가능성이 있는 Grid 위치 (인접위치) 반환.
std::vector<IntPosition> MarbleControl::getTestSet(const shooted_ptr& shootedMarble) const
{
	IntPosition marblePosition = _marbleBoard.positionToIndex(shootedMarble->getPrevCentralPosition());
	return getTestSet(marblePosition);
}
//Attach 가능성이 있는 Grid 위치 (인접위치) 반환.
std::vector<IntPosition> MarbleControl::getTestSet(const IntPosition& marblePosition) const
{
	std::vector<IntPosition> testSet;
	int x = marblePosition._x;
	int y = marblePosition._y;

	int maxY = (_marbleBoard.getRowType(x)==RowType::Even)?MAX_Y: MAX_Y-1;

	// 좌 우 Marble
	if (y > 0)
		testSet.push_back({ x, y - 1 });
	if (y < maxY-1)
		testSet.push_back({ x, y + 1 });

	// 다음 X와 Y의 모든 쌍을 검사해야함.
	int testLeftY = (_marbleBoard.getRowType(x) == RowType::Even) ? y - 1: y;
	int testRightY = (_marbleBoard.getRowType(x) == RowType::Even) ? y : y + 1;
	int testUpX = x + 1;
	int testDownX = x - 1;

	//row-1, row+1 의 상황.
	maxY = (_marbleBoard.getRowType(x) == RowType::Odd) ? MAX_Y : MAX_Y - 1;

	if (testDownX >= 1)
	{
		if (testLeftY >= 0)
			testSet.push_back({ testDownX, testLeftY});
		if (testRightY < maxY)
			testSet.push_back({ testDownX, testRightY });
	}

	if (testUpX <= _marbleBoard.getHeight())
	{
		if (testLeftY >= 0)
			testSet.push_back({ testUpX, testLeftY });
		if (testRightY < maxY)
			testSet.push_back({ testUpX, testRightY });
	}
	return testSet;
}
// vector내의순서가유의미함.
std::vector<IntPosition> MarbleControl::getTwoTestSet(const shooted_ptr& shootedMarble) const
{
	std::vector<IntPosition> testSet;
	IntPosition index = _marbleBoard.positionToIndex(shootedMarble->getPrevCentralPosition());
	Quadrant quad = getQuadrant(shootedMarble->getPrevCentralPosition());

	// 다음 X와 Y의 모든 쌍을 검사해야함.
	int testLeftY = (_marbleBoard.getRowType(index._x) == RowType::Even) ? index._y - 1 : index._y;
	int testRightY = (_marbleBoard.getRowType(index._x) == RowType::Even) ? index._y : index._y + 1;
	int testUpX = index._x + 1;
	int testDownX = index._x - 1;

	//row-1, row+1 의 상황.
	int maxY = (_marbleBoard.getRowType(index._x) == RowType::Odd) ? MAX_Y : MAX_Y - 1;

	if (quad == Quadrant::first || quad == Quadrant::second) {
		if (testUpX <= _marbleBoard.getHeight())
		{
			if (quad == Quadrant::second && testLeftY >= 0)
				testSet.push_back({ testUpX, testLeftY });
			if (quad == Quadrant::first && testRightY < maxY)
				testSet.push_back({ testUpX, testRightY });
		}
	}
	else {
		if (testDownX >= 1)
		{
			if (quad == Quadrant::third && testLeftY >= 0)
				testSet.push_back({ testDownX, testLeftY });
			if (quad == Quadrant::fourth && testRightY < maxY)
				testSet.push_back({ testDownX, testRightY });
		}
	}

	// 내위치의 RowType
	maxY = (_marbleBoard.getRowType(index._x) == RowType::Even) ? MAX_Y : MAX_Y - 1;

	// 왼쪽 Marble
	if (quad == Quadrant::second || quad == Quadrant::third) {
		if (index._y > 0)
			testSet.push_back({ index._x, index._y - 1 });
	}
	// 오른쪽 Marble
	else {
		if (index._y < maxY - 1)
			testSet.push_back({ index._x, index._y + 1 });
	}

	return testSet;
}
Quadrant MarbleControl::getQuadrant(const shooted_ptr& shootedMarble) const
{
	return getQuadrant(shootedMarble->getPrevCentralPosition());
}
Quadrant MarbleControl::getQuadrant(const Position& marblePosition) const
{
	IntPosition index = _marbleBoard.positionToIndex(marblePosition);
	Position leftTop;
	bool even = (_marbleBoard.getRowType(index._x) == RowType::Odd) ? false : true;
	bool left;
	bool up;

	if (even)
		leftTop = { 0 + index._y*MARBLE_WIDTH, LINE - index._x*MARBLE_HEIGHT };
	else
		leftTop = { 0 + index._y*MARBLE_WIDTH + (MARBLE_WIDTH / 2.0f), LINE - index._x*MARBLE_HEIGHT };
	if (marblePosition._x < leftTop._x + MARBLE_WIDTH / 2.0f)
		left = true;
	else
		left = false;
	if (marblePosition._y < leftTop._y + MARBLE_HEIGHT / 2.0f)
		up = true;
	else
		up = false;

	if (up == true) {
		if (left == false)
			return Quadrant::first;
		else
			return Quadrant::second;
	}
	else {
		if (left == true)
			return Quadrant::third;
		else
			return Quadrant::fourth;
	}
}

//attach shooted marble
bool MarbleControl::isAttachable(const shooted_ptr& shootedMarble, const IntPosition& gridPosition) const
{
	/*
	2016. 1. 22.

	1. shootedMarble이 gridPosition에 포함되었는지 검사.
	2. Attach 하고자 하는 위치가 비었는지 검사.
	3. isAttachable(const shooted_ptr& shootedMarble)const 호출.
	*/
	IntPosition currentIndex = _marbleBoard.positionToIndex(shootedMarble->getPrevCentralPosition());
	if (currentIndex._x == gridPosition._x	&&	currentIndex._y == gridPosition._y )
		if (_marbleBoard.existMarble(gridPosition) == MarbleColor::None)
			return isAttachable(shootedMarble);

	return false;
}
bool MarbleControl::isAttachable(const shooted_ptr& shootedMarble) const
{
	/*
	2016. 1. 22.
	shootedMarble의 인접 위치의 Marble에 대해 붙을 가능성이 있는지 검사.

	1. MarbleColor::None 검사. (marble이 붙고자 하는 위치(현재위치)에 이미 존재하는 marble이 있는지 검사)
	2. testSet을 얻음.
	3. MarbleColor::None 검사.. (testSet (인접 marble 위치) 중 marble이 없는 위치는 다음 검사 제외.)
	4. 반지름 검사. (원형충돌검사)
	*/

	//1. MarbleColor::None 검사.
	IntPosition currentIndex = _marbleBoard.positionToIndex(shootedMarble->getPrevCentralPosition());
	if (_marbleBoard.existMarble(currentIndex)!=MarbleColor::None)
		return false;

	//2. testSet을 얻음.
	auto testSet = getTwoTestSet(shootedMarble);
	//3. 인접위치 (testSet)을 하나씩 확인.
	for (auto& testPosition : testSet){
		// 해당 인접위치가 비어있지않으면, 
		if (_marbleBoard.existMarble(testPosition) != MarbleColor::None){
			// 4. 반지름 검사. (원형 충돌 검사)
			if (shootedMarble->circularHitTest(*_marbleBoard.getMarble(testPosition._x, testPosition._y).get())){
				return true;
			}
		}
	}
	return false;
}
//shootedMarble은 color값만 넘겨주고, reset()된다.
bool MarbleControl::attach(shooted_ptr& shootedMarble, const IntPosition& gridPosition)
{
	if (isAttachable(shootedMarble, gridPosition))
	{
		//attach 확정.

		_marbleBoard.addMarble(gridPosition, shootedMarble->getColor());
		shootedMarble.reset();

		_justAttached = gridPosition;
		return true;
	}
	// if(ceiling)
	// force attach.


	return false;
}
// attach 의 오버로드 된 함수.
bool MarbleControl::attach(shooted_ptr& shootedMarble)
{
	IntPosition currentIndex = _marbleBoard.positionToIndex(shootedMarble->getPrevCentralPosition());
	return attach(shootedMarble, currentIndex);
}

void MarbleControl::render()
{
	_marbleBoard.render();

	if (_shootedMarble != nullptr)
	{
		_shootedMarble->draw();
	}
}
void MarbleControl::update(float frameTime)
{
	if (_shootedMarble != nullptr)
		_shootedMarble->move(_marbleBoard, frameTime);
	_marbleBoard.update(frameTime);
}