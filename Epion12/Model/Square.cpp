#include "../Epion12.h"
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

	bool Square::Initialize(com_ptr<ID3DBlob>& vs_blob, com_ptr<ID3DBlob>& ps_blob, D3D12_RASTERIZER_DESC& r_desc, com_ptr<ID3D12RootSignature>& root_sig)
	{
		HRESULT hr = S_OK;

		m_is_update = true;

		m_vertex->Initialize(sizeof(SquareVertex), sizeof(SquareVertex) * 4);

		unsigned short indices[] = { 0,1,2, 2,1,3 };

		m_index->Initialize(sizeof(indices));

		unsigned short* mappedIdx = nullptr;
		m_index->GetBuffer()->Map(0, nullptr, (void**)&mappedIdx);
		std::copy(std::begin(indices), std::end(indices), mappedIdx);
		m_index->GetBuffer()->Unmap(0, nullptr);


		m_shader_reflection = std::make_unique<DX12::ShaderReflection>();
		m_shader_reflection->ReflectionInputLayout(vs_blob);

		DefaultSetPipeLine(vs_blob, ps_blob, r_desc, root_sig);
		DX12::Device::Get()->CreateGraphicsPipelineState(&m_pipeline_desc, IID_PPV_ARGS(&m_pipeline_state));

		return true;
	}
	bool Square::Initialize(com_ptr<ID3DBlob>& vs_blob, com_ptr<ID3DBlob>& ps_blob, com_ptr<ID3DBlob>& gs_blob, D3D12_RASTERIZER_DESC& r_desc, com_ptr<ID3D12RootSignature>& root_sig)
	{
		HRESULT hr = S_OK;

		m_is_update = true;

		m_vertex->Initialize(sizeof(SquareVertex), sizeof(SquareVertex) * 4);

		unsigned short indices[] = { 0,1,2, 2,1,3 };

		m_index->Initialize(sizeof(indices));

		unsigned short* mappedIdx = nullptr;
		m_index->GetBuffer()->Map(0, nullptr, (void**)&mappedIdx);
		std::copy(std::begin(indices), std::end(indices), mappedIdx);
		m_index->GetBuffer()->Unmap(0, nullptr);


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

		m_pipeline_desc.BlendState.AlphaToCoverageEnable = false;
		m_pipeline_desc.BlendState.IndependentBlendEnable = false;



		D3D12_RENDER_TARGET_BLEND_DESC renderTargetBlendDesc = {};

		//ひとまず加算や乗算やαブレンディングは使用しない
		renderTargetBlendDesc.BlendEnable = false;
		renderTargetBlendDesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;

		//ひとまず論理演算は使用しない
		renderTargetBlendDesc.LogicOpEnable = false;

		m_pipeline_desc.BlendState.RenderTarget[0] = renderTargetBlendDesc;

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

	bool Square::Initialize(com_ptr<ID3DBlob>& vs_blob, com_ptr<ID3DBlob>& ps_blob, com_ptr<ID3DBlob>& hs_blob, com_ptr<ID3DBlob>& ds_blob,com_ptr<ID3DBlob>& gs_blob, D3D12_RASTERIZER_DESC& r_desc, com_ptr<ID3D12RootSignature>& root_sig)
	{
		HRESULT hr = S_OK;

		m_is_update = true;

		m_vertex->Initialize(sizeof(SquareVertex), sizeof(SquareVertex) * 4);

		unsigned short indices[] = { 0,1,2, 2,1,3 };

		m_index->Initialize(sizeof(indices));

		unsigned short* mappedIdx = nullptr;
		m_index->GetBuffer()->Map(0, nullptr, (void**)&mappedIdx);
		std::copy(std::begin(indices), std::end(indices), mappedIdx);
		m_index->GetBuffer()->Unmap(0, nullptr);


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

		m_pipeline_desc.BlendState.AlphaToCoverageEnable = false;
		m_pipeline_desc.BlendState.IndependentBlendEnable = false;



		D3D12_RENDER_TARGET_BLEND_DESC renderTargetBlendDesc = {};

		//ひとまず加算や乗算やαブレンディングは使用しない
		renderTargetBlendDesc.BlendEnable = false;
		renderTargetBlendDesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;

		//ひとまず論理演算は使用しない
		renderTargetBlendDesc.LogicOpEnable = false;

		m_pipeline_desc.BlendState.RenderTarget[0] = renderTargetBlendDesc;

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
			std::array<SquareVertex, 4> vertices;

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
			SquareVertex* vertMap = nullptr;
			m_vertex->GetBuffer()->Map(0, nullptr, (void**)&vertMap);
			std::copy(vertices.begin(), vertices.end(), vertMap);
			m_vertex->GetBuffer()->Unmap(0, nullptr);
		}
		m_is_update = false;
	}



	void Square::Render()
	{
		DX12::CommandList::GetPtr()->SetPipelineState(m_pipeline_state.Get());
		DX12::CommandList::GetPtr()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY::D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		DX12::CommandList::GetPtr()->IASetVertexBuffers(0, 1, &m_vertex->GetView());
		DX12::CommandList::GetPtr()->IASetIndexBuffer(&m_index->GetView());
		DX12::CommandList::GetPtr()->DrawIndexedInstanced(6, 1, 0, 0, 0);
	}
}