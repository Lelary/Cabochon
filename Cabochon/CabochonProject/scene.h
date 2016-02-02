#ifndef _SCENE_H
#define _SCENE_H

#include "frameworks.h"

/*
	2016. 2. 2.
	dx9_game_engine 의 Game class와 
	controls 과의 연결고리.
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