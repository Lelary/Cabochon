#ifndef _SCENE_H
#define _SCENE_H

#include "frameworks.h"

/*
	2016. 2. 2.
	dx9_game_engine �� Game class�� 
	controls ���� �����.
*/
namespace frameworks
{
	class Scene
	{		
		virtual void start() = 0;
		virtual void update() = 0;
		virtual void lateUpdate() = 0;
		virtual void render() = 0;
	};
}

#endif