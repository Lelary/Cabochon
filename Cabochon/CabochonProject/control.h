#ifndef _CONTROL_H
#define _CONTROL_H
#include "controls.h"

namespace controls
{
	class Control
	{
	private:

	public:
		virtual void render() = 0;
		virtual void update(float frameTime) = 0;
	};
}
#endif // _CONTROL_H