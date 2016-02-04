// 2016. 2. 2.

#ifndef _CABOCHON_H
#define _CABOCHON_H
#define WIN32_LEAN_AND_MEAN
#include "dx9_game_engine\game.h"
#include "dx9_game_engine\texture_manager.h"
#include "dx9_game_engine\image.h"
#include "scene.h"
#include "main_scene.h"
#include "in_game_scene.h"

class Cabochon : public Game
{
private:
	// 게임 아이템
	frameworks::Scene* _currentScene;
	void changeScene(frameworks::SceneName newSceneName);

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