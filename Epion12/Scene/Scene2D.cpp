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
	epion::com_ptr<ID3D12Resource> cresouce;
	epion::com_ptr<ID3D12DescriptorHeap> m_pCbvHeap;
	TestCBuffer *buffer_data;
	TestCBuffer data2;
}
namespace epion
{
	bool Scene2D::Initialize()
	{
		HRESULT hr;
		DX12::RasterizerManager::Initialize();

		bool aaaaa=true;
		aaaaa = DX12::ShaderManager::Compile(L"Epion12\\HLSL\\VS\\VertexShader.hlsl", vs_blob, DX12::ShaderType::TYPE_VERTEX);
		assert(aaaaa);
		aaaaa = DX12::ShaderManager::Compile(L"Epion12\\HLSL\\PS\\PixelShader.hlsl", ps_blob, DX12::ShaderType::TYPE_PIXEL);
		assert(aaaaa);
		//aaaaa=DX12::ShaderManager::Compile(L"Epion12\\HLSL\\HS\\HullShader.hlsl", hs_blob, DX12::ShaderType::TYPE_HULL);
		//assert(aaaaa);
		aaaaa=DX12::ShaderManager::Compile(L"Epion12\\HLSL\\GS\\GeometryShader.hlsl", gs_blob, DX12::ShaderType::TYPE_GEOMETRY);
		assert(aaaaa);
		//aaaaa=DX12::ShaderManager::Compile(L"Epion12\\HLSL\\DS\\DomainShader.hlsl", ds_blob, DX12::ShaderType::TYPE_DOMAIN);
		//assert(aaaaa);
		//DX12::ShaderManager::Compile(L"Epion12\\HLSL\\PS\\PixelShaderConst.hlsl", ps_blob2, DX12::ShaderType::TYPE_PIXEL);

		m_square = std::make_unique<Model::Square>();
		m_square->Initialize(vs_blob, ps_blob, gs_blob, DX12::RasterizerManager::GetSolidDesc());
		//m_square->Initialize(vs_blob, ps_blob,  DX12::RasterizerManager::GetSolidDesc());

		//{
		//	D3D12_DESCRIPTOR_HEAP_DESC desc = {};
		//	desc.NumDescriptors = 1;
		//	desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
		//	desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;

		//	hr=DX12::Device::Get()->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&m_pCbvHeap));
		//	assert(SUCCEEDED(hr));

		//}
		//D3D12_HEAP_PROPERTIES prop = {};
		//prop.Type = D3D12_HEAP_TYPE_UPLOAD;
		//prop.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
		//prop.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
		//prop.CreationNodeMask = 1;
		//prop.VisibleNodeMask = 1;

		//// リソースの設定.
		//D3D12_RESOURCE_DESC desc = {};
		//desc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
		//desc.Alignment = 0;
		//desc.Width = (sizeof(TestCBuffer)+0xff)&~0xff;
		//desc.Height = 1;
		//desc.DepthOrArraySize = 1;
		//desc.MipLevels = 1;
		//desc.Format = DXGI_FORMAT_UNKNOWN;
		//desc.SampleDesc.Count = 1;
		//desc.SampleDesc.Quality = 0;
		//desc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
		//desc.Flags = D3D12_RESOURCE_FLAG_NONE;

		//hr = DX12::Device::Get()->CreateCommittedResource(
		//	&prop,
		//	D3D12_HEAP_FLAG_NONE,
		//	&desc,
		//	D3D12_RESOURCE_STATE_GENERIC_READ,
		//	nullptr,
		//	IID_PPV_ARGS(&cresouce));
		//assert(SUCCEEDED(hr));

		////auto basicHeapHandle = m_pCbvHeap->GetCPUDescriptorHandleForHeapStart();
		////basicHeapHandle.ptr +=DX12::Device::Get()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

		//D3D12_CONSTANT_BUFFER_VIEW_DESC bufferDesc = {};
		//bufferDesc.BufferLocation = cresouce->GetGPUVirtualAddress();
		//bufferDesc.SizeInBytes = cresouce->GetDesc().Width;
		//DX12::Device::Get()->CreateConstantBufferView(&bufferDesc, m_pCbvHeap->GetCPUDescriptorHandleForHeapStart());
		//hr = cresouce->Map(0, nullptr, reinterpret_cast<void**>(&buffer_data));
		//data2.A = 0.1f;
		//data2.B = 0.1f;
		//data2.C = 0.1f;
		//data2.Time = 0.1f;
		//memcpy(buffer_data, &data2, sizeof(data2));

		//DX12::Device::Get()->CreateConstantBufferView(&bufferDesc, basicHeapHandle);
		//hr= DX12::Device::Get()->GetDeviceRemovedReason();
		//assert(SUCCEEDED(hr));

		//hr = cresouce->Map(0, nullptr, reinterpret_cast<void**>(&buffer_data));



		return true;
	}
	bool Scene2D::Finalize()
	{
		return true;
	}
	void Scene2D::Update()
	{
		m_square->Update(Math::FVector2(200, 200), Math::FVector2(200, 200));
	}
	void Scene2D::Render()
	{
		//m_square->A();
		//DX12::CommandList::GetPtr()->SetDescriptorHeaps(1, &m_pCbvHeap);
		////// ディスクリプタヒープテーブルを設定.
		//DX12::CommandList::GetPtr()->SetGraphicsRootDescriptorTable(0, m_pCbvHeap->GetGPUDescriptorHandleForHeapStart());


		m_square->Render();
	}
	void Scene2D::RenderTex()
	{
	}

}