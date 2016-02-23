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
//Attach 가능성이 있는 Grid 위치 (인접위치) 반환.
std::vector<IntPosition> MarbleControl::getTestSet(const shooted_ptr& shootedMarble) const
{
	IntPosition marblePosition = _marbleBoard.positionToIndex(shootedMarble->getPrevCentralPosition());
	return getTestSet(marblePosition);
}
//Attach 가능성이 있는 Grid 위치 (인접위치) 반환.
std::vector<IntPosition> MarbleControl::getTestSet(IntPosition marblePosition) const
{
	std::vector<IntPosition> testSet;
	int x = marblePosition.x;
	int y = marblePosition.y;

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

	if (testUpX < _marbleBoard.getHeight())
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
	// getTestSet()으로 (최대)6개의 testSet을 받아서, 
	// Quadrant를 이용하여 정확하게 attachable 검사를 하기 위한 (최대)2개의 위치만을 남긴다.
	// getTestSet()과 비슷한 함수를 만드는 편이 간단하고 빠르지만, 코드중복을 없애는 것이 더 중요.

	//std::vector<IntPosition> newTestSet;
	std::vector<IntPosition> testSet = getTestSet(shootedMarble);
	Quadrant quadrant = getQuadrant(shootedMarble);
	IntPosition index = _marbleBoard.positionToIndex(shootedMarble->getPrevCentralPosition());

	bool even = _marbleBoard.getRowType(index.x) == RowType::Even;

	int remove_col;
	int remove_row;
	IntPosition removeSide;
	removeSide.x = index.x;

	// first||fourth 면 왼쪽을, second||third 면 오른쪽을 지운다.
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

	// first || second 면 아래쪽을, third || fourth면 윗쪽을 지운다.
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

	1. shootedMarble이 gridPosition에 포함되었는지 검사.
	2. Attach 하고자 하는 위치가 비었는지 검사.
	3. isAttachable(const shooted_ptr& shootedMarble)const 호출.
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
	shootedMarble의 인접 위치의 Marble에 대해 붙을 가능성이 있는지 검사.

	1. testSet을 얻음.
	2. MarbleColor::None 검사.. (testSet (인접 marble 위치) 중 marble이 없는 위치는 다음 검사 제외.)
	3. 반지름 검사. (원형충돌검사)
	*/

	//1. testSet을 얻음.
	auto testSet = getLessTestSet(shootedMarble);
	//2. 인접위치 (testSet)을 하나씩 확인.
	for (auto& testPosition : testSet){
		//3. 해당 인접위치가 비어있지않으면, 
		if (_marbleBoard.existMarble(testPosition) != MarbleColor::None){
			// 4. 반지름 검사. (원형 충돌 검사)
			if (shootedMarble->circularHitTest(*_marbleBoard.getMarble(testPosition).get(), 0.8f)){
				return true;
			}
		}
	}
	return false;
}
//shootedMarble은 color값만 넘겨주고, reset()된다.
bool MarbleControl::attach(shooted_ptr& shootedMarble)
{
	IntPosition gridPosition = _marbleBoard.positionToIndex(shootedMarble->getPrevCentralPosition());
	
	// row 검사.
	if (gridPosition.x >= _marbleBoard.getHeight() || gridPosition.x<0)
		return false;
	// column 검사.
	int maxY = (_marbleBoard.getRowType(gridPosition.x) == RowType::Even) ? MAX_Y : MAX_Y - 1;
	if (gridPosition.y >= maxY || gridPosition.y<0)
		return false;

	// 블록의 인접블록을 검사하는 방법으로 attach.
	if (isAttachable(shootedMarble, gridPosition))
	{
		//attach 확정.
		_marbleBoard.addMarble(gridPosition, shootedMarble->getColor());
		shootedMarble.reset();

		_justAttached = gridPosition;
		return true;
	}

	// 이전인덱스와 현재 인덱스 확인하여 attach
	if (shootedMarble->indexChanged()) {
		// 현재 위치가 valid (그래야 color검사가능.) 하고 이전 위치가 valid ( 그래야 부착 가능, 최초 위치를 제외하곤 항상 valid)
		if (shootedMarble->isInInvalidIndex() == false && shootedMarble->wasInInvalidIndex()==false){
			// currentIndex has Color
			if (_marbleBoard.getMarble(shootedMarble->getCurrentIndex())->getColor() != MarbleColor::None) {
				//attach 확정, prevIndex에 부착.
				_marbleBoard.addMarble(shootedMarble->getPrevIndex(), shootedMarble->getColor());

				_justAttached = shootedMarble->getPrevIndex();
				shootedMarble.reset();
				return true;
			}
		}
		// 이전 위치가 invalid인데 현재 위치에 color 가 있음.
		// 사실 이 상황이 오기전에 이미 gameOver 처리가 되었어야함. (현재는 처리하는 로직이 미완성)
		// 나중에 예외처리로 교체.
		else if (shootedMarble->isInInvalidIndex() == false && shootedMarble->wasInInvalidIndex())
		{
			if (_marbleBoard.getMarble(shootedMarble->getCurrentIndex())->getColor() != MarbleColor::None)
				_marbleBoard.setBoardState(BoardState::GameOver);
		}

	}

	// 천장에 닿아서 force attach.
	if (shootedMarble->getCurrentIndex().x == _marbleBoard.getHeight()-1) {
		//attach 확정.
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

	// tag 제거.
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

std::vector<bool> MarbleControl::linkFromUpperLine(const std::vector<bool>& upperLine, int upperRow) const
{
	// upperLine(Row) 로부터 nextLine(Row)를의 Linking 여부를 구함.
	// 모든 Line에 대해 이 함수를 호출 한 뒤, 같은 방법으로
	// getLinkingFromSideways()를 수행해야 한다.
	//---------------------------------------------------------------
	// 2016. 2. 22. 
	// 예외처리 꼭 추가.
	// ftn은 임의의 색깔 확인 함수.
	// ftn 함수작성하되, 예외처리가 아닌 false를 반환하도록 작성할것.
	//---------------------------------------------------------------

	// upperRow가 invalid 하면 안됨.
	// upperRow == getHeight() 인 경우는 ceiling 바로 아래라인을 nextLine으로 구하고자하므로 예외처리하지않는다.
	if (upperRow <0 || upperRow>_marbleBoard.getHeight()) {
		throw(GameError(gameErrorNS::FATAL_ERROR, "error in getNextLinkedRow"));
	}

	int nextRow = upperRow - 1;
	// 더 체크할 필요가 없음. 근데 이함수호출뒤에 문제발생여지가있으니 예외처리.
	if (nextRow < 0)
		throw(GameError(gameErrorNS::FATAL_ERROR, "error in getNextLinkedRow"));

	int left, right;

	//upperRow가 even 인지 false 인지. (nextRow의 반대.)
	bool upperEven = _marbleBoard.getRowType(nextRow) == RowType::Even ? false: true;
	int nextMaxY = (upperEven) ? MAX_Y-1 : MAX_Y;
	std::vector<bool> nextLine;
	nextLine.assign(nextMaxY, false);

	for (int i = 0; i < upperLine.size(); i++)
	{
		if (upperEven){
			left = i - 1;
			right = i;
		}
		else{
			left = i;
			right = i+1;
		}

		// left, right의 index 범위 검사 nextLine에 대해서만 함. (_marbleBoard 에 대해서는 하지않고, isNotMarbleColorNone()에게 위임.)
		// if upperLine[i] 가 true로 마크되어 있으면

		if (upperLine[i]){
			if (left>=0 && isNotMarbleColorNone({ nextRow, left }))
				nextLine[left] = true;
			if (right < nextLine.size() &&isNotMarbleColorNone({ nextRow, right }))
				nextLine[right] = true;
		}
	}

	return nextLine;
}

void MarbleControl::linkFromSideWays(std::vector<bool>& line, int row) const
{
	// Row가 invalid 하면 안됨.
	if (row < 0 || row >= _marbleBoard.getHeight()) {
		throw(GameError(gameErrorNS::FATAL_ERROR, "error in getNextLinkedRow"));
	}

	int size = line.size();

	//left to right
	for (int col = 1; col < size; col++)
	{
		if (line[col] == false)
			// MarbleColor::None 이 아니고, 옆칸(왼쪽)이 linked 상태이면, 나도 linked 상태이다.
			if (isNotMarbleColorNone({ row, col }) && line[col - 1] == true)
				line[col] = true;
	}

	//right to left, 상동.
	for (int col = size - 2; col > 0; col--)
	{
		if (line[col] == false)
			if (isNotMarbleColorNone({ row, col }) && line[col + 1] == true)
				line[col] = true;
	}
}

bool MarbleControl::isNotMarbleColorNone(IntPosition index) const
{
	// 이 함수는 인덱스에 대해 예외를 발생시키지 않는 대신, false 를 리턴한다.
	if (_marbleBoard.isInvalidIndex(index))
		return false;

	if (_marbleBoard.getMarble(index)->getColor() == MarbleColor::None)
		return false;
	else
		return true;
}

void MarbleControl::drop()
{
	//======================================================================================
	// checked와 _marbles는 역순. 
	//======================================================================================
	std::vector < std::vector<bool> > checked;
	int highestRow = _marbleBoard.getHeight() - 1;

	
	std::vector<bool> ceiling;
	int ceilingMaxY = _marbleBoard.getRowType(highestRow) == RowType::Even ? MAX_Y-1 : MAX_Y;
	ceiling.assign(ceilingMaxY, true);
	checked.push_back(linkFromUpperLine(ceiling, _marbleBoard.getHeight()));	//firstLine

	// Pre : highestRow의 linkFromUpperLine을 구함.

	for (int row = highestRow; row >= 1; row--)
	{
		auto line = linkFromUpperLine(checked[highestRow - row], row);
		checked.push_back(line);
	}

	// Pre : checked 에 linkFromUpperLine() 을 적용함. (윗줄의 정보로 아랫줄의 Link여부를 판정함.)
	// Post : checked 에 getLinkingFromSideways을 적용함. ( 왼쪽의 정보로 오른쪽의 Linke 여부를 판정, 반대방향으로 다시 판정.)
	for (int row = 0; row < checked.size();row++)
		linkFromSideWays(checked[row], row);

	// Pre : checked 를 구함.
	// Post : checked를 가지고, false인 marble을 drop(remove)함.

	for (int row = 0; row < checked.size(); row++)
	{
		for (int col = 0; col < checked[row].size(); col++)
		{
			// 연결이 되어 있으면 true.
			if (checked[row][col] == false)
			{
				//drop
				if (isNotMarbleColorNone({ checked.size()-1-row, col }))	
					_marbleBoard.removeMarble({ checked.size()-1-row, col });
			}
		}
	}
}

void MarbleControl::render()
{
	_marbleBoard.render();

	if (_shootedMarble != nullptr) {
		_shootedMarble->draw();
	}
}
void MarbleControl::update(float frameTime)
{
	if (_shootedMarble != nullptr) {
		_shootedMarble->move(_marbleBoard, frameTime);
		_shootedMarble->update(frameTime);
	}
	_marbleBoard.update(frameTime);
}