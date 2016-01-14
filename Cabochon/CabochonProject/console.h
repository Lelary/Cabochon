#ifndef _CONSOLE_H
#define _CONSOLE_H

#include "frameworks.h"
#include "patterns.h"
#include "controls.h"
#include "marble_control.h"
using frameworks::Console;

/*
	2016. 1. 7
	Model-View ���� ����ϱ� ���� �ܼ�â���� ����� main �Լ��� �̰����� �ۼ��Ѵ�.
*/
/*
	2016. 1. 9.
	�ٸ� ���� Ŭ�������� �̱������� ����� ��ſ� ���⼭ ������ ����
*/
class Console
	:public patterns::Singleton<Console>
{
private:
	controls::MarbleControl marbleControl;
public:
	Console(){}
	~Console(){};
	static int main();
};

#endif