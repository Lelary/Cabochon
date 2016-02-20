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
//Attach ���ɼ��� �ִ� Grid ��ġ (������ġ) ��ȯ.
std::vector<IntPosition> MarbleControl::getTestSet(const shooted_ptr& shootedMarble) const
{
	IntPosition marblePosition = _marbleBoard.positionToIndex(shootedMarble->getPrevCentralPosition());
	return getTestSet(marblePosition);
}
//Attach ���ɼ��� �ִ� Grid ��ġ (������ġ) ��ȯ.
std::vector<IntPosition> MarbleControl::getTestSet(const IntPosition& marblePosition) const
{
	std::vector<IntPosition> testSet;
	int x = marblePosition._x;
	int y = marblePosition._y;

	int maxY = (_marbleBoard.getRowType(x)==RowType::Even)?MAX_Y: MAX_Y-1;

	// �� �� Marble
	if (y > 0)
		testSet.push_back({ x, y - 1 });
	if (y < maxY-1)
		testSet.push_back({ x, y + 1 });

	// ���� X�� Y�� ��� ���� �˻��ؾ���.
	int testLeftY = (_marbleBoard.getRowType(x) == RowType::Even) ? y - 1: y;
	int testRightY = (_marbleBoard.getRowType(x) == RowType::Even) ? y : y + 1;
	int testUpX = x + 1;
	int testDownX = x - 1;

	//row-1, row+1 �� ��Ȳ.
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

std::vector<IntPosition> MarbleControl::getLessTestSet(const shooted_ptr& shootedMarble) const
{
	// getTestSet()���� (�ִ�)6���� testSet�� �޾Ƽ�, 
	// Quadrant�� �̿��Ͽ� ��Ȯ�ϰ� attachable �˻縦 �ϱ� ���� (�ִ�)2���� ��ġ���� �����.
	// getTestSet()�� ����� �Լ��� ����� ���� �����ϰ� ��������, �ڵ��ߺ��� ���ִ� ���� �� �߿�.

	//std::vector<IntPosition> newTestSet;
	std::vector<IntPosition> testSet = getTestSet(shootedMarble);
	Quadrant quadrant = getQuadrant(shootedMarble);
	IntPosition index = _marbleBoard.positionToIndex(shootedMarble->getPrevCentralPosition());

	bool even = _marbleBoard.getRowType(index._x) == RowType::Even;

	int remove_col;
	int remove_row;
	IntPosition removeSide;
	removeSide._x = index._x;

	// first||fourth �� ������, second||third �� �������� �����.
	if (quadrant == Quadrant::first || quadrant == Quadrant::fourth)
	{
		removeSide._y = index._y - 1;

		if (even)
			remove_col = index._y - 1; //left
		else
			remove_col = index._y;	//left
	}
	else
	{
		removeSide._y = index._y + 1;

		if (even)
			remove_col = index._y; //right
		else
			remove_col = index._y + 1;	//right
	}

	// first || second �� �Ʒ�����, third || fourth�� ������ �����.
	if (quadrant == Quadrant::first || quadrant == Quadrant::second){
		remove_row = index._x - 1;
	}
	else{
		remove_row = index._x + 1;
	}

	auto toRemove = [&](const IntPosition& position) -> bool {return
		(position._y == remove_col 
		|| position._x == remove_row 
		|| (position._x == removeSide._x && position._y == removeSide._y)
		) ? true : false; };

	testSet.erase(
		std::remove_if(testSet.begin(), testSet.end(), toRemove),
		testSet.end()
		);

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

	1. shootedMarble�� gridPosition�� ���ԵǾ����� �˻�.
	2. Attach �ϰ��� �ϴ� ��ġ�� ������� �˻�.
	3. isAttachable(const shooted_ptr& shootedMarble)const ȣ��.
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
	shootedMarble�� ���� ��ġ�� Marble�� ���� ���� ���ɼ��� �ִ��� �˻�.

	1. MarbleColor::None �˻�. (marble�� �ٰ��� �ϴ� ��ġ(������ġ)�� �̹� �����ϴ� marble�� �ִ��� �˻�)
	2. testSet�� ����.
	3. MarbleColor::None �˻�.. (testSet (���� marble ��ġ) �� marble�� ���� ��ġ�� ���� �˻� ����.)
	4. ������ �˻�. (�����浹�˻�)
	*/

	/*
	// ���ִ°� ������ ����.
	//1. MarbleColor::None �˻�.
	IntPosition currentIndex = _marbleBoard.positionToIndex(shootedMarble->getPrevCentralPosition());
	if (_marbleBoard.existMarble(currentIndex)!=MarbleColor::None)
		return false;
	*/

	//2. testSet�� ����.
	auto testSet = getLessTestSet(shootedMarble);
	//3. ������ġ (testSet)�� �ϳ��� Ȯ��.
	for (auto& testPosition : testSet){
		// �ش� ������ġ�� �������������, 
		if (_marbleBoard.existMarble(testPosition) != MarbleColor::None){
			// 4. ������ �˻�. (���� �浹 �˻�)
			if (shootedMarble->circularHitTest(*_marbleBoard.getMarble(testPosition._x, testPosition._y).get())){
				return true;
			}
		}
	}
	return false;
}
//shootedMarble�� color���� �Ѱ��ְ�, reset()�ȴ�.
bool MarbleControl::attach(shooted_ptr& shootedMarble, const IntPosition& gridPosition)
{
	if (isAttachable(shootedMarble, gridPosition))
	{
		//attach Ȯ��.

		_marbleBoard.addMarble(gridPosition, shootedMarble->getColor());
		shootedMarble.reset();

		_justAttached = gridPosition;
		return true;
	}
	// if(ceiling)
	// force attach.


	return false;
}
// attach �� �����ε� �� �Լ�.
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