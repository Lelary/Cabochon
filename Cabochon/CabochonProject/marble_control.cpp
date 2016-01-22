//2016. 1. 16.

#include "marble_control.h"

using controls::MarbleControl;
using components::Marble;
using components::marble_ptr;
using components::ShootedMarble;
using components::Grid;
using temporary::marble_array;
using temporary::maxX;
using temporary::maxY;
using mathematics::IntPosition;
using shooted_ptr = std::unique_ptr < ShootedMarble >;

MarbleControl::MarbleControl()
{

}

MarbleControl::~MarbleControl()
{
	/*
	2016. 1. 16.
	Nothing to do yet.
	*/
}

//���� ����
int MarbleControl::getCurrentHeight() const
{
	// index �� ��ȯ�ϱ� ���� raw for statement ���.
	for (int row = _marbles.size() - 1; row >= 0; row--)
	{
		for (auto& marblePtr : _marbles[row])
		{
			if (marblePtr != nullptr)
				return row + 1;
		}
	}
	
	//marble�� �Ѱ��� ����
	return 0;
}

//Shooted Marble
shooted_ptr& MarbleControl::getShootedMarble()
{
	return _shootedMarble;
}
void MarbleControl::setShootedMarble(shooted_ptr& shootedMarble)
{
	_shootedMarble = std::move(shootedMarble);
}
//Attach ���ɼ��� �ִ� Grid ��ġ ��ȯ.
std::vector<IntPosition> MarbleControl::getTestSet(const shooted_ptr& shootedMarble) const
{
	IntPosition marblePosition = Grid::getGridPosition(shootedMarble->getMarble()->getCentralPosition());
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

	switch (Grid::getRowType(marblePosition._y))
	{
	case Grid::RowType::even:
		testSet.push_back({ marblePosition._x - 1, marblePosition._y - 1 });
		break;

	case Grid::RowType::odd:
		testSet.push_back({ marblePosition._x - 1, marblePosition._y + 1 });
		break;
	default:
		/*
			2016. 1. 22.
			exception �߰��ؾ���.
		*/
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
			if (position._x < 0 || position._x >= maxX)
				return true;
			if (position._y < 0 || position._y >= maxY)
				return true;
			if (position._y >= maxY - 1 && Grid::getRowType(position._y) == Grid::RowType::odd)
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

	if (Grid::isInGrid(shootedMarble->getMarble()->getCentralPosition(), gridPosition))
		if (existMarble(gridPosition) == false)
			return isAttachable(shootedMarble);

	return false;
}
bool MarbleControl::isAttachable(const shooted_ptr& shootedMarble) const
{
	/*
	2016. 1. 22.
	shootedMarble�� ���� ��ġ�� Marble�� ���� ���� ���ɼ��� �ִ��� �˻�.

	1. nullptr �˻�. (marble�� �ٰ��� �ϴ� ��ġ(������ġ)�� �̹� �����ϴ� marble�� �ִ��� �˻�)
	2. testSet�� ����.
	3. nullptr �˻�. (testSet (���� marble ��ġ) �� marble�� ���� ��ġ�� ���� �˻� ����.)
	4. ������ �˻�. (�����浹�˻�)
	*/


	//1. nullptr �˻�.
	IntPosition gridPosition = Grid::getGridPosition(shootedMarble->getMarble()->getCentralPosition());
	if (existMarble(gridPosition)==true)
		return false;

	//2. testSet�� ����.
	auto testSet = getTestSet(shootedMarble);
	for (auto testPosition : testSet)
	{
		//3. nullptr �˻�
		if (existMarble(testPosition)==true)
		{
			// 4. ������ �˻�. (���� �浹 �˻�)
			if (shootedMarble->getMarble()->circularHitTest(*_marbles[testPosition._x][testPosition._y]))
			{
				return true;
			}
		}
	}
	return false;
}
void MarbleControl::attach(shooted_ptr& shootedMarble, const IntPosition& gridPosition)
{
	if (isAttachable(shootedMarble, gridPosition))
		addMarble(shootedMarble->getMarble(), gridPosition);
		
}
void MarbleControl::attach(shooted_ptr& shootedMarble)
{
	if (isAttachable(shootedMarble))
	{
		IntPosition gridPosition = Grid::getGridPosition(shootedMarble->getMarble()->getCentralPosition());
		addMarble(shootedMarble->getMarble(), gridPosition);
	}
}

// build map
bool MarbleControl::existMarble(const IntPosition& gridPosition) const
{
	if (_marbles[gridPosition._x][gridPosition._y] == nullptr)
		return false;
	return true;
}
void MarbleControl::addMarble(marble_ptr& marble, const IntPosition& gridPosition)
{
	if (existMarble(gridPosition)==false)
		_marbles[gridPosition._x][gridPosition._y] = std::move(marble);
}
void MarbleControl::removeMarble(const IntPosition& gridPosition)
{

}