#ifndef _MATHEMATICS_H
#define _MATHEMATICS_H

namespace mathematics
{
	typedef float scalar;
	
	//vector2
	template <typename T>
	struct Vector2;
	typedef Vector2<scalar> Position;

	/*
		2016. 1. 11
		degree 로 나타낸 angle
		0 <= degree < 360 의 scalar 값을 가진다.
		이에 대한 예외처리는 필요하지 않음(자동으로 계산)
	*/
	class Angle;
	
}

#endif	