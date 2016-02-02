#ifndef _CONTROLS_H
#define _CONTROLS_H

#include "controls.h"
#include "components.h"
#include "marble.h"
#include "control.h"
#include <memory>
namespace controls
{
	using components::marble_ptr;
	using components::Marble;

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

		// pure virtual function
		// nothing to do.
		virtual void render();
		virtual void update();
	};


}


#endif //_CONTROLS_H