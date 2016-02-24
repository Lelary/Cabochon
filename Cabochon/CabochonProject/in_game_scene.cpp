//2016. 2. 4

#include "in_game_scene.h"
#include "cabochon_constants.h"
#include "marble_control.h"
using mathematics::Angle;
using components::ShootedMarble;
using controls::BoardState;
using controls::MarbleColorOn;
using controls::SteeringWheelControl;
using scenes::InGameScene;
using scenes::TextureList;

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
	
	// Image, Text
	_backGround.initialize(&_graphics, 0, 0, 0, _textureList.getTexture(TextureList::TextureName::BackGroundMountain));
	_debugText.initialize(&_graphics, 20, false, false, cabochon_constants::FONT);
	_errorText.initialize(&_graphics, 20, false, false, cabochon_constants::FONT);
	
	// wheelControl
	_wheelControl.loadTextures(_textureList);

	// marbleControl random 한 board map 을 생성.
	_marbleControl.getMarbleBoard().makeRandomBoard();
	_marbleControl.getMarbleBoard().loadTextures(_textureList);

	// wheelControl의 Marble
	_wheelControl.getMarbleCurrent()->loadLayers(_textureList);
	_wheelControl.getMarbleNext()->loadLayers(_textureList);

	// board map 을 기준으로 marbleNext, marbleCurrent 의 색상을 결정.
	MarbleColorOn colorOn = _marbleControl.getExistColors();
	colorOn.bitData.None = false;
	_wheelControl.setMarbleNext(MarbleGenerator::getRandomMarbleColor(colorOn));
	_wheelControl.setMarbleCurrent(MarbleGenerator::getRandomMarbleColor(colorOn));

	_started = true;
}
void InGameScene::update(float frameTime)
{
	//----------------------------------------------------------
	// BoardState::Play 일 떄만
	//----------------------------------------------------------

	if (getBoardState() != BoardState::Play)
		return;

	//----------------------------------------------------------
	// Scene이 가진 Control 객체 들에 대한 업데이트.
	//----------------------------------------------------------
	_wheelControl.update(frameTime);
	_marbleControl.update(frameTime);

	//----------------------------------------------------------
	// MarbleCurrent 를 Shooting함.
	//----------------------------------------------------------
	// 스페이스 바를 눌렀고, 현재 발사된 marble이 없을 때.
	if (_input.wasKeyPressed(VK_SPACE) && ! _marbleControl.isShooting())
	{
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
	}
	else if (_input.isKeyDown(VK_LEFT) && _input.isKeyDown(VK_RIGHT))
	{
		// 아무것도안함
	}
	else if (_input.isKeyDown(VK_LEFT))
	{
		// Wheel 회전.
		_wheelControl.rotateLeft(frameTime);
	}
	else if (_input.isKeyDown(VK_RIGHT))
	{
		// Wheel 회전.
		_wheelControl.rotateRight(frameTime);
	}

	//----------------------------------------------------------
	// Debug Message Setting
	//----------------------------------------------------------

	static float x = -1, y = -1;
	if (_marbleControl.getShootedMarble() != nullptr)
	{
		x = _marbleControl.getShootedMarble()->getCentralPosition().x;
		y = _marbleControl.getShootedMarble()->getCentralPosition().y;
	}

	if (mathematics::IntPosition{ x, y } == cabochon_constants::NO_POSITION)
		return;

	_debugMessage =
		"\n Index Row: "
		+ std::to_string(_marbleControl.getMarbleBoard().positionToRowIndex(y))
		+ "\n Index Column: "
		+ std::to_string(_marbleControl.getMarbleBoard().positionToColumnIndex(x, _marbleControl.getMarbleBoard().getRowType(y)));

}
void InGameScene::lateUpdate(float frameTime)
{
	//----------------------------------------------------------
	// BoardState::Play 이외의 상태에 대한 처리.
	//----------------------------------------------------------
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

	// 게임 클리어. 지금은 딱히 할 게 없어서 메인씬으로 돌려 보냄.
	else if (getBoardState() == BoardState::GameClear)
		_nextScene = SceneName::MainScene;

	// 게임 오버. 지금은 딱히 할 게 없어서 메인씬으로 돌려 보냄.
	else if (getBoardState() == BoardState::GameOver)
		_nextScene = SceneName::MainScene;
	 
	//----------------------------------------------------------
	// 현재 상태에 따른 계산 수행.
	//----------------------------------------------------------
	if (getBoardState() == BoardState::Play)
	{
		// 현재 shooting 중 일 때,
		if (_marbleControl.isShooting())
		{
			_marbleControl.attach(_marbleControl.getShootedMarble());
		}
		// shooting 된 marble이 방금 attach 되었을 때, 
		// 부가효과 ( marble smach ) 확인, 처리.
		if (_marbleControl.hasJustAttached())
		{
			// 애니메이션과, 카운트가 필요하다.
			if(_marbleControl.smash())
				_marbleControl.drop();
		}

		// drop 오류 있음.



	}
}
void InGameScene::render()
{
	_backGround.draw();
	_wheelControl.render();
	_marbleControl.render();

	_debugText.print(_debugMessage, 100, 100);
	_errorText.print(_errorMessage, 100, 300);
}

void InGameScene::releaseAll()
{
	_errorText.onLostDevice();
	_debugText.onLostDevice();
}

void InGameScene::resetAll()
{
	_debugText.onResetDevice();
	_errorText.onResetDevice();
}

BoardState InGameScene::getBoardState() const
{
	return _marbleControl.getMarbleBoard().getBoardState();
}

SteeringWheelControl& InGameScene::getSteeringWheelControl()
{
	return _wheelControl;
}