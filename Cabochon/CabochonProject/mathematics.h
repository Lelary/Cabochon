#ifndef _MATHEMATICS_H
#define _MATHEMATICS_H

//forward declaration of classes
namespace mathematics
{
	enum class Origin{LEFT_TOP, CENTER};

	//vector2
	struct Position;
	struct IntPosition;
	/*
	2016. 1. 11
	degree �� ��Ÿ�� angle
	0 <= degree < 360 �� scalar ���� ������.
	�̿� ���� ����ó���� �ʿ����� ����(�ڵ����� ���)
	*/
	class Angle;

	typedef float scalar;
	using Velocity = Position;


}

#endif	