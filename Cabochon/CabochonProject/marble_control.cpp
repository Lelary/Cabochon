//2016. 1. 16.

#include "marble_control.h"
#include <vector>

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
	IntPosition marblePosition = shootedMarble->getMarble()->getGridPosition();
	return std::move(getTestSet(marblePosition));
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
	shootedMarble�� ���� ��ġ�� Marble�� ���� ���� ���ɼ��� �ִ��� �˻�.

	1. testSet�� ����.
	2. nullptr �˻�
	3. ������ �˻�. (�����浹�˻�)
	
	*/

	auto testSet = getTestSet(shootedMarble);
	

}
bool MarbleControl::isAttachable(const shooted_ptr& shootedMarble) const
{

}
void MarbleControl::attach(shooted_ptr& shootedMarble, const IntPosition& gridPosition)
{

}
void MarbleControl::attach(shooted_ptr& shootedMarble)
{

}

// build map
bool MarbleControl::existMarble(IntPosition gridPosition);
void MarbleControl::addMarble(marble_ptr& marble, IntPosition gridPosition);
void MarbleControl::removeMarble(IntPosition gridPosition);