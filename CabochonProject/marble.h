#include "object.h"
using components::Marble;
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

	int getPx();
	int getPy();

	void setPx(int puzzleX);
	void setPy(int puzzleY);

};