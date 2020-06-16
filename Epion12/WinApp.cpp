#include	"Epion12.h"
#include	"../ImGui_Docking\\imgui.h"
#include	"../ImGui_Docking\\imgui_impl_win32.h"
#include	"../ImGui_Docking\\imgui_impl_dx12.h"
#include	"../ImGui_Docking\\imgui_internal.h"

#include	"WinApp.h"

namespace
{
}
LRESULT	ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace epion
{
	bool	WinApp::m_fullscreen_mode;
	WNDCLASSEX	WinApp::m_w;
	HINSTANCE	WinApp::m_hInst;
	HWND		WinApp::m_hwnd;


	WinApp::WinApp()
	{}
	WinApp::~WinApp()
	{}
	bool WinApp::InitInstance(HINSTANCE hInstance, int nCmdShow, int width, int height)
	{
		RECT wrc = { 0,0,width,height };//ウィンドウサイズを決める
		AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);//ウィンドウのサイズはちょっと面倒なので関数を使って補正する

		m_hInst = hInstance;

		m_hwnd = CreateWindow(
			L"DX12 Epion",
			L"Epion 12",
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			width,
			height,
			nullptr,
			nullptr,
			hInstance,
			nullptr);

		if (!m_hwnd)
		{
			return false;
		}


		return true;
	}
	ATOM WinApp::CallRegisterClass(HINSTANCE hInstance)
	{
		m_w.cbSize = sizeof(WNDCLASSEX);
		m_w.style = CS_HREDRAW | CS_VREDRAW;
		m_w.lpfnWndProc = WndProc;
		m_w.cbClsExtra = 0;
		m_w.cbWndExtra = 0;
		m_w.hInstance = hInstance;
		m_w.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_EPION12));
		m_w.hCursor = LoadCursor(nullptr, IDC_ARROW);
		m_w.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		//m_w.lpszMenuName = MAKEINTRESOURCEW(IDC_EPION12);
		m_w.lpszMenuName = nullptr;
		m_w.lpszClassName = L"DX12 Epion";
		m_w.hIconSm = LoadIcon(m_w.hInstance, MAKEINTRESOURCE(IDI_SMALL));
		return RegisterClassEx(&m_w);
	}


	// グローバル変数:
	LRESULT CALLBACK WinApp::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
		{
			return	true;
		}

		switch (message)
		{
			//case WM_COMMAND:
			//{
			//	int wmId = LOWORD(wParam);
			//	// 選択されたメニューの解析:
			//	switch (wmId)
			//	{
			//	case IDM_ABOUT:
			//		DialogBox(m_hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			//		break;
			//	case IDM_EXIT:
			//		DestroyWindow(hWnd);
			//		break;
			//	default:
			//		return DefWindowProc(hWnd, message, wParam, lParam);
			//	}
			//}
			//break;
		//case WM_PAINT:
		//{
		//	PAINTSTRUCT ps;
		//	HDC hdc = BeginPaint(hWnd, &ps);
		//	EndPaint(hWnd, &ps);
		//}
		//break;
		//case WM_SIZE:
			//if (/*g_pd3dDevice != nullptr && */wParam != SIZE_MINIMIZED)
			//{
			//	ImGui_ImplDX12_InvalidateDeviceObjects();
			//	CleanupRenderTarget();
			//	ResizeSwapChain(hWnd, (UINT)LOWORD(lParam), (UINT)HIWORD(lParam));
			//	CreateRenderTarget();
			//	ImGui_ImplDX12_CreateDeviceObjects();
			//}
			//return 0;

		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		return 0;
	}
	void WinApp::UpdateWindowCall(int nCmdShow)
	{
		ShowWindow(m_hwnd, nCmdShow);
		UpdateWindow(m_hwnd);
	}

	void WinApp::UnRegisterCall()
	{
		UnregisterClass(m_w.lpszClassName, m_w.hInstance);
	}

	HWND& WinApp::GetHwnd()
	{
		return m_hwnd;
	}

	// バージョン情報ボックスのメッセージ ハンドラーです。
	INT_PTR CALLBACK WinApp::About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
	{
		UNREFERENCED_PARAMETER(lParam);
		switch (message)
		{
		case WM_INITDIALOG:
			return (INT_PTR)TRUE;

		case WM_COMMAND:
			if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
			{
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}
			break;
		}
		return (INT_PTR)FALSE;
	}

}