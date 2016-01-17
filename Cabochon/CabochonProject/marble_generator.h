#ifndef _CONTROLS_H
#define _CONTROLS_H

#include "controls.h"
#include "components.h"
#include "marble.h"
#include <memory>
namespace controls
{
	using components::marble_ptr;
	using components::Marble;

	class MarbleGenerator
	{
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
	};


}


#endif //_CONTROLS_H