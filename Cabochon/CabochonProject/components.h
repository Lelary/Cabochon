#ifndef COMPONENTS_H
#define COMPONENTS_H
#include <memory>
namespace components
{
//Ŭ���� ����====================================
	class Object;
	class Marble;
	class ShootedMarble;
	class SteeringWheel;
	//class Board;
	//class BackGround;	
/*
	2016. 1. 10
	controls ? components ?
	Grid - Quadrant - Object
	��ü�� �ʿ�ġ �ʰ�(�޸𸮸� �Ҵ��ϰ� ����� ������ ����)
	������� ���� ���� �� �ִ�.
*/
	//Marble�� ��ġ�κ��� ����ġ�� ���ĭ���� �˷���
	class Grid;
//===============================================
//typedef ����===================================
	//unique ptr�� Marble�� ����, �����Ѵ�
	typedef std::unique_ptr<Marble> marble_ptr;
//===============================================
}
#endif