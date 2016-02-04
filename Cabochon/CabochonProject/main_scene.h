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

		// 그래픽 디바이스가 로스트 상태가 됐을 떄 호출됨. 예약된 모든 비디오 메모리를 해제하고 그래픽 디바이스를 리셋한다.
		// Texture의 onLostDevice() 호출.
		virtual void releaseAll();

		// 모든 표면을 재생성 하고 모든 개체를 리셋한다.
		// Texture의 onResetDevice() 호출.
		virtual void resetAll();
	};
}