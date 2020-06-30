#pragma once
#include"Model.h"

namespace epion::Model
{
	class TestModel final :public Model
	{
		TestModel();
		~TestModel();
		bool init();
		void update();
		void render();
	};
}