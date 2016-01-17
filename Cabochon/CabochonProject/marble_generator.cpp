#include "marble_generator.h"
using components::marble_ptr;
using controls::MarbleGenerator;

marble_ptr MarbleGenerator::makeMarble()
{
	return std::make_unique<Marble>();
}