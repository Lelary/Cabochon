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
	���� ���� �ڵ�� ���߿� �߰�.
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
		1. ���� ��,
		2. �� ����
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