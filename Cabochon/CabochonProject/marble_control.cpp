//2016. 1. 16.

#include "marble_control.h"

using controls::MarbleControl;
using components::Marble;
using components::marble_ptr;
using components::MarbleColor;
using components::ShootedMarble;
using controls::Grid;
using controls::RowType;
using mathematics::Position;
using mathematics::IntPosition;
using mathematics::scalar;
using shooted_ptr = std::unique_ptr < ShootedMarble >;
using controls::MarbleColorOn;
using controls::MarbleBoard;
using frameworks::TextureList;

MarbleControl::MarbleControl()
	:_shooting(false), _justAttached({ -1, -1 })
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
	return _shooting;
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
	_shooting = true;
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
//Attach ���ɼ��� �ִ� Grid ��ġ ��ȯ.
std::vector<IntPosition> MarbleControl::getTestSet(const shooted_ptr& shootedMarble) const
{
	IntPosition marblePosition = Grid::getGridPosition(_marbleBoard, shootedMarble->getCentralPosition());
	return getTestSet(marblePosition);
}
//Attach ���ɼ��� �ִ� Grid ��ġ ��ȯ.
std::vector<IntPosition> MarbleControl::getTestSet(const IntPosition& marblePosition) const
{
	//quadrant �� ���� 6�� �˻�.
	const int testNumber = 6;
	std::vector<IntPosition> testSet(testNumber);

	testSet.push_back({ marblePosition._x - 1, marblePosition._y });
	testSet.push_back({ marblePosition._x + 1, marblePosition._y });

	testSet.push_back({ marblePosition._x, marblePosition._y - 1 });
	testSet.push_back({ marblePosition._x, marblePosition._y + 1 });

	switch (_marbleBoard.getRowType(marblePosition._y))
	{
	case RowType::Even:
		testSet.push_back({ marblePosition._x - 1, marblePosition._y - 1 });
		break;

	case RowType::Odd:
		testSet.push_back({ marblePosition._x - 1, marblePosition._y + 1 });
		break;
	default:
		throw(GameError(gameErrorNS::FATAL_ERROR,"Error in MarbleControl : getTestSet()!"));
		break;
	}

	//�����˻� ( 0~maxX-1, 0~maxY-1), odd row �� ��� 0~maxY-2
	/*
		2016. 1. 22.
		�׽�Ʈ �ʿ�
	*/
	testSet.erase(
		std::remove_if(
		testSet.begin(),
		testSet.end(),
		[&](const IntPosition& position) -> bool {
			if (position._x < 0 || position._x >= MAX_X)
				return true;
			if (position._y < 0 || position._y >= _marbleBoard.getHeight())
				return true;
			if (position._y >= _marbleBoard.getHeight() - 1 && _marbleBoard.getRowType(position._y) == RowType::Odd)
				return true;		
			return false;
		}),
		testSet.end()
		);

	return std::move(testSet);
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

	if (Grid::isInGrid(_marbleBoard, shootedMarble->getCentralPosition(), gridPosition))
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


	//1. MarbleColor::None �˻�.
	IntPosition gridPosition = Grid::getGridPosition(_marbleBoard, shootedMarble->getCentralPosition());
	if (_marbleBoard.existMarble(gridPosition)!=MarbleColor::None)
		return false;

	//2. testSet�� ����.
	auto testSet = getTestSet(shootedMarble);
	for (auto testPosition : testSet)
	{
		//3. nullptr �˻�
		if (_marbleBoard.existMarble(gridPosition) != MarbleColor::None)
		{
			// 4. ������ �˻�. (���� �浹 �˻�)
			if (shootedMarble->circularHitTest(*_marbleBoard.getMarble(testPosition._x, testPosition._y).get()))
			{
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
		_marbleBoard.addMarble(gridPosition, shootedMarble->getColor());

		_justAttached = gridPosition;
		_shooting = false;
		shootedMarble.reset();		
		return true;
	}
	return false;
}
bool MarbleControl::attach(shooted_ptr& shootedMarble)
{
	IntPosition gridPosition = Grid::getGridPosition(_marbleBoard, shootedMarble->getCentralPosition());
	return attach(shootedMarble, gridPosition);
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