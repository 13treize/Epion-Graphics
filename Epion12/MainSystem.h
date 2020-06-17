#pragma once
#include	"DX12/PipeLine.h"
#include	"GUI/WindowSetting.h"

/**
 * @file MainSystem .h
 * @brief MainSystemクラス
 * @author treize
 * @date 2020/02/18
 * @details MainSystemクラス
 */

namespace epion
{
	class MainSystem final
	{
	public:
		static bool	Initialize(HWND hwnd, const Math::Vector2<int>& screen_size);
		static bool	Finalize();
		static void	Update();
		static void	Render();

	private:
		static	DX12::PipeLine m_pipeline;
		static	GUI::SettingWindow setting_window;
		static	std::array<float, 4> m_back_color;
	};
}