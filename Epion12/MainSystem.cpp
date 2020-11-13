#include	"Epion12.h"
#include	"DX12/ViewPort.h"
#include	"DX12/Device.h"
#include	"DX12/CommandList.h"
//#include	"DX12/PipeLine.h"
#include	"DX12/ShaderManager.h"

#include	"GUI/ImGuiManager.h"

#include	"Scene/SceneManager.h"
#include	"MainSystem.h"

namespace
{
}


namespace epion
{
	DX12::PipeLine MainSystem::m_pipeline;
	GUI::SettingWindow MainSystem::setting_window;
	std::array<float, 4> MainSystem::m_back_color;

	bool MainSystem::Initialize(HWND hwnd, const Math::Vector2<int>& screen_size)
	{
		DX12::ViewPort::SetScreenSize(screen_size);
		DX12::ViewPort::Initialize();
		m_pipeline.Initialize(hwnd);
		GUI::ImGuiManager::Init(hwnd, DX12::Device::Get(), m_pipeline.GetHeapImGui());
		setting_window.Initialize();

		return true;
	}
	bool MainSystem::Finalize()
	{
		GUI::ImGuiManager::Release();
		setting_window.Finalize();
		return true;
	}
	void MainSystem::Update()
	{
		SceneManager::ChangeScene();
		GUI::ImGuiManager::Begin();
		SceneManager::Update();
		setting_window.Update(m_back_color);
		m_pipeline.SetBackColor(m_back_color);
		m_pipeline.Update();
	}

	void MainSystem::Render()
	{
		m_pipeline.Render();
		DX12::ViewPort::RSSets(DX12::CommandList::GetCmd());
		SceneManager::Render(m_pipeline.GetFrameCount());
		GUI::ImGuiManager::End(DX12::CommandList::GetCmd(), m_pipeline.GetHeapImGui());
		GUI::ImGuiManager::UpdatePlatformWindow(DX12::CommandList::GetCmd());
		m_pipeline.EndUpdate();
		m_pipeline.End();
	}
}