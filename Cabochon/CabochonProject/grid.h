#ifndef _GRID_H
#define _GRID_H

#include "components.h"
#include "vector2.h"
#include "temporary.h"

namespace components
{
	using mathematics::scalar;
	using mathematics::Position;
	using mathematics::IntPosition;
	using temporary::maxX;
	using temporary::maxY;
	using temporary::radius;

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
	class Grid
	{
	public:
		enum class RowType{ none = -1, even, odd };
		enum class Quadrant{ none = -1, first = 1, second, third, fourth};
	private:
		// radius of marble.. 
		static const int width = 2 * radius;
		static const int height = 2 * radius;
		static const int leftWall = 0;
		static const int rightWall = width * maxX;
		static const int ceiling = 0;
		static const int floor = height * maxY;
	public:
		/*
			2016. 1. 10
			�Լ������ �ٽ� �����غ�����

			2016. 1. 13
			���� �Լ����� ������ �� ����
		*/
		/*
			2016. 1. 16
			���� ��� ���, ���� ��� �Լ� ���� ������ �����Ƿ� ��ü ������ �����Ѵ�.
			(�ʿ����������Ƿ�)
		*/
		Grid() = delete;
		Grid(const Grid& rhs) = delete;
		~Grid() = delete;

		static RowType getRowType(scalar y);

		static bool isInGrid(scalar x, scalar y);
		static bool isInGrid(scalar x, scalar y, int gx, int gy);
		static bool isInGrid(Position position, IntPosition gridPosition);

		static bool isInGridSub(scalar x, scalar y, Quadrant q);
		static bool isInGridSub(Position position, Quadrant q);
		static bool isInGridSub(scalar x, scalar y, int gx, int gy, Quadrant q);
		static bool isInGridSub(Position position, IntPosition gridPosition, Quadrant q);

		static Quadrant getQuadrant(scalar x, scalar y);
		static Quadrant getQuadrant(Position position);

		static IntPosition getGridPosition(scalar x, scalar y);
		static IntPosition getGridPosition(Position position);

		static int getLeftWall();
		static int getRightWall();
		static int getCeiling();
		static int getFloor();
	};
}
#endif