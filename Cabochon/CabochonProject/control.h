#include "controls.h"

namespace controls
{
	class Control
	{
	private:

	public:
		virtual void render() = 0;
		virtual void update() = 0;
	};
}