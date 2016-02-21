//2016. 2. 4

#include "in_game_scene.h"
#include "cabochon_constants.h"
#include "marble_control.h"
using mathematics::Angle;
using components::ShootedMarble;
using controls::BoardState;
using controls::MarbleColorOn;
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
	_text.initialize(&_graphics, 20, false, false, cabochon_constants::FONT);
	_text2.initialize(&_graphics, 20, false, false, cabochon_constants::FONT);
	
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

	// ���� shooting �� �� ��,
	if (_marbleControl.isShooting())
	{
		_marbleControl.attach(_marbleControl.getShootedMarble());
	}
	// shooting �� marble�� ��� attach �Ǿ��� ��, 
	// �ΰ�ȿ�� ( marble smach ) Ȯ��, ó��.
	if (_marbleControl.hasJustAttached())
	{
		_marbleControl.smash();
	}

	// smash() �� marble �� ���� ��, 
	// �ΰ�ȿ�� ( ceiling���� ������ ���������� ���� drop() ó��.
	// ���ۼ�.
}
void InGameScene::render()
{
	_backGround.draw();
	_wheelControl.render();
	_marbleControl.render();

	static float x=-1, y=-1;
	if (_marbleControl.getShootedMarble() != nullptr)
	{
		x = _marbleControl.getShootedMarble()->getCentralPosition().x;
		y = _marbleControl.getShootedMarble()->getCentralPosition().y;
	}
	_text2.print(
	"\n Index Row: "
	+ std::to_string(_marbleControl.getMarbleBoard().positionToRowIndex(y))
	+ "\n Index Column: "
	+ std::to_string(_marbleControl.getMarbleBoard().positionToColumnIndex(x, _marbleControl.getMarbleBoard().getRowType(y)))
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