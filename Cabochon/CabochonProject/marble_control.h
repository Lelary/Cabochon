#ifndef _MARBLE_CONTROL_H
#define _MARBLE_CONTROL_H

#include "temporary.h"
#include "controls.h"
#include "marble.h"
#include "grid.h"
#include <array>

namespace controls
{
	using controls::MarbleControl;
	using components::Marble;
	using components::Grid;
	using temporary::marble_array;

	class MarbleControl
	{
	private:
		//marble_ptr 에 대한 2차원 배열
		marble_array marbles;

		//현재 높이
		int currentHeight;

	public:
		MarbleControl();
		MarbleControl(const MarbleControl& rhs) = delete;
		virtual ~MarbleControl();
		MarbleControl& operator=(const MarbleControl& rhs) = delete;

		int getCurrentHeight() const;
	};

}
#endif