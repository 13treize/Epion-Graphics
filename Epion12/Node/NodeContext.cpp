#include "../Epion12.h"
#include "../GUI/ImGuiFunction.h"
#include "NodeContext.h"

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
				if(GUI::MenuItem("Create Node",is_event)) CloseMenu();
				//if (ImGui::MenuItem("Create Node", nullptr, &is_event))
				//{
				//	//is_event = true;
				//	CloseMenu();
				//}
			}
			PopupEndSettings();
		}
	}
	NodeTypeMenuContext::NodeTypeMenuContext()
		:GUI::ContextObject()
	{
	}
	NodeTypeMenuContext::~NodeTypeMenuContext()
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
				if (GUI::MenuItem("Noise", is_event)) CloseMenu();

				//for (int i = 0; i < static_cast<int>(ArraySize); i++)
				//{
				//	if (GUI::MenuItem(TO_STRING(static_cast<NodeType>(i)), is_event)) CloseMenu();
				//}
				//if (ImGui::MenuItem("Create Node", nullptr, &is_event))
				//{
				//	//is_event = true;
				//	CloseMenu();
				//}
			}
			PopupEndSettings();
		}
	}

}