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
	bool Polygon::Initialize(com_ptr<ID3DBlob>& vs_blob, com_ptr<ID3DBlob>& ps_blob, D3D12_RASTERIZER_DESC& r_desc, D3D12_BLEND_DESC& b_desc, com_ptr<ID3D12RootSignature>& root_sig,unsigned int cb_index)
	{
		m_model_param->ObjCBIndex = cb_index;
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
		DX12::Device::Get()->CreateGraphicsPipelineState(&m_pipeline_desc, IID_PPV_ARGS(&m_model_param->PipeLineState));


		PrimitiveBufferSet<PrimitiveData::Polygon,ID3D12Device,Model3DVertex>(DX12::Device::Get());
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
		ResourceUpdate();
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
	bool CubeMesh::Initialize(com_ptr<ID3DBlob>& vs_blob, com_ptr<ID3DBlob>& ps_blob, D3D12_RASTERIZER_DESC& r_desc, D3D12_BLEND_DESC& b_desc, com_ptr<ID3D12RootSignature>& root_sig, unsigned int cb_index)
	{
		m_model_param->ObjCBIndex = cb_index;
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
		m_pipeline_desc.DSVFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;;

		m_pipeline_desc.DepthStencilState.DepthEnable = true;
		m_pipeline_desc.DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
		m_pipeline_desc.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_LESS;
		m_pipeline_desc.DepthStencilState.StencilEnable = false;
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
		DX12::Device::Get()->CreateGraphicsPipelineState(&m_pipeline_desc, IID_PPV_ARGS(&m_model_param->PipeLineState));

		PrimitiveBufferSet<PrimitiveData::CubeMesh,ID3D12Device,Model3DVertex>(DX12::Device::Get());
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
		ResourceUpdate();
	}
	void CubeMesh::Render()
	{
		Draw(DX12::CommandList::GetCmd());
	}

	SphereMesh::SphereMesh()
		:Model3D()
	{
	}
	SphereMesh::~SphereMesh()
	{
	}
	bool SphereMesh::Initialize(com_ptr<ID3DBlob>& vs_blob, com_ptr<ID3DBlob>& ps_blob, D3D12_RASTERIZER_DESC& r_desc, D3D12_BLEND_DESC& b_desc, com_ptr<ID3D12RootSignature>& root_sig, unsigned int cb_index)
	{
		m_model_param->ObjCBIndex = cb_index;
		m_shader_reflection = std::make_unique<DX12::ShaderReflection>();
		m_shader_reflection->ReflectionInputLayout(vs_blob);

		m_pipeline_desc = {};
		m_pipeline_desc.VS = { vs_blob->GetBufferPointer(), vs_blob->GetBufferSize() };
		m_pipeline_desc.PS = { ps_blob->GetBufferPointer(), ps_blob->GetBufferSize() };

		m_pipeline_desc.SampleMask = D3D12_DEFAULT_SAMPLE_MASK;

		m_pipeline_desc.BlendState = b_desc;
		m_pipeline_desc.RasterizerState = r_desc;

		m_pipeline_desc.DSVFormat = DXGI_FORMAT_D32_FLOAT;

		m_pipeline_desc.DepthStencilState.DepthEnable = TRUE;
		m_pipeline_desc.DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
		m_pipeline_desc.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_LESS;
		m_pipeline_desc.DepthStencilState.StencilEnable = FALSE;
		m_pipeline_desc.DepthStencilState.StencilReadMask = D3D12_DEFAULT_STENCIL_READ_MASK;
		m_pipeline_desc.DepthStencilState.StencilWriteMask = D3D12_DEFAULT_STENCIL_WRITE_MASK;
		const D3D12_DEPTH_STENCILOP_DESC defaultStencilOp = { D3D12_STENCIL_OP_KEEP, D3D12_STENCIL_OP_KEEP, D3D12_STENCIL_OP_KEEP, D3D12_COMPARISON_FUNC_ALWAYS };
		m_pipeline_desc.DepthStencilState.FrontFace = defaultStencilOp;
		m_pipeline_desc.DepthStencilState.BackFace = defaultStencilOp;

		m_pipeline_desc.InputLayout = { m_shader_reflection->GetInputLayout().data(), static_cast<UINT>(m_shader_reflection->GetInputLayout().size()) };

		//m_pipeline_desc.IBStripCutValue = D3D12_INDEX_BUFFER_STRIP_CUT_VALUE_DISABLED;
		m_pipeline_desc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;

		m_pipeline_desc.NumRenderTargets = 1;
		m_pipeline_desc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
		m_pipeline_desc.SampleDesc = { 1,0 };
		m_pipeline_desc.SampleMask = UINT_MAX;
		m_pipeline_desc.pRootSignature = root_sig.Get();
		DX12::Device::Get()->CreateGraphicsPipelineState(&m_pipeline_desc, IID_PPV_ARGS(&m_model_param->PipeLineState));

		PrimitiveData::Sphere sphere;
		sphere.CreateSphere(0.5f, 4, 4);
		m_vertex_resource = std::make_unique<DX12::ResourceBuffer<Model3DVertex>>();
		m_vertex_resource->Initialize(DX12::Device::Get(), sizeof(Model3DVertex), false);
		m_vertex_resource->CopyResource(sphere.mesh.Vertices);
		m_model_param->VertexBufferView = { m_vertex_resource->GetGPUVirtualAddress() ,sizeof(Model3DVertex) * static_cast<UINT>(sphere.mesh.Vertices.size()),sizeof(Model3DVertex) };

		m_index_resource = std::make_unique<DX12::ResourceBuffer<unsigned short>>();
		m_index_resource->Initialize(DX12::Device::Get(), sphere.mesh.Indices.size(), false);
		m_index_resource->CopyResource(sphere.mesh.Indices);
		m_model_param->IndexBufferView = { m_index_resource->GetGPUVirtualAddress(),static_cast<UINT>(sphere.mesh.Indices.size()) * sizeof(unsigned short),DXGI_FORMAT::DXGI_FORMAT_R16_UINT };
		m_model_param->IndexCount = m_index_resource->GetCount();

		return true;
	}
	bool SphereMesh::Finalize()
	{
		m_vertex_resource->Finalize();
		m_index_resource->Finalize();
		return true;
	}
	void SphereMesh::Update()
	{
		ResourceUpdate();
	}
	void SphereMesh::Render()
	{
		Draw(DX12::CommandList::GetCmd());
	}

}