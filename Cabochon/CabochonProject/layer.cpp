#include "layer.h"
using components::Layer;
using mathematics::Position;
using mathematics::Origin;
using mathematics::scalar;

Layer::Layer() 
	:Image(), _distance({0.0f,0.0f})
{

}	
Layer::~Layer()
{
	Image::~Image(); 
}
//private
void Layer::setX(float newX)
{
	Image::setX(newX);
}
//private
void Layer::setY(float newY)
{
	Image::setY(newY);
}
Position Layer::getDistance()
{
	return _distance;
}
void Layer::setDistance(const Position& object, const Position& distance)
{
	_distance = distance;
	adjustPosition(object);
}
void Layer::setDistanceFromCenter(const Position& object, scalar objectWidth, scalar objectHeight, const Position& distance)
{
	setDistance(object, { objectWidth / 2.0f - getScale()*getWidth() / 2.0f + distance._x, objectHeight / 2.0f - getScale()*getHeight() / 2.0f + distance._y});
}
void Layer::adjustPosition(const Position& object)
{
	setX(object._x + _distance._x);
	setY(object._y + _distance._y);
}
void Layer::setScaleFromWidth(float s, float objectWidth)
{
	Image::setScale((objectWidth / getWidth()) * s);
}
void Layer::setScaleFromHeight(float s, float objectHeight)
{
	Image::setScale((objectHeight / getHeight()) * s);
}