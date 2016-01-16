//2016. 1. 16.

#include "marble_control.h"

using controls::MarbleControl;
using components::Marble;
using temporary::marble_array;

MarbleControl::MarbleControl()
{
	//�ӽ÷� move, unique_ptr ����غ�
	marbles[3][4] = Marble::makeMarble();
	marbles[3][5] = std::move(marbles[3][4]);
}

MarbleControl::~MarbleControl()
{
	/*
	2016. 1. 16.
	Nothing to do yet.
	*/
}
int MarbleControl::getCurrentHeight() const
{
	return currentHeight;
}