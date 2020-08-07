#include	"../Epion12.h"
#include	"SceneManager.h"
#include	"../DX12/Device.h"
#include	"../DX12/CommandList.h"

#include	"Scene2D.h"
#include	"../DX12/ShaderManager.h"
#include	"../DX12/BlendState.h"
#include	"../DX12/RasterizerManager.h"
#include	"../DX12/ConstantBufferManager.h"
#include	"../DX12/RootSignature.h"
#include	"../DX12/DescriptorHeap.h"
namespace
{

}
namespace epion
{
	bool Scene2D::Initialize()
	{
		HRESULT hr;
		//m_frame_resouce.push_back(std::make_unique<DX12::FrameResource>(DX12::Device::Get()));

		DX12::ConstantBufferManager::Build2D();
		DX12::RootSignatureManager::Build2D(D3D12_ROOT_PARAMETER_TYPE_CBV);
		DX12::BlendStateManager::Initialize();
		DX12::RasterizerManager::Initialize();

		// Build Shader
		DX12::ShaderResouceManager::Compile(L"Epion12\\HLSL\\VS\\VertexShader.hlsl", vs_blob, DX12::ShaderType::TYPE_VERTEX);
		//DX12::ShaderResouceManager::Compile(L"Epion12\\HLSL\\PS\\PixelShader.hlsl", ps_blob, DX12::ShaderType::TYPE_PIXEL);
		DX12::ShaderResouceManager::Compile(L"Epion12\\HLSL\\GS\\GeometryShader.hlsl", gs_blob, DX12::ShaderType::TYPE_GEOMETRY);
		DX12::ShaderResouceManager::Compile(L"Epion12\\HLSL\\PS\\Scene2DDemo.hlsl", ps_blob, DX12::ShaderType::TYPE_PIXEL);
		DX12::ShaderResouceManager::Compile(L"Epion12\\HLSL\\PS\\Scene2DDemo.hlsl","PS"+std::to_string(2), ps_blob2, DX12::ShaderType::TYPE_PIXEL);

		for (int i = 0; i < 48; i++)
		{
			m_square[i] = std::make_unique<Model::Square>();
			m_square[i]->Initialize(vs_blob, ps_blob,DX12::RasterizerManager::GetSolidDesc(), DX12::BlendStateManager::GetDesc(), DX12::RootSignatureManager::Get());
		}

		return true;
	}	

	bool Scene2D::Finalize()
	{
		return true;
	}
	void Scene2D::Update()
	{
		for (int y = 0; y < 2; y++)
		{
			for (int x = 0; x < 2; x++)
			{
				m_square[2*y+x]->Update(Math::FVector2(x*420, y * 420), Math::FVector2(400, 400));
			}
		}
		Math::FVector2 pos = { 0.0f,0.0f };
		DX12::ConstantBufferManager::UpdateCBuffer0(pos);
		//m_plane->Update(Math::FVector2(200, 200), Math::FVector2(200, 200));

	}

	void Scene2D::Render(int frame_count)
	{
		DX12::RootSignatureManager::SetGraphicsRootSignature();
		DX12::CommandList::GetCmd()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY::D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		//DX12::ConstantBufferManager::SetHeap();
		DX12::ConstantBufferManager::SetCBuffer0(0);
		for (int i = 0; i < 4; i++)
		{
			m_square[i]->Render();
		}
	}
	void Scene2D::RenderTex()
	{
	}

}