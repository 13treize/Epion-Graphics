#pragma once

namespace epion
{
	class WinApp final
	{
	public:
		WinApp();
		~WinApp();
		static bool InitInstance(HINSTANCE hInstance, int nCmdShow, int width, int height);
		static ATOM CallRegisterClass(HINSTANCE hInstance);
		static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
		static void UpdateWindowCall(int nCmdShow);
		static void UnRegisterCall();
		//get
		static HWND& GetHwnd();

		//set
		static void CallReSizeSwap();


	private:
		static INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	private:
		static bool m_fullscreen_mode;
		static WNDCLASSEX	m_w;
		static HINSTANCE	m_hInst;
		static HWND	m_hwnd;
	};
}