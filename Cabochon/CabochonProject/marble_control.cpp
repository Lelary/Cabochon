//2016. 1. 16.

#include "marble_control.h"
#include <deque>
using mathematics::Position;
using mathematics::IntPosition;
using mathematics::scalar;
using components::Marble;
using components::marble_ptr;
using components::MarbleColor;
using components::ShootedMarble;
using controls::MarbleControl;
using controls::RowType;
using controls::MarbleColorOn;
using controls::MarbleBoard;
using controls::Quadrant;
using scenes::TextureList;
using cabochon_constants::MAX_Y;
using cabochon_constants::MARBLE_HEIGHT;
using cabochon_constants::MARBLE_WIDTH;
using cabochon_constants::LINE;
using cabochon_constants::NO_POSITION;
using shooted_ptr = std::unique_ptr < ShootedMarble >;

MarbleControl::MarbleControl()
	:_justAttached(NO_POSITION), _shootedMarble(nullptr)
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
	if (getJustAttached() == NO_POSITION)
		return false;
	else
		return true;
}
//Shooted Marble
shooted_ptr& MarbleControl::getShootedMarble()
{
	return _shootedMarble;
}
void MarbleControl::setShootedMarble(MarbleColor color, Position centralPosition, scalar speed, mathematics::Angle degree, TextureList& textureList)
{
	shooted_ptr shootedMarble=std::make_unique<ShootedMarble>(color, _marbleBoard);
	shootedMarble->setCentralPosition(centralPosition);
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
std::vector<IntPosition> MarbleControl::getTestSet(IntPosition marblePosition) const
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
		|| (position == removeSide)
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
Quadrant MarbleControl::getQuadrant(Position marblePosition) const
{
	IntPosition index = _marbleBoard.positionToIndex(marblePosition);
	Position leftTop;
	bool even = (_marbleBoard.getRowType(index.x) == RowType::Odd) ? false : true;
	bool left;
	bool up;

	if (even)
		leftTop = {	static_cast<scalar>(0 + index.y * MARBLE_WIDTH),
					static_cast<scalar>(LINE - index.x * MARBLE_HEIGHT) };
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
bool MarbleControl::isAttachable(const shooted_ptr& shootedMarble, IntPosition gridPosition) const
{
	/*
	2016. 1. 22.

	1. shootedMarble�� gridPosition�� ���ԵǾ����� �˻�.
	2. Attach �ϰ��� �ϴ� ��ġ�� ������� �˻�.
	3. isAttachable(const shooted_ptr& shootedMarble)const ȣ��.
	*/
	IntPosition currentIndex = _marbleBoard.positionToIndex(shootedMarble->getPrevCentralPosition());
	if (currentIndex == gridPosition )
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
			if (shootedMarble->circularHitTest(*_marbleBoard.getMarble(testPosition).get(), 0.8f)){
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
	
	if (gridPosition.y > _marbleBoard.getHeight() || gridPosition.y<0)
		return false;
	int maxY = (_marbleBoard.getRowType(gridPosition.y) == RowType::Even) ? MAX_Y : MAX_Y - 1;
	if (gridPosition.x >= maxY || gridPosition.x<0)
		return false;

	// ����� ��������� �˻��ϴ� ������� attach.
	if (isAttachable(shootedMarble, gridPosition))
	{
		//attach Ȯ��.
		_marbleBoard.addMarble(gridPosition, shootedMarble->getColor());
		shootedMarble.reset();

		_justAttached = gridPosition;
		return true;
	}

	// �����ε����� ���� �ε��� Ȯ���Ͽ� attach
	if (shootedMarble->indexChanged()) {
		// ���� ��ġ�� valid (�׷��� color�˻簡��.) �ϰ� ���� ��ġ�� valid ( �׷��� ���� ����, ���� ��ġ�� �����ϰ� �׻� valid)
		if (shootedMarble->isInInvalidIndex() == false && shootedMarble->wasInInvalidIndex()==false){
			// currentIndex has Color
			if (_marbleBoard.getMarble(shootedMarble->getCurrentIndex())->getColor() != MarbleColor::None) {
				//attach Ȯ��, prevIndex�� ����.
				_marbleBoard.addMarble(shootedMarble->getPrevIndex(), shootedMarble->getColor());

				_justAttached = shootedMarble->getPrevIndex();
				shootedMarble.reset();
				return true;
			}
		}
		// ���� ��ġ�� invalid�ε� ���� ��ġ�� color �� ����.
		// ��� �� ��Ȳ�� �������� �̹� gameOver ó���� �Ǿ������. (����� ó���ϴ� ������ �̿ϼ�)
		// ���߿� ����ó���� ��ü.
		else if (shootedMarble->isInInvalidIndex() == false && shootedMarble->wasInInvalidIndex())
		{
			if (_marbleBoard.getMarble(shootedMarble->getCurrentIndex())->getColor() != MarbleColor::None)
				_marbleBoard.setBoardState(BoardState::GameOver);
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

	bool toContinue = false;
	
	//-----------------------------------------
	sameColors.push_back(_justAttached);
	checked.push_back(_justAttached);

	int i=0;
	for (unsigned int i = 0; i < sameColors.size(); i++) {
		testSet = getTestSet(sameColors[i]);

		for (auto test : testSet) {
			for (auto c : checked) {
				if (test == c) {
					toContinue = true;
					break;
				}
			}
			if (toContinue) {
				toContinue = false;
				continue;
			}

			// if not checked yet
			checked.push_front(test);
			if (_marbleBoard.getMarble(test)->getColor() == color) {
				sameColors.push_back(test);
			}
		}
	}

	// tag ����.
	_justAttached = NO_POSITION;

	if (sameColors.size() >= 3)	{
		for (auto index : sameColors) {
			_marbleBoard.removeMarble(index);
		}
		return true;
	}
	else
		return false;
}

std::vector<bool> MarbleControl::getNextLinkedLine(const std::vector<bool>& thisLine, int thisRow) const
{

	//---------------------------------------------------------------
	// 2016. 2. 22. 
	// ����ó�� �� �߰�.
	// ftn�� ������ ���� Ȯ�� �Լ�.
	// ftn �Լ��ۼ��ϵ�, ����ó���� �ƴ� false�� ��ȯ�ϵ��� �ۼ��Ұ�.
	//---------------------------------------------------------------

	// thisRow�� invalid �ϸ� �ȵ�.
	if (thisRow <0 || thisRow>_marbleBoard.getHeight()) {
		throw(GameError(gameErrorNS::FATAL_ERROR, "error in getNextLinkedRow"));
	}

	int nextRow = thisRow - 1;

	// �� üũ�� �ʿ䰡 ����. �ٵ� ���Լ�ȣ��ڿ� �����߻������������� ����ó��.
	if (nextRow < 0)
		throw(GameError(gameErrorNS::FATAL_ERROR, "error in getNextLinkedRow"));


	int left, right;

	//thisLine
	bool even = _marbleBoard.getRowType(thisRow) == RowType::Even ? true : false;

	int maxY = (even) ? MAX_Y - 1 : MAX_Y;
	std::vector<bool> nextLine(maxY);

	for (int i = 0; i < thisLine.size(); i++)
	{
		if (even){
			left = i - 1;
			right = i;
		}
		else{
			left = i;
			right = i+1;
		}

		// left, right�� index ���� �˻� nextLine�� ���ؼ��� ��. (_marbleBoard �� ���ؼ��� �����ʰ�, isNotMarbleColorNone()���� ����.)
		// if thisLine[i] �� true�� ��ũ�Ǿ� ������

		if (thisLine[i]){
			if (left>0 && isNotMarbleColorNone({ nextRow, left }))
				nextLine[left] = true;
			if (right < nextLine.size() &&isNotMarbleColorNone({ nextRow, right }))
				nextLine[right] = true;
		}
	}

	return nextLine;
}


bool MarbleControl::isNotMarbleColorNone(IntPosition index) const
{
	// �� �Լ��� �ε����� ���� ���ܸ� �߻���Ű�� �ʴ� ���, false �� �����Ѵ�.
	if (_marbleBoard.isInvalidIndex(index))
		return false;

	if (_marbleBoard.getMarble(index)->getColor() == MarbleColor::None)
		return false;
	else
		return true;
}

void MarbleControl::drop()
{
	std::vector < std::vector<bool> > checked;

	// height �� bool vector �� �߰��ϰ� ����. = ��¥ ����(õ��) �� �߰��ϰ� getNextLinkedLine()�� ȣ���ϰ� �;��µ�
	// �׷��� ������ ����Ǵ� �Լ��鿡�� ����ó���� ���ϴϱ�, �ȵ�.
	//======================================================================================
	// getHeight()�� ���̰� �ƴ�. size()!=height. 
	// �ش� �Լ� ȣ�� �Լ� �� ���ľ���.
	// ������ �ӽ÷� getHeight()-1 ���.
	//======================================================================================
	bool even = _marbleBoard.getRowType(_marbleBoard.getHeight()-1) == RowType::Even ? true : false;
	// height Row.
	int maxY = (even) ? MAX_Y : MAX_Y-1;
	auto firstLine = std::vector<bool>(maxY);
	for (int i = 0; i < maxY; i++)
		firstLine[i]=isNotMarbleColorNone({ _marbleBoard.getHeight()-1, i });
	checked.push_back(firstLine);

	// Pre : checked �� ù��° line (ceiling �ٷ� �Ʒ� line) �� ����.
	// Post : getNextLinkedLine�� �̿��Ͽ� ������ line�� ����.

	for (int i = _marbleBoard.getHeight()-1; i >= 1; i--)
	{
		auto line = getNextLinkedLine(checked[_marbleBoard.getHeight()-1 - i], i);
		checked.push_back(line);
	}

	for (int i = 1; i < checked.size(); i++)
	{
		for (int j = 0; j < checked[i].size(); j++)
		{
			// ������ �Ǿ� ������ true.
			if (checked[i][j] == false)
			{
				//drop
				if (isNotMarbleColorNone({ i, j }))	
					_marbleBoard.removeMarble({ i, j });
			}
		}
	}
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
	{
		_shootedMarble->move(_marbleBoard, frameTime);
		_shootedMarble->update(frameTime);
	}
	_marbleBoard.update(frameTime);
}