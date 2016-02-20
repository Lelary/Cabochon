// 2016. 2. 2.

#ifndef _CABOCHON_H
#define _CABOCHON_H
#define WIN32_LEAN_AND_MEAN
#include "dx9_game_engine\game.h"
#include "scene.h"
#include "main_scene.h"
#include "in_game_scene.h"
#include "texture_list.h"

class Cabochon : public Game
{
private:
	// 게임 아이템
	scenes::Scene* _currentScene;
	void changeScene(scenes::SceneName newSceneName);

	scenes::TextureList _textureList;

	//TextureManager startButtonTexture;

	//std::vector<TextureManager> textures;

public:

	Cabochon();
	virtual ~Cabochon();

	void initialize(HWND hwnd);
	void update();
	void ai();
	void collisions();
	void render();

	// 그래픽 디바이스가 로스트 상태가 됐을 떄 호출됨. 예약된 모든 비디오 메모리를 해제하고 그래픽 디바이스를 리셋한다.
	// Texture의 onLostDevice() 호출.
	void releaseAll();

	// 모든 표면을 재생성 하고 모든 개체를 리셋한다.
	// Texture의 onResetDevice() 호출.
	void resetAll();
};

#endif