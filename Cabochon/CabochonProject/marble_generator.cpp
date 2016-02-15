#include "marble_generator.h"
using components::marble_ptr;
using controls::MarbleGenerator;
using frameworks::TextureList;

marble_ptr MarbleGenerator::makeMarble()
{
	return std::make_unique<Marble>();
}
marble_ptr MarbleGenerator::initializeMarbleImage(marble_ptr marble, TextureList& textureList)
{
	marble->loadLayers(textureList);
	return marble;
}


void MarbleGenerator::render()
{
	// nothing to do.
}
void MarbleGenerator::update()
{
	// nothing to do.
}