//2016. 1. 16.

#include "marble_control.h"

using controls::MarbleControl;
using components::Marble;
using temporary::marble_array;

MarbleControl::MarbleControl()
{

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