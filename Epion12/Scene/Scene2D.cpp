#include	"../Epion12.h"
#include	"SceneManager.h"
#include	"../DX12/Device.h"
#include	"../DX12/CommandList.h"

#include	"Scene2D.h"
#include	"../DX12/ShaderManager.h"
#include	"../DX12/RasterizerManager.h"
#include	"../DX12/RootSignature.h"
#include	"../DX12/DescriptorHeap.h"
namespace
{
	struct TestCBuffer
	{
		float Time;
		float A;
		float B;
		float C;
	};
	std::unique_ptr<epion::DX12::DescriptorHeap> cheap;
	TestCBuffer *buffer_data;
	TestCBuffer data2;
}
namespace epion
{
	bool Scene2D::Initialize()
	{
		HRESULT hr;
		cheap = std::make_unique<DX12::DescriptorHeap>();
		cheap->Initialize(1, D3D12_DESCRIPTOR_HEAP_TYPE::D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
		D3D12_DESCRIPTOR_RANGE desc_range = {};//テクスチャと定数の２つ
		desc_range.NumDescriptors = 1;//定数ひとつ
		desc_range.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_CBV;//種別は定数
		desc_range.BaseShaderRegister = 0;//0番スロットから
		desc_range.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

		D3D12_ROOT_PARAMETER rootparam = {};
		rootparam.ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
		rootparam.DescriptorTable.pDescriptorRanges = &desc_range;//デスクリプタレンジのアドレス
		rootparam.DescriptorTable.NumDescriptorRanges = 1;//デスクリプタレンジ数
		rootparam.ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;//全てのシェーダから見える


		DX12::RasterizerManager::Initialize();

		DX12::ShaderManager::Compile(L"Epion12\\HLSL\\VS\\VertexShader.hlsl", vs_blob, DX12::ShaderType::TYPE_VERTEX);
		DX12::ShaderManager::Compile(L"Epion12\\HLSL\\PS\\PixelShader.hlsl", ps_blob, DX12::ShaderType::TYPE_PIXEL);
		DX12::ShaderManager::Compile(L"Epion12\\HLSL\\GS\\GeometryShader.hlsl", gs_blob, DX12::ShaderType::TYPE_GEOMETRY);
		DX12::ShaderManager::Compile(L"Epion12\\HLSL\\PS\\PixelShaderConst.hlsl", ps_blob2, DX12::ShaderType::TYPE_PIXEL);

		//aaaaa=DX12::ShaderManager::Compile(L"Epion12\\HLSL\\HS\\HullShader.hlsl", hs_blob, DX12::ShaderType::TYPE_HULL);
		//assert(aaaaa);
		//aaaaa=DX12::ShaderManager::Compile(L"Epion12\\HLSL\\DS\\DomainShader.hlsl", ds_blob, DX12::ShaderType::TYPE_DOMAIN);
		//assert(aaaaa);

		DX12::RootSignature root;
		root.Initialize(rootparam);


		//m_square = std::make_unique<Model::Square>();
		//m_square->Initialize(vs_blob, ps_blob, gs_blob, DX12::RasterizerManager::GetSolidDesc());
	/*	m_plane= std::make_unique<Model::Plane>();
		m_plane->Initialize(vs_blob, ps_blob, DX12::RasterizerManager::GetSolidDesc());*/

		m_square = std::make_unique<Model::Square>();
		m_square->Initialize(vs_blob, ps_blob2, gs_blob, DX12::RasterizerManager::GetSolidDesc(), root.Get());

		m_cbuffer = std::make_unique<DX12::ConstantBuffer>();
		m_cbuffer->Initialize(256);
		DX12::Device::Get()->CreateConstantBufferView(&m_cbuffer->GetView(), cheap->m_heap->GetCPUDescriptorHandleForHeapStart());

		m_cbuffer->GetBuffer()->Map(0, nullptr, (void**)&buffer_data);

		data2 = { 1.0f,0.0f,0.0f,0.0f };

		memcpy(buffer_data, &data2, sizeof(data2));
		return true;
	}	

	bool Scene2D::Finalize()
	{
		return true;
	}
	void Scene2D::Update()
	{
		data2 = { 1.0f,0.0f,1.0f,0.0f };
		memcpy(buffer_data, &data2, sizeof(data2));

		m_square->Update(Math::FVector2(200, 200), Math::FVector2(200, 200));
		//m_plane->Update(Math::FVector2(200, 200), Math::FVector2(200, 200));

	}

	void Scene2D::Render()
	{
		m_square->A();

		ID3D12DescriptorHeap* ppHeaps[] = { cheap->m_heap.Get() };

		DX12::CommandList::GetPtr()->SetDescriptorHeaps(1, ppHeaps);
		//DX12::CommandList::GetPtr()->SetDescriptorHeaps(1, &cheap->m_heap);
		DX12::CommandList::GetPtr()->SetGraphicsRootDescriptorTable(0, cheap->m_heap->GetGPUDescriptorHandleForHeapStart());

		m_square->Render();
		//m_plane->Render();

	}
	void Scene2D::RenderTex()
	{
	}

}