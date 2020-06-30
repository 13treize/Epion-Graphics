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
	epion::DX12::RootSignature root;
	epion::DX12::RootSignature root2;

}
namespace epion
{
	bool Scene2D::Initialize()
	{
		HRESULT hr;

		DX12::ConstantBufferManager::Initialize();

		D3D12_DESCRIPTOR_RANGE desc_range = {};
		desc_range.NumDescriptors = 1;//定数ひとつ
		desc_range.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_CBV;//種別は定数
		desc_range.BaseShaderRegister = 0;//0番スロットから
		desc_range.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

		D3D12_ROOT_PARAMETER rootparam = {};
		rootparam.ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
		rootparam.DescriptorTable.pDescriptorRanges = &desc_range;//デスクリプタレンジのアドレス
		rootparam.DescriptorTable.NumDescriptorRanges = 1;//デスクリプタレンジ数
		rootparam.ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;//全てのシェーダから見える


		root.Initialize(rootparam);

		root2.Initialize();

		DX12::RasterizerManager::Initialize();

		DX12::ShaderResouceManager::Compile(L"Epion12\\HLSL\\VS\\VertexShader.hlsl", vs_blob, DX12::ShaderType::TYPE_VERTEX);
		DX12::ShaderResouceManager::Compile(L"Epion12\\HLSL\\PS\\PixelShader.hlsl", ps_blob, DX12::ShaderType::TYPE_PIXEL);
		DX12::ShaderResouceManager::Compile(L"Epion12\\HLSL\\GS\\GeometryShader.hlsl", gs_blob, DX12::ShaderType::TYPE_GEOMETRY);
		DX12::ShaderResouceManager::Compile(L"Epion12\\HLSL\\PS\\Scene2DDemo.hlsl", ps_blob2, DX12::ShaderType::TYPE_PIXEL);

		m_square = std::make_unique<Model::Square>();
		m_square->Initialize(vs_blob, ps_blob2, gs_blob, DX12::RasterizerManager::GetSolidDesc(), root.Get());

		return true;
	}	

	bool Scene2D::Finalize()
	{
		return true;
	}
	void Scene2D::Update()
	{
		Math::FVector2 pos = {0.0f,0.0f};
		m_square->Update(Math::FVector2(0, 0), Math::FVector2(200, 200));
		DX12::ConstantBufferManager::UpdateCBuffer0(pos);
		//m_plane->Update(Math::FVector2(200, 200), Math::FVector2(200, 200));

	}

	void Scene2D::Render()
	{
		DX12::CommandList::GetPtr()->SetGraphicsRootSignature(root.Get().Get());
		DX12::ConstantBufferManager::SetCBuffer0();
		m_square->Render();
		//m_plane->Render();

	}
	void Scene2D::RenderTex()
	{
	}

}