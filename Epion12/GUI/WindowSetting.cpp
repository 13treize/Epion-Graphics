#include"../Epion12.h"
#include "ImGuiManager.h"

#include "ImGuiFunction.h"
#include "../Scene/SceneManager.h"
#include "../Scene/Scene2D.h"
#include "../Scene/SceneDefault.h"

#include "WindowSetting.h"

namespace epion::GUI
{

	bool SettingWindow::Initialize()
	{
		m_bar_title = "SettingWindow";
		m_window_flags = 0;
		m_select_scene = 0;
		return true;
	}
	bool SettingWindow::Finalize()
	{
		return true;
	}

	void SettingWindow::Update(std::array<float, 4>& color)
	{
		//Begin(m_bar_title.c_str(), m_window_flags);
		ImGui::Begin(m_bar_title.c_str(), nullptr, m_window_flags);
		if (ImGui::BeginTabBar("##sets", ImGuiTabBarFlags_None))
		{
			if (ImGui::BeginTabItem("Option"))
			{
				ShowFPS();
				ImGui::ColorEdit3("BackColor", (float*)&color);
				ImGui::EndTabItem();
			}
		}
		if (ImGui::BeginTabItem("DemoScene"))
		{
			if (ImGui::RadioButton("Default Scene", &m_select_scene, 0))
			{
				SceneManager::SetNextScene<SceneDefault>();
			}
			if (ImGui::RadioButton("2D Scene", &m_select_scene, 1))
			{
				SceneManager::SetNextScene<Scene2D>();
			}
			ImGui::EndTabItem();
		}
		ImGui::EndTabBar();
		ImGui::End();
	}
}