#ifndef _MATHEMATICS_H
#define _MATHEMATICS_H

//forward declaration of classes
namespace mathematics
{
	typedef float scalar;

	enum class Origin{LEFT_TOP, CENTER};

	struct IntPosition;
	struct Position;
	using Velocity = Position;

	/*
	2016. 1. 11
	degree �� ��Ÿ�� angle
	0 <= degree < 360 �� scalar ���� ������.
	�̿� ���� ����ó���� �ʿ����� ����(�ڵ����� ���)
	*/
	class Angle;
}

#endif	