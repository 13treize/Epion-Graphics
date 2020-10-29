#include "../Epion12.h"
#include "NodeWindow.h"
#include "ImGuiFunction.h"

#include "../Node/NodeParam.h"
#include "../Node/NodeBase.h"
#include "../Node/NodeContext.h"
namespace
{
	epion::Node::NodeMenuContext context;
	epion::Node::NodeTypeMenuContext menus;
	constexpr	float	NODE_SLOT_RADIUS = 5.0f;

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
		m_nodes.push_back(std::make_unique<Node::SampleNode>("Sample", 0, Math::FVector2(120.0f, 20.0f)));
		m_nodes.push_back(std::make_unique<Node::SampleNode>("Sample2", 1, Math::FVector2(360.0f, 120.0f)));

		//m_links.push_back(Node::NodeLink(0, 0, Node::SLOT_TYPE::VECTOR1, 1, 0, Node::SLOT_TYPE::VECTOR1));
		m_scroll_scale = 1.0f;
		m_is_context = false;
		m_is_slot_hit = false;

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
				DrawLinkLine(draw_list);

				NodeUpdate(draw_list);
				MouseUpdate(draw_list);

				if (IsRightClick())	context.OpenMenu();
				context.ContextMenu("Create Node First", m_is_context);
				if (m_is_context)
				{
					menus.OpenMenu();
					m_is_context = false;
				}
				menus.ContextMenu("Create Node", m_is_context);
				menus.ContextChild(m_nodes);
				//menus.ProceduralContext(m_nodes);

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

	void NodeWindow::MouseUpdate(ImDrawList* draw_list)
	{
		CallContext();
		Drag(draw_list);
		Enclose(draw_list);
		Scroll();
	}


	void NodeWindow::CallContext()
	{
		//if (m_is_line_hit)
		//{
		//	if (!ImGui::IsAnyItemHovered() &&
		//		ImGui::IsMouseClicked(1) &&	//右クリック
		//		!ImGui::IsMouseClicked(0))	//!左クリック
		//	{
		//		ContextManager::OpenLineDeleteContext(ImGui::GetIO().MousePos);
		//	}
		//}
		//else
		//{
		//	if (ImGui::IsMouseClicked(1) &&	//右クリック
		//		!ImGui::IsMouseClicked(0))	//!左クリック
		//	{
		//		if (!ImGui::IsAnyItemHovered())
		//		{
		//			m_node_select_num = m_node_hovered_list = m_node_hovered_in_scene = Node::INIT_NUM;
		//			ContextManager::OpenNodeCreateContext(ImGui::GetIO().MousePos);
		//		}
		//		else
		//		{
		//			m_node_select_num = m_node_hovered_list = m_node_hovered_in_scene = Node::INIT_NUM;
		//			ContextManager::OpenNodeDeleteContext(ImGui::GetIO().MousePos);
		//		}
		//	}
		//}
		//ContextManager::CreateNodeMenu(m_offset);
		////ContextManager::DeleteNodeMenu(m_nodes,m_hit_line_num);
		//ContextManager::DeleteLineMenu(m_links, m_hit_line_num);
	}

	void NodeWindow::Drag(ImDrawList* draw_list)
	{
		if (m_click_param.is_click_input_slot ||
			m_click_param.is_click_output_slot)
		{
			draw_list->AddBezierCurve(m_click_param.pos + m_offset, m_click_param.pos + ImVec2(50.0f, 0.0f) + m_offset, ImGui::GetIO().MousePos, ImGui::GetIO().MousePos, Node::NODE_LINE_COLOR, 4.0f);
			//ドラッグをやめる
			if (ImGui::IsMouseClicked(0))
			{
				m_click_param.is_click_input_slot = false;
				m_click_param.is_click_output_slot = false;
			}
		}
	}

	void NodeWindow::Enclose(ImDrawList* draw_list)
	{
		//if (ImGui::IsMouseClicked(0) &&
		//	!m_click_state.is_click_input_slot &&
		//	!m_click_state.is_click_output_slot)
		//{
		//	m_click_state.is_click_display = true;
		//	m_enclose_pos = ImGui::GetIO().MousePos;
		//}
		//if ((!m_click_state.is_click_input_slot ||
		//	!m_click_state.is_click_output_slot) &&
		//	m_click_state.is_click_display &&
		//	ImGui::IsMouseDragging(0))
		//{
		//	draw_list->AddRect(m_enclose_pos, ImGui::GetIO().MousePos, IM_COL32(215, 15, 15, 255), 5.0f, 0);
		//}
	}

	void NodeWindow::Scroll()
	{
		if (ImGui::IsWindowHovered() &&
			!ImGui::IsAnyItemActive() &&
			ImGui::IsMouseDragging(2, 0.0f))
		{
			m_offset = m_offset + ImGui::GetIO().MouseDelta;
			m_offset.x = std::clamp(m_offset.x, -1000.0f, 1000.0f);
			m_offset.y = std::clamp(m_offset.y, -1000.0f, 1000.0f);
		}
	}
	void	NodeWindow::NodeUpdate(ImDrawList* draw_list)
	{
		//	draw_list->ChannelsSetCurrent(1); // Background
		for (int node_size = 0; node_size < static_cast<int>(m_nodes.size()); node_size++)
		{
			ImGui::PushID(m_nodes[node_size]->GetID());
			ImVec2 node_rect_min = m_offset + ImGuiFunction::GetImVec2(m_nodes[node_size]->GetPos());

			ImGui::SetCursorScreenPos(node_rect_min);
			NodeMouseUpdate(draw_list, node_size);
			m_nodes[node_size]->Draw(draw_list, m_offset, m_scroll_scale);
			//NodeErase(draw_list, node_size);
			NodeInputUpdate(draw_list, node_size);
			NodeOutputUpdate(draw_list, node_size);
			ImGui::PopID();
		}
		draw_list->ChannelsMerge();
	}
	void NodeWindow::NodeInputUpdate(ImDrawList* draw_list, int size)
	{
		for (int slot_index = 0; slot_index < m_nodes[size]->GetInputsSize(); slot_index++)
		{
			Math::FVector2	slot_pos = ImGuiFunction::GetFVector2(m_offset) + m_nodes[size]->GetInputSlotPos(slot_index, Math::FVector2(0.0f, 10.0f));

			//input slotをクリックしたとき
			if (!m_click_param.is_click_output_slot &&
				ImGui::IsMouseDown(0) &&
				Physics::Collider2D::SphereAndSphere<float>(slot_pos, ImGuiFunction::GetFVector2(ImGui::GetIO().MousePos), NODE_SLOT_RADIUS, 2.0f))
			{
				m_click_param = { m_nodes[size]->GetID(),	slot_index,ImGuiFunction::GetImVec2(m_nodes[size]->GetInputSlotPos(slot_index, Math::FVector2(0.0f, 10.0f))),	false,	true,	false };
				break;
			}

			//output slotをクリックしてる
			if (m_click_param.is_click_output_slot && ImGui::IsMouseReleased(0))
			{
				m_is_slot_hit = false;
				bool	is_input = false;
				if (Physics::Collider2D::SphereAndSphere(slot_pos, ImGuiFunction::GetFVector2(ImGui::GetIO().MousePos), NODE_SLOT_RADIUS, 2.0f))
				{
					if (m_click_param.id != m_nodes[size]->GetID())
					{
						for (auto& check_link : m_links)
						{
							//既にノードがあるか確認
							if (check_link == Node::NodeLink(m_click_param.id, m_click_param.slot, m_nodes[size]->GetID(), slot_index))
							{
								m_is_slot_hit = true;
								break;
							}
							if (check_link.GetInputID() == m_nodes[size]->GetID() &&
								check_link.GetInputSlot() == slot_index)
							{
								is_input = true;
								break;
							}
						}
						if (is_input)	m_links.erase(m_links.begin() + slot_index - 1);
						if (!m_is_slot_hit)
						{
							m_links.push_back(Node::NodeLink(m_click_param.id, m_click_param.slot, m_nodes[m_click_param.id]->GetInputSlotType(slot_index), m_nodes[size]->GetID(), slot_index, m_nodes[size]->GetOutputSlotType(slot_index)));
						}
					}
					m_click_param = { Node::INIT_NUM,	Node::INIT_NUM,	ImVec2(0, 0),	false,	false,	false };
					break;
				}
			}
		}

	}

	void NodeWindow::NodeOutputUpdate(ImDrawList* draw_list, int size)
	{
		for (int slot_index = 0; slot_index < m_nodes[size]->GetOutputsSize(); slot_index++)
		{
			Math::FVector2	slot_pos = ImGuiFunction::GetFVector2(m_offset) + m_nodes[size]->GetOutputSlotPos(slot_index, Math::FVector2(0.0f, 10.0f));
			//slotをクリックしたとき
			if (!m_click_param.is_click_input_slot &&
				IsLeftMouseDown() &&
				Physics::Collider2D::SphereAndSphere(slot_pos, ImGuiFunction::GetFVector2(ImGui::GetIO().MousePos), NODE_SLOT_RADIUS, 2.0f))
			{
				m_click_param = { m_nodes[size]->GetID(),	slot_index,	ImGuiFunction::GetImVec2(m_nodes[size]->GetOutputSlotPos(slot_index, Math::FVector2(0.0f, 10.0f))),false,false,true };
				break;
			}
			//input →outputにノードを挿入するとき
			if (m_click_param.is_click_input_slot && ImGui::IsMouseReleased(0))
			{
				m_is_slot_hit = false;
				if (Physics::Collider2D::SphereAndSphere(slot_pos, Math::FVector2(ImGui::GetIO().MousePos.x, ImGui::GetIO().MousePos.y), NODE_SLOT_RADIUS, 2.0f))
				{
					if (m_click_param.id != m_nodes[size]->GetID())
					{
						for (auto& check_link : m_links)
						{
							//既にノードがあるか確認
							if (check_link == Node::NodeLink(m_nodes[size]->GetID(), slot_index, m_click_param.id, m_click_param.slot))
							{
								m_is_slot_hit = true;
								break;
							}
						}
						if (!m_is_slot_hit)
						{
							m_links.push_back(Node::NodeLink(m_nodes[size]->GetID(), slot_index, m_nodes[size]->GetOutputSlotType(slot_index), m_click_param.id, m_click_param.slot, m_nodes[m_click_param.id]->GetInputSlotType(m_click_param.slot)));
						}
					}
					m_click_param = { Node::INIT_NUM,Node::INIT_NUM,ImVec2(0, 0),	false,	false,	false };
					break;
				}
			}
		}

	}

	void NodeWindow::NodeDraw(ImDrawList* draw_list, int size)
	{
		m_nodes[size]->Draw(draw_list, m_offset, m_scroll_scale);

	}
	void NodeWindow::NodeMouseUpdate(ImDrawList* draw_list, int size)
	{
		m_is_old_any_active = ImGui::IsAnyItemActive();

		m_is_node_widgets_active = (!m_is_old_any_active && ImGui::IsAnyItemActive());

		ImGui::InvisibleButton("Nodes", GUI::ImGuiFunction::GetImVec2(m_nodes[size]->GetSize()));
		if (ImGui::IsItemHovered())
		{
			m_node_hovered_in_scene = m_nodes[size]->GetID();
		}
		else
		{
			m_node_hovered_in_scene = Node::INIT_NUM;
		}

		m_is_now_any_active = ImGui::IsItemActive();
		if (m_is_node_widgets_active ||
			m_is_now_any_active)
		{
			m_node_select_num = m_nodes[size]->GetID();
		}
		else
		{
			m_node_select_num = Node::INIT_NUM;
		}

		//Nodeに当たったか
		if (
			//m_node_hovered_list == m_nodes[size]->m_ID ||
			m_node_hovered_in_scene == m_nodes[size]->GetID())
		{
			m_nodes[size]->PushEventBegin();
		}
		else
		{
			m_nodes[size]->PushEventEnd();
		}

		if (m_nodes[size]->GetIsPush() &&
			ImGui::IsMouseDoubleClicked(0))
		{
			//m_nodes[size]->m_is_double_clicked = true;
			m_nodes[size]->PushEventEnd();
		}

		if (m_is_now_any_active &&
			ImGui::IsMouseDragging(0) &&
			!m_click_param.is_click_input_slot &&
			!m_click_param.is_click_output_slot)
		{
			m_nodes[size]->SetPos(m_nodes[size]->GetPos() + ImGuiFunction::GetFVector2(ImGui::GetIO().MouseDelta));
		}

	}

	void NodeWindow::DrawLinkLine(ImDrawList* draw_list)
	{
		draw_list->ChannelsSetCurrent(2); // Line
#ifdef DEBUG
		draw_list->AddCircle(ImGui::GetMousePos(), 10.0f, IM_COL32(255, 255, 255, 255));
#endif //  DEBUG

		for (auto& l : m_links)
		{
			ImVec2 input_pos = m_offset + ImGuiFunction::GetImVec2(m_nodes[l.GetInputID()]->GetInputSlotPos(l.GetInputSlot(), Math::FVector2(0.0f, 10.0f)));
			ImVec2 output_pos = m_offset + ImGuiFunction::GetImVec2(m_nodes[l.GetOutputID()]->GetOutputSlotPos(l.GetOutputSlot(), Math::FVector2(0.0f, 10.0f)));

			ImVec2 get_pos = ImBezierClosestPoint(output_pos, output_pos + Node::BEZIERCURVE_LEFT_POS, input_pos + Node::BEZIERCURVE_RIGHT_POS, input_pos, ImGui::GetIO().MousePos, 12.0f);

			if (Physics::Collider2D::SphereAndSphere(ImGuiFunction::GetFVector2(ImGui::GetIO().MousePos), ImGuiFunction::GetFVector2(get_pos), 8.0f))
			{
				draw_list->AddBezierCurve(output_pos, output_pos + Node::BEZIERCURVE_LEFT_POS, input_pos + Node::BEZIERCURVE_RIGHT_POS, input_pos, Node::NODE_LINE_HIT_COLOR, 7.0f, 12.0f);
				l.m_is_hit = true;
			}
			else
			{
				m_line_size = 3.0f;
				l.m_is_hit = false;
			}
			draw_list->AddBezierCurve(output_pos, output_pos + Node::BEZIERCURVE_LEFT_POS, input_pos + Node::BEZIERCURVE_RIGHT_POS, input_pos, Node::NODE_LINE_COLOR, m_line_size, 12.0f);
		}

		for (int i = 0; i < m_links.size(); i++)
		{
			if (m_links[i].m_is_hit)
			{
				m_hit_line_num = i;
				m_is_line_hit = true;
				break;
			}
			m_is_line_hit = false;
		}

	}
}