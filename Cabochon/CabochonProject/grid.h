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

		odd - even 이 반복되는
		블록의 구조를 생각해야한다.
		벽에대한 정보를 가지게 될 수 도 있다.

		한칸의 너비와 높이를 알아야한다. -> Marble의 지름
		이로부터 주어진 Marble의 위치가 어느 칸에 해당하는지 계산으로 알 수 있다.

		파라미터로 Marble을 받는 경우와 좌표를 받는경우를 오버로딩 할 수 있다.
	*/

	/*
		2016. 1. 10
		구슬의 좌표로 부터 위치를 계산해준다.
	*/

	/*
		2016. 1. 16
		instance를 만들 필요가 없으므로 생성자 delete.

		cpp 파일에 함수 구현 1차 작성 완료
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
			함수명들은 다시 생각해봐야함

			2016. 1. 13
			지금 함수명이 괜찮은 것 같다
		*/
		/*
			2016. 1. 16
			정적 멤버 상수, 정적 멤버 함수 만을 가지고 있으므로 객체 생성을 제한한다.
			(필요하지않으므로)
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