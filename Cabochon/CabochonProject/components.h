#ifndef COMPONENTS_H
#define COMPONENTS_H
#include <memory>
namespace components
{
//클래스 선언====================================
	class Layer;
	class Object;
	class Marble;
	class ShootedMarble;
	class SteeringWheel;
	class CeilingBlock;
//===============================================
//typedef 구문===================================
	//unique ptr로 Marble을 생성, 관리한다
	typedef std::unique_ptr<Marble> marble_ptr;
//===============================================
}
#endif