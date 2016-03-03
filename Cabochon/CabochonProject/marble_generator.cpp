#include "marble_generator.h"
using mathematics::scalar;
using components::marble_ptr;
using components::MarbleColor;
using controls::MarbleColorOn;
using controls::MarbleGenerator;
using scenes::TextureList;

int MarbleGenerator::getRandomNumber(int min, int max)
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_int_distribution<>  dist(min, max);

	return dist(gen);
}
scalar MarbleGenerator::getGaussianRandomNumber(scalar mean, scalar sigma)
{
	static std::random_device rd;
	static std::mt19937 gen(rd());

	std::normal_distribution<float> dist(mean, sigma);
	return dist(gen);
}

MarbleColor MarbleGenerator::getRandomMarbleColor()
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	// None~Gray
	std::uniform_int_distribution<>  dist((int)MarbleColor::None, (int)MarbleColor::Gray);
	int randomNumber = dist(gen);
	return (MarbleColor)randomNumber;
}
MarbleColor MarbleGenerator::getRandomMarbleColor(MarbleColorOn colorRange)
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

	// 2016. 2. 25.
	// clear 시. 
	// 이렇게 테스트 해보고 어떻게 처리할지 다시 생각.
	// 이함수에 안오면 더 좋음.
	//--------------------------------------
	if (sum <= 0)
		return MarbleColor::None;
	//--------------------------------------

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
	return (MarbleColor)(i - 1);
}

marble_ptr MarbleGenerator::makeMarble(MarbleColor color)
{
	return std::make_unique<Marble>(color);
}
marble_ptr MarbleGenerator::makeRandomMarble()
{
	return std::make_unique<Marble>(getRandomMarbleColor());
}
marble_ptr MarbleGenerator::makeRandomMarble(MarbleColorOn colorRange)
{
	return std::make_unique<Marble>(getRandomMarbleColor(colorRange));
}
/*
marble_ptr MarbleGenerator::loadTexture(marble_ptr marble, TextureList& textureList)
{
	marble->loadLayers(textureList);
	return marble;
}
*/