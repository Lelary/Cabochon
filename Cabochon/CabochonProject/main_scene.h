// 2016. 2. 3.

#include "scene.h"

namespace frameworks
{
	class MainScene
		:public Scene
	{
	private:
		const char* START_BUTTON_IMAGE = "images\\start_button.png";
		const char* EXIT_BUTTON_IMAGE = "images\\exit_button.png";

		TextureManager startButtonTexture;
		TextureManager exitButtonTexture;

		Image startButton;
		Image exitButton;

	public:
		MainScene(Graphics* graphics) :Scene(graphics){}

		virtual void start();
		virtual void update();
		virtual void lateUpdate();
		virtual void render();

		// �׷��� ����̽��� �ν�Ʈ ���°� ���� �� ȣ���. ����� ��� ���� �޸𸮸� �����ϰ� �׷��� ����̽��� �����Ѵ�.
		// Texture�� onLostDevice() ȣ��.
		virtual void releaseAll();

		// ��� ǥ���� ����� �ϰ� ��� ��ü�� �����Ѵ�.
		// Texture�� onResetDevice() ȣ��.
		virtual void resetAll();
	};
}