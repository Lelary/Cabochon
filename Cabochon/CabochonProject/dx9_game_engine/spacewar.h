/*
// 2016. 1. 30.
// Reference : "2D Game Programming" , Charles Kelly, 2011
// �� Reference�� �ڵ带 Ÿ������. Ch 4.

// �� Ŭ������ Game �� Derived class��, ���� ������. (�ǻ�� Ŭ������ ��ü).

#ifndef _SPACEWAR_H
#define _SPACEWAR_H
#define WIN32_LEAN_AND_MEAN
#include "game.h"
#include "texture_manager.h"
#include "image.h"

const char NEBULA_IMAGE[] = "orion.jpg";
const char PLANET_IMAGE[] = "planet.png";
const char SHIP_IMAGE[] = "textures.png";

const int   SHIP_START_FRAME = 0;      // ship1 starts at frame 0
const int   SHIP_END_FRAME = 3;        // ship1 animation frames 0,1,2,3
const float SHIP_ANIMATION_DELAY = 0.2f;    // time between frames

class Spacewar : public Game
{
private:
	// ���� ������

	TextureManager nebulaTexture;
	TextureManager planetTexture;
	TextureManager shipTexture;
	Image planet;
	Image nebula;
	Image ship;

public:

	Spacewar();
	virtual~Spacewar();

	void initialize(HWND hwnd);
	void update();
	void ai();
	void collisions();
	void render();
	void releaseAll();
	void resetAll();
};

#endif
*/