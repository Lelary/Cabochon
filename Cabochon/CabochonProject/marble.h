#include "object.h"
using components::Marble;
using components::marble_ptr;

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
public:
	Marble(){}
	virtual ~Marble(){}

	int getPx() const;
	int getPy() const;

	void setPx(int puzzleX);
	void setPy(int puzzleY);

	/*
		2016. 1. 10. 
		다른 곳으로 이사가야 할 함수
		팩토리로 구현할 것
		
		이사안가는게 낫나?
		사용되는 곳 : 
			1. 구슬 쏠때, 
			2. 맵 생성
	*/
	static marble_ptr makeMarble()
	{
		return std::make_unique<Marble>();
	}
};