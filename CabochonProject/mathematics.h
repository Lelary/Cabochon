#ifndef _MATHEMATICS_H
#define _MATHEMATICS_H

//forward declaration of classes
namespace mathematics
{
	//vector2
	template < typename T >
	struct Vector2;
	/*
	2016. 1. 11
	degree �� ��Ÿ�� angle
	0 <= degree < 360 �� scalar ���� ������.
	�̿� ���� ����ó���� �ʿ����� ����(�ڵ����� ���)
	*/
	class Angle;

	typedef float scalar;	

	using Position = Vector2 < scalar > ;
	using IntPosition = Vector2 < int > ;
	
}

#endif	