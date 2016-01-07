#include "object.h"
using components::Marble;
/*
	2016. 1. 5
	class Marble

	게임의 구슬을 나타냅니다. 
	Object를 상속받아 자신의 좌표공간상의 위치를 기술합니다.

	TODO :
		퍼즐공간상의 좌표 생성

	_px, _py 는 puzzle x puzzle y 를 의미합니다.

*/
class Marble
	:public Object
{
private:
	int _px, _py;

	int getPx();
	int getPy();

	void setPx(int puzzleX);
	void setPy(int puzzleY);

};