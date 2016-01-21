#ifndef _TEMPORARY_H
#define _TEMPORARY_H
#include <array>
#include "components.h"
#include "mathematics.h"
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
	using mathematics::scalar;
	//-> constants 관련 헤더파일로
	//static const unsigned int radius = 3;

	/*
	2016. 1. 16
	구슬 판의 최대 크기 = 구슬이 가질수 있는 최대위치 +1
	구슬판의 마지막 행은 dead zone
	maxX는 8이지만 실제로는
	해당 행이 even인 경우 8이며, odd 일 경우 8-1=7 이다.
	maxY는 차후 변경 가능
	*/
	static const unsigned int maxX = 8;
	static const unsigned int maxY = 10;

	/*
	2016. 1. 21.
	constants
	*/
	static const unsigned int boardWidth = 100;
	static const unsigned int boardHeight = 120;
	static const unsigned int deckHeight = 30;
	static const scalar blockWidth = static_cast<scalar>(boardWidth) / static_cast<scalar>(maxX);
	static const scalar blockHeight = blockWidth;
	static const scalar marbleRadius = blockWidth * 0.9f / 2.0f;
	static const unsigned int boardMargin = 10;

	//static const unsigned int ceiling = 10;
	//static const unsigned int floor = ceiling + boardHeight;


	//-> 어디로?
	typedef std::array<std::array<components::marble_ptr, maxX>, maxY> marble_array;

}

#endif _TEMPORARY_H