#ifndef _CHEAT_H
#define _CHEAT_H

#include "controls.h"
#include "marble.h"

namespace controls
{
	using components::MarbleColor;

	class Cheat
	{
	private:

	public:
		Cheat() = delete;
		Cheat(const Cheat& rhs) = delete;
		virtual ~Cheat() = delete;
		Cheat& operator=(const Cheat& rhs) = delete;

		static void cheatColor(SteeringWheelControl& wheelControl, MarbleColor color);

	};
}


#endif