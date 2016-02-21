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
	scenes::TextureList _textureList;
	TextDX _text;
	std::string _errorMessage;
	void changeScene(scenes::SceneName newSceneName);

public:
	Cabochon();
	virtual ~Cabochon();

	virtual void initialize(HWND hwnd);
	virtual void update();
	virtual void ai();
	virtual void collisions();
	virtual void render();

	// �׷��� ����̽��� �ν�Ʈ ���°� ���� �� ȣ���. ����� ��� ���� �޸𸮸� �����ϰ� �׷��� ����̽��� �����Ѵ�.
	// Texture�� onLostDevice() ȣ��.
	virtual void releaseAll();

	// ��� ǥ���� ����� �ϰ� ��� ��ü�� �����Ѵ�.
	// Texture�� onResetDevice() ȣ��.
	virtual void resetAll();
};

#endif