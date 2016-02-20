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
	using components::MarbleColor;
	using scenes::TextureList;

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
		MarbleColorOn()
			:data(0x0000000){}
	};

	class MarbleGenerator
	{
	private:
	public:
		MarbleGenerator()=delete;
		MarbleGenerator(const MarbleGenerator& rhs)=delete;
		virtual ~MarbleGenerator();
		MarbleGenerator& operator=(const MarbleGenerator& rhs) = delete;

		/*
		2016. 1. 18.
		1. ±¸½½ ½ò¶§,
		2. ¸Ê »ý¼º
		*/
		static int getRandomNumber(int min, int max);

		static MarbleColor getRandomMarbleColor();
		static MarbleColor getRandomMarbleColor(MarbleColorOn colorRange);

		static marble_ptr makeMarble(MarbleColor color=MarbleColor::None);
		static marble_ptr makeRandomMarble();
		static marble_ptr makeRandomMarble(MarbleColorOn colorRange);
		
	};


}


#endif //_MARBLE_GENERATOR_H