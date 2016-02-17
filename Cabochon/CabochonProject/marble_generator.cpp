#include "marble_generator.h"
using components::marble_ptr;
using components::MarbleColor;
using controls::MarbleGenerator;
using frameworks::TextureList;

marble_ptr MarbleGenerator::makeMarble(MarbleColor color=MarbleColor::None)
{
	return std::make_unique<Marble>(color);
}
marble_ptr MarbleGenerator::makeRandomMarble()
{
	// None~Gray
	std::uniform_int_distribution<>  dist(-1, 6);
	int randomNumber = dist(gen);

	return std::make_unique<Marble>((MarbleColor)randomNumber);
}
marble_ptr MarbleGenerator::makeRandomMarble(MarbleColorOn colorRange)
{
	// 2016. 2. 17.
	// TODO. 개선 방법 찾기.

	int sum;
	for (int i = 0; i < 8; i++)
		if ((colorRange.data << i) && 1)
			sum++;

	std::uniform_int_distribution<>  dist(0, sum-1);
	int randomNumber = dist(gen);

	sum = 0;
	int i;
	for (i = 0; i < 8; i++){
		if ((colorRange.data << i) && 1){
			sum++;
			if (sum == randomNumber)
				break;
		}
	}
	return std::make_unique<Marble>((MarbleColor)i);
}
marble_ptr MarbleGenerator::loadTexture(marble_ptr marble, TextureList& textureList)
{
	marble->loadLayers(textureList);
	return marble;
}


void MarbleGenerator::render()
{
	// nothing to do.
}
void MarbleGenerator::update(float frameTime)
{
	// nothing to do.
}