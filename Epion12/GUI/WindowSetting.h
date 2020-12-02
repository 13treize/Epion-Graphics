#pragma once
#include "ImGuiBase.h"

namespace epion::GUI
{
	class SettingWindow final :public ImGuiBase
	{
	public:
		bool Initialize();
		bool Finalize();
		void Update(std::array<float, 4>& color);
	private:
		std::string m_bar_title;
		int m_select_scene;

	};
}