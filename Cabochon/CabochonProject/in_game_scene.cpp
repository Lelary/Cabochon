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
void InGameScene::update(float frameTime)
{
	//----------------------------------------------------------
	// BoardState::Play �� ����
	//----------------------------------------------------------

	if (getBoardState() != BoardState::Play)
		return;

	//----------------------------------------------------------
	// Scene�� ���� Control ��ü �鿡 ���� ������Ʈ.
	//----------------------------------------------------------
	_wheelControl.update(frameTime);
	_marbleControl.update(frameTime);

	//----------------------------------------------------------
	// MarbleCurrent �� Shooting��.
	//----------------------------------------------------------
	// �����̽� �ٸ� ������, ���� �߻�� marble�� ���� ��.
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
		// �ƹ��͵�����
	}
	else if (_input.isKeyDown(VK_LEFT))
	{
		// Wheel ȸ��.
		_wheelControl.rotateLeft(frameTime);
	}
	else if (_input.isKeyDown(VK_RIGHT))
	{
		// Wheel ȸ��.
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
	// BoardState::Play �̿��� ���¿� ���� ó��.
	//----------------------------------------------------------
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

	// ���� Ŭ����. ������ ���� �� �� ��� ���ξ����� ���� ����.
	else if (getBoardState() == BoardState::GameClear)
		_nextScene = SceneName::MainScene;

	// ���� ����. ������ ���� �� �� ��� ���ξ����� ���� ����.
	else if (getBoardState() == BoardState::GameOver)
		_nextScene = SceneName::MainScene;
	 
	//----------------------------------------------------------
	// ���� ���¿� ���� ��� ����.
	//----------------------------------------------------------
	if (getBoardState() == BoardState::Play)
	{
		// ���� shooting �� �� ��,
		if (_marbleControl.isShooting())
		{
			_marbleControl.attach(_marbleControl.getShootedMarble());
		}
		// shooting �� marble�� ��� attach �Ǿ��� ��, 
		// �ΰ�ȿ�� ( marble smach ) Ȯ��, ó��.
		if (_marbleControl.hasJustAttached())
		{
			// �ִϸ��̼ǰ�, ī��Ʈ�� �ʿ��ϴ�.
			if(_marbleControl.smash())
				_marbleControl.drop();
		}

		// drop ���� ����.



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