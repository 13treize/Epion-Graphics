#include "../Epion12.h"
#include "NodeWindow.h"
#include "ImGuiFunction.h"
#include "../Node/NodeContext.h"
namespace
{
	epion::Node::NodeMenuContext context;
	epion::Node::NodeTypeMenuContext menus;
}
namespace epion::GUI
{
	bool	NodeWindow::Initialize()
	{
		m_bar_flags = 0;
		m_bar_flags |= ImGuiTabBarFlags_::ImGuiTabBarFlags_NoTooltip;
		m_bar_flags |= ImGuiTabBarFlags_::ImGuiTabBarFlags_NoTabListScrollingButtons;
		m_bar_flags |= ImGuiTabBarFlags_::ImGuiTabBarFlags_TabListPopupButton;

		m_nodes.clear();
		m_links.clear();
		m_nodes.push_back(std::make_unique<Node::SampleNode>("Sample",1, Math::FVector2(120.0f,20.0f)));

		m_scroll_scale = 1.0f;
		is_context=false;

		return true;
	}
	bool	NodeWindow::Finalize()
	{
		return true;
	}
	void	NodeWindow::Update()
	{
		ImGui::SetNextWindowPos(ImVec2(30, 10));
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(1, 1));
		ImGui::PushStyleColor(ImGuiCol_Border, ImColors::U32::GREEN);
		ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_ChildBg, ImColors::U32::GRAYBLACK);

		ImGui::BeginChild("NodeWindow", ImVec2(800, 600));
		ImDrawList* draw_list = ImGui::GetWindowDrawList();
		draw_list->ChannelsSplit(5);

		if (ImGui::BeginTabBar("##tabs", m_bar_flags))
		{
			if (ImGui::BeginTabItem("Node"))
			{
				DrawGrid(draw_list, 64.0f, IM_COL32(0, 200, 120, 120), m_offset);
				//DrawLinkLine(draw_list);

				NodeUpdate(draw_list);
				if (IsRightClick())	context.OpenMenu();
				context.ContextMenu("AAAA", is_context);
				if (is_context)
				{
					menus.OpenMenu();
					is_context = false;
				}
				menus.ContextMenu("Noise ", is_context);
				//MouseUpdate(draw_list);

				//if (m_node_hovered_list != Node::INIT_NUM)
				//{
				//	m_node_select_num = m_node_hovered_list;
				//}
				//if (m_node_hovered_in_scene != Node::INIT_NUM)
				//{
				//	m_node_select_num = m_node_hovered_in_scene;
				//}
				//	ContextManager::ClickEvent(m_offset);

					//ContextManager::LineEvent();

				ImGui::EndTabItem();
			}

			ImGui::EndTabBar();
		}
		ImGui::EndChild();

		ImGui::PopStyleColor(2);
		ImGui::PopStyleVar();

	}
	void	NodeWindow::NodeUpdate(ImDrawList* draw_list)
	{
		//	draw_list->ChannelsSetCurrent(1); // Background
		for (int node_size = 0; node_size < static_cast<int>(m_nodes.size()); node_size++)
		{
			ImGui::PushID(m_nodes[node_size]->GetID());
			ImVec2 node_rect_min = m_offset + ImGuiFunction::GetImVec2(m_nodes[node_size]->GetPos());

			ImGui::SetCursorScreenPos(node_rect_min);
			//NodeMouseUpdate(draw_list, node_size);
			m_nodes[node_size]->Draw(draw_list, m_offset, m_scroll_scale);
			//NodeErase(draw_list, node_size);
			//NodeInputUpdate(draw_list, node_size);
			//NodeOutputUpdate(draw_list, node_size);

			ImGui::PopID();
		}
		draw_list->ChannelsMerge();
	}

	void NodeWindow::NodeDraw(ImDrawList* draw_list, int size)
	{
		m_nodes[size]->Draw(draw_list,m_offset, m_scroll_scale);

	}

}