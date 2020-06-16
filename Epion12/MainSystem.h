#pragma once
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
		static bool	Initialize(HWND hwnd);
		static bool	Finalize();
		static void	Update();
		static void	Render();

	private:
		//static	DX12::DX12Pipeline2 dx2;
		//static	GUI::SettingWindow setting_window;
		static	std::array<float, 4> m_back_color;
	};
}