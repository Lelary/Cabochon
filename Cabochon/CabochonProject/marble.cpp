#include "marble.h"
#include "temporary.h"
#include "texture_list.h"
#include "dx9_game_engine\graphics.h"
using components::Marble;
using mathematics::scalar;
using mathematics::IntPosition;
using frameworks::TextureList;
using components::Layer;
using components::MarbleColor;

Marble::Marble(const IntPosition& gridPosition, MarbleColor color)
	: _gridPosition(gridPosition), _color(color)
{
	setWidth(marbleWidth);
	setHeight(marbleHeight);
}

Marble::Marble(MarbleColor color)
	: Marble({ noPosition, noPosition }, color)
{
}

Marble::Marble(const Marble& rhs)
	:Object(rhs), _gridPosition(rhs._gridPosition), _color(rhs._color)
{
	setWidth(marbleWidth);
	setHeight(marbleHeight);
	/*
	2016. 1. 15
	���� �ڱ� ���� ó�� �ʿ� ����
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
	// 0 ~ 7
	int width = 128;
	int height = 128;
	int row = 0;
	int rows = 7;
	int cols = 8;		

	for (row = 0; row < rows; row++)
	{
		_layers.push_back(Layer());
		_layers.back().initialize(textureList.getGraphics(), width, height, cols, textureList.getTexture(TextureList::TextureName::Marbles));
		_layers.back().setFrames(row*cols, row*cols + cols - 1);
		_layers.back().setCurrentFrame(row*cols);
		_layers.back().setFrameDelay(0.1);
		_layers.back().setLoop(true);
		_layers.back().setScaleFromWidth(1.0f, getWidth());
		_layers.back().setDistanceFromCenter(getPosition(), getWidth(), getHeight(), { 0, 0 });
		_layers.back().setVisible(false);
	}
	// �ʱ�ȭ ���ѻ���.
	_layers.at((int)MarbleColor::Transparent).setVisible(true);
	_color = MarbleColor::Transparent;
	adjustLayersPosition();
}

MarbleColor Marble::getColor()
{
	return _color;
}
MarbleColor Marble::setColor(MarbleColor color)
{
	_layers.at((int)_color).setVisible(false);
	_color = color;
	_layers.at((int)_color).setVisible(true);
}
void Marble::rotate(scalar degree)
{
	for (Layer& layer : _layers)
		layer.setDegrees(layer.getDegrees()+degree);
}

void Marble::setGridPosition(IntPosition gridPosition)
{
	_gridPosition = gridPosition;
}
IntPosition Marble::getGridPosition() const
{
	return _gridPosition;
}

void Marble::draw()
{
	for (Layer layer : _layers)
		layer.draw();
}

void Marble::update(float frameTime)
{
	for (Layer& layer : _layers)
		layer.update(frameTime);
}

bool Marble::circularHitTest(const Marble& anotherMarble) const
{
	return circularHitTest(*this, anotherMarble);
}
bool Marble::circularHitTest(const Marble& marble1, const Marble& marble2)
{
	/* 
		2016. 1. 22.
		Marble ��ü�� Width = Height = 2*radius
		����� radius ��������� �����Ƿ� �̸� �̿��Ѵ�.
	*/
	scalar radius1 = marble1.getWidth() / 2.0f;
	scalar radius2 = marble2.getWidth() / 2.0f;

	scalar distanceSquare =
		powf((marble2.getCentralPosition()._x - marble1.getCentralPosition()._x), 2.0f)
		-
		powf((marble2.getCentralPosition()._y - marble1.getCentralPosition()._y), 2.0f);
	
	//���������� �� ������.
	if (powf(radius1 + radius2, 2.0f) < distanceSquare)
		return false;
	else
		return true;
}
