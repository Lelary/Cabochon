#ifndef _CONSOLE_H
#define _CONSOLE_H

#include "frameworks.h"
#include "patterns.h"
#include "typedefs.h"

using frameworks::Console;

/*
	2016. 1. 7
	Model-View ���� ����ϱ� ���� �ܼ�â���� ����� main �Լ��� �̰����� �ۼ��Ѵ�.
*/

class Console
	:public patterns::Singleton<Console>
{
public:
	static int main();
};

#endif