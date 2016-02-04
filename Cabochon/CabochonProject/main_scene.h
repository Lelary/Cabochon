// 2016. 2. 3.

#include "scene.h"

namespace frameworks
{
	class MainScene
		:public Scene
	{
	public:
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