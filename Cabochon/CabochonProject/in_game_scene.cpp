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
	const float gameOverLineY = 448.0f;

	if (_started)
		return;

	Scene::start();
	
	// Image, Text
	_backGround.initialize(&_graphics, 0, 0, 0, _textureList.getTexture(TextureList::TextureName::BackGroundMountain));
	_gameOverLine.initialize(&_graphics, 0, 0, 0, _textureList.getTexture(TextureList::TextureName::GameOverLine));
	_gameOverMessage.initialize(&_graphics, 0, 0, 0, _textureList.getTexture(TextureList::TextureName::GameOverMessage));
	_gameClearMessage.initialize(&_graphics, 0, 0, 0, _textureList.getTexture(TextureList::TextureName::GameClearMessage));
	_debugText.initialize(&_graphics, 20, false, false, cabochon_constants::FONT);
	_errorText.initialize(&_graphics, 20, false, false, cabochon_constants::FONT);

	_gameOverLine.setX(0);
	_gameOverLine.setY(gameOverLineY);
	_gameOverMessage.setVisible(false);	
	_gameClearMessage.setVisible(false);

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
void InGameScene::keyInPlayState(float frameTime)
{
	if (getBoardState() != BoardState::Play)
		return;
	
	bool shooted = false;

	if (_marbleControl.getMarbleBoard().animationFinished())
		shooted = shootMarble();

	if(!shooted)
		rotateWheel(frameTime);
}
bool InGameScene::shootMarble()
{
	// 스페이스 바를 눌렀고, 현재 발사된 marble이 없고, 방금부착한 marble이 없을 때
	// MarbleCurrent 를 Shooting함.
	if (_input.wasKeyPressed(VK_SPACE) && !_marbleControl.isShooting() && !_marbleControl.hasJustAttached())
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

		return true;
	}
	return false;
}
void InGameScene::rotateWheel(float frameTime)
{
	if (_input.isKeyDown(VK_LEFT) && _input.isKeyDown(VK_RIGHT)) {
		// 아무것도안함
	}
	else if (_input.isKeyDown(VK_LEFT))	{
		_wheelControl.rotateLeft(frameTime);		// Wheel 회전.
	}
	else if (_input.isKeyDown(VK_RIGHT)) {
		_wheelControl.rotateRight(frameTime);		// Wheel 회전.
	}
}
void InGameScene::updatePlayState(float frameTime)
{
	if (getBoardState() != BoardState::Play)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error in updatePlayState()"));

	//----------------------------------------------------------
	// 키입력 처리.
	//----------------------------------------------------------
	keyInPlayState(frameTime);
	//----------------------------------------------------------
	// 현재 상태에 따른 계산 수행.
	// 함수 호출 순서가 유의미함.
	// 2016. 3. 8
	// 만약 나중에 순서나 if문의 괄호의 범위를 변경한다면
	// removeRowZero()에서 justAttached을 업데이트 하도록 수정해야함.
	//----------------------------------------------------------
	// 현재 shooting 중 일 때,
	if (_marbleControl.isShooting())
	{
		if (_marbleControl.attach(_marbleControl.getShootedMarble()))
		{
			// shooting 된 marble이 방금 attach 되었을 때, 
			// 부가효과 ( marble smach ) 판정 확인, 처리.
			if (_marbleControl.hasJustAttached())
			{
				// 애니메이션과, 카운트가 필요하다.
				if (_marbleControl.smash())
					_marbleControl.drop();	// drop 오류 있음.

				// gameOver 를 유발했는지 검사.
				if (_marbleControl.getMarbleBoard().gameOver())
					return;
			}
			_marbleControl.ceilingComeDown();
		}
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
void InGameScene::update(float frameTime)
{
	switch (getBoardState())
	{	
	case BoardState::Build:
		// 로딩문구를 띄우는게 좋을 것 같다.
		break;
	case BoardState::Ready:
		// 하는일 없음.
		// Play 상태로 이동하기전에 수행할 디테일한 부분 (애니메이션등) 이곳에 작성.
		_marbleControl.getMarbleBoard().setBoardState(BoardState::Play);
		break;
	case BoardState::Play:
		updatePlayState(frameTime);			// 너무 길어서 이동.
		break;
	case BoardState::GameOver:
		_gameOverMessage.setVisible(true);
		if (_input.wasKeyPressed(VK_SPACE))	{
			_nextScene = SceneName::MainScene;
		}
		break;
	case BoardState::GameClear:
		_gameClearMessage.setVisible(true);
		if (_input.wasKeyPressed(VK_SPACE))	{
			_nextScene = SceneName::MainScene;
		}
		break;
	default:
		break;
	}
}
void InGameScene::lateUpdate(float frameTime)
{
	switch (getBoardState())
	{
	case controls::BoardState::Build:
		break;
	case controls::BoardState::Ready:
		break;
	case controls::BoardState::Play:
		//----------------------------------------------------------
		// Scene이 가진 Control 객체 들에 대한 업데이트.
		//----------------------------------------------------------
		_wheelControl.update(frameTime);
		_marbleControl.update(frameTime);
		break;
	case controls::BoardState::GameOver:
		break;
	case controls::BoardState::GameClear:
		break;
	default:
		break;
	}
	 
}
void InGameScene::render()
{
	_backGround.draw();
	_gameOverLine.draw();
	_wheelControl.render();
	_marbleControl.render(); 
	_gameOverMessage.draw();
	_gameClearMessage.draw();
#if defined(DEBUG) | defined(_DEBUG)
	_debugText.print(_debugMessage, 100, 100);
	_errorText.print(_errorMessage, 100, 300);
#endif
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