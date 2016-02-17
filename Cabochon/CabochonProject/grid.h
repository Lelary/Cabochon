#ifndef _GRID_H
#define _GRID_H

#include "controls.h"
#include "mathematics.h"
#include "vector2.h"
#include "cabochon_constants.h"
#include "marble_board.h"
namespace controls
{
	using mathematics::scalar;
	using mathematics::Position;
	using mathematics::IntPosition;
	
	/*
		2016. 1. 10
		Block -> Quadrant -> Grid

		odd - even �� �ݺ��Ǵ�
		����� ������ �����ؾ��Ѵ�.
		�������� ������ ������ �� �� �� �ִ�.

		��ĭ�� �ʺ�� ���̸� �˾ƾ��Ѵ�. -> Marble�� ����
		�̷κ��� �־��� Marble�� ��ġ�� ��� ĭ�� �ش��ϴ��� ������� �� �� �ִ�.

		�Ķ���ͷ� Marble�� �޴� ���� ��ǥ�� �޴°�츦 �����ε� �� �� �ִ�.
	*/

	/*
		2016. 1. 10
		������ ��ǥ�� ���� ��ġ�� ������ش�.
	*/

	/*
		2016. 1. 16
		instance�� ���� �ʿ䰡 �����Ƿ� ������ delete.

		cpp ���Ͽ� �Լ� ���� 1�� �ۼ� �Ϸ�
	*/
	using cabochon_constants::MAX_X;
	using cabochon_constants::MIN_Y;
	using cabochon_constants::MARBLE_WIDTH;
	using cabochon_constants::MARBLE_HEIGHT;
	
	class Grid
	{
	public:
		enum class Quadrant{ none = -1, first = 1, second, third, fourth};
	private:
	public:
		/*
			2016. 1. 16
			���� ��� ���, ���� ��� �Լ� ���� ������ �����Ƿ� ��ü ������ �����Ѵ�.
			(�ʿ����������Ƿ�)
		*/
		Grid() = delete;
		Grid(const Grid& rhs) = delete;
		~Grid() = delete;

		static bool isInGrid(const MarbleBoard& board, scalar x, scalar y);
		static bool isInGrid(const MarbleBoard& board, scalar x, scalar y, int gx, int gy);
		static bool isInGrid(const MarbleBoard& board, Position centralPosition, IntPosition gridPosition);

		static bool isInGridSub(const MarbleBoard& board, scalar x, scalar y, Quadrant q);
		static bool isInGridSub(const MarbleBoard& board, Position centralPosition, Quadrant q);
		static bool isInGridSub(const MarbleBoard& board, scalar x, scalar y, int gx, int gy, Quadrant q);
		static bool isInGridSub(const MarbleBoard& board, Position centralPosition, IntPosition gridPosition, Quadrant q);

		static Quadrant getQuadrant(const MarbleBoard& board, scalar x, scalar y);
		static Quadrant getQuadrant(const MarbleBoard& board, Position centralPosition);

		static IntPosition getGridPosition(const MarbleBoard& board, scalar x, scalar y);
		static IntPosition getGridPosition(const MarbleBoard& board, Position centralPosition);

	};
}
#endif