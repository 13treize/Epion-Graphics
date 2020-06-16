#include	"Epion12.h"
#include	"MainSystem.h"

namespace
{

}


namespace epion
{
	std::array<float, 4> MainSystem::m_back_color;

	bool MainSystem::Initialize(HWND hwnd)
	{
		return true;
	}
	bool MainSystem::Finalize()
	{
		return true;
	}
	void MainSystem::Update()
	{
		////SceneManager::ChangeScene();
		//GUI::ImGuiManager::Begin();
		////SceneManager::Update();
		//setting_window.Update(m_back_color);
		////GUI::NodeEditor::Update();
		//dx2.SetBackColor(m_back_color);
		//dx2.Update();
	}

	void MainSystem::Render()
	{
		//dx2.Render();
		//DX12::DX12ScreenData::RSSets(DX12::DX12CommandList::GetPtr());
		////SceneManager::Render();
		//GUI::ImGuiManager::End(DX12::DX12CommandList::GetPtr(), dx2.GetHeapImGui());
		//GUI::ImGuiManager::UpdatePlatformWindow(DX12::DX12CommandList::GetPtr());
		//dx2.EndUpdate();
		//dx2.End();
	}

}