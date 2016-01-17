#ifndef _SHOOTED_MARBLE_H
#define _SHOOTED_MARBLE_H
#include "marble.h"

/*
2016. 1. 17

��Ӱ���� ������
wrapper�� composite�� ������ �����ؾ���

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