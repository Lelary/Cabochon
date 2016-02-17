#ifndef _MARBLE_GENERATOR_H
#define _MARBLE_GENERATOR_H

#include "controls.h"
#include "components.h"
#include "marble.h"
#include "control.h"
#include "texture_list.h"
#include <memory>
#include <random>

namespace controls
{
	using components::marble_ptr;
	using components::Marble;
	using frameworks::TextureList;
	
	struct MarbleColorBitField
	{
		unsigned char None : 1;
		unsigned char Red : 1;
		unsigned char Orange : 1;
		unsigned char Yellow : 1;
		unsigned char Green : 1;
		unsigned char Blue : 1;
		unsigned char Purple : 1;
		unsigned char Gray : 1;
	};
	union MarbleColorOn
	{
		MarbleColorBitField bitData;
		unsigned char data;
	};

	class MarbleGenerator
		:public Control
	{
	private:
		// ���α׷� ������ ���� �� �ϳ��� ����.
		//static std::mt19937 gen(std::random_device);
		static std::mt19937 gen;
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
		static int getRandomNumber();
		static marble_ptr makeMarble();
		static marble_ptr makeMarble(MarbleColor color=MarbleColor::None);
		static marble_ptr makeRandomMarble();
		static marble_ptr makeRandomMarble(MarbleColorOn colorRange);
		static marble_ptr loadTexture(marble_ptr marble, TextureList& textureList);
		
		// pure virtual function
		// nothing to do.
		virtual void render();
		virtual void update(float frameTime);
	};


}


#endif //_MARBLE_GENERATOR_H