#include "layer.h"
using components::Layer;
using mathematics::Position;

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
void Layer::adjustPosition(const Position& object)
{
	setX(object._x + _distance._x);
	setY(object._y + _distance._y);
}