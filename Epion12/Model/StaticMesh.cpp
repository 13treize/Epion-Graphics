#include "../Epion12.h"
#include "StaticMesh.h"

#include "../DX12/ViewPort.h"
#include "../DX12/Device.h"
#include "../DX12/CommandList.h"
#include "../DX12/ConstantBufferManager.h"
#include "PrimitiveModelData.h"
namespace epion::Model
{

	StaticMesh::StaticMesh()
		:Model()
	{
	}
	StaticMesh::~StaticMesh()
	{
	}

	bool StaticMesh::Initialize(com_ptr<ID3DBlob>& vs_blob, com_ptr<ID3DBlob>& ps_blob, D3D12_RASTERIZER_DESC& r_desc, com_ptr<ID3D12RootSignature>& root_sig)
	{

		return true;
	}

	bool StaticMesh::Finalize()
	{
		return false;
	}
	void StaticMesh::CBufferUpdate()
	{

	}
	void StaticMesh::Update()
	{
	}
	void StaticMesh::Render()
	{
		DX12::CommandList::GetPtr()->SetPipelineState(m_pipeline_state.Get());
		DX12::CommandList::GetPtr()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY::D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		DX12::CommandList::GetPtr()->IASetVertexBuffers(0, 1, &m_vertex->GetView());
		DX12::CommandList::GetPtr()->IASetIndexBuffer(&m_index->GetView());
		DX12::CommandList::GetPtr()->DrawIndexedInstanced(36, 1, 0, 0, 0);
	}



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
		m_pipeline_desc.pRootSignature = nullptr;
		m_pipeline_desc.VS.pShaderBytecode = vs_blob->GetBufferPointer();
		m_pipeline_desc.VS.BytecodeLength = vs_blob->GetBufferSize();
		m_pipeline_desc.PS.pShaderBytecode = ps_blob->GetBufferPointer();
		m_pipeline_desc.PS.BytecodeLength = ps_blob->GetBufferSize();

		m_pipeline_desc.SampleMask = D3D12_DEFAULT_SAMPLE_MASK;

		m_pipeline_desc.BlendState = b_desc;
		m_pipeline_desc.RasterizerState = r_desc;

		m_pipeline_desc.DepthStencilState.DepthEnable = false;
		m_pipeline_desc.DepthStencilState.StencilEnable = false;

		m_pipeline_desc.InputLayout.pInputElementDescs = m_shader_reflection->GetInputLayout().data();
		m_pipeline_desc.InputLayout.NumElements = m_shader_reflection->GetInputLayout().size();

		m_pipeline_desc.IBStripCutValue = D3D12_INDEX_BUFFER_STRIP_CUT_VALUE_DISABLED;
		m_pipeline_desc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;

		m_pipeline_desc.NumRenderTargets = 1;//今は１つのみ
		m_pipeline_desc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;//0～1に正規化されたRGBA

		m_pipeline_desc.SampleDesc.Count = 1;//サンプリングは1ピクセルにつき１
		m_pipeline_desc.SampleDesc.Quality = 0;//クオリティは最低

		m_pipeline_desc.pRootSignature = root_sig.Get();
		DX12::Device::Get()->CreateGraphicsPipelineState(&m_pipeline_desc, IID_PPV_ARGS(&m_pipeline_state));

		std::array <PolygonVertex, 4> vertices;
		vertices[0] = { {	-1.0f,	-1.0f, 0.0f },	{ 0.0f, 0.0f, -1.0f }, { 0.0f, 1.0f }, { 1.0f, 0.0f, 0.0f, 1.0f } };
		vertices[1] = { {	-1.0f,	1.0f, 0.0f },	{ 0.0f, 0.0f, -1.0f }, { 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f, 1.0f } };
		vertices[2] = { {	1.0f,	-1.0f, 0.0f },	{ 0.0f, 0.0f, -1.0f }, { 1.0f, 1.0f }, { 0.0f, 0.0f, 1.0f, 1.0f } };
		vertices[3] = { {	1.0f,	1.0f, 0.0f },	{ 0.0f, 0.0f, -1.0f }, { 1.0f, 0.0f }, { 1.0f, 0.0f, 1.0f, 1.0f } };


		m_vertex = std::make_unique<DX12::VertexBuffer>();
		m_vertex->Initialize(sizeof(PolygonVertex), sizeof(PolygonVertex) * 4);

		m_index = std::make_unique<DX12::IndexBuffer>();
		m_index->Initialize(PrimitiveData::Polygon::indices.size());

		PolygonVertex* vertex_data = nullptr;
		m_vertex->GetBuffer()->Map(0, nullptr, reinterpret_cast<void**>(&vertex_data));
		memcpy(vertex_data, vertices.data(), sizeof(vertices));

		unsigned short* index_data = nullptr;
		m_index->GetBuffer()->Map(0, nullptr, reinterpret_cast<void**>(&index_data));
		memcpy(index_data, PrimitiveData::Polygon::indices.data(), sizeof(PrimitiveData::Polygon::indices));
		m_index->GetBuffer()->Unmap(0, nullptr);
		return true;
	}
	bool Polygon::Finalize()
	{
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
		DX12::CommandList::GetPtr()->SetPipelineState(m_pipeline_state.Get());
		DX12::CommandList::GetPtr()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		DX12::CommandList::GetPtr()->IASetVertexBuffers(0, 1, &m_vertex->GetView());
		DX12::CommandList::GetPtr()->IASetIndexBuffer(&m_index->GetView());
		DX12::CommandList::GetPtr()->DrawIndexedInstanced(m_index->GetBufferCount(), 1, 0, 0, 0);
	}
}