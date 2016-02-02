/*
// 2016. 1. 30.
// Reference : "2D Game Programming" , Charles Kelly, 2011
// �� Reference�� �ڵ带 Ÿ������. Ch 4.

// �� Ŭ������ Game �� Derived class��, ���� ������. (�ǻ�� Ŭ������ ��ü).

#include "spacewar.h"

Spacewar::Spacewar() {}

Spacewar::~Spacewar()
{
	releaseAll();
}

void Spacewar::initialize(HWND hwnd)
{
	Game::initialize(hwnd);

	// ���� �ؽ�ó
	if (!nebulaTexture.initialize(graphics, NEBULA_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing nebula texture"));

	// �༺ �ؽ�ó
	if (!planetTexture.initialize(graphics, PLANET_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing planet texture"));

	// ���ּ� �ؽ�ó
	if (!shipTexture.initialize(graphics, SHIP_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing planet texture"));

	// ����
	if (!nebula.initialize(graphics, 0, 0, 0, &nebulaTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing nebula"));

	// �༺
	if (!planet.initialize(graphics, 0, 0, 0, &planetTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing planet"));

	// ���ּ�
	if (!ship.initialize(graphics, 0, 0, 0, &shipTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing planet"));

	// �༺ ��ġ.
	planet.setX(GAME_WIDTH * 0.5f - planet.getWidth()*0.5f);
	planet.setY(GAME_HEIGHT*0.5f - planet.getHeight()*0.5f);

	// �༺�� ���� ��ܿ��� �����Ѵ�.
	ship.setX(GAME_WIDTH / 4);
	ship.setY(GAME_HEIGHT / 4);

	ship.setFrames(SHIP_START_FRAME, SHIP_END_FRAME);
	ship.setCurrentFrame(SHIP_START_FRAME);
	ship.setFrameDelay(SHIP_ANIMATION_DELAY);
	ship.setDegrees(45.0f);

	return;
}

void Spacewar::update()
{
	ship.update(frameTime);
}
void Spacewar::ai(){}
void Spacewar::collisions(){}
void Spacewar::render()
{
	graphics->spriteBegin();

	nebula.draw();
	planet.draw();
	ship.draw();

	graphics->spriteEnd();
}
void Spacewar::releaseAll()
{
	planetTexture.onLostDevice();
	nebulaTexture.onLostDevice();
	shipTexture.onLostDevice();
	Game::releaseAll();
	return;
}
void Spacewar::resetAll()
{
	nebulaTexture.onResetDevice();
	planetTexture.onResetDevice();
	shipTexture.onResetDevice();
	Game::resetAll();
	return;
}

*/