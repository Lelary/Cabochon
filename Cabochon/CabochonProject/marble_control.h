#ifndef _MARBLE_CONTROL_H
#define _MARBLE_CONTROL_H

#include "temporary.h"
#include "controls.h"
#include "marble.h"
#include <array>

namespace controls
{
	using components::Marble;
	using controls::MarbleControl;
	using temporary::marble_array;

	class MarbleControl
	{
	private:
		//marble_ptr 에 대한 2차원 배열
		marble_array marbles;

		//현재 높이
		int currentHeight;

	public:
		MarbleControl()
		{
			//임시로 move, unique_ptr 사용해봄
			marbles[3][4] = Marble::makeMarble();
			marbles[3][5] = std::move(marbles[3][4]);
		}
		MarbleControl(const MarbleControl& rhs);
		virtual ~MarbleControl(){}
		MarbleControl& operator=(const MarbleControl& rhs);

		const int getMaxX() const;
		const int getMaxY() const;
		const int getCurrentHeight() const;
	};

}
#endif