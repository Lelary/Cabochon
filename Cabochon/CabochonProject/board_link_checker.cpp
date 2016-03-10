#include "board_link_checker.h"
#include "marble_board.h"
using mathematics::IntPosition;
using controls::BoardLinkChecker;
using controls::LinkState;
using controls::MarbleBoard;
using cabochon_constants::NO_POSITION;
using cabochon_constants::MAX_Y;

BoardLinkChecker::BoardLinkChecker(const MarbleBoard& marbleBoard)
	:_board(marbleBoard)
{

}
BoardLinkChecker::~BoardLinkChecker()
{
}

void BoardLinkChecker::linkAll(IntPosition me)
{
	linkUpper(me);
	linkSide(me);
	linkLower(me);
}

void BoardLinkChecker::linkUpper(IntPosition me)
{
	std::array<IntPosition, two> upper;
	upper.assign(NO_POSITION);

	if (me.x < 0 || me.y > _board.getHeight())
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error in BoardLinkChecker"));

	if (me.x == _board.getHeight())
		return;

	RowType myRowType = _board.getRowType(me.x);

	int left, right;
	if (myRowType == RowType::Even)	{
		left = me.y - 1;
		right = me.y;
	}
	else {
		left = me.y;
		right = me.y + 1;
	}

	//left
	if (left >= 0)
		upper[0] = { me.x + 1, left };
	
	//right
	int maxY = (myRowType == RowType::Even) ? MAX_Y-1 : MAX_Y;
	if (right < maxY)
		upper[1] = { me.x + 1, right };

	check(upper);	
}
void BoardLinkChecker::linkSide(IntPosition me)
{
	std::array<IntPosition, two> side;
	side.assign(NO_POSITION);

	if (me.x < 0 || me.y > _board.getHeight())
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error in BoardLinkChecker"));

	RowType myRowType = _board.getRowType(me.x);
	int myMaxY = myRowType == RowType::Even ? MAX_Y : MAX_Y - 1;
	int left = me.y - 1;
	int right = me.y + 1;

	//left
	if (left >= 0)
		side[0] = { me.x, left };
	//right
	if (right < myMaxY)
		side[1] = { me.x, right };

	check(side);
}
void BoardLinkChecker::linkLower(IntPosition me)
{
	std::array<IntPosition, two> lower;
	lower.assign(NO_POSITION);

	if (me.x < 0 || me.y > _board.getHeight())
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error in BoardLinkChecker"));

	if (me.x == 0)
		return;

	RowType myRowType = _board.getRowType(me.x);

	int left, right;
	if (myRowType == RowType::Even)	{
		left = me.y - 1;
		right = me.y;
	}
	else {
		left = me.y;
		right = me.y + 1;
	}

	//left
	if (left >= 0)
		lower[0] = { me.x - 1, left };

	//right
	int maxY = (myRowType == RowType::Even) ? MAX_Y - 1 : MAX_Y;
	if (right < maxY)
		lower[1] = { me.x - 1, right };

	check(lower);
}
void BoardLinkChecker::check(std::array<IntPosition, two> testSet)
{
	for (IntPosition index : testSet)
	{
		if (index == NO_POSITION)
			continue;

		if (_result[index.x][index.y] == LinkState::NotChecked)
		{
			if (_data[index.x][index.y] == true)
			{
				_result[index.x][index.y] = LinkState::Linked;
				linkAll(index);
			}
			else
				_result[index.x][index.y] = LinkState::NotLinked;
		}
	}
}
void BoardLinkChecker::makeData()
{
	// 기존 데이터 삭제.
	_data.clear();

	// ceiling 을 인위적으로 추가.
	int ceilingCol = (_board.getRowType(_board.getHeight()-1) == RowType::Even)
		? MAX_Y-1 : MAX_Y;
	std::vector<bool> ceiling;
	ceiling.assign(ceilingCol, true);
	_data.push_back(ceiling);

	for (int row = 0; row < _board.getHeight(); row++)
	{
		int maxCol = (_board.getRowType(row) == RowType::Even)
			? cabochon_constants::MAX_Y : cabochon_constants::MAX_Y - 1;
		_data.push_back(std::vector<bool>());
		for (int col = 0; col < maxCol; col++)
		{
			switch (_board.existMarble({ row, col }))
			{
			case MarbleColor::Num:
				throw(GameError(gameErrorNS::FATAL_ERROR, "Marble Color can not be MarbleColor::Num!"));
				break;
			case MarbleColor::None:
				_data.at(row).push_back(false);
				break;
			default:
				// Num과 None을 제외한 MarbleColor은 컬러 색상이다. (Marble이 있음을 의미).
				_data.at(row).push_back(true);
				break;
			}
		}
	}
}
void BoardLinkChecker::makeLinkedResult()
{
	makeData();

	_result.clear();
	for (int row = 0; row < _data.size() - 1; row++)
	{
		_result.push_back(std::vector<LinkState>());
		_result.back().assign(_data[row].size(), LinkState::NotChecked);
	}

	//천장에서 시작.
	int ceilingX = _data.size() - 1;
	int ceilingMaxY = _data.back().size();
	for (int col = 0; col < ceilingMaxY; col++)
		linkAll({ ceilingX, col });
}
const std::deque<std::vector<LinkState>>& BoardLinkChecker::getLinkedResult()
{
	makeLinkedResult();
	return _result;
}