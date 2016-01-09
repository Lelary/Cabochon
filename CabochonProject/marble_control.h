#ifndef _MARBLE_CONTROL_H
#define _MARBLE_CONTROL_H

#include "temporary.h"
#include "controls.h"
#include "marble.h"
#include <array>
using controls::MarbleControl;
using temporary::marble_array;

class MarbleControl
{
private:
	//marble_ptr �� ���� 2���� �迭
	marble_array marbles;

	//���� ����
	int currentHeight;
	
public:
	MarbleControl()
	{
		//�ӽ÷� move, unique_ptr ����غ�
		marbles[3][4] = Marble::makeMarble();
		marbles[3][5] = std::move(marbles[3][4]);
	}
	virtual ~MarbleControl(){}

	const int getMaxX() const;
	const int getMaxY() const;
	const int getCurrentHeight() const;
};


#endif