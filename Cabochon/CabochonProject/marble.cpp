#include "marble.h"
#include "texture_list.h"
#include "dx9_game_engine\graphics.h"
#include "marble_generator.h"
using mathematics::scalar;
using mathematics::Position;
using mathematics::IntPosition;
using components::Marble;
using components::Layer;
using components::MarbleColor;
using controls::MarbleGenerator;
using scenes::TextureList;

Marble::Marble(const IntPosition& index, MarbleColor color)
	: _index(index), _color(color)
{
	setWidth(marbleWidth);
	setHeight(marbleHeight);
}

Marble::Marble(MarbleColor color)
	: Marble(NO_POSITION, color)
{
}

Marble::Marble(const Marble& rhs)
	: Object(rhs), _index(rhs._index), _color(rhs._color)
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
	
	Object::operator=(rhs);

	_color = rhs._color;
	_index = rhs._index;
	return *this;
}
void Marble::loadLayers(TextureList& textureList)
{
	const int marbleTextureWidth = 128;
	const int marbleTextureHeight = 128;
	const int rows = (int)MarbleColor::Num;
	const int cols = 8;		

	for (int row = 0; row < rows; row++)
	{
		_layers.push_back(Layer());
		_layers.back().initialize(textureList.getGraphics(), marbleTextureWidth, marbleTextureHeight, cols, textureList.getTexture(TextureList::TextureName::Marbles));
		// ���� �ִϸ��̼� �̻��.
		_layers.back().setFrames(row*cols, row*cols);

		// �ִϸ��̼� ����.
		// _layers.back().setFrames(row*cols, row*cols + cols - 1);
		_layers.back().setCurrentFrame(row*cols);
		_layers.back().setFrameDelay(0.1);
		_layers.back().setLoop(false);
		_layers.back().setAnimationComplete(true);
		_layers.back().setScaleFromWidth(1.0f, getWidth());
		_layers.back().setDistanceFromCenter(getPosition(), getWidth(), getHeight(), { 0, 0 });
		_layers.back().setVisible(false);
	}
	_layersLoaded = true;
	setColor(_color);
	adjustLayersPosition();
}

MarbleColor Marble::getColor() const
{
	return _color;
}
MarbleColor Marble::setColor(MarbleColor color)
{
	if (_color != MarbleColor::None)
		_layers.at((int)_color).setVisible(false);
	_color = color;
	if (_color != MarbleColor::None)
		_layers.at((int)_color).setVisible(true);
	return _color;
}
void Marble::rotate(scalar degree)
{
	for (Layer& layer : _layers)
		layer.setDegrees(layer.getDegrees()+degree);
}

void Marble::setIndex(IntPosition index)
{
	_index = index;
}
IntPosition Marble::getIndex() const
{
	return _index;
}

void Marble::draw()
{
	for (Layer& layer : _layers)
		layer.draw();
}

void Marble::update(float frameTime)
{
	for (Layer& layer : _layers)
		layer.update(frameTime);
}

bool Marble::circularHitTest(const Marble& anotherMarble, scalar scale) const
{
	return circularHitTest(*this, anotherMarble, scale);
}
bool Marble::circularHitTest(const Marble& marble1, const Marble& marble2, scalar scale)
{
	/* 
		2016. 1. 22.
		Marble ��ü�� Width = Height = 2*radius
		����� radius ��������� �����Ƿ� �̸� �̿��Ѵ�.
	*/
	scalar radius1 = marble1.getWidth() * scale / 2.0f;
	scalar radius2 = marble2.getWidth() * scale / 2.0f;

	scalar distanceSquare =
		powf((marble2.getCentralPosition().x - marble1.getCentralPosition().x), 2.0f)
		-
		powf((marble2.getCentralPosition().y - marble1.getCentralPosition().y), 2.0f);
	
	//���������� �� ������.
	if (powf(radius1 + radius2, 2.0f) < distanceSquare)
		return false;
	else
		return true;
}
// Marble �Ѱ��� ������� �ִϸ��̼�.
void Marble::disappearing(int progressedFrame, int totalFrame, Position position)
{
	scalar progress = static_cast<scalar>(progressedFrame) 
					/ static_cast<scalar>(totalFrame);

	// ����. �ִϸ��̼��� ���¿� ������� ����.
	if (progressedFrame >= totalFrame || progressedFrame<=0){
		setColor(MarbleColor::None);
		setPosition(position);
		adjustLayersPosition();
		return;
	}
	// �׽�Ʈ�� ��ļ���
	setPosition(position.x, position.y + progress*GAME_HEIGHT);
	adjustLayersPosition();
}