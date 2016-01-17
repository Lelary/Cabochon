#ifndef _SHOOTED_MARBLE_H
#define _SHOOTED_MARBLE_H
#include "marble.h"

/*
2016. 1. 17

��Ӱ���� ������
wrapper�� composite�� ������ �����ؾ���
Marble�� �ӵ� ���Ϳ� �����Ӹ� �߰��ϱ� ���� �ʿ��ϴ�.

wrapper�� �����ϴ�.
wrapper�� �ۼ�.
*/

namespace components
{
	using mathematics::Velocity;
	class ShootedMarble
	{
	private:
		marble_ptr marble;
		Velocity velocity;
	public:
		ShootedMarble();
		ShootedMarble(const ShootedMarble& rhs);
		virtual ~ShootedMarble();
		ShootedMarble& operator=(const ShootedMarble& rhs);

		/*
		2016. 1. 17

		Velocity ��ŭ �̵��ϸ�, ���� �浹ó���� �ؾ��Ѵ�.
		�ٸ� Marble���� Attach ó���� MarbleControl�� ������
		( marble_array�� �߰��ؾ��ϱ� ����)
		Attach �ϰ� ���� �Ǵ��ϰ� �����ϴ� ���� ���⼭ �ص� �ȴ�.
		(�����ʴ��� ����)
		*/
		void move();
	};
}

#endif // _SHOOTED_MARBLE_H