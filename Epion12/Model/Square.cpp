#include "../Epion12.h"
#include "PrimitiveModelData.h"
#include "Square.h"
#include "../DX12/ViewPort.h"
#include "../DX12/Device.h"
#include "../DX12/CommandList.h"

namespace
{
}

namespace epion::Model
{
	Square::Square()
		:Model()
	{
		m_pipeline_state = nullptr;
	}

	Square::~Square()
	{
	}

	bool Square::Initialize(com_ptr<ID3DBlob>& vs_blob, com_ptr<ID3DBlob>& ps_blob, D3D12_RASTERIZER_DESC& r_desc, D3D12_BLEND_DESC& b_desc, com_ptr<ID3D12RootSignature>& root_sig)
	{
		HRESULT hr = S_OK;

		m_is_update = true;

		m_vertex->Initialize(sizeof(Model2DVertex), sizeof(Model2DVertex) * 4);

		m_index_resource = std::make_unique<DX12::ResourceBuffer<unsigned short>>();
		m_index_resource->Initialize(DX12::Device::Get(), PrimitiveData::Polygon::SIZE, false);
		m_index_resource->CopyResource<PrimitiveData::Polygon::SIZE>(PrimitiveData::Polygon::indices);
		m_index_buffer_view = { m_index_resource->GetGPUVirtualAddress(), PrimitiveData::Polygon::SIZE * sizeof(unsigned short),DXGI_FORMAT::DXGI_FORMAT_R16_UINT };

		m_shader_reflection = std::make_unique<DX12::ShaderReflection>();
		m_shader_reflection->ReflectionInputLayout(vs_blob);

		DefaultSetPipeLine(vs_blob, ps_blob, r_desc, root_sig);
		DX12::Device::Get()->CreateGraphicsPipelineState(&m_pipeline_desc, IID_PPV_ARGS(&m_pipeline_state));

		return true;
	}
	bool Square::Initialize(com_ptr<ID3DBlob>& vs_blob, com_ptr<ID3DBlob>& ps_blob, com_ptr<ID3DBlob>& gs_blob, D3D12_RASTERIZER_DESC& r_desc, D3D12_BLEND_DESC& b_desc, com_ptr<ID3D12RootSignature>& root_sig)
	{
		HRESULT hr = S_OK;

		m_is_update = true;

		m_vertex->Initialize(sizeof(Model2DVertex), sizeof(Model2DVertex) * 4);

		m_index_resource = std::make_unique<DX12::ResourceBuffer<unsigned short>>();
		m_index_resource->Initialize(DX12::Device::Get(), PrimitiveData::Polygon::SIZE, false);
		m_index_resource->CopyResource<PrimitiveData::Polygon::SIZE>(PrimitiveData::Polygon::indices);
		m_index_buffer_view = { m_index_resource->GetGPUVirtualAddress(), PrimitiveData::Polygon::SIZE * sizeof(unsigned short),DXGI_FORMAT::DXGI_FORMAT_R16_UINT };


		m_shader_reflection = std::make_unique<DX12::ShaderReflection>();
		m_shader_reflection->ReflectionInputLayout(vs_blob);


		m_pipeline_desc = {};
		m_pipeline_desc.pRootSignature = nullptr;
		m_pipeline_desc.VS.pShaderBytecode = vs_blob->GetBufferPointer();
		m_pipeline_desc.VS.BytecodeLength = vs_blob->GetBufferSize();
		m_pipeline_desc.PS.pShaderBytecode = ps_blob->GetBufferPointer();
		m_pipeline_desc.PS.BytecodeLength = ps_blob->GetBufferSize();
		m_pipeline_desc.GS.pShaderBytecode = gs_blob->GetBufferPointer();
		m_pipeline_desc.GS.BytecodeLength = gs_blob->GetBufferSize();

		m_pipeline_desc.SampleMask = D3D12_DEFAULT_SAMPLE_MASK;//中身は0xffffffff

		m_pipeline_desc.BlendState = b_desc;
		m_pipeline_desc.RasterizerState = r_desc;

		m_pipeline_desc.DepthStencilState.DepthEnable = false;
		m_pipeline_desc.DepthStencilState.StencilEnable = false;

		m_pipeline_desc.InputLayout.pInputElementDescs = m_shader_reflection->GetInputLayout().data();//レイアウト先頭アドレス
		m_pipeline_desc.InputLayout.NumElements = static_cast<UINT>(m_shader_reflection->GetInputLayout().size());

		m_pipeline_desc.IBStripCutValue = D3D12_INDEX_BUFFER_STRIP_CUT_VALUE_DISABLED;//ストリップ時のカットなし
		m_pipeline_desc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;//三角形で構成

		m_pipeline_desc.NumRenderTargets = 1;//今は１つのみ
		m_pipeline_desc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;//0～1に正規化されたRGBA

		m_pipeline_desc.SampleDesc.Count = 1;//サンプリングは1ピクセルにつき１
		m_pipeline_desc.SampleDesc.Quality = 0;//クオリティは最低
		m_pipeline_desc.pRootSignature = root_sig.Get();
		DX12::Device::Get()->CreateGraphicsPipelineState(&m_pipeline_desc, IID_PPV_ARGS(&m_pipeline_state));
		return true;

	}

	bool Square::Initialize(com_ptr<ID3DBlob>& vs_blob, com_ptr<ID3DBlob>& ps_blob, com_ptr<ID3DBlob>& hs_blob, com_ptr<ID3DBlob>& ds_blob,com_ptr<ID3DBlob>& gs_blob, D3D12_RASTERIZER_DESC& r_desc, D3D12_BLEND_DESC& b_desc, com_ptr<ID3D12RootSignature>& root_sig)
	{
		HRESULT hr = S_OK;

		m_is_update = true;

		m_vertex->Initialize(sizeof(Model2DVertex), sizeof(Model2DVertex) * 4);

		m_index_resource = std::make_unique<DX12::ResourceBuffer<unsigned short>>();
		m_index_resource->Initialize(DX12::Device::Get(), PrimitiveData::Polygon::SIZE, false);
		m_index_resource->CopyResource<PrimitiveData::Polygon::SIZE>(PrimitiveData::Polygon::indices);
		m_index_buffer_view = { m_index_resource->GetGPUVirtualAddress(), PrimitiveData::Polygon::SIZE * sizeof(unsigned short),DXGI_FORMAT::DXGI_FORMAT_R16_UINT };



		m_shader_reflection = std::make_unique<DX12::ShaderReflection>();
		m_shader_reflection->ReflectionInputLayout(vs_blob);

		m_pipeline_desc = {};
		m_pipeline_desc.VS.pShaderBytecode = vs_blob->GetBufferPointer();
		m_pipeline_desc.VS.BytecodeLength = vs_blob->GetBufferSize();
		m_pipeline_desc.PS.pShaderBytecode = ps_blob->GetBufferPointer();
		m_pipeline_desc.PS.BytecodeLength = ps_blob->GetBufferSize();
		m_pipeline_desc.HS.pShaderBytecode = hs_blob->GetBufferPointer();
		m_pipeline_desc.HS.BytecodeLength = hs_blob->GetBufferSize();
		m_pipeline_desc.DS.pShaderBytecode = ds_blob->GetBufferPointer();
		m_pipeline_desc.DS.BytecodeLength = ds_blob->GetBufferSize();
		m_pipeline_desc.GS.pShaderBytecode = gs_blob->GetBufferPointer();
		m_pipeline_desc.GS.BytecodeLength = gs_blob->GetBufferSize();

		m_pipeline_desc.SampleMask = D3D12_DEFAULT_SAMPLE_MASK;//中身は0xffffffff

		m_pipeline_desc.BlendState = b_desc;
		m_pipeline_desc.RasterizerState = r_desc;

		m_pipeline_desc.DepthStencilState.DepthEnable = false;
		m_pipeline_desc.DepthStencilState.StencilEnable = false;

		m_pipeline_desc.InputLayout.pInputElementDescs = m_shader_reflection->GetInputLayout().data();//レイアウト先頭アドレス
		m_pipeline_desc.InputLayout.NumElements = static_cast<UINT>(m_shader_reflection->GetInputLayout().size());

		m_pipeline_desc.IBStripCutValue = D3D12_INDEX_BUFFER_STRIP_CUT_VALUE_DISABLED;//ストリップ時のカットなし
		m_pipeline_desc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;//三角形で構成

		m_pipeline_desc.NumRenderTargets = 1;//今は１つのみ
		m_pipeline_desc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;//0～1に正規化されたRGBA

		m_pipeline_desc.SampleDesc.Count = 1;//サンプリングは1ピクセルにつき１
		m_pipeline_desc.SampleDesc.Quality = 0;//クオリティは最低

		m_pipeline_desc.pRootSignature = root_sig.Get();
		DX12::Device::Get()->CreateGraphicsPipelineState(&m_pipeline_desc, IID_PPV_ARGS(&m_pipeline_state));

		return true;
	}

	bool Square::Finalize()
	{
		return true;
	}
	void Square::Update(const Math::FVector2& d_xy, const Math::FVector2& d_wh)
	{
		if (m_is_update)
		{
			std::valarray<float>	arr_x =
			{
				d_xy.x,				//left-top
				d_xy.x + d_wh.x,	//right-top
				d_xy.x,				//left-bottom
				d_xy.x + d_wh.x,	//right-bottom
			};

			std::valarray<float>	arr_y =
			{
				d_xy.y,				//left-top
				d_xy.y,				//right-top
				d_xy.y + d_wh.y,	//left-bottom
				d_xy.y + d_wh.y,	//right-bottom
			};
			std::array<Model2DVertex, 4> vertices;

			arr_x = 2.0f * arr_x / static_cast<float>(DX12::ViewPort::GetScreenSize().x) - 1.0f;
			arr_y = 1.0f - 2.0f * arr_y / static_cast<float>(DX12::ViewPort::GetScreenSize().y);

			I_FOR(4)
			{
				vertices[i].pos.x = arr_x[i];
				vertices[i].pos.y = arr_y[i];
				vertices[i].pos.z = 0.0f;
				vertices[i].pos.w = 1.0f;
			}
			vertices[0].uv = { 0.0f,1.0f };
			vertices[1].uv = { 1.0f,1.0f };
			vertices[2].uv = { 0.0f,0.0f };
			vertices[3].uv = { 1.0f,0.0f };
			Model2DVertex* vertMap = nullptr;
			m_vertex->GetBuffer()->Map(0, nullptr, (void**)&vertMap);
			std::copy(vertices.begin(), vertices.end(), vertMap);
			m_vertex->GetBuffer()->Unmap(0, nullptr);
		}
		m_is_update = false;
	}



	void Square::Render()
	{
		DX12::CommandList::GetPtr()->SetPipelineState(m_pipeline_state.Get());
		DX12::CommandList::GetPtr()->IASetVertexBuffers(0, 1, &m_vertex->GetView());
		DX12::CommandList::GetPtr()->IASetIndexBuffer(&m_index_buffer_view);
		DX12::CommandList::GetPtr()->DrawIndexedInstanced(m_index_resource->GetCount(), 1, 0, 0, 0);
	}
}