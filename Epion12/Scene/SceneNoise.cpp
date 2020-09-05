#include	"../Epion12.h"
#include	"SceneManager.h"
#include	"../DX12/Device.h"
#include	"../DX12/CommandList.h"

#include	"SceneNoise.h"
#include	"../DX12/ShaderManager.h"
#include	"../DX12/DX12State.h"
#include	"../DX12/ConstantBufferManager.h"
#include	"../DX12/RootSignature.h"
#include	"../DX12/DescriptorHeap.h"
#include	"../GUI/ImGuiFunction.h"

namespace epion
{
	bool SceneNoise::Initialize()
	{
		DX12::ConstantBufferManager::Build2D();
		DX12::RootSignatureManager::Build2D(D3D12_ROOT_PARAMETER_TYPE_CBV);
		DX12::BlendStateManager::Initialize();
		DX12::RasterizerManager::Initialize();
		DX12::ShaderResouceManager::Compile(L"Epion12\\HLSL\\VS\\VertexShader.hlsl", m_vs_blob, DX12::ShaderType::TYPE_VERTEX);
		m_data[0] = { 6.0f,6.0f,10.0f,3.0f };
		m_data[1] = { 5.0f,1.0f,1.0f,1.0f };
		m_data[2] = { 1.0f,1.0f,1.0f,1.0f };
		m_data[3] = { 1.0f,1.0f,1.0f,1.0f };

		for (int i = 0; i < 10; i++)
		{
			DX12::ShaderResouceManager::Compile(L"Epion12\\HLSL\\PS\\SceneNoiseDemo.hlsl", "PS" + std::to_string(i), m_ps_blob[i], DX12::ShaderType::TYPE_PIXEL);
		}
		for (int i = 0; i < 48; i++)
		{
			m_square[i] = std::make_unique<Model::Square>();
			m_square[i]->Initialize(m_vs_blob, m_ps_blob[std::clamp(i, 0, 9)], DX12::RasterizerManager::GetSolidDesc(), DX12::BlendStateManager::GetDesc(), DX12::RootSignatureManager::Get());
		}

		return true;
	}
	bool SceneNoise::Finalize()
	{
		return true;
	}
	void SceneNoise::Update()
	{
		UpdataGUI();
		for (int y = 0; y < 6; y++)
		{
			for (int x = 0; x < 8; x++)
			{
				m_square[8 * y + x]->Update(Math::FVector2(x * 120, y * 100), Math::FVector2(90, 90));
			}
		}
		Math::FVector2 pos = { 0.0f,0.0f };
		DX12::ConstantBufferManager::UpdateCBuffer0(pos);
		DX12::ConstantBufferManager::UpdateCBuffer3(m_data);

	}
	void SceneNoise::Render(int frame_count)
	{
		DX12::RootSignatureManager::SetGraphicsRootSignature();
		DX12::CommandList::GetCmd()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY::D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		DX12::ConstantBufferManager::SetCBuffer0(0);
		DX12::ConstantBufferManager::SetCBuffer3(1);

		for (int i = 0; i <10; i++)
		{
			m_square[i]->Render();
		}
	}
	void SceneNoise::RenderTex()
	{
	}
	void SceneNoise::UpdataGUI()
	{
		auto get_data = m_data;
		ImGuiWindowFlags m_window_flags=0;
		GUI::Begin("NoiseParam", m_window_flags);
		ImGui::SliderFloat("Random Scale", &get_data[0].x, 0.01f, 100.0f, "%.3f");
		ImGui::SliderFloat("RandomMaze Scale", &get_data[0].y, 0.01f, 100.0f, "%.3f");
		ImGui::SliderFloat("0_z", &get_data[0].z, 0.01f, 100.0f, "%.3f");
		ImGui::SliderFloat("0_w", &get_data[0].w, 0.01f, 100.0f, "%.3f");
		ImGui::SliderFloat("1_x", &get_data[1].x, 0.01f, 100.0f, "%.3f");
		ImGui::SliderFloat("1_y", &get_data[1].y, 0.01f, 100.0f, "%.3f");
		ImGui::SliderFloat("1_z", &get_data[1].z, 0.01f, 100.0f, "%.3f");
		ImGui::SliderFloat("1_w", &get_data[1].w, 0.01f, 100.0f, "%.3f");
		GUI::End();
		m_data = get_data;

	}

}