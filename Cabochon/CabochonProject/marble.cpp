#include "marble.h"
#include "temporary.h"
#include "texture_list.h"
#include "dx9_game_engine\graphics.h"
using components::Marble;
using mathematics::scalar;
using mathematics::IntPosition;
using temporary::maxX;
using temporary::maxY;
using frameworks::TextureList;

Marble::Marble()
	:_gridPosition({ noPosition, noPosition })
{
	/*
	2016. 1. 15
	nothing to do.
	*/
}

Marble::Marble(const IntPosition& gridPosition)
	: _gridPosition(gridPosition)
{ 
	/*
	2016. 1. 15
	nothing to do.
	*/
}

Marble::Marble(const Marble& rhs)
	:Object(rhs), _gridPosition(rhs._gridPosition)
{
	/*
	2016. 1. 15
	현재 자기 대입 처리 필요 없음
	*/
}

Marble::~Marble()
{
	/*
	2016. 1. 16
	nothing to do.
	*/
}

Marble& Marble::operator=(const Marble& rhs)
{ 
	if (&rhs == this)
		return *this;

	_gridPosition = rhs._gridPosition;
	return *this;
}
void Marble::loadLayers(TextureList& textureList)
{
	_layers.push_back(Layer());
	_layers[0].initialize(textureList.getGraphics(), 128, 128, 8, textureList.getTexture(TextureList::TextureName::Marbles));
	_layers[0].setFrames(0, 0);
	_layers[0].setCurrentFrame(0);
	_layers[0].setLoop(false);
	_layers[0].setDistance(getPosition(), { 0, 0 });

	_layers.push_back(Layer());
	_layers[1].initialize(textureList.getGraphics(), 128, 128, 8, textureList.getTexture(TextureList::TextureName::Marbles));
	_layers[1].setFrames(8, 15);
	_layers[1].setCurrentFrame(8);
	_layers[1].setFrameDelay(1);
	_layers[1].setLoop(true);
	_layers[1].setDistance(getPosition(), { 0, 0 });

	_layers.push_back(Layer());
	_layers[2].initialize(textureList.getGraphics(), 128, 128, 8, textureList.getTexture(TextureList::TextureName::Marbles));
	_layers[2].setFrames(16, 16);
	_layers[2].setCurrentFrame(16);
	_layers[2].setLoop(false);
	_layers[2].setDistance(getPosition(), { 0, 0 });

	adjustLayersPosition();
}

void Marble::draw()
{
	_layers[0].draw(graphicsNS::ORANGE);
	_layers[1].draw();
	_layers[2].draw();
}

void Marble::update(scalar frameTime)
{

}

bool Marble::circularHitTest(const Marble& anotherMarble) const
{
	return circularHitTest(*this, anotherMarble);
}
bool Marble::circularHitTest(const Marble& marble1, const Marble& marble2)
{
	/* 
		2016. 1. 22.
		Marble 객체는 Width = Height = 2*radius
		현재는 radius 멤버변수가 없으므로 이를 이용한다.
	*/
	scalar radius1 = marble1.getWidth() / 2.0f;
	scalar radius2 = marble2.getWidth() / 2.0f;

	scalar distanceSquare =
		powf((marble2.getCentralPosition()._x - marble1.getCentralPosition()._x), 2.0f)
		-
		powf((marble2.getCentralPosition()._y - marble1.getCentralPosition()._y), 2.0f);
	
	//제곱연산이 더 빠르다.
	if (powf(radius1 + radius2, 2.0f) < distanceSquare)
		return false;
	else
		return true;
}
