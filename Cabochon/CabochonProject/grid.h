#ifndef _GRID_H
#define _GRID_H

#include "typedefs.h"
#include "temporary.h"
#include "components.h"
#include <tuple>
using components::Grid;
using namespace temporary;
using temporary::maxX;
using temporary::maxY;

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
class Grid
{
private:
	int width;
	int height;
	//사분면
	enum Quadrant{ none, one = 0, two, three, four, num };
public:
/*
	2016. 1. 10
	함수명들은 다시 생각해봐야함
*/

	static bool isIn(scalar x, scalar y);
	static bool isInSub(scalar x, scalar y);

	static Quadrant getQuadrant(scalar x, scalar y);

	//typedef필요
	std::tuple<int, int> isWhere(scalar x, scalar y);

	
};

#endif