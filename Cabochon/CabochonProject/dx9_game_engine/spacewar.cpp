/*
// 2016. 1. 30.
// Reference : "2D Game Programming" , Charles Kelly, 2011
// 위 Reference의 코드를 타이핑함. Ch 4.

// 이 클래스는 Game 의 Derived class로, 차후 삭제됨. (실사용 클래스로 교체).

#include "spacewar.h"

Spacewar::Spacewar() {}

Spacewar::~Spacewar()
{
	releaseAll();
}

void Spacewar::initialize(HWND hwnd)
{
	Game::initialize(hwnd);

	// 성운 텍스처
	if (!nebulaTexture.initialize(graphics, NEBULA_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing nebula texture"));

	// 행성 텍스처
	if (!planetTexture.initialize(graphics, PLANET_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing planet texture"));

	// 우주선 텍스처
	if (!shipTexture.initialize(graphics, SHIP_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing planet texture"));

	// 성운
	if (!nebula.initialize(graphics, 0, 0, 0, &nebulaTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing nebula"));

	// 행성
	if (!planet.initialize(graphics, 0, 0, 0, &planetTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing planet"));

	// 우주선
	if (!ship.initialize(graphics, 0, 0, 0, &shipTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing planet"));

	// 행성 배치.
	planet.setX(GAME_WIDTH * 0.5f - planet.getWidth()*0.5f);
	planet.setY(GAME_HEIGHT*0.5f - planet.getHeight()*0.5f);

	// 행성의 왼쪽 상단에서 시작한다.
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