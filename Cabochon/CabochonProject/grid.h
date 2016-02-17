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
			정적 멤버 상수, 정적 멤버 함수 만을 가지고 있으므로 객체 생성을 제한한다.
			(필요하지않으므로)
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