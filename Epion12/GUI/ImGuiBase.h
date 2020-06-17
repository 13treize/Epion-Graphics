#pragma once
#include "EpionGUI.h"
namespace epion::GUI
{
	class ImGuiBase abstract
	{
	public:
		virtual	~ImGuiBase() {};
	protected:

		ImGuiWindowFlags m_window_flags = {};
	};
}