#include	"../Epion12.h"
#include	"../DX12/Device.h"
#include	"../DX12/CommandList.h"
#include	"../DX12/ViewPort.h"
#include	"SceneManager.h"
#include	"SceneNodeEditor.h"


namespace epion
{
	bool	SceneNodeEditor::Initialize()
	{
		m_viewport.Initialize(1280,720);
		m_node_window.Initialize();


		return true;
	}
	bool	SceneNodeEditor::Finalize()
	{
		return true;
	}
	void	SceneNodeEditor::Update()
	{
		m_window_flags = 0;
		//m_window_flags |= ImGuiWindowFlags_NoTitleBar;
		m_window_flags |= ImGuiWindowFlags_MenuBar;
		m_window_flags |= ImGuiWindowFlags_NoMove;
		m_window_flags |= ImGuiWindowFlags_NoResize;

		ImGui::SetNextWindowSize(ImVec2(1280, 720), 1);
		if (!ImGui::Begin("Editor", nullptr, m_window_flags))
		{
			ImGui::End();
			return;
		}
		m_node_window.Update();
		ImGui::End();
	}
	void	SceneNodeEditor::Render(int frame_count)
	{
		m_viewport.RSSets(DX12::CommandList::GetCmd());

	}
	void	SceneNodeEditor::RenderTex()
	{}
}