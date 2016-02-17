#include "grid.h"

using controls::Grid;
using mathematics::scalar;
using mathematics::Position;
using mathematics::IntPosition;
using controls::MarbleBoard;
using controls::RowType;

using cabochon_constants::MAX_X;
using cabochon_constants::MIN_Y;
using cabochon_constants::MARBLE_WIDTH;
using cabochon_constants::MARBLE_HEIGHT;
using cabochon_constants::LEFT_WALL;
using cabochon_constants::RIGHT_WALL;
using cabochon_constants::LINE;


/*
	2016. 1. 16
	실제 구현 함수
*/
bool Grid::isInGrid(const MarbleBoard& board, scalar x, scalar y)
{
	//grid 안에 없음
	if (x < LEFT_WALL || x>RIGHT_WALL)
		return false;

	//grid 안에 없음
	if (y < board.getCeilingPosition() || y> LINE + MARBLE_HEIGHT)
		return false;

	return true;
}
bool Grid::isInGrid(const MarbleBoard& board, scalar x, scalar y, int gx, int gy)
{
	// 실제 계산된 grid 내에서의 position
	IntPosition gridPosition;

	if (isInGrid(board, x, y) == false)
		return false;

	gridPosition = getGridPosition(board, x, y);
	
	// 기대한 위치 gx, gy 와 실제 gridPosition이 일치하는지 검사
	if (gridPosition._x == gx
		&&
		gridPosition._y == gy)
		return true;
	else
		return false;
}
bool Grid::isInGrid(const MarbleBoard& board, Position centralPosition, IntPosition gridPosition)
{
	return isInGrid(board, centralPosition._x, centralPosition._y, gridPosition._x, gridPosition._y);
}

bool Grid::isInGridSub(const MarbleBoard& board, scalar x, scalar y, Quadrant q)
{
	if (isInGrid(board, x, y) == false)
		return false;

	// 기대한 값과 일치함
	if (q == getQuadrant(board, x, y))
		return true;
	else
		return false;
}
bool Grid::isInGridSub(const MarbleBoard& board, Position centralPosition, Quadrant q)
{
	return isInGridSub(board, centralPosition._x, centralPosition._y, q);
}
bool Grid::isInGridSub(const MarbleBoard& board, scalar x, scalar y, int gx, int gy, Quadrant q)
{
	if (isInGrid(board, x, y, gx, gy) == false)
		return false;

	// 기대한 값과 일치함
	if (q == getQuadrant(board, x, y))
		return true;
	else
		return false;

}
bool Grid::isInGridSub(const MarbleBoard& board, Position centralPosition, IntPosition gridPosition, Quadrant q)
{
	return isInGridSub(board, centralPosition._x, centralPosition._y, gridPosition._x, gridPosition._y, q);
}

/*
	2016. 1. 16
	실제 구현 함수
*/
Grid::Quadrant Grid::getQuadrant(const MarbleBoard& board, scalar x, scalar y)
{
	IntPosition gridPosition;
	Position centralPosition;

	//grid 안에 없음
	if (isInGrid(board, x, y) == false)
		return Quadrant::none;
	
	//x, y 가 속한 칸 번호를 구함
	gridPosition = getGridPosition(board, x, y);
	
	//칸번호를 통해 칸 내에서의 상대적 위치를 구함.
	centralPosition._x = x - gridPosition._x * MARBLE_WIDTH;
	centralPosition._y = y - gridPosition._y * MARBLE_HEIGHT;

	//상대적 위치로부터 해당칸에서 어느 사분면에 속하는지 구함
	if (centralPosition._x > MARBLE_WIDTH / 2.0f)
	{
		if (centralPosition._y > MARBLE_HEIGHT / 2.0f)
			return Quadrant::first;
		else
			return Quadrant::fourth;
	}
	else
	{
		if (centralPosition._y > MARBLE_HEIGHT / 2.0f)
			return Quadrant::second;
		else
			return Quadrant::third;
	}

}
Grid::Quadrant Grid::getQuadrant(const MarbleBoard& board, Position centralPosition)
{
	return getQuadrant(board, centralPosition._x, centralPosition._y);
}

IntPosition Grid::getGridPosition(const MarbleBoard& board, scalar x, scalar y)
{
	//grid 안에 없음
	if (isInGrid(board, x, y) == false)
		return{ -1, -1 };

	return{ board.positionToIndexX(x, board.getRowType(y)), board.positionToIndexY(y) };
}
IntPosition Grid::getGridPosition(const MarbleBoard& board, Position centralPosition)
{
	return getGridPosition(board, centralPosition._x, centralPosition._y);
}