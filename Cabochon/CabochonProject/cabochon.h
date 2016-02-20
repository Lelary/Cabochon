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
	// ���� ������
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

	// �׷��� ����̽��� �ν�Ʈ ���°� ���� �� ȣ���. ����� ��� ���� �޸𸮸� �����ϰ� �׷��� ����̽��� �����Ѵ�.
	// Texture�� onLostDevice() ȣ��.
	void releaseAll();

	// ��� ǥ���� ����� �ϰ� ��� ��ü�� �����Ѵ�.
	// Texture�� onResetDevice() ȣ��.
	void resetAll();
};

#endif