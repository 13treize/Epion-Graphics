#include	"../Epion12.h"
#include	"SceneManager.h"
#include	"../DX12/Device.h"
#include	"../DX12/CommandList.h"

#include	"Scene2D.h"
#include	"../DX12/ShaderManager.h"
#include	"../DX12/RasterizerManager.h"

namespace
{
	struct TestCBuffer
	{
		float Time;
		float A;
		float B;
		float C;
	};


	epion::com_ptr<ID3D12DescriptorHeap> m_pCbvHeap;
	TestCBuffer *buffer_data;
	TestCBuffer data2;
}
namespace epion
{
	bool Scene2D::Initialize()
	{
		HRESULT hr;
		m_cbuffer=std::make_unique<DX12::ConstantBuffer>();

		DX12::RasterizerManager::Initialize();

		bool is_compile=true;
		is_compile = DX12::ShaderManager::Compile(L"Epion12\\HLSL\\VS\\VertexShader.hlsl", vs_blob, DX12::ShaderType::TYPE_VERTEX);
		assert(is_compile);
		is_compile = DX12::ShaderManager::Compile(L"Epion12\\HLSL\\PS\\PixelShader.hlsl", ps_blob, DX12::ShaderType::TYPE_PIXEL);
		assert(is_compile);
		//aaaaa=DX12::ShaderManager::Compile(L"Epion12\\HLSL\\HS\\HullShader.hlsl", hs_blob, DX12::ShaderType::TYPE_HULL);
		//assert(aaaaa);
		is_compile=DX12::ShaderManager::Compile(L"Epion12\\HLSL\\GS\\GeometryShader.hlsl", gs_blob, DX12::ShaderType::TYPE_GEOMETRY);
		assert(is_compile);
		//aaaaa=DX12::ShaderManager::Compile(L"Epion12\\HLSL\\DS\\DomainShader.hlsl", ds_blob, DX12::ShaderType::TYPE_DOMAIN);
		//assert(aaaaa);
		DX12::ShaderManager::Compile(L"Epion12\\HLSL\\PS\\PixelShaderConst.hlsl", ps_blob2, DX12::ShaderType::TYPE_PIXEL);

		//m_square = std::make_unique<Model::Square>();
		//m_square->Initialize(vs_blob, ps_blob, gs_blob, DX12::RasterizerManager::GetSolidDesc());
		m_plane= std::make_unique<Model::Plane>();
		m_plane->Initialize(vs_blob, ps_blob, DX12::RasterizerManager::GetSolidDesc());
		return true;
	}
	bool Scene2D::Finalize()
	{
		return true;
	}
	void Scene2D::Update()
	{
		//m_square->Update(Math::FVector2(200, 200), Math::FVector2(200, 200));
		m_plane->Update(Math::FVector2(200, 200), Math::FVector2(200, 200));

	}
	void Scene2D::Render()
	{
		//m_square->Render();
		m_plane->Render();

	}
	void Scene2D::RenderTex()
	{
	}

}