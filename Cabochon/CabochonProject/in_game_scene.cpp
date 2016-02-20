//2016. 2. 4

#include "in_game_scene.h"
#include "marble_control.h"
using frameworks::InGameScene;
using frameworks::TextureList;
using components::ShootedMarble;
using controls::BoardState;
using controls::MarbleColorOn; 
using mathematics::Angle;
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
	_text2.initialize(&_graphics, 20, false, false, frameworks::default_settings::FONT);
	_wheelControl.loadTextures(_textureList);

	_marbleControl.getMarbleBoard().makeRandomBoard();
	_marbleControl.getMarbleBoard().loadTextures(_textureList);

	_wheelControl.getMarbleCurrent()->loadLayers(_textureList);
	_wheelControl.getMarbleNext()->loadLayers(_textureList);

	MarbleColorOn colorOn = _marbleControl.getExistColors();
	colorOn.bitData.None = false;
	_wheelControl.setMarbleNext(MarbleGenerator::getRandomMarbleColor(colorOn));
	_wheelControl.setMarbleCurrent(MarbleGenerator::getRandomMarbleColor(colorOn));

	_started = true;
}
void InGameScene::update(float frameTime)
{
	if (getBoardState() != BoardState::Play)
		return;

	_wheelControl.update(frameTime);
	_marbleControl.update(frameTime);

	if (_input.wasKeyPressed(VK_SPACE) && ! _marbleControl.isShooting())
	{
		// _nowShooting = true
		// while Animation
		// or now Flying... whatever


		// MarbleCurrent -> ShootedMarble
		if (_wheelControl.getMarbleCurrent() != nullptr)
		{
			_marbleControl.setShootedMarble(
				_wheelControl.getMarbleCurrent()->getColor(), 
				_wheelControl.getMarbleCurrent()->getCentralPosition(),
				ShootedMarble::getDefaultSpeed(), 
				_wheelControl.getDegree(),
				_textureList);
		}
		// MarbleNext -> MarbleCurrent
		if (_wheelControl.getMarbleNext() != nullptr)
		{
			_wheelControl.setMarbleCurrent(_wheelControl.getMarbleNext()->getColor());

		}
		// New Color -> MarbleNext
		MarbleColorOn colorOn = _marbleControl.getExistColors();
		colorOn.bitData.None = false;
		_wheelControl.setMarbleNext(MarbleGenerator::getRandomMarbleColor(colorOn));	
		
		//---------------------
	}
	else if (_input.isKeyDown(VK_LEFT) && _input.isKeyDown(VK_RIGHT))
	{
		// 아무것도안함
	}
	else if (_input.isKeyDown(VK_LEFT))
	{
		_wheelControl.rotateLeft(frameTime);
	}
	else if (_input.isKeyDown(VK_RIGHT))
	{
		_wheelControl.rotateRight(frameTime);
	}
}
void InGameScene::lateUpdate(float frameTime)
{
	// 로딩문구를 띄우는게 좋을 것 같다.
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

	// 지금은 딱히 할 게 없어서 메인씬으로 돌려 보냄.
	else if (getBoardState() == BoardState::GameClear)
		_nextScene = SceneName::MainScene;

	// 지금은 딱히 할 게 없어서 메인씬으로 돌려 보냄.
	else if (getBoardState() == BoardState::GameOver)
		_nextScene = SceneName::MainScene;

	//attach, break
	if (_marbleControl.isShooting())
	{
		if (_marbleControl.attach(_marbleControl.getShootedMarble()))
		{
			// dummy
			int i = 0;
			i++;
			i++;
		}
	}








}
void InGameScene::render()
{
	_backGround.draw();
	_wheelControl.render();
	_marbleControl.render();
	if (_marbleControl.getShootedMarble()!=nullptr)
		_text2.print("\nx: "
		+ std::to_string(_marbleControl.getShootedMarble()->getCentralPosition()._x)
		+ "\ny: "
		+ std::to_string(_marbleControl.getShootedMarble()->getCentralPosition()._y)
		+ "\nVx: "
		+ std::to_string(_marbleControl.getShootedMarble()->getVelocity()._x)
		+ "\nVy: "
		+ std::to_string(_marbleControl.getShootedMarble()->getVelocity()._y)
		+ "\nDegree: "
		+ std::to_string(_wheelControl.getDegree())
		, 100, 200);

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