#include "../Epion12.h"
#include "StaticMesh.h"

#include "../DX12/ViewPort.h"
#include "../DX12/Device.h"
#include "../DX12/CommandList.h"
#include "../DX12/ConstantBufferManager.h"
#include "PrimitiveModelData.h"

namespace epion::Model
{
	Polygon::Polygon()
		:Model3D()
	{
	}

	Polygon::~Polygon()
	{
	}
	bool Polygon::Initialize(com_ptr<ID3DBlob>& vs_blob, com_ptr<ID3DBlob>& ps_blob, D3D12_RASTERIZER_DESC& r_desc, D3D12_BLEND_DESC& b_desc, com_ptr<ID3D12RootSignature>& root_sig)
	{
		m_shader_reflection = std::make_unique<DX12::ShaderReflection>();
		m_shader_reflection->ReflectionInputLayout(vs_blob);

		m_pipeline_desc = {};
		m_pipeline_desc.VS = { vs_blob->GetBufferPointer(), vs_blob->GetBufferSize() };
		m_pipeline_desc.PS = { ps_blob->GetBufferPointer(), ps_blob->GetBufferSize() };

		m_pipeline_desc.BlendState = b_desc;
		m_pipeline_desc.RasterizerState = r_desc;

		m_pipeline_desc.DepthStencilState.DepthEnable = false;
		m_pipeline_desc.DepthStencilState.StencilEnable = false;

		m_pipeline_desc.InputLayout = { m_shader_reflection->GetInputLayout().data(), static_cast<UINT>(m_shader_reflection->GetInputLayout().size()) };

		m_pipeline_desc.IBStripCutValue = D3D12_INDEX_BUFFER_STRIP_CUT_VALUE_DISABLED;
		m_pipeline_desc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;

		m_pipeline_desc.NumRenderTargets = 1;
		m_pipeline_desc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
		m_pipeline_desc.SampleDesc = { 1,0 };
		m_pipeline_desc.SampleMask = UINT_MAX; // ‚±‚ê‚ð–Y‚ê‚é‚ÆŠG‚ªo‚È‚¢•Œx‚ào‚È‚¢‚Ì‚Å’ˆÓ.

		m_pipeline_desc.pRootSignature = root_sig.Get();
		DX12::Device::Get()->CreateGraphicsPipelineState(&m_pipeline_desc, IID_PPV_ARGS(&m_pipeline_state));


		m_vertex_resource = std::make_unique<DX12::ResourceBuffer<Model3DVertex>>();
		m_vertex_resource->Initialize(DX12::Device::Get(), sizeof(Model3DVertex), false);
		m_vertex_resource->CopyResource<PrimitiveData::Polygon::VERTEX_SIZE>(PrimitiveData::Polygon::vertices);
		m_vertex_buffer_view = { m_vertex_resource->GetGPUVirtualAddress() ,sizeof(Model3DVertex) * PrimitiveData::Polygon::VERTEX_SIZE,sizeof(Model3DVertex) };

		m_index_resource = std::make_unique<DX12::ResourceBuffer<unsigned short>>();
		m_index_resource->Initialize(DX12::Device::Get(), PrimitiveData::Polygon::INDEX_SIZE, false);
		m_index_resource->CopyResource<PrimitiveData::Polygon::INDEX_SIZE>(PrimitiveData::Polygon::indices);
		m_index_buffer_view = { m_index_resource->GetGPUVirtualAddress(), PrimitiveData::Polygon::INDEX_SIZE * sizeof(unsigned short),DXGI_FORMAT::DXGI_FORMAT_R16_UINT };
		return true;
	}
	bool Polygon::Finalize()
	{
		m_vertex_resource->Finalize();
		m_index_resource->Finalize();

		return true;
	}

	void Polygon::Update()
	{
		DirectX::XMMATRIX S, R, T;
		S = DirectX::XMMatrixScaling(m_scale.x, m_scale.y, m_scale.z);
		R = DirectX::XMMatrixRotationRollPitchYaw(m_angle.x * 0.01745f, m_angle.y * 0.01745f, m_angle.z * 0.01745f);
		T = DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z);
		m_world_matrix = S * R * T;
	}

	void Polygon::Render()
	{
		Draw(DX12::CommandList::GetCmd());
	}

	CubeMesh::CubeMesh()
		:Model3D()
	{
	}

	CubeMesh ::~CubeMesh()
	{
	}
	bool CubeMesh::Initialize(com_ptr<ID3DBlob>& vs_blob, com_ptr<ID3DBlob>& ps_blob, D3D12_RASTERIZER_DESC& r_desc, D3D12_BLEND_DESC& b_desc, com_ptr<ID3D12RootSignature>& root_sig)
	{
		m_shader_reflection = std::make_unique<DX12::ShaderReflection>();
		m_shader_reflection->ReflectionInputLayout(vs_blob);

		m_pipeline_desc = {};
		m_pipeline_desc.VS = { vs_blob->GetBufferPointer(), vs_blob->GetBufferSize() };
		m_pipeline_desc.PS = { ps_blob->GetBufferPointer(), ps_blob->GetBufferSize() };

		m_pipeline_desc.SampleMask = D3D12_DEFAULT_SAMPLE_MASK;

		m_pipeline_desc.BlendState = b_desc;
		m_pipeline_desc.RasterizerState = r_desc;

		//m_pipeline_desc.DepthStencilState.DepthEnable = false;
		//m_pipeline_desc.DepthStencilState.StencilEnable = false;
		m_pipeline_desc.DSVFormat = DXGI_FORMAT_D32_FLOAT;

		m_pipeline_desc.DepthStencilState.DepthEnable = TRUE;
		m_pipeline_desc.DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
		m_pipeline_desc.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_LESS;
		m_pipeline_desc.DepthStencilState.StencilEnable = FALSE;
		m_pipeline_desc.DepthStencilState.StencilReadMask = D3D12_DEFAULT_STENCIL_READ_MASK;
		m_pipeline_desc.DepthStencilState.StencilWriteMask = D3D12_DEFAULT_STENCIL_WRITE_MASK;
		const D3D12_DEPTH_STENCILOP_DESC defaultStencilOp =	{ D3D12_STENCIL_OP_KEEP, D3D12_STENCIL_OP_KEEP, D3D12_STENCIL_OP_KEEP, D3D12_COMPARISON_FUNC_ALWAYS };
		m_pipeline_desc.DepthStencilState.FrontFace = defaultStencilOp;
		m_pipeline_desc.DepthStencilState.BackFace = defaultStencilOp;

		m_pipeline_desc.InputLayout = { m_shader_reflection->GetInputLayout().data(), static_cast<UINT>(m_shader_reflection->GetInputLayout().size()) };

		m_pipeline_desc.IBStripCutValue = D3D12_INDEX_BUFFER_STRIP_CUT_VALUE_DISABLED;
		m_pipeline_desc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;

		m_pipeline_desc.NumRenderTargets = 1;
		m_pipeline_desc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
		m_pipeline_desc.SampleDesc = { 1,0 };
		m_pipeline_desc.SampleMask = UINT_MAX;
		m_pipeline_desc.pRootSignature = root_sig.Get();
		DX12::Device::Get()->CreateGraphicsPipelineState(&m_pipeline_desc, IID_PPV_ARGS(&m_pipeline_state));


		m_vertex_resource = std::make_unique<DX12::ResourceBuffer<Model3DVertex>>();
		m_vertex_resource->Initialize(DX12::Device::Get(), sizeof(Model3DVertex), false);
		m_vertex_resource->CopyResource<PrimitiveData::CubeMesh::VERTEX_SIZE>(PrimitiveData::CubeMesh::vertices);
		m_vertex_buffer_view = { m_vertex_resource->GetGPUVirtualAddress() ,sizeof(Model3DVertex) * PrimitiveData::CubeMesh::VERTEX_SIZE,sizeof(Model3DVertex) };

		m_index_resource = std::make_unique<DX12::ResourceBuffer<unsigned short>>();
		m_index_resource->Initialize(DX12::Device::Get(), PrimitiveData::CubeMesh::INDEX_SIZE, false);
		m_index_resource->CopyResource<PrimitiveData::CubeMesh::INDEX_SIZE>(PrimitiveData::CubeMesh::indices);
		m_index_buffer_view = { m_index_resource->GetGPUVirtualAddress(), PrimitiveData::CubeMesh::INDEX_SIZE * sizeof(unsigned short),DXGI_FORMAT::DXGI_FORMAT_R16_UINT };
		return true;
	}
	bool CubeMesh::Finalize()
	{
		m_vertex_resource->Finalize();
		m_index_resource->Finalize();

		return true;
	}

	void CubeMesh::Update()
	{
		DirectX::XMMATRIX S, R, T;
		S = DirectX::XMMatrixScaling(m_scale.x, m_scale.y, m_scale.z);
		R = DirectX::XMMatrixRotationRollPitchYaw(m_angle.x * 0.01745f, m_angle.y * 0.01745f, m_angle.z * 0.01745f);
		T = DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z);
		m_world_matrix = S * R * T;
	}

	void CubeMesh::Render()
	{
		Draw(DX12::CommandList::GetCmd());
	}

}