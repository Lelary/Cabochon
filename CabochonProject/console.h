#ifndef _CONSOLE_H
#define _CONSOLE_H

#include "frameworks.h"
#include "patterns.h"
#include "controls.h"
#include "marble_control.h"
using frameworks::Console;

/*
	2016. 1. 7
	Model-View 모델을 사용하기 위해 콘솔창에서 사용할 main 함수를 이곳에서 작성한다.
*/
/*
	2016. 1. 9.
	다른 관리 클래스들은 싱글톤으로 만드는 대신에 여기서 원본을 가짐
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