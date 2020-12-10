#include "../Epion12.h"
#include <cereal/cereal.hpp>
#include <cereal/archives/json.hpp>
#include <cereal/types/vector.hpp>

#include "../GUI/ImGuiFunction.h"
#include "NodeParam.h"
#include "NodeBase.h"
#include "NodeContext.h"
#include "../FileIO/EpionFileIO.h"

namespace
{

	std::array<std::string, epion::Node::NodeType::ArraySize> node_type_name =
	{
		"Artistic",
		"Channel",
		"Input",
		"Master",
		"Math",
		"Procedural",
		"Utility",
		"UV",
		"Hash",
		"Noise"
	};
}
namespace	epion::Node
{
	NodeMenuContext::NodeMenuContext()
		:GUI::ContextObject()
	{

	}
	NodeMenuContext::~NodeMenuContext()
	{

	}
	void NodeMenuContext::OpenMenu()
	{
		m_is_open_menu = true;
		m_menu_pos = ImGui::GetIO().MousePos;

	}
	void NodeMenuContext::CloseMenu()
	{
		m_is_open_menu = false;

	}
	void NodeMenuContext::PopupBeginSettings()
	{
		ImGui::SetNextWindowPos(m_menu_pos);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(12, 16));
		ImGui::PushStyleColor(ImGuiCol_Border, GUI::ImColors::U32::GREEN);
		ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_PopupBg, GUI::ImColors::U32::GRAY);
	}
	void NodeMenuContext::PopupEndSettings()
	{
		ImGui::PopStyleColor(2);
		ImGui::PopStyleVar();
		ImGui::EndPopup();
	}
	void NodeMenuContext::ContextMenu(std::string_view popup_name, bool& is_event)
	{
		if (m_is_open_menu)
		{
			ImGui::OpenPopup(popup_name.data());
			PopupBeginSettings();
			if (ImGui::BeginPopup(popup_name.data()))
			{
				GUI::TextMenu("Menu");
				GUI::CloseContext(m_is_open_menu);
				if (GUI::MenuItem("Create Node", is_event)) CloseMenu();
			}
			PopupEndSettings();
		}
	}
	NodeTypeMenuContext::NodeTypeMenuContext()
		:GUI::ContextObject()
	{
		m_is_first_click = false;
		m_create_node_count = 0;

		for (int i = 0; i < NodeType::ArraySize; i++)
		{
			m_menu_item_states[i].IsOpen = false;
			m_menu_item_states[i].ItemChild.clear();
			m_menu_item_states[i].Name = node_type_name[i];
			m_context_data[i].Name.clear();
			FileIO::FileIOManager::InputJson<ContextData>("Epion12\\Settings\\ContextSetting.json", node_type_name[i], m_context_data[i]);
			//FileIO::FileIOManager::OutputJson<ContextData>("Epion12\\ContextSetting2.json", NodeTypeName[i], m_context_data[i]);
			for (const auto& e : m_context_data[i].Name)
			{
				m_menu_item_states[i].ItemChild.push_back({ e, false, {} });
			}
		}
	}
	NodeTypeMenuContext::~NodeTypeMenuContext()
	{

	}

	void NodeTypeMenuContext::Update()
	{

	}

	void NodeTypeMenuContext::OpenMenu()
	{
		m_is_open_menu = true;
		m_menu_pos = ImGui::GetIO().MousePos;
	}
	void NodeTypeMenuContext::CloseMenu()
	{
		m_is_open_menu = false;
	}
	void NodeTypeMenuContext::PopupBeginSettings()
	{
		ImGui::SetNextWindowPos(m_menu_pos);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(12, 16));
		ImGui::PushStyleColor(ImGuiCol_Border, GUI::ImColors::U32::GREEN);
		ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_PopupBg, GUI::ImColors::U32::GRAY);
	}
	void NodeTypeMenuContext::PopupEndSettings()
	{
		ImGui::PopStyleColor(2);
		ImGui::PopStyleVar();
		ImGui::EndPopup();
	}
	void NodeTypeMenuContext::ContextMenu(std::string_view popup_name, bool& is_event)
	{
		if (m_is_open_menu)
		{
			ImGui::OpenPopup(popup_name.data());
			PopupBeginSettings();
			if (ImGui::BeginPopup(popup_name.data()))
			{
				GUI::TextMenu("Create Node");
				GUI::CloseContext(m_is_open_menu);
				ImGui::Separator();
				for (int i = 0; i < NodeType::ArraySize; i++)
				{
					if (GUI::MenuItem(m_menu_item_states[i].Name, m_menu_item_states[i].IsOpen))
					{
						CloseMenu();
					}
				}
			}
			PopupEndSettings();
		}
		if (GUI::IsRightClick() && m_is_open_menu)
		{
			m_is_open_menu = false;
		}
	}

	void NodeTypeMenuContext::ContextChild(std::vector<std::unique_ptr<Node::NodeBase>>& nodes)
	{
		for (int i = 0; i < NodeType::ArraySize; i++)
		{
			if (m_menu_item_states[i].IsOpen)
			{
				PopupBeginSettings();
				ImGui::OpenPopup(m_menu_item_states[i].Name.c_str());
				if (ImGui::BeginPopup(m_menu_item_states[i].Name.c_str()))
				{
					GUI::TextMenu(m_menu_item_states[i].Name);
					GUI::BackContext(m_is_open_menu, m_menu_item_states[i].IsOpen);
					GUI::CloseContext(m_menu_item_states[i].IsOpen);
					if (!m_menu_item_states[i].ItemChild.empty())
					{
						for (auto& item : m_menu_item_states[i].ItemChild)
						{
							MenuCreateNode<Node::FunctionNode>(nodes, m_menu_item_states[i].Name,item.Name, m_menu_pos, m_create_node_count, m_menu_item_states[i].IsOpen);
						}
					}
					ImGui::Separator();
				}
				PopupEndSettings();
			}
			if (GUI::IsRightClick() && m_menu_item_states[i].IsOpen)
			{
				CloseMenu();
				m_menu_item_states[i].IsOpen = false;
			}
		}
	}

}