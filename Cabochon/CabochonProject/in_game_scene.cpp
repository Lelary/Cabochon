//2016. 2. 4

#include "in_game_scene.h"
using frameworks::InGameScene;
using frameworks::TextureList;
using components::ShootedMarble;
using controls::BoardState;
using controls::MarbleColorOn;
InGameScene::InGameScene(Graphics& graphics, Input& input, TextureList& textureList)
	:Scene(graphics, input, textureList)
{
	
}
InGameScene::~InGameScene()
{
	releaseAll();
}
void InGameScene::start()
{
	if (_started)
		return;

	Scene::start();

	
	_backGround.initialize(&_graphics, 0, 0, 0, _textureList.getTexture(TextureList::TextureName::BackGroundMountain));
	_text.initialize(&_graphics, 20, false, false, frameworks::default_settings::FONT);
	_wheelControl.loadTextures(_textureList);

	_marbleControl.getMarbleBoard().makeRandomBoard();
	_marbleControl.getMarbleBoard().loadTextures(_textureList);

	MarbleColorOn colorOn = _marbleControl.getExistColors();
	colorOn.bitData.None = false;
	_wheelControl.setMarbleNext(MarbleGenerator::makeRandomMarble(colorOn));
	_wheelControl.getMarbleNext()->loadLayers(_textureList);


	_started = true;
}
void InGameScene::update(float frameTime)
{
	if (getBoardState() != BoardState::Play)
		return;

	_wheelControl.update(frameTime);

	if (_input.isKeyDown(VK_LEFT) && _input.isKeyDown(VK_RIGHT))
	{
		// �ƹ��͵�����
	}
	else if (_input.isKeyDown(VK_LEFT))
	{
		_wheelControl.rotateLeft(frameTime);
	}
	else if (_input.isKeyDown(VK_RIGHT))
	{
		_wheelControl.rotateRight(frameTime);
	}
	else if (_input.isKeyDown(VK_SPACE))
	{
		if (_wheelControl.getMarbleCurrent() != nullptr)
			_marbleControl.setShootedMarble(_wheelControl.getMarbleCurrent());
		if (_wheelControl.getMarbleNext() != nullptr)
		{
			_wheelControl.setMarbleCurrent(_wheelControl.getMarbleNext());

		}
		// �μ���, Count.
		MarbleColorOn colorOn = _marbleControl.getExistColors();
		colorOn.bitData.None = false;
		_wheelControl.setMarbleNext(MarbleGenerator::makeRandomMarble(colorOn));
		_wheelControl.getMarbleNext()->loadLayers(_textureList);
		
	}
}
void InGameScene::lateUpdate(float frameTime)
{
	// �ε������� ���°� ���� �� ����.
	if (getBoardState() == BoardState::Build)
	{
		return;
	}
	else if (getBoardState() == BoardState::Ready)
	{
		//GameStart (set BoardState::Play)
		if (_input.isKeyDown(VK_SPACE))
		{
			_marbleControl.getMarbleBoard().setBoardState(BoardState::Play);
		}
	}

	// ������ ���� �� �� ��� ���ξ����� ���� ����.
	else if (getBoardState() == BoardState::GameClear)
		_nextScene = SceneName::MainScene;

	// ������ ���� �� �� ��� ���ξ����� ���� ����.
	else if (getBoardState() == BoardState::GameOver)
		_nextScene = SceneName::MainScene;


}
void InGameScene::render()
{
	_backGround.draw();
	_wheelControl.render();
	_marbleControl.render();

	switch (getBoardState())
	{
	case BoardState::Build:
		_text.print("Build", 100, 100);
		break;
	case BoardState::Ready:
		_text.print("Ready", 100, 100);
		break;
	case BoardState::Play:
		_text.print("Play", 100, 100);
		break;
	case BoardState::GameClear:
		_text.print("GameClear", 100, 100);
		break;
	case BoardState::GameOver:
		_text.print("GameOver", 100, 100);
		break;
	default:
		break;
	}

}

void InGameScene::releaseAll()
{

}

void InGameScene::resetAll()
{

}

BoardState InGameScene::getBoardState() const
{
	return _marbleControl.getMarbleBoard().getBoardState();
}