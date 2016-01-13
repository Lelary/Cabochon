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
		degree �� ��Ÿ�� angle
		0 <= degree < 360 �� scalar ���� ������.
		�̿� ���� ����ó���� �ʿ����� ����(�ڵ����� ���)
	*/
	class Angle;
	
}

#endif	