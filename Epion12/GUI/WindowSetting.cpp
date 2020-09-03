#include"../Epion12.h"
#include "ImGuiManager.h"

#include "ImGuiFunction.h"
#include "../Scene/SceneManager.h"
#include "../Scene/SceneDefault.h"
#include "../Scene/Scene2D.h"
#include "../Scene/Scene3D.h"
#include "../Scene/SceneNoise.h"
#include "../Scene/SceneTest.h"
#include "../Scene/SceneDemoProcedural.h"
#include "../Camera/CameraManager.h"
#include "../DX12/ViewPort.h"

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
			if (ImGui::RadioButton("3D Scene", &m_select_scene, 2))
			{
				SceneManager::SetNextScene<Scene3D>();
			}
			if (ImGui::RadioButton("Noise Scene", &m_select_scene, 3))
			{
				SceneManager::SetNextScene<SceneNoise>();
			}
			if (ImGui::RadioButton("Test Scene", &m_select_scene, 4))
			{
				SceneManager::SetNextScene<SceneTest>();
			}
			if (ImGui::RadioButton("Procedural Scene ", &m_select_scene, 5))
			{
				SceneManager::SetNextScene<SceneProcedural>();
			}

			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Camera Manager"))
		{
			if (ImGui::TreeNode("Basic Camera"))
			{
				auto pos = Camera::CameraManager::GetBasicCamera()->GetPos();
				auto target = Camera::CameraManager::GetBasicCamera()->GetTarget();

				ImGui::Text("Pos");
				ImGui::InputFloat("x", &pos.x, 0.01f, 100.0f, "%.3f");
				ImGui::InputFloat("y", &pos.y, 0.01f, 100.0f, "%.3f");
				ImGui::InputFloat("z", &pos.z, 0.01f, 100.0f, "%.3f");

				ImGui::Text("Target");
				ImGui::InputFloat("x ", &target.x, 0.01f, 100.0f, "%.3f");
				ImGui::InputFloat("y ", &target.y, 0.01f, 100.0f, "%.3f");
				ImGui::InputFloat("z ", &target.z, 0.01f, 100.0f, "%.3f");

				Camera::CameraManager::GetBasicCamera()->SetPos(pos);
				Camera::CameraManager::GetBasicCamera()->SetTarget(target);
				ImGui::TreePop();
			}
			if (ImGui::TreeNode("Scene3D Camera"))
			{
				auto pos = Camera::CameraManager::GetScene3DCamera()->GetPos();
				auto target = Camera::CameraManager::GetScene3DCamera()->GetTarget();

				ImGui::Text("Pos");
				ImGui::InputFloat("x  ", &pos.x, 0.01f, 100.0f, "%.3f");
				ImGui::InputFloat("y  ", &pos.y, 0.01f, 100.0f, "%.3f");
				ImGui::InputFloat("z  ", &pos.z, 0.01f, 100.0f, "%.3f");

				ImGui::Text("Target");
				ImGui::InputFloat("x   ", &target.x, 0.01f, 100.0f, "%.3f");
				ImGui::InputFloat("y   ", &target.y, 0.01f, 100.0f, "%.3f");
				ImGui::InputFloat("z   ", &target.z, 0.01f, 100.0f, "%.3f");

				ImGui::Text("Aspect %f", DX12::ViewPort::GetAspect());

				Camera::CameraManager::GetScene3DCamera()->SetPos(pos);
				Camera::CameraManager::GetScene3DCamera()->SetTarget(target);
				ImGui::TreePop();
			}
			ImGui::EndTabItem();
		}
		ImGui::EndTabBar();
		ImGui::End();
	}
}