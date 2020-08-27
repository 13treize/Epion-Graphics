#include	"../Epion12.h"
#include	"SceneManager.h"
#include	"../DX12/Device.h"
#include	"../DX12/CommandList.h"

#include	"SceneNoise.h"
#include	"../DX12/ShaderManager.h"
#include	"../DX12/BlendState.h"
#include	"../DX12/RasterizerManager.h"
#include	"../DX12/ConstantBufferManager.h"
#include	"../DX12/RootSignature.h"
#include	"../DX12/DescriptorHeap.h"

namespace epion
{
	bool SceneNoise::Initialize()
	{
		DX12::ConstantBufferManager::Build2D();
		DX12::RootSignatureManager::Build2D(D3D12_ROOT_PARAMETER_TYPE_CBV);
		DX12::BlendStateManager::Initialize();
		DX12::RasterizerManager::Initialize();
		DX12::ShaderResouceManager::Compile(L"Epion12\\HLSL\\VS\\VertexShader.hlsl", m_vs_blob, DX12::ShaderType::TYPE_VERTEX);
		DX12::ShaderResouceManager::Compile(L"Epion12\\HLSL\\PS\\SceneNoiseDemo.hlsl", "PS" + std::to_string(2), m_ps_blob[0], DX12::ShaderType::TYPE_PIXEL);

		for (int i = 0; i < 48; i++)
		{
			m_square[i] = std::make_unique<Model::Square>();
			m_square[i]->Initialize(m_vs_blob, m_ps_blob[0], DX12::RasterizerManager::GetSolidDesc(), DX12::BlendStateManager::GetDesc(), DX12::RootSignatureManager::Get());
		}

		return true;
	}
	bool SceneNoise::Finalize()
	{
		return true;
	}
	void SceneNoise::Update()
	{
		for (int y = 0; y < 6; y++)
		{
			for (int x = 0; x < 8; x++)
			{
				m_square[8 * y + x]->Update(Math::FVector2(x * 120, y * 100), Math::FVector2(90, 90));
			}
		}
		Math::FVector2 pos = { 0.0f,0.0f };
		DX12::ConstantBufferManager::UpdateCBuffer0(pos);
	}
	void SceneNoise::Render(int frame_count)
	{
		DX12::RootSignatureManager::SetGraphicsRootSignature();
		DX12::CommandList::GetCmd()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY::D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		DX12::ConstantBufferManager::SetCBuffer0(0);
		for (int i = 0; i < 48; i++)
		{
			m_square[i]->Render();
		}
	}
	void SceneNoise::RenderTex()
	{
	}
}