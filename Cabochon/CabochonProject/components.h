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
/*
	2016. 1. 10
	controls ? components ?
	Grid - Quadrant - Object
	객체는 필요치 않고(메모리를 할당하고 계산할 이유가 없음)
	계산으로 값을 구할 수 있다.
*/
	//Marble의 위치로부터 그위치가 어느칸인지 알려줌
	class Grid;
//===============================================
//typedef 구문===================================
	//unique ptr로 Marble을 생성, 관리한다
	typedef std::unique_ptr<Marble> marble_ptr;
//===============================================
}
#endif