#include "object.h"
using components::Object;
using mathematics::scalar;
using mathematics::Position;

Object::Object()
	:_position({ 0, 0 }), _width(0), _height(0)
{
	/*
	2016. 1. 15
	nothing to do.
	*/
}

Object::Object(const Position& position, scalar width, scalar height)
	: _position(position), _width(width), _height(height)
{
	/*
	2016. 1. 15
	nothing to do.
	*/
}
Object::Object(const Object& rhs)
	: _position(rhs._position), _width(rhs._width), _height(rhs._height)
{
	/*
	2016. 1. 15
	이 경우 자기대입에 대한 처리를 하지 않아도 됨
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
	return{ _position._x + _width / 2.0f, _position._y + _height / 2.0f };
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
	_image.setX(position._x);
	_image.setY(position._y);
}

// the position of Left Top 
void Object::setPosition(scalar x, scalar y)
{
	_position = { x, y };
	_image.setX(x);
	_image.setY(y);
}

// the position of middle, changes position property.
void Object::setCentralPosition(const Position& position)
{
	_position = { position._x - _width/2.0f, position._y - _height/2.0f };
	_image.setX(_position._x);
	_image.setY(_position._y);
}
// the position of middle, changes position property.
void Object::setCentralPosition(scalar x, scalar y)
{
	_position = { x - _width/2.0f, y - _height/2.0f };
	_image.setX(_position._x);
	_image.setY(_position._y);
}

void Object::setWidth(scalar width)
{
	_width = width;
}
void Object::setHeight(scalar height)
{
	_height = height;
}

scalar Object::getScale()
{
	// 현재 Image 의 멤버 함수에 const가 붙어있지않음.
	return _image.getScale();
}
void Object::setScale(scalar scale)
{
	_image.setScale(scale);
}		
Image Object::getImage() const
{
	return _image;
}
TextureManager Object::getTexture() const
{
	return _texture;
}

void Object::draw(COLOR_ARGB color)
{
	_image.draw(color);
}
void Object::draw(SpriteData sd, COLOR_ARGB color)
{
	_image.draw(sd, color);
}
void Object::update(scalar frameTime)
{
	_image.update(frameTime);
}