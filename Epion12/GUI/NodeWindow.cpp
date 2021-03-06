#include "../Epion12.h"
#include "NodeWindow.h"
#include "ImGuiFunction.h"

#include "../Node/NodeParam.h"
#include "../Node/NodeBase.h"
#include "../Node/NodeContext.h"
#include "../FileIO/EpionFileIO.h"
namespace
{
	epion::Node::NodeMenuContext context;
	epion::Node::NodeTypeMenuContext menus;
	constexpr	float	NODE_SLOT_RADIUS = 5.0f;
	bool m_is_open_line_delete_menu;
	std::string file_name;
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
		m_scroll_scale = 1.0f;
		m_is_context = false;
		m_is_node_hit = false;
		m_is_slot_hit = false;

		return true;
	}
	bool	NodeWindow::Finalize()
	{
		return true;
	}
	void	NodeWindow::Update()
	{
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("Menu"))
			{
				if (ImGui::BeginMenu("Json Generate"))
				{
					ImGui::InputText("File Name", const_cast<char*>(file_name.c_str()), CHAR_MAX);

					if (ImGui::MenuItem("Save(json)"))
					{
						std::string path;
						path = path + "Epion12\\NodeSceneData\\" + file_name.c_str() + ".json";
						FileIO::FileIOManager::OutputJson<Node::NodeBase, Node::NodeLink>(path, "NodeParam", m_nodes, "LinkParam", m_links);
					}
					ImGui::EndMenu();
				}

				if (ImGui::MenuItem("HLSL Generate"))
				{
				}

				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Examples"))
			{
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Tools"))
			{
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Option"))
			{
				if (ImGui::BeginMenu("ShaderGenerate"))
				{
					ImGui::Combo("Shader Space", &m_space_type, "None\0Tab\0Space\0");

					ImGui::EndMenu();
				}
				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

		Begin();
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
				ContextUpdate();
				ImGui::EndTabItem();
			}
			ImGui::EndTabBar();
		}
		End();
	}

	void NodeWindow::Begin()
	{
		ImGui::SetNextWindowPos(ImVec2(0, 10));
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(1, 1));
		ImGui::PushStyleColor(ImGuiCol_Border, ImColors::U32::GREEN);
		ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_ChildBg, ImColors::U32::GRAYBLACK);
		ImGui::BeginChild("NodeWindow", ImVec2(1200, 700));
	}
	void NodeWindow::End()
	{
		ImGui::EndChild();
		ImGui::PopStyleColor(2);
		ImGui::PopStyleVar();
	}

	void NodeWindow::ContextUpdate()
	{
		LineDeleteContext();
		context.ContextMenu("Create Node First", m_is_context);
		if (m_is_context)
		{
			menus.OpenMenu();
			m_is_context = false;
		}
		menus.ContextMenu("Create Node", m_is_context);
		menus.ContextChild(m_nodes);
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
		if (IsRightClick() && m_is_open_line_delete_menu)
		{
			m_hit_line_num = Node::INIT_NUM;
			m_is_open_line_delete_menu = false;
		}
		else	if (IsRightClick() && !m_is_node_hit && !m_is_line_hit)
		{
			context.OpenMenu();
		}
		else	if (IsRightClick() && !m_is_node_hit && m_is_line_hit && !m_is_open_line_delete_menu)
		{
			m_is_open_line_delete_menu = true;
		}
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

	}
	void NodeWindow::Scroll()
	{
		if (ImGui::IsWindowHovered() && !ImGui::IsAnyItemActive() && ImGui::IsMouseDragging(2, 0.0f))
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
						if (!m_is_slot_hit
							&& !m_nodes[size]->GetIsSlotInputONE(slot_index)
							)
						{
							m_links.push_back(Node::NodeLink(m_click_param.id, m_click_param.slot, m_nodes[m_click_param.id]->GetOutputSlotType(m_click_param.slot), m_nodes[size]->GetID(), slot_index, m_nodes[size]->GetInputSlotType(slot_index)));
							m_nodes[size]->SetIsSlotInput(slot_index, Node::INPUT_SLOT_STATE::ONE);
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
							m_nodes[m_click_param.id]->SetIsSlotInput(m_click_param.slot, Node::INPUT_SLOT_STATE::ONE);
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
			m_is_node_hit = true;
		}
		else
		{
			m_nodes[size]->PushEventEnd();
			m_is_node_hit = false;
		}

		if (m_nodes[size]->GetIsPush() &&
			ImGui::IsMouseDoubleClicked(0))
		{
			//m_nodes[size]->m_is_double_clicked = true;
			m_nodes[size]->PushEventEnd();
			m_is_node_hit = false;
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
			ImVec2 get_pos = ImBezierClosestPoint(output_pos, output_pos + Node::BEZIERCURVE_LEFT_POS, input_pos + Node::BEZIERCURVE_RIGHT_POS, input_pos, ImGui::GetIO().MousePos, 12);
			if (Physics::Collider2D::SphereAndSphere(ImGuiFunction::GetFVector2(ImGui::GetIO().MousePos), ImGuiFunction::GetFVector2(get_pos), 8.0f))
			{
				draw_list->AddBezierCurve(output_pos, output_pos + Node::BEZIERCURVE_LEFT_POS, input_pos + Node::BEZIERCURVE_RIGHT_POS, input_pos, Node::NODE_LINE_HIT_COLOR, 7.0f, 12);
				l.m_is_hit = true;
			}
			else
			{
				m_line_size = 3.0f;
				l.m_is_hit = false;
			}
			draw_list->AddBezierCurve(output_pos, output_pos + Node::BEZIERCURVE_LEFT_POS, input_pos + Node::BEZIERCURVE_RIGHT_POS, input_pos, Node::NODE_LINE_COLOR, m_line_size, 12);
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
	void NodeWindow::LineDeleteContext()
	{
		if (m_is_open_line_delete_menu)
		{
			PopUpBegin("delete_line_menu");
			if (ImGui::BeginPopup("delete_line_menu"))
			{
				ImGui::TextColored(ImColors::Vec4::BLACK, "Menu");
				ImGui::Separator();
				CloseContext(m_is_open_line_delete_menu);
				if (ImGui::MenuItem("Delete", nullptr))
				{
					m_nodes[m_links[m_hit_line_num].GetInputID()]->SetIsSlotInput(m_links[m_hit_line_num].GetInputSlot(), Node::INPUT_SLOT_STATE::ZERO);
					m_links.erase(m_links.begin() + m_hit_line_num);
					m_hit_line_num = Node::INIT_NUM;
					m_is_open_line_delete_menu = false;
				}
			}
			PopUpEnd();
		}
	}
	void NodeWindow::PopUpBegin(std::string_view str)
	{
		ImGui::OpenPopup(str.data());
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(12, 16));
		ImGui::PushStyleColor(ImGuiCol_Border, ImColors::U32::GREEN);
		ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_PopupBg, ImColors::U32::GRAY);
	}
	void NodeWindow::PopUpEnd()
	{
		ImGui::PopStyleColor(2);
		ImGui::PopStyleVar();
		ImGui::EndPopup();
	}

}