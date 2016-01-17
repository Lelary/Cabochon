#ifndef _SHOOTED_MARBLE_H
#define _SHOOTED_MARBLE_H
#include "marble.h"

/*
2016. 1. 17

상속관계로 만들지
wrapper로 composite로 만들지 결정해야함

*/

namespace components
{
	using mathematics::IntPosition;

	class ShootedMarble
		:public Marble
	{
	private:
		
	public:
		ShootedMarble();
		ShootedMarble(const ShootedMarble& rhs);
		virtual ~ShootedMarble();
		ShootedMarble& operator=(const ShootedMarble& rhs);




	};
}

#endif // _SHOOTED_MARBLE_H