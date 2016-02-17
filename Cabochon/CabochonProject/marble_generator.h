#ifndef _MARBLE_GENERATOR_H
#define _MARBLE_GENERATOR_H

#include "controls.h"
#include "components.h"
#include "marble.h"
#include "control.h"
#include "texture_list.h"
#include <memory>
namespace controls
{
	using components::marble_ptr;
	using components::Marble;
	using frameworks::TextureList;
	/*
	2016. 1. 18.
	색깔 관련 코드는 나중에 추가.
	*/
	class MarbleGenerator
		:public Control
	{
	private:
	public:
		MarbleGenerator()=delete;
		MarbleGenerator(const MarbleGenerator& rhs)=delete;
		virtual ~MarbleGenerator();
		MarbleGenerator& operator=(const MarbleGenerator& rhs) = delete;

		/*
		2016. 1. 18.
		1. 구슬 쏠때,
		2. 맵 생성
		*/
		static marble_ptr makeMarble();
		static marble_ptr loadTexture(marble_ptr marble, TextureList& textureList);
		
		// pure virtual function
		// nothing to do.
		virtual void render();
		virtual void update(float frameTime);
	};


}


#endif //_MARBLE_GENERATOR_H