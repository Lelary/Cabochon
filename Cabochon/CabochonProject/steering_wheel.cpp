//2016. 1. 15.
#include "steering_wheel.h"
using components::SteeringWheel;
using mathematics::Angle;
using mathematics::scalar;
using frameworks::TextureList;

SteeringWheel::SteeringWheel()
{
	/*
	2016. 1. 15
	nothing to do.
	*/
	
}
SteeringWheel::SteeringWheel(const Angle& angle)
	:_angle(angle)
{
	/*
	2016. 1. 15
	nothing to do.
	*/
}
SteeringWheel::SteeringWheel(const SteeringWheel& rhs)
	: Object(rhs), _angle(rhs._angle)
{
	/*
	2016. 1. 15
	현재 자기 대입 처리를 하지 않아도 됨
	*/
}
SteeringWheel::~SteeringWheel()
{
	/*
	2016. 1. 15
	nothing to do.
	*/
}
SteeringWheel& SteeringWheel::operator=(const SteeringWheel& rhs)
{
	if (&rhs == this)
		return *this;

	_angle = rhs._angle;
	return *this;
}

Angle SteeringWheel::getAngle() const
{
	return _angle;
}
void SteeringWheel::setAngle(Angle angle)
{
	/*
	2016. 1. 15
	추가적인 각도 예외 처리?

	2016. 1. 16
	SteeringWheelControl에서 하자
	*/
	_angle = angle;
}

void SteeringWheel::setOrigin()
{
	setAngle(0);
}
void SteeringWheel::rotateLeft(unsigned int angle)
{
	setAngle(_angle - static_cast<scalar>(angle));
}
void SteeringWheel::rotateRight(unsigned int angle)
{
	setAngle(_angle + static_cast<scalar>(angle));
}

void SteeringWheel::loadLayers(TextureList& textureList)
{
	// 0, 1, 2 순서로 그려짐.
	_layers.push_back(Layer());
	_layers[0].initialize(textureList.getGraphics(), 512, 256, 1, textureList.getTexture(TextureList::TextureName::SteeringWheel));
	_layers[0].setFrames(1, 1);
	_layers[0].setCurrentFrame(1);
	_layers[0].setLoop(false);
	_layers[0].setDistance(getPosition(), { 70, 400 });
	_layers[0].setScale(0.3);

	_layers.push_back(Layer());
	_layers[1].initialize(textureList.getGraphics(), 256, 256, 2, textureList.getTexture(TextureList::TextureName::SteeringWheel));
	_layers[1].setFrames(0, 0);
	_layers[1].setCurrentFrame(0);
	_layers[1].setLoop(false);
	_layers[1].setDistance(getPosition(), { 100, 360 });
	_layers[1].setScale(0.4);

	_layers.push_back(Layer());
	_layers[2].initialize(textureList.getGraphics(), 256, 256, 2, textureList.getTexture(TextureList::TextureName::SteeringWheel));
	_layers[2].setFrames(1, 1);
	_layers[2].setCurrentFrame(1);
	_layers[2].setLoop(false);
	_layers[2].setDistance(getPosition(), {100,330});
	_layers[2].setScale(0.4);


}

void SteeringWheel::draw()
{
	_layers[0].draw();
	_layers[1].draw();
	_layers[2].draw();
}
void SteeringWheel::update(scalar frameTime)
{

}