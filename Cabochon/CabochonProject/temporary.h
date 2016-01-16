#ifndef _TEMPORARY_H
#define _TEMPORARY_H
#include <array>
#include "components.h"
/*
	2016. 1. 10
	당장 필요한 constant 변수, typedef 구문인데
	어느 namespace, class에 위치시켜야 할지 정말 애매할 때,
	혹은 적합한 클래스가 아직 작성되지 않았을 때,
	사용

	차후에 알맞은 위치로 구문들을 옮기고 이 파일은 삭제
*/

namespace temporary
{
	//-> constants 관련 헤더파일로
	static const unsigned int radius = 3;

	//-> 어디로?
	typedef std::array<std::array<components::marble_ptr, maxX>, maxY> marble_array;

}

#endif _TEMPORARY_H