#include "Epion12.h"
#include "WinApp.h"
#include "MainSystem.h"

namespace
{
	constexpr int SCREEN_WIDTH = 1920;
	constexpr int SCREEN_HEIGHT = 1080;
	epion::Math::Vector2<int> SCREEN_SIZE =
	{
		 SCREEN_WIDTH,SCREEN_HEIGHT
	};
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);


	epion::WinApp::CallRegisterClass(hInstance);
	//RECT wrc = { 0,0,	SCREEN_WIDTH,SCREEN_HEIGHT };//�E�B���h�E�T�C�Y�����߂�
	//AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);//�E�B���h�E�̃T�C�Y�͂�����Ɩʓ|�Ȃ̂Ŋ֐����g���ĕ␳����
	if (!epion::WinApp::InitInstance(hInstance, nCmdShow, SCREEN_WIDTH, SCREEN_HEIGHT))
	{
		return 0;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_EPION12));

	epion::WinApp::UpdateWindowCall(nCmdShow);

	epion::MainSystem::Initialize(epion::WinApp::GetHwnd(), SCREEN_SIZE);


	MSG msg = {};

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		epion::MainSystem::Update();
		epion::MainSystem::Render();
	}
	epion::MainSystem::Finalize();

	epion::WinApp::UnRegisterCall();

	return (int)msg.wParam;
}