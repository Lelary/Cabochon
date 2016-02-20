#include "object.h"
using components::Object;
using mathematics::scalar;
using mathematics::Position;
using mathematics::Origin;

Object::Object()
	:_position({ 0, 0 }), _width(0), _height(0), _layersLoaded(false)
{
	/*
	2016. 1. 15
	nothing to do.
	*/
}

Object::Object(const Position& position, scalar width, scalar height)
	: _position(position), _width(width), _height(height), _layersLoaded(false)
{
	/*
	2016. 1. 15
	nothing to do.
	*/
}
Object::Object(const Object& rhs)
	: _position(rhs._position), _width(rhs._width), _height(rhs._height), _layersLoaded(rhs._layersLoaded)
{
	/*
	2016. 1. 15
	�� ��� �ڱ���Կ� ���� ó���� ���� �ʾƵ� ��
	*/
}
Object::~Object()
{
	/*
	2016. 1. 15
	nothing to do.
	*/
}
Object& Object::operator=(const Object& rhs)
{
	if (&rhs == this)
		return *this;

	_position = rhs._position;
	_width = rhs._width;
	_height = rhs._height;
	return *this;
}

// the position of Left Top 
Position Object::getPosition() const
{
	return _position;
}
// the position of middle
Position Object::getCentralPosition() const
{
	return convertOrigin(_position, Origin::CENTER, _width, _height);
}
scalar Object::getWidth() const
{
	return _width;
}
scalar Object::getHeight() const
{
	return _height;
}

// the position of Left Top 
void Object::setPosition(const Position& position)
{
	_position = position;
	
	//vector �� iterate �ϸ� ��� ��ġ ����.
	adjustLayersPosition();
}

// the position of Left Top 
void Object::setPosition(scalar x, scalar y)
{
	_position = { x, y };
	//vector �� iterate �ϸ� ��� ��ġ ����.
	adjustLayersPosition();
}

// the position of middle, changes position property.
void Object::setCentralPosition(const Position& position)
{
	_position = convertOrigin(position, Origin::LEFT_TOP, _width, _height);
	//vector �� iterate �ϸ� ��� ��ġ ����.
	adjustLayersPosition();
}
// the position of middle, changes position property.
void Object::setCentralPosition(scalar x, scalar y)
{
	_position = convertOrigin({ x, y }, Origin::LEFT_TOP, _width, _height);
	//vector �� iterate �ϸ� ��� ��ġ ����.
	adjustLayersPosition();
}

void Object::setWidth(scalar width)
{
	_width = width;
}
void Object::setHeight(scalar height)
{
	_height = height;
}

Position Object::convertOrigin(const Position& oldPosition, Origin newOrigin, scalar width, scalar height)
{
	Position newPosition;

	switch (newOrigin)
	{
	case Origin::LEFT_TOP:
		newPosition.x = oldPosition.x - width / 2.0f;
		newPosition.y = oldPosition.y - height / 2.0f;
		break;

	case Origin::CENTER:
		newPosition.x = oldPosition.x + width / 2.0f;
		newPosition.y = oldPosition.y + height / 2.0f;
		break;
	}
	return newPosition;
}

bool Object::isLayersLoaded()
{
	return _layersLoaded;
}
void Object::adjustLayersPosition()
{
	for (Layer& layer : _layers)
	{
		layer.adjustPosition(_position);
	}
}