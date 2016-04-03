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

	// marbleControl random �� board map �� ����.
	_marbleControl.getMarbleBoard().makeRandomBoard();
	_marbleControl.getMarbleBoard().loadTextures(_textureList);

	// wheelControl�� Marble
	_wheelControl.getMarbleCurrent()->loadLayers(_textureList);
	_wheelControl.getMarbleNext()->loadLayers(_textureList);

	// board map �� �������� marbleNext, marbleCurrent �� ������ ����.
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
	// �����̽� �ٸ� ������, ���� �߻�� marble�� ����, ��ݺ����� marble�� ���� ��
	// MarbleCurrent �� Shooting��.
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
		// �ƹ��͵�����
	}
	else if (_input.isKeyDown(VK_LEFT))	{
		_wheelControl.rotateLeft(frameTime);		// Wheel ȸ��.
	}
	else if (_input.isKeyDown(VK_RIGHT)) {
		_wheelControl.rotateRight(frameTime);		// Wheel ȸ��.
	}
}
void InGameScene::updatePlayState(float frameTime)
{
	if (getBoardState() != BoardState::Play)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error in updatePlayState()"));

	//----------------------------------------------------------
	// Ű�Է� ó��.
	//----------------------------------------------------------
	keyInPlayState(frameTime);
	//----------------------------------------------------------
	// ���� ���¿� ���� ��� ����.
	// �Լ� ȣ�� ������ ���ǹ���.
	// 2016. 3. 8
	// ���� ���߿� ������ if���� ��ȣ�� ������ �����Ѵٸ�
	// removeRowZero()���� justAttached�� ������Ʈ �ϵ��� �����ؾ���.
	//----------------------------------------------------------
	// ���� shooting �� �� ��,
	if (_marbleControl.isShooting())
	{
		if (_marbleControl.attach(_marbleControl.getShootedMarble()))
		{
			// shooting �� marble�� ��� attach �Ǿ��� ��, 
			// �ΰ�ȿ�� ( marble smach ) ���� Ȯ��, ó��.
			if (_marbleControl.hasJustAttached())
			{
				// �ִϸ��̼ǰ�, ī��Ʈ�� �ʿ��ϴ�.
				if (_marbleControl.smash())
					_marbleControl.drop();	// drop ���� ����.

				// gameOver �� �����ߴ��� �˻�.
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
		// �ε������� ���°� ���� �� ����.
		break;
	case BoardState::Ready:
		// �ϴ��� ����.
		// Play ���·� �̵��ϱ����� ������ �������� �κ� (�ִϸ��̼ǵ�) �̰��� �ۼ�.
		_marbleControl.getMarbleBoard().setBoardState(BoardState::Play);
		break;
	case BoardState::Play:
		updatePlayState(frameTime);			// �ʹ� �� �̵�.
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
		// Scene�� ���� Control ��ü �鿡 ���� ������Ʈ.
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