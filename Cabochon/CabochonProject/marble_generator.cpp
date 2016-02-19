#include "marble_generator.h"
using components::marble_ptr;
using components::MarbleColor;
using controls::MarbleColorOn;
using controls::MarbleGenerator;
using frameworks::TextureList;

int MarbleGenerator::getRandomNumber(int min, int max)
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_int_distribution<>  dist(min, max);

	return dist(gen);
}
marble_ptr MarbleGenerator::makeMarble(MarbleColor color)
{
	return std::make_unique<Marble>(color);
}
marble_ptr MarbleGenerator::makeRandomMarble()
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	// None~Gray
	std::uniform_int_distribution<>  dist((int)MarbleColor::None, (int)MarbleColor::Gray);
	int randomNumber = dist(gen);

	return std::make_unique<Marble>((MarbleColor)randomNumber);
}
marble_ptr MarbleGenerator::makeRandomMarble(MarbleColorOn colorRange)
{
	// 2016. 2. 17.
	// TODO. 개선 방법 찾기.
	static std::random_device rd;
	static std::mt19937 gen(rd());
	int sum = 0;
	//None제외.
	for (int i = (int)MarbleColor::None + 1; i < (int)MarbleColor::Num; i++){
		if ((colorRange.data >> i) & true)
			sum++;
	}

	std::uniform_int_distribution<>  dist(1, sum);
	int randomNumber = dist(gen);

	sum = 0; 
	int i = (int)MarbleColor::None + 1;
	for (; i <= (int)MarbleColor::Gray + 1; i++){
		if ((colorRange.data >> i) & true){
			sum++;
			if (sum == randomNumber)
				break;
		}
	}

	return std::make_unique<Marble>((MarbleColor)(i-1));
}
/*
marble_ptr MarbleGenerator::loadTexture(marble_ptr marble, TextureList& textureList)
{
	marble->loadLayers(textureList);
	return marble;
}
*/