#include "../Epion12.h"
#include "PrimitiveModelData.h"
#include "Square.h"
#include "../DX12/ViewPort.h"
#include "../DX12/Device.h"
#include "../DX12/CommandList.h"
#include "../DX12/DX12Wrapper.h"

namespace
{
}

namespace epion::Model
{
	Square::Square()
		:ModelCore()
	{
		m_pipeline_state = nullptr;
	}

	Square::~Square()
	{
	}

	bool Square::Initialize(com_ptr<ID3DBlob>& vs_blob, com_ptr<ID3DBlob>& ps_blob, com_ptr<ID3D12RootSignature>& root_sig)
	{
		HRESULT hr = S_OK;

		m_is_update = true;

		m_vertex_resource = std::make_unique<DX12::ResourceBuffer<Model2DVertex>>();
		m_vertex_resource->Initialize<ID3D12Device>(DX12::Device::Get(), sizeof(Model2DVertex), false);
		m_vertex_buffer_view = { m_vertex_resource->GetGPUVirtualAddress() ,sizeof(Model2DVertex) * PrimitiveData::Polygon::VERTEX_SIZE,sizeof(Model2DVertex) };

		m_index_resource = std::make_unique<DX12::ResourceBuffer<unsigned short>>();
		m_index_resource->Initialize<ID3D12Device>(DX12::Device::Get(), PrimitiveData::Polygon::INDEX_SIZE, false);
		m_index_resource->CopyResource<PrimitiveData::Polygon::INDEX_SIZE>(PrimitiveData::Polygon::indices);
		m_index_buffer_view = { m_index_resource->GetGPUVirtualAddress(), PrimitiveData::Polygon::INDEX_SIZE * sizeof(unsigned short),DXGI_FORMAT::DXGI_FORMAT_R16_UINT };

		m_shader_reflection = std::make_unique<DX12::ShaderReflection>();
		m_shader_reflection->ReflectionInputLayout(vs_blob);

		DefaultSetPipeLine(vs_blob, ps_blob, root_sig);
		DX12::Device::Get()->CreateGraphicsPipelineState(&m_pipeline_desc, IID_PPV_ARGS(&m_pipeline_state));

		return true;
	}
	bool Square::Initialize(com_ptr<ID3DBlob>& vs_blob, com_ptr<ID3DBlob>& ps_blob, com_ptr<ID3DBlob>& gs_blob, com_ptr<ID3D12RootSignature>& root_sig)
	{
		HRESULT hr = S_OK;

		m_is_update = true;

		m_vertex_resource = std::make_unique<DX12::ResourceBuffer<Model2DVertex>>();
		m_vertex_resource->Initialize<ID3D12Device>(DX12::Device::Get(), sizeof(Model2DVertex), false);
		m_vertex_buffer_view = { m_vertex_resource->GetGPUVirtualAddress() ,sizeof(Model2DVertex) * PrimitiveData::Polygon::VERTEX_SIZE,sizeof(Model2DVertex) };

		m_index_resource = std::make_unique<DX12::ResourceBuffer<unsigned short>>();
		m_index_resource->Initialize<ID3D12Device>(DX12::Device::Get(), PrimitiveData::Polygon::INDEX_SIZE, false);
		m_index_resource->CopyResource<PrimitiveData::Polygon::INDEX_SIZE>(PrimitiveData::Polygon::indices);
		m_index_buffer_view = { m_index_resource->GetGPUVirtualAddress(), PrimitiveData::Polygon::INDEX_SIZE * sizeof(unsigned short),DXGI_FORMAT::DXGI_FORMAT_R16_UINT };


		m_shader_reflection = std::make_unique<DX12::ShaderReflection>();
		m_shader_reflection->ReflectionInputLayout(vs_blob);


		m_pipeline_desc = {};
		m_pipeline_desc.VS = { vs_blob->GetBufferPointer(), vs_blob->GetBufferSize() };
		m_pipeline_desc.PS = { ps_blob->GetBufferPointer(), ps_blob->GetBufferSize() };
		m_pipeline_desc.GS = { gs_blob->GetBufferPointer(), gs_blob->GetBufferSize() };
		m_pipeline_desc.BlendState = DX12::DX12Wrapper::BLEND_DESC;
		m_pipeline_desc.RasterizerState = DX12::DX12Wrapper::RASTERIZER_SOLID_DESC;
		m_pipeline_desc.DepthStencilState = DX12::DX12Wrapper::DEPTH_STENCIL_DEFAULT_DESC;
		m_pipeline_desc.SampleMask = D3D12_DEFAULT_SAMPLE_MASK;
		m_pipeline_desc.InputLayout = { m_shader_reflection->GetInputLayout().data(), static_cast<UINT>(m_shader_reflection->GetInputLayout().size()) };
		m_pipeline_desc.IBStripCutValue = D3D12_INDEX_BUFFER_STRIP_CUT_VALUE_DISABLED;
		m_pipeline_desc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
		m_pipeline_desc.NumRenderTargets = 1;
		m_pipeline_desc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
		m_pipeline_desc.SampleDesc.Count = 1;
		m_pipeline_desc.SampleDesc.Quality = 0;
		m_pipeline_desc.pRootSignature = root_sig.Get();
		DX12::Device::Get()->CreateGraphicsPipelineState(&m_pipeline_desc, IID_PPV_ARGS(&m_pipeline_state));
		return true;

	}

	bool Square::Initialize(com_ptr<ID3DBlob>& vs_blob, com_ptr<ID3DBlob>& ps_blob, com_ptr<ID3DBlob>& hs_blob, com_ptr<ID3DBlob>& ds_blob, com_ptr<ID3DBlob>& gs_blob, com_ptr<ID3D12RootSignature>& root_sig)
	{
		HRESULT hr = S_OK;

		m_is_update = false;

		m_vertex_resource = std::make_unique<DX12::ResourceBuffer<Model2DVertex>>();
		m_vertex_resource->Initialize<ID3D12Device>(DX12::Device::Get(), sizeof(Model2DVertex), false);
		m_vertex_buffer_view = { m_vertex_resource->GetGPUVirtualAddress() ,sizeof(Model2DVertex) * PrimitiveData::Polygon::VERTEX_SIZE,sizeof(Model2DVertex) };

		m_index_resource = std::make_unique<DX12::ResourceBuffer<unsigned short>>();
		m_index_resource->Initialize<ID3D12Device>(DX12::Device::Get(), PrimitiveData::Polygon::INDEX_SIZE, false);
		m_index_resource->CopyResource<PrimitiveData::Polygon::INDEX_SIZE>(PrimitiveData::Polygon::indices);
		m_index_buffer_view = { m_index_resource->GetGPUVirtualAddress(), PrimitiveData::Polygon::INDEX_SIZE * sizeof(unsigned short),DXGI_FORMAT::DXGI_FORMAT_R16_UINT };

		m_shader_reflection = std::make_unique<DX12::ShaderReflection>();
		m_shader_reflection->ReflectionInputLayout(vs_blob);

		m_pipeline_desc = {};
		m_pipeline_desc.VS = { vs_blob->GetBufferPointer(), vs_blob->GetBufferSize() };
		m_pipeline_desc.PS = { ps_blob->GetBufferPointer(), ps_blob->GetBufferSize() };
		m_pipeline_desc.HS = { hs_blob->GetBufferPointer(), hs_blob->GetBufferSize() };
		m_pipeline_desc.DS = { ds_blob->GetBufferPointer(), ds_blob->GetBufferSize() };
		m_pipeline_desc.GS = { gs_blob->GetBufferPointer(), gs_blob->GetBufferSize() };
		m_pipeline_desc.BlendState = DX12::DX12Wrapper::BLEND_DESC;
		m_pipeline_desc.RasterizerState = DX12::DX12Wrapper::RASTERIZER_SOLID_DESC;
		m_pipeline_desc.SampleMask = D3D12_DEFAULT_SAMPLE_MASK;
		m_pipeline_desc.DepthStencilState = DX12::DX12Wrapper::DEPTH_STENCIL_DEFAULT_DESC;
		m_pipeline_desc.InputLayout = { m_shader_reflection->GetInputLayout().data(), static_cast<UINT>(m_shader_reflection->GetInputLayout().size()) };
		m_pipeline_desc.IBStripCutValue = D3D12_INDEX_BUFFER_STRIP_CUT_VALUE_DISABLED;
		m_pipeline_desc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
		m_pipeline_desc.NumRenderTargets = 1;
		m_pipeline_desc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
		m_pipeline_desc.SampleDesc.Count = 1;
		m_pipeline_desc.SampleDesc.Quality = 0;
		m_pipeline_desc.pRootSignature = root_sig.Get();
		DX12::Device::Get()->CreateGraphicsPipelineState(&m_pipeline_desc, IID_PPV_ARGS(&m_pipeline_state));

		return true;
	}

	bool Square::Finalize()
	{
		m_vertex_resource->Finalize();
		m_index_resource->Finalize();
		return true;
	}
	void Square::Update(const Math::FVector2& d_xy, const Math::FVector2& d_wh, const Math::FVector2& sc_size)
	{
		if (m_is_update)
		{
			//left-top,right-top,left-bottom,right-bottom
			std::valarray<float> arr_x = { d_xy.x,	d_xy.x + d_wh.x,	d_xy.x,	d_xy.x + d_wh.x, };
			std::valarray<float> arr_y = { d_xy.y,	d_xy.y,	d_xy.y + d_wh.y,	d_xy.y + d_wh.y, };
			std::array<Model2DVertex, 4> vertices;

			arr_x = 2.0f * arr_x / sc_size.x - 1.0f;
			arr_y = 1.0f - 2.0f * arr_y / sc_size.y;

			I_FOR(4)
			{
				vertices[i].pos = { arr_x[i], arr_y[i], 0.0f, 1.0f };
			}
			vertices[0].uv = { 0.0f,1.0f };
			vertices[1].uv = { 1.0f,1.0f };
			vertices[2].uv = { 0.0f,0.0f };
			vertices[3].uv = { 1.0f,0.0f };
			m_vertex_resource->CopyResource<PrimitiveData::Polygon::VERTEX_SIZE>(vertices);
		}
		m_is_update = false;
	}

	void Square::Render()
	{
		DX12::CommandList::GetCmd()->SetPipelineState(m_pipeline_state.Get());
		DX12::CommandList::GetCmd()->IASetVertexBuffers(0, 1, &m_vertex_buffer_view);
		DX12::CommandList::GetCmd()->IASetIndexBuffer(&m_index_buffer_view);
		DX12::CommandList::GetCmd()->DrawIndexedInstanced(m_index_resource->GetCount(), 1, 0, 0, 0);
	}
}