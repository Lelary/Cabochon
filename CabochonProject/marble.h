#include "object.h"

/*
	2016. 1. 5
	class Marble

	������ ������ ��Ÿ���ϴ�. 
	Object�� ��ӹ޾� �ڽ��� ��ǥ�������� ��ġ�� ����մϴ�.

	TODO :
		����������� ��ǥ ����

	_px, _py �� puzzle x puzzle y �� �ǹ��մϴ�.
	-> vector2<int>, IntPosition

*/
/*
	2016. 1. 15
	cpp �ۼ� 1�� �Ϸ�
*/

namespace components
{
	using components::Marble;
	using components::marble_ptr;
	using mathematics::IntPosition;

	class Marble
		:public Object
	{
	public:
		static const int noPosition = -1;
	private:
		IntPosition _gridPosition;
	public:
		Marble();
		Marble(const IntPosition& gridPosition);
		Marble(const Marble& rhs);
		virtual ~Marble();
		Marble& operator=(const Marble& rhs);

		IntPosition getGridPosition() const;
		void setGridPosition(IntPosition gridPosition);

		/*
			2016. 1. 10.
			�ٸ� ������ �̻簡�� �� �Լ�
			���丮�� ������ ��

			�̻�Ȱ��°� ����?
			���Ǵ� �� :
			1. ���� ��,
			2. �� ����
		*/
		static marble_ptr makeMarble()
		{
			return std::make_unique<Marble>();
		}
	};
}