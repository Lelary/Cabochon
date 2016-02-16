//2016. 1. 15.
#include "steering_wheel.h"
using components::SteeringWheel;
using mathematics::Angle;
using mathematics::scalar;
using frameworks::TextureList;
using components::Layer;

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
	_layers.at(1).setDegrees(_angle.getDegree());
}
void SteeringWheel::rotateRight(unsigned int angle)
{
	setAngle(_angle + static_cast<scalar>(angle));
	_layers.at(1).setDegrees(_angle.getDegree());
}

void SteeringWheel::loadLayers(TextureList& textureList)
{
	// 0, 1, 2 순서로 그려짐.
	_layers.push_back(Layer());
	_layers.back().initialize(textureList.getGraphics(), 512, 256, 1, textureList.getTexture(TextureList::TextureName::SteeringWheel));
	_layers.back().setFrames(1, 1);
	_layers.back().setCurrentFrame(1);
	_layers.back().setLoop(false);
	_layers.back().setScaleFromWidth(1.2, getWidth());
	_layers.back().setDistanceFromCenter(getPosition(), getWidth(), getHeight(), { 0, 0 });

	_layers.push_back(Layer());
	_layers.back().initialize(textureList.getGraphics(), 256, 256, 2, textureList.getTexture(TextureList::TextureName::SteeringWheel));
	_layers.back().setFrames(0, 0);
	_layers.back().setCurrentFrame(0);
	_layers.back().setLoop(false);
	_layers.back().setScaleFromWidth(1, getWidth());
	_layers.back().setDistanceFromCenter(getPosition(), getWidth(), getHeight(), { 0, 0 });

}

void SteeringWheel::draw()
{
	for (Layer layer:_layers)
		layer.draw();
}
void SteeringWheel::update(float frameTime)
{

}