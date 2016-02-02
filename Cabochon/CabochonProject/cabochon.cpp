#include "cabochon.h"

Cabochon::Cabochon() {}

Cabochon::~Cabochon()
{
	releaseAll();
}

void Cabochon::initialize(HWND hwnd)
{
	Game::initialize(hwnd);

	//if (!shipTexture.initialize(graphics, SHIP_IMAGE))
	//	throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing planet texture"));

	//if (!ship.initialize(graphics, 0, 0, 0, &shipTexture))
	//	throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing planet"));

	//planet.setX(GAME_WIDTH * 0.5f - planet.getWidth()*0.5f);
	//planet.setY(GAME_HEIGHT*0.5f - planet.getHeight()*0.5f);

	//ship.setX(GAME_WIDTH / 4);
	//ship.setY(GAME_HEIGHT / 4);

	//ship.setFrames(SHIP_START_FRAME, SHIP_END_FRAME);
	//ship.setCurrentFrame(SHIP_START_FRAME);
	//ship.setFrameDelay(SHIP_ANIMATION_DELAY);
	//ship.setDegrees(45.0f);

	return;
}

void Cabochon::update()
{
	//ship.update(frameTime);
}
void Cabochon::ai(){}
void Cabochon::collisions(){}
void Cabochon::render()
{
	graphics->spriteBegin();

	//ship.draw();

	graphics->spriteEnd();
}
void Cabochon::releaseAll()
{
	//shipTexture.onLostDevice();
	Game::releaseAll();
	return;
}
void Cabochon::resetAll()
{
	//shipTexture.onResetDevice();
	Game::resetAll();
	return;
}