// 2016. 2. 2.

#ifndef _CABOCHON_H
#define _CABOCHON_H
#define WIN32_LEAN_AND_MEAN
#include "dx9_game_engine\game.h"
#include "dx9_game_engine\texture_manager.h"
#include "dx9_game_engine\image.h"

class Cabochon : public Game
{
private:
	// 게임 아이템


public:

	Cabochon();
	virtual ~Cabochon();

	void initialize(HWND hwnd);
	void update();
	void ai();
	void collisions();
	void render();
	void releaseAll();
	void resetAll();
};

#endif