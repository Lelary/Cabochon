#include "object.h"
using components::Marble;
using components::marble_ptr;

/*
	2016. 1. 5
	class Marble

	������ ������ ��Ÿ���ϴ�. 
	Object�� ��ӹ޾� �ڽ��� ��ǥ�������� ��ġ�� ����մϴ�.

	TODO :
		����������� ��ǥ ����

	_px, _py �� puzzle x puzzle y �� �ǹ��մϴ�.

*/
class Marble
	:public Object
{
private:
	int _px, _py;
public:
	Marble(){}
	virtual ~Marble(){}

	int getPx() const;
	int getPy() const;

	void setPx(int puzzleX);
	void setPy(int puzzleY);

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