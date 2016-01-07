#ifndef _CONSOLE_H
#define _CONSOLE_H

#include "frameworks.h"
#include "patterns.h"
#include "typedefs.h"

using frameworks::Console;

/*
	2016. 1. 7
	Model-View 모델을 사용하기 위해 콘솔창에서 사용할 main 함수를 이곳에서 작성한다.
*/

class Console
	:public patterns::Singleton<Console>
{
public:
	static int main();
};

#endif