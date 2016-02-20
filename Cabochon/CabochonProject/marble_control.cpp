//2016. 1. 16.

#include "marble_control.h"
#include <deque>
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
using scenes::TextureList;
using cabochon_constants::MAX_Y;
using controls::Quadrant;
using cabochon_constants::MARBLE_HEIGHT;
using cabochon_constants::MARBLE_WIDTH;
using cabochon_constants::LINE;

const IntPosition MarbleControl::noPosition = { -1, -1 };
MarbleControl::MarbleControl()
	:_justAttached(noPosition), _shootedMarble(nullptr)
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
	if (getJustAttached().x == -1 || getJustAttached().y == -1)
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
	int x = marblePosition.x;
	int y = marblePosition.y;

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

	bool even = _marbleBoard.getRowType(index.x) == RowType::Even;

	int remove_col;
	int remove_row;
	IntPosition removeSide;
	removeSide.x = index.x;

	// first||fourth �� ������, second||third �� �������� �����.
	if (quadrant == Quadrant::first || quadrant == Quadrant::fourth)
	{
		removeSide.y = index.y - 1;

		if (even)
			remove_col = index.y - 1; //left
		else
			remove_col = index.y;	//left
	}
	else
	{
		removeSide.y = index.y + 1;

		if (even)
			remove_col = index.y; //right
		else
			remove_col = index.y + 1;	//right
	}

	// first || second �� �Ʒ�����, third || fourth�� ������ �����.
	if (quadrant == Quadrant::first || quadrant == Quadrant::second){
		remove_row = index.x - 1;
	}
	else{
		remove_row = index.x + 1;
	}

	auto toRemove = [&](const IntPosition& position) -> bool {return
		(position.y == remove_col 
		|| position.x == remove_row 
		|| (position.x == removeSide.x && position.y == removeSide.y)
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
	bool even = (_marbleBoard.getRowType(index.x) == RowType::Odd) ? false : true;
	bool left;
	bool up;

	if (even)
		leftTop = { 0 + index.y*MARBLE_WIDTH, LINE - index.x*MARBLE_HEIGHT };
	else
		leftTop = { 0 + index.y*MARBLE_WIDTH + (MARBLE_WIDTH / 2.0f), LINE - index.x*MARBLE_HEIGHT };
	if (marblePosition.x < leftTop.x + MARBLE_WIDTH / 2.0f)
		left = true;
	else
		left = false;
	if (marblePosition.y < leftTop.y + MARBLE_HEIGHT / 2.0f)
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
	if (currentIndex.x == gridPosition.x	&&	currentIndex.y == gridPosition.y )
		if (_marbleBoard.existMarble(gridPosition) == MarbleColor::None)
			return isAttachable(shootedMarble);

	return false;
}
bool MarbleControl::isAttachable(const shooted_ptr& shootedMarble) const
{
	/*
	2016. 1. 22.
	shootedMarble�� ���� ��ġ�� Marble�� ���� ���� ���ɼ��� �ִ��� �˻�.

	1. testSet�� ����.
	2. MarbleColor::None �˻�.. (testSet (���� marble ��ġ) �� marble�� ���� ��ġ�� ���� �˻� ����.)
	3. ������ �˻�. (�����浹�˻�)
	*/

	//1. testSet�� ����.
	auto testSet = getLessTestSet(shootedMarble);
	//2. ������ġ (testSet)�� �ϳ��� Ȯ��.
	for (auto& testPosition : testSet){
		//3. �ش� ������ġ�� �������������, 
		if (_marbleBoard.existMarble(testPosition) != MarbleColor::None){
			// 4. ������ �˻�. (���� �浹 �˻�)
			if (shootedMarble->circularHitTest(*_marbleBoard.getMarble(testPosition.x, testPosition.y).get())){
				return true;
			}
		}
	}
	return false;
}
//shootedMarble�� color���� �Ѱ��ְ�, reset()�ȴ�.
bool MarbleControl::attach(shooted_ptr& shootedMarble)
{
	IntPosition gridPosition = _marbleBoard.positionToIndex(shootedMarble->getPrevCentralPosition());
	/*
	if (isAttachable(shootedMarble, gridPosition))
	{
		//attach Ȯ��.
		_marbleBoard.addMarble(gridPosition, shootedMarble->getColor());
		shootedMarble.reset();

		_justAttached = gridPosition;
		return true;
	}
	*/
	if (shootedMarble->updateIndex(getMarbleBoard())) {
		if (_marbleBoard.getMarble(shootedMarble->getCurrentIndex())->getColor() != MarbleColor::None) {
			//attach Ȯ��.
			_marbleBoard.addMarble(gridPosition, shootedMarble->getColor());
			shootedMarble.reset();

			_justAttached = gridPosition;
			return true;
		}
	}

	// õ�忡 ��Ƽ� force attach.
	if (shootedMarble->getCurrentIndex().x == _marbleBoard.getHeight()) {
		//attach Ȯ��.
		_marbleBoard.addMarble(gridPosition, shootedMarble->getColor());
		shootedMarble.reset();

		_justAttached = gridPosition;
		return true;
	}
	return false;

}
bool MarbleControl::smash()
{
	if (hasJustAttached() == false)
		return false;

	MarbleColor color = _marbleBoard.getMarble(_justAttached)->getColor();
	std::vector<IntPosition> testSet;

	std::deque<IntPosition> checked;
	std::vector<IntPosition> sameColors;

	bool toBreak = false;


	//-----------------------------------------
	sameColors.push_back(_justAttached);
	int i=0;
	for (int i = 0; i < sameColors.size(); i++) {
		testSet = getTestSet(sameColors[i]);

		for (auto test : testSet)
		{
			for (auto c : checked) {
				if (test.x == c.x && test.y == c.y) {
					toBreak = true;
					break;
				}
			}
			if (toBreak) {
				toBreak = false;
				break;
			}

			// if not checked yet
			checked.push_front(test);
			if (_marbleBoard.getMarble(test)->getColor() == color) {
				sameColors.push_back(test);
			}
		}
	}

	// tag ����.
	_justAttached = { -1, -1 };

	if (sameColors.size() >= 3)	{
		for (auto index : sameColors) {
			_marbleBoard.removeMarble(index.x, index.y);
		}
		return true;
	}
	else
		return false;
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