#include "marble.h"
#include "temporary.h"
#include "texture_list.h"
#include "dx9_game_engine\graphics.h"
using components::Marble;
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
	int x, y;
	x = 0;
	y = 0;
	_layers[0].image.initialize(textureList.getGraphics(), 128, 128, 8, textureList.getTexture(TextureList::TextureName::Marbles));
	_layers[0].image.setFrames(0, 0);
	_layers[0].image.setCurrentFrame(0);
	_layers[0].image.setLoop(false);
	_layers[0].distance = { 0, 0 };

	_layers[1].image.initialize(textureList.getGraphics(), 128, 128, 8, textureList.getTexture(TextureList::TextureName::Marbles));
	_layers[1].image.setFrames(8, 15);
	_layers[1].image.setCurrentFrame(8);
	_layers[1].image.setFrameDelay(1);
	_layers[1].image.setLoop(true);
	_layers[1].distance = { 0, 0 };


	_layers[2].image.initialize(textureList.getGraphics(), 128, 128, 8, textureList.getTexture(TextureList::TextureName::Marbles));
	_layers[2].image.setFrames(16, 16);
	_layers[2].image.setCurrentFrame(16);
	_layers[2].image.setLoop(false);
	_layers[2].distance = { 0, 0 };

	adjustLayersPosition();
}

void Marble::draw()
{
	_layers[0].image.draw(graphicsNS::ORANGE);
	_layers[1].image.draw();
	_layers[2].image.draw();
}

void Marble::update()
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
