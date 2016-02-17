#ifndef COMPONENTS_H
#define COMPONENTS_H
#include <memory>
namespace components
{
//Ŭ���� ����====================================
	class Layer;
	class Object;
	class Marble;
	class ShootedMarble;
	class SteeringWheel;
	class CeilingBlock;
//===============================================
//typedef ����===================================
	//unique ptr�� Marble�� ����, �����Ѵ�
	typedef std::unique_ptr<Marble> marble_ptr;
//===============================================
}
#endif