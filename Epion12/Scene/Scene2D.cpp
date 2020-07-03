#include	"../Epion12.h"
#include	"SceneManager.h"
#include	"../DX12/Device.h"
#include	"../DX12/CommandList.h"

#include	"Scene2D.h"
#include	"../DX12/ShaderManager.h"
#include	"../DX12/RasterizerManager.h"
#include	"../DX12/ConstantBufferManager.h"
#include	"../DX12/RootSignature.h"
#include	"../DX12/DescriptorHeap.h"
namespace
{
	epion::DX12::RootSignature root2;
}
namespace epion
{
	bool Scene2D::Initialize()
	{
		HRESULT hr;

		DX12::ConstantBufferManager::Initialize();
		//root2.Initialize();
		DX12::RootSignatureManager::Build();
		DX12::RasterizerManager::Initialize();

		// Build Shader
		DX12::ShaderResouceManager::Compile(L"Epion12\\HLSL\\VS\\VertexShader.hlsl", vs_blob, DX12::ShaderType::TYPE_VERTEX);
		DX12::ShaderResouceManager::Compile(L"Epion12\\HLSL\\PS\\PixelShader.hlsl", ps_blob, DX12::ShaderType::TYPE_PIXEL);
		DX12::ShaderResouceManager::Compile(L"Epion12\\HLSL\\GS\\GeometryShader.hlsl", gs_blob, DX12::ShaderType::TYPE_GEOMETRY);
		DX12::ShaderResouceManager::Compile(L"Epion12\\HLSL\\PS\\Scene2DDemo.hlsl", ps_blob2, DX12::ShaderType::TYPE_PIXEL);

		m_square = std::make_unique<Model::Square>();
		m_square->Initialize(vs_blob, ps_blob2, gs_blob, DX12::RasterizerManager::GetSolidDesc(), DX12::RootSignatureManager::Get());


		//m_square->Initialize(vs_blob, ps_blob2, gs_blob, DX12::RasterizerManager::GetSolidDesc(), DX12::RootSignatureManager::Get());

		return true;
	}	

	bool Scene2D::Finalize()
	{
		return true;
	}
	void Scene2D::Update()
	{
		m_square->Update(Math::FVector2(0, 0), Math::FVector2(200, 200));
		Math::FVector2 pos = { 0.0f,0.0f };
		DX12::ConstantBufferManager::UpdateCBuffer0(pos);
		//m_plane->Update(Math::FVector2(200, 200), Math::FVector2(200, 200));

	}

	void Scene2D::Render()
	{
		DX12::RootSignatureManager::SetGraphicsRootSignature();
		DX12::ConstantBufferManager::SetCBuffer0();
		m_square->Render();
		//m_plane->Render();

	}
	void Scene2D::RenderTex()
	{
	}

}